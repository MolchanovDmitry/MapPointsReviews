import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.0
import "../assets"

Dialog {
    objectName: "aboutPage"
    allowedOrientations: Orientation.All

    Column {
        anchors.fill: parent
        DialogHeader {
            acceptText: qsTr("Save")
            cancelText: qsTr("Cancel")
        }

        Button {
            id: addPhotoButton
            text: "Выберите фото"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                console.log("add button clicked")
            }
        }

        TextArea {
            id: titleText
            placeholderText: "Введите наименование заведения"
        }

        TextArea {
            id: descriptionText
            placeholderText: "Введите описание заведения"
        }
    }

    onAccepted: {

    }
}
