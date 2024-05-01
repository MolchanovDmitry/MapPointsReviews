import QtQuick 2.0
import Sailfish.Silica 1.0

Row {
    id: stars
    spacing: 2
    property int starCount: 5
    property int rating: 3
    property int starSize: 50
    property bool isClickAvailable

    Repeater {
        model: stars.starCount

        Item {
            width: stars.starSize
            height: stars.starSize

            Label {
                id: starButton
                text: index < stars.rating ? "★" : "☆"

                width: parent.width
                height: parent.height
                font.pixelSize: width
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (isClickAvailable) {
                            stars.rating = index + 1
                        }
                    }
                }
            }
        }
    }
}
