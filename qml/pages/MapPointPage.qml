import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    objectName: "mapPointPage"
    allowedOrientations: Orientation.All

    // TODO удалить отладочную информацию
    property variant imageUrls: ["https://samplelib.com/lib/preview/jpeg/sample-city-park-400x300.jpg", "https://samplelib.com/lib/preview/jpeg/sample-birch-400x300.jpg"]
    property string pageTitle: "asdasdaaaaas"
    property string description: "asdasd"
    property int mapPointId

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height
        anchors.topMargin: Theme.paddingLarge
        anchors.leftMargin: Theme.horizontalPageMargin

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
                height: imageUrls.count === 0 ? 0 : Theme.dp(400)
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
                text: qsTr("description")
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeMedium
            }

            Text {
                id: descriptionText
                text: description
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeMedium
            }

            Text {
                text: qsTr("comments")
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeMedium
            }

            TextField {
                id: commentField
                height: contentHeight
                placeholderText: "Место для комментария"
                validator: RegExpValidator {
                    regExp: /^[A-Za-zА-Яа-я0-9\s\-_,\.;:()]+$/
                }
                onErrorHighlightChanged: {
                    canAccept = !errorHighlight
                }

                Component.onCompleted: {
                    text = "мой комментарий"
                }
            }

            Button {
                id: addComment
                text: "Добавить комментарий"
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    console.log("addComment " + mapPointId + " " + commentField.text)
                    addCommentHandler.addComment(mapPointId, commentField.text)
                }
            }

            ListView {
                id: commentsView
                width: parent.width
                height: contentHeight
                spacing: Theme.paddingSmall
                orientation: ListView.Vertical
                model: commentsModel
                interactive: false

                delegate: Text {
                    text: model.comment
                }
            }
        }

        Component.onCompleted: {

            fetchCommentsHandler.fetchComments(mapPointId)
        }
    }
}
