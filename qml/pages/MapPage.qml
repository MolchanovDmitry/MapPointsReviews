// SPDX-FileCopyrightText: 2021-2023 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause
import QtQuick 2.6
import QtSensors 5.2
import QtLocation 5.0
import QtPositioning 5.3
import Sailfish.Silica 1.0
import ru.auroraos.PointsMapReviews 1.0
import "../assets"

Page {
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
                    "labelText": qsTr("Satellite map"),
                    "destinationPage": "SatelliteInfoPage",
                    "destinationProperties": {
                        "compass": compass,
                        "gpsInfoProvider": gpsInfoProvider
                    }
                }, {
                    "labelText": qsTr("Location information"),
                    "destinationPage": "LocationInfoPage",
                    "destinationProperties": {
                        "gpsInfoProvider": gpsInfoProvider
                    }
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
                    pageStack.push(Qt.resolvedUrl(
                                       "%1.qml".arg(
                                           modelData.destinationPage)),
                                   modelData.destinationProperties)
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
                minimumZoomLevel: 2.5
                maximumZoomLevel: 19.0
                zoomLevel: zoomSlider.value
                center: gpsInfoProvider.coordinate

                MapItemView {
                    model: markermodel
                    delegate: MapQuickItem {
                        coordinate: model.position
                        sourceItem: Image {
                            width: 50
                            height: 50
                            source: "../graphics/footprints.svg"
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

                    }

                    onPressAndHold: {
                        console.log("mouse.x" + mouse.x)

                        var coord = map.toCoordinate(Qt.point(mouse.x, mouse.y))
                        markermodel.append({
                                               "position": coord
                                           })
                    }
                }

                Component.onCompleted: {
                    center = QtPositioning.coordinate(56.85836, 35.90057)
                }
            }

            Button {
                objectName: "menuButton"
                anchors {
                    left: parent.left
                    bottom: parent.bottom
                    margins: Theme.paddingLarge
                }
                width: height
                color: Theme.highlightDimmerColor
                border {
                    color: Theme.rgba(color, Theme.opacityFaint)
                    highlightColor: Theme.rgba(highlightBackgroundColor,
                                               Theme.highlightBackgroundOpacity)
                }
                icon.source: "image://theme/icon-m-menu?%1".arg(
                                 Theme.highlightDimmerColor)

                onClicked: {
                    if (drawer.opened) {
                        drawer.hide()
                    } else {
                        drawer.show()
                    }
                }
            }

            Button {
                objectName: "centerButton"
                anchors {
                    right: parent.right
                    bottom: parent.bottom
                    margins: Theme.paddingLarge
                }
                width: height
                color: Theme.highlightDimmerColor
                border {
                    color: Theme.rgba(color, Theme.opacityFaint)
                    highlightColor: Theme.rgba(highlightBackgroundColor,
                                               Theme.highlightBackgroundOpacity)
                }
                icon.source: "image://theme/icon-m-whereami?%1".arg(
                                 Theme.highlightDimmerColor)

                onClicked: {
                    //map.zoomLevel = map.maximumZoomLevel
                    map.center.latitude = 0
                    map.center.longitude = 0
                    map.center = positionCircle.center
                }
            }
        }

        Component.onCompleted: {

        }

        Slider {
            id: zoomSlider
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
                bottomMargin: Theme.paddingLarge
            }
            color: "red"
            highlightColor: "red"
            minimumValue: map.minimumZoomLevel
            maximumValue: map.maximumZoomLevel
            value: 11
        }
    }
}
