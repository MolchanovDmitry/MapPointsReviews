// SPDX-FileCopyrightText: 2021-2023 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause
import QtQuick 2.6
import QtSensors 5.2
import QtLocation 5.0
import QtQuick.Layouts 1.0
import QtPositioning 5.3
import Sailfish.Silica 1.0
import "../assets"

Page {
    property int markerSize: 75

    objectName: "mapPage"

    property real latitude: positionSource.position.coordinate.latitude
    property real longitude: positionSource.position.coordinate.longitude

    // Для позиционирования либо использовать nmea,
    // либо задать координаты через "Инструменты -> AuroraOs -> Управление эмуляцией -> Местоположение"
    PositionSource {
        id: positionSource
        onPositionChanged: {
            console.log("Position change latitude = " + latitude + " longitude = " + longitude)
        }

        //active: true
        //nmeaSource: "../../nmea/path.nmea"
    }

    ListModel {
        id: drawerModel
    }

    Drawer {
        id: drawer

        dock: Dock.Bottom

        objectName: "drawer"
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        open: false
        backgroundSize: backgroundView.contentHeight
        background: SilicaListView {
            id: backgroundView

            objectName: "backgroundView"
            anchors.fill: parent
            model: drawerModel
            delegate: BackgroundItem {
                id: drawerMenuItem
                objectName: "drawerMenuItem_%1".arg(index)
                anchors {
                    left: parent.left
                    right: parent.right
                }
                height: contentHeight
                contentHeight: Theme.itemSizeMedium

                onClicked: {
                    drawer.hide()
                    pageStack.push(Qt.resolvedUrl("%1.qml".arg(model.page)),
                                   model.properties)
                }

                Label {
                    objectName: "drawerItemLabel"
                    anchors.centerIn: parent
                    text: model.label
                }
            }
        }

        Map {
            id: map
            anchors.fill: parent
            gesture.enabled: true
            objectName: "map"
            minimumZoomLevel: 2
            maximumZoomLevel: 17
            zoomLevel: 13

            plugin: Plugin {
                id: mapPlugin
                objectName: "mapPlugin"
                name: "webtiles"
                allowExperimental: false

                PluginParameter {
                    name: "webtiles.scheme"
                    value: "https"
                }
                PluginParameter {
                    name: "webtiles.host"
                    value: "tile.openstreetmap.org"
                }
                PluginParameter {
                    name: "webtiles.path"
                    value: "/${z}/${x}/${y}.png"
                }
            }

            MapItemView {
                model: mapPointsUiModel
                delegate: MapQuickItem {
                    coordinate: QtPositioning.coordinate(latitude, longitude)
                    sourceItem: Image {
                        width: markerSize
                        height: markerSize
                        source: isConfirmed ? "../graphics/marker.svg" : "../graphics/marker_unconfirmed.svg"
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            console.log("Нажали на точку с параметрами id:" + id
                                        + " title:" + title + " isConfirmed:"
                                        + isConfirmed + " images:" + imageUrls)
                            pageStack.push(Qt.resolvedUrl("MapPointPage.qml"), {
                                               "pageTitle": title,
                                               "description": description,
                                               "imageUrls": imageUrls,
                                               "mapPointId": id
                                           })
                        }
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                preventStealing: false
                onClicked: {
                    if (drawer.opened) {
                        drawer.hide()
                    }
                }

                onPressAndHold: {
                    console.log("mouse.x" + mouse.x)

                    var coord = map.toCoordinate(Qt.point(
                                                     mouse.x - markerSize / 2,
                                                     mouse.y - markerSize / 2))

                    drawerModel.clear()
                    drawerModel.append([{
                                            "label": qsTr("Добавить точку"),
                                            "page": "AddMapPointPage",
                                            "properties": {
                                                "latitude": coord.latitude,
                                                "longitude": coord.longitude
                                            }
                                        }])
                    if (drawer.opened) {
                        drawer.hide()
                    }
                    drawer.show()
                }
            }

            Component.onCompleted: {
                console.log("112233 latitude = " + latitude + " longitude = " + longitude)
                //center = QtPositioning.coordinate(latitude, longitude)
                center = QtPositioning.coordinate(56.85836, 35.90057)
            }
        }

        ColumnLayout {
            anchors {
                right: parent.right
                verticalCenter: parent.verticalCenter
                margins: Theme.paddingLarge
            }
            spacing: Theme.paddingMedium

            MapButton {
                objectName: "plusButton"
                sourceIcon: "image://theme/icon-l-add?%1"
                onClicked: {
                    map.zoomLevel = map.zoomLevel + 1
                }
            }

            MapButton {
                objectName: "minusButton"
                sourceIcon: "image://theme/icon-l-remove?%1"
                onClicked: {
                    map.zoomLevel = map.zoomLevel - 1
                }
            }
        }

        ColumnLayout {
            anchors {
                right: parent.right
                bottom: parent.bottom
                margins: Theme.paddingLarge
            }
            spacing: Theme.paddingMedium

            MapButton {
                objectName: "centerButton"
                sourceIcon: "image://theme/icon-l-whereami?%1"
                onClicked: {
                    console.log("112233 latitude = " + latitude + " longitude = " + longitude)
                    map.center = QtPositioning.coordinate(latitude, longitude)
                    //map.center = gpsInfoProvider.coordinate.center
                }
            }

            MapButton {
                objectName: "menuButton"
                sourceIcon: "image://theme/icon-l-menu?%1"
                onClicked: {
                    if (drawer.opened) {
                        drawer.hide()
                    } else {
                        drawer.show()
                    }
                }
            }
        }
    }

    //    PullDownMenu {
    //        MenuItem {
    //            text: qsTr("Add_note")
    //            onClicked: {
    //                console.log("kokoke")
    //            }
    //        }
    //    }
}
