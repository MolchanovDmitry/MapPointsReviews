import QtQuick 2.0
import Sailfish.Silica 1.0
import "../assets"


/*
    Экран информации о точке.
*/
Page {
    objectName: "mapPointPage"
    allowedOrientations: Orientation.All

    property variant imageUrls
    property string pageTitle
    property string description
    property int mapPointId
    property bool isConfirmed

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height
        anchors.topMargin: Theme.paddingLarge
        anchors.leftMargin: Theme.horizontalPageMargin
        anchors.rightMargin: Theme.horizontalPageMargin

        Column {
            id: column
            width: parent.width
            spacing: Theme.paddingSmall

            anchors.topMargin: Theme.paddingLarge

            PageHeader {
                id: header
                title: pageTitle
            }

            ListView {
                id: listView
                width: parent.width
                height: Theme.dp(400)
                visible: imageUrls.length !== 0 && imageUrls[0] !== ""
                orientation: ListView.Horizontal
                spacing: Theme.paddingSmall
                anchors.topMargin: Theme.paddingMedium

                model: imageUrls

                delegate: Image {
                    id: mainImage
                    height: parent.height
                    source: modelData
                    width: parent.height * sourceSize.width / sourceSize.height
                    fillMode: Image.PreserveAspectFit
                }
            }

            Text {
                text: qsTr("no_photos")
                color: Theme.primaryColor
                visible: imageUrls.length === 0 || imageUrls[0] === ""
                font.pixelSize: Theme.fontSizeMedium
            }
            SectionHeader {
                text: qsTr("description")
            }

            Text {
                id: descriptionText
                text: description
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeMedium
            }

            SectionHeader {
                text: qsTr("comments")
                visible: isConfirmed
            }

            Row {
                width: parent.width
                visible: isConfirmed
                height: commentField.height

                TextField {
                    id: commentField
                    width: parent.width - sendIcon.width
                    placeholderText: "Место для комментария"
                    validator: RegExpValidator {
                        regExp: /^[A-Za-zА-Яа-я0-9\s\-_,\.;:()]+$/
                    }
                    Component.onCompleted: {
                        text = "мой комментарий"
                    }
                }

                Image {
                    id: sendIcon
                    source: "image://theme/icon-m-send"
                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent
                        onClicked: {
                            console.log("addComment " + mapPointId + " " + commentField.text)
                            addCommentHandler.addReview(mapPointId, 5,
                                                        commentField.text)
                        }
                    }
                }
            }

            ListView {
                visible: isConfirmed
                id: commentsView
                width: parent.width
                height: contentHeight
                spacing: Theme.paddingSmall
                orientation: ListView.Vertical
                model: commentsModel
                anchors.leftMargin: Theme.paddingLarge
                interactive: false

                delegate: Item {
                    width: listView.width
                    height: icon.height + rating.height + comment.height

                    Image {
                        id: icon
                        height: 50
                        width: height
                        source: "image://theme/icon-cover-people"
                        anchors.left: parent.left
                        anchors.top: parent.top
                    }

                    Label {
                        id: name
                        text: qsTr("anonymous")
                        anchors.verticalCenter: icon.verticalCenter
                        anchors.left: icon.right
                        anchors.leftMargin: 10
                        font.pixelSize: 20
                    }

                    RatingStarsRow {
                        id: rating
                        rating: model.starsCount
                        anchors.top: name.bottom
                        anchors.left: parent.left
                    }

                    Text {
                        id: comment
                        text: model.comment
                        width: parent.width
                        color: Theme.primaryColor
                        anchors.top: rating.bottom
                        wrapMode: Text.WordWrap
                        font.pixelSize: Theme.fontSizeMedium
                    }
                }
            }
        }

        Component.onCompleted: {
            fetchCommentsHandler.fetchComments(mapPointId)
        }
    }
}
