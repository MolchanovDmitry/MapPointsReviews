import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    objectName: "mapPointPage"
    allowedOrientations: Orientation.All

    // TODO удалить отладочную информацию
    property variant imageUrls: []
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
                visible: imageUrls.count > 0 || imageUrls.count !== undefined
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
                visible: imageUrls.count === 0 || imageUrls.count === undefined
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
                    width: parent.width - icon.width
                    placeholderText: "Место для комментария"
                    validator: RegExpValidator {
                        regExp: /^[A-Za-zА-Яа-я0-9\s\-_,\.;:()]+$/
                    }
                    Component.onCompleted: {
                        text = "мой комментарий"
                    }
                }

                Image {
                    id: icon
                    source: "image://theme/icon-m-send"
                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent
                        onClicked: {
                            console.log("addComment " + mapPointId + " " + commentField.text)
                            addCommentHandler.addComment(mapPointId,
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

                delegate: Text {
                    text: model.comment
                    color: Theme.primaryColor
                }
            }
        }

        Component.onCompleted: {
            var result = imageUrls.count === undefined
            console.log("imageUrls.count = " + imageUrls.count
                        + " imageUrls == undefined =" + result)
            fetchCommentsHandler.fetchComments(mapPointId)
        }
    }
}
