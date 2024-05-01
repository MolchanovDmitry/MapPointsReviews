import QtQuick 2.0
import Sailfish.Silica 1.0

Row {

    id: stars
    spacing: 2
    property int starCount: 5
    property int rating: 3
    property int starSize: 100

    Repeater {
        model: stars.starCount

        Button {
            width: starSize
            height: starSize
            id: starButton
            text: index < stars.rating ? "★" : "☆"
            onClicked: {
                stars.rating = index + 1
            }
        }
    }
}
