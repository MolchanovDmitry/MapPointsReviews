import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailfish.WebView 1.0

Page {
    objectName: "webViewPage"
    allowedOrientations: Orientation.All

    SilicaFlickable {
        anchors.fill: parent

        WebView {
            id: webview
            url: "https://github.com/MolchanovDmitry/MapPointsReviews.git"
            anchors.fill: parent
        }
    }
}
