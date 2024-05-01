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
                visible: description !== ""
                text: qsTr("description")
            }

            Text {
                id: descriptionText
                text: description
                visible: description !== ""
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeMedium
            }

            SectionHeader {
                text: qsTr("add_comments")
                visible: isConfirmed
            }

            Column {
                visible: isConfirmed
                width: parent.width

                RatingStarsRow {
                    id: commentRating
                    isClickAvailable: true
                    starSize: Theme.dp(50)
                    anchors.left: parent.left
                }

                Row {
                    width: parent.width
                    height: commentField.height

                    TextField {
                        id: commentField
                        width: parent.width - sendIcon.width
                        placeholderText: "Место для комментария"
                        validator: RegExpValidator {
                            regExp: /^[A-Za-zА-Яа-я0-9\s\-_,\.;:()]+$/
                        }
                    }

                    Image {
                        id: sendIcon
                        source: "image://theme/icon-m-send"
                        MouseArea {
                            id: mouseArea
                            anchors.fill: parent
                            onClicked: {
                                if (!commentField.errorHighlight
                                        && commentField.text !== "") {
                                    console.log("addComment " + mapPointId + " "
                                                + commentField.text)
                                    addCommentHandler.addReview(
                                                mapPointId,
                                                commentRating.rating,
                                                commentField.text)
                                    commentField.text = ""
                                }
                            }
                        }
                    }
                }
            }

            SectionHeader {
                text: qsTr("comments")
                visible: isConfirmed
            }

            ListView {
                visible: isConfirmed
                id: commentsView
                width: parent.width
                height: contentHeight
                spacing: Theme.paddingLarge
                orientation: ListView.Vertical
                model: commentsModel
                anchors.leftMargin: Theme.paddingLarge
                interactive: false

                delegate: Item {
                    width: listView.width
                    implicitHeight: icon.height + rating.height + comment.height

                    Image {
                        id: icon
                        height: Theme.dp(50)
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
                        anchors.leftMargin: Theme.dp(10)
                        font.pixelSize: Theme.fontSizeMedium
                    }

                    RatingStarsRow {
                        id: rating
                        starSize: Theme.dp(40)
                        rating: model.starCount
                        anchors.top: name.bottom
                        anchors.left: parent.left
                    }

                    Text {
                        text: getFormattedDate(model.date)
                        anchors.right: parent.right
                        anchors.top: icon.top
                        color: Theme.primaryColor
                        anchors.bottom: rating.bottom
                    }

                    Text {
                        id: comment
                        text: model.comment
                        width: parent.width
                        color: Theme.primaryColor
                        anchors.top: rating.bottom
                        wrapMode: Text.WordWrap
                        font.pixelSize: Theme.fontSizeLarge
                    }
                }
            }
        }

        Connections {
            target: commentsModel
            onAvgStarCountChanged: updateRating(avgStarCount)
        }

        Component.onCompleted: fetchCommentsHandler.fetchComments(mapPointId)
    }

    function updateRating(avgStarCount) {
        console.log("Средний рейтинг " + avgStarCount)
        if (isFinite(avgStarCount)) {
            header.title = pageTitle + " (★" + avgStarCount.toFixed(1) + ")"
        }
    }

    function getFormattedDate(timeMs) {
        var currentDateTime = new Date(timeMs)
        var formattedDate = Qt.formatDateTime(currentDateTime,
                                              "dd MMMM yyyy HH:mm")
        return formattedDate
    }
}
