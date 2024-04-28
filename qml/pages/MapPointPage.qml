import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    objectName: "mapPointPage"
    allowedOrientations: Orientation.All

    // TODO удалить отладочную информацию
    property variant imageUrls: ["https://samplelib.com/lib/preview/jpeg/sample-city-park-400x300.jpg", "https://samplelib.com/lib/preview/jpeg/sample-birch-400x300.jpg"]
    property string pageTitle: "asdasdaaaaas"
    property string description: "asdasd"

    PageHeader {
        id: header
        title: pageTitle
    }

    Column {
        anchors.fill: parent
        spacing: Theme.paddingLarge
        anchors.topMargin: Theme.paddingLarge * 4
        anchors.leftMargin: Theme.horizontalPageMargin

        ListView {
            id: listView
            width: parent.width
            height: imageUrls.count === 0 ? 0 : Theme.dp(400)
            orientation: ListView.Horizontal
            spacing: Theme.paddingSmall

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
            id: descriptionText
            text: description
            color: Theme.primaryColor
            font.pixelSize: Theme.fontSizeMedium
        }
    }
}
