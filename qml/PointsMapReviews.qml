import QtQuick 2.0
import Sailfish.Silica 1.0

ApplicationWindow {
    objectName: "applicationWindow"
    //initialPage: Qt.resolvedUrl("pages/MapPage.qml")
    initialPage: Qt.resolvedUrl("pages/AddMapPointPage.qml")
    cover: Qt.resolvedUrl("cover/DefaultCoverPage.qml")
    allowedOrientations: defaultAllowedOrientations
    displayMode: Orientation.PortraitMask
    statusbarForceVisible: true
}
