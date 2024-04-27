// SPDX-FileCopyrightText: 2021-2023 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause
import QtQuick 2.6
import QtSensors 5.2
import QtLocation 5.0
import QtQuick.Layouts 1.0
import QtPositioning 5.3
import Sailfish.Silica 1.0
import ru.auroraos.PointsMapReviews 1.0
import "../assets"

Page {
    property int markerSize: 75

    objectName: "mapPage"

    Compass {
        id: compass

        objectName: "compass"
        active: true
    }

    GpsInfoProvider {
        id: gpsInfoProvider

        objectName: "gpsInfoProvider"
        active: true
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
            model: [{
                    "labelText": qsTr("Добавить точку"),
                    "destinationPage": "AddMapPointPage"
                }]
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
                    var dialog = pageStack.push(
                                Qt.resolvedUrl("%1.qml".arg(
                                                   modelData.destinationPage)))
                    dialog.onAccepted.connect(function () {
                        console.log(dialog.imageUrls + " " + dialog.title + " "
                                    + dialog.description)
                    })
                }

                Label {
                    objectName: "drawerItemLabel"
                    anchors.centerIn: parent
                    text: modelData.labelText
                }
            }
        }

        Rectangle {
            objectName: "mapRectangle"
            anchors.fill: parent

            Plugin {
                id: mapPlugin

                objectName: "mapPlugin"
                name: "webtiles"
                allowExperimental: false

                PluginParameter {
                    objectName: "schemeParameter"
                    name: "webtiles.scheme"
                    value: "https"
                }

                PluginParameter {
                    objectName: "hostParameter"
                    name: "webtiles.host"
                    value: "tile.openstreetmap.org"
                }

                PluginParameter {
                    objectName: "pathParameter"
                    name: "webtiles.path"
                    value: "/${z}/${x}/${y}.png"
                }
            }

            ListModel {
                id: markermodel
                dynamicRoles: true
            }

            Map {

                id: map
                objectName: "map"
                anchors.fill: parent
                plugin: mapPlugin
                minimumZoomLevel: 5
                maximumZoomLevel: 17
                zoomLevel: 13
                center: gpsInfoProvider.coordinate

                MapItemView {

                    model: mapPointsUiModel
                    delegate: MapQuickItem {
                        coordinate: QtPositioning.coordinate(latitude,
                                                             longitude)
                        sourceItem: Image {
                            width: markerSize
                            height: markerSize
                            source: "../graphics/marker.svg"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                console.log("MapQuickItem clicked")
                                // Дополнительная обработка для нажатия на MapQuickItem
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

                        var coord = map.toCoordinate(
                                    Qt.point(mouse.x - markerSize / 2,
                                             mouse.y - markerSize / 2))
                        markermodel.append({
                                               "position": coord
                                           })
                    }
                }

                Component.onCompleted: {
                    center = QtPositioning.coordinate(56.85836, 35.90057)

                    console.log("*********************** Connections ********************")
                    markermodel.clear() // Очищаем текущие элементы
                    var mapPoints = mapPointsUiModel
                    console.log("mapPoints = " + mapPoints)
                    //                    for (var i = 0; i < mapPoints.count; i++) {
                    //                        var point = mapPoints[i]
                    //                        console.log("point = " + point)
                    //                        //markermodel.append(point) // Добавляем новую точку
                    //                        //                        var coord = map.toCoordinate(point.latitude,
                    //                        //                                                     point.longitude)
                    //                        //                        markermodel.append({
                    //                        //                                               "position": coord
                    //                        //                                           })
                    //                    }
                }
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
                    //map.zoomLevel = map.maximumZoomLevel
                    map.center.latitude = gpsInfoProvider.coordinate.latitude
                    map.center.longitude = gpsInfoProvider.coordinate.longitude
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

    PullDownMenu {
        MenuItem {
            text: qsTr("Add_note")
            onClicked: {
                console.log("kokoke")
            }
        }
    }
}
