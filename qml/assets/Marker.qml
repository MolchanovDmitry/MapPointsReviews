import QtQuick 2.6
import QtLocation 5.0

MapQuickItem {

    property alias marker: marker

    id: marker
    sourceItem: Rectangle {
        width: 10
        height: 10
        color: "red"
        smooth: true
        radius: 15
    }
    opacity: 1.0
    anchorPoint: Qt.point(sourceItem.width / 2, sourceItem.height / 2)
}
