import QtQuick 2.0
import Sailfish.Silica 1.0


/*
    Страница о приложении
*/
Page {
    objectName: "aboutPage"
    allowedOrientations: Orientation.All

    SilicaFlickable {
        objectName: "flickable"
        anchors.fill: parent
        anchors.leftMargin: Theme.horizontalPageMargin
        anchors.rightMargin: Theme.horizontalPageMargin
        anchors.topMargin: Theme.paddingLarge * 2
        contentHeight: layout.height + Theme.paddingLarge

        Column {
            id: layout
            objectName: "layout"
            width: parent.width

            PageHeader {
                objectName: "pageHeader"
                title: qsTr("About Application")
            }

            Text {
                text: "\t" + qsTr("#about").arg(
                          "<a href='https://github.com/MolchanovDmitry/MapPointsReviews' style='color: #008000;'>" + qsTr(
                              "#repositoryLinkText") + "</a>")
                color: Theme.primaryColor
                wrapMode: Text.Wrap
                width: parent.width
                textFormat: Text.RichText
                font.pixelSize: Theme.fontSizeLarge
                onLinkActivated: Qt.openUrlExternally(link)
            }
        }
    }
}
