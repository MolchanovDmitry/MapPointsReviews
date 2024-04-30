import QtQuick 2.6
import Sailfish.Silica 1.0
import QtPositioning 5.3
import "../assets"


/*
    Экран проверки показетелей позиционирования.
*/
Page {

    PositionSource {
        id: positionSource
        updateInterval: 1000
        active: true
    }
    Flickable {
        anchors.fill: parent
        contentHeight: displayColumn.height
        anchors.topMargin: Theme.paddingLarge * 2

        Column {
            id: displayColumn
            width: parent.width

            ValueDisplay {
                label: qsTr("Timestamp")
                value: positionSource.position.timestamp
                valid: positionSource.position.coordinate.isValid
                width: parent.width
            }
            ValueDisplay {
                label: qsTr("Coordinate")
                value: positionSource.position.coordinate
                valid: positionSource.position.coordinate.isValid
                width: parent.width
            }
            ValueDisplay {
                label: qsTr("Latitude")
                value: positionSource.position.coordinate.latitude.toFixed(6)
                valid: positionSource.position.latitudeValid
                width: parent.width
            }
            ValueDisplay {
                label: qsTr("Longitude")
                value: positionSource.position.coordinate.longitude.toFixed(6)
                valid: positionSource.position.longitudeValid
                width: parent.width
            }
            ValueDisplay {
                label: qsTr("Altitude")
                value: positionSource.position.coordinate.altitude.toFixed(6)
                valid: positionSource.position.altitudeValid
                width: parent.width
            }
            ValueDisplay {
                label: qsTr("Speed")
                value: qsTr("%1 meters / second").arg(
                           positionSource.position.speed)
                valid: positionSource.position.speedValid
                width: parent.width
            }
        }
    }
}
