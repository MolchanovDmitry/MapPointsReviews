import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.0
import Sailfish.Pickers 1.0
import "../assets"

Dialog {
    objectName: "aboutPage"
    allowedOrientations: Orientation.All

    Column {
        anchors.fill: parent
        spacing: Theme.paddingLarge
        DialogHeader {
            acceptText: qsTr("Save")
            cancelText: qsTr("Cancel")
        }

        ListModel {
            id: imageModel
        }

        ListView {
            id: listView
            width: parent.width
            height: imageModel.count === 0 ? 0 : 400
            orientation: ListView.Horizontal
            spacing: Theme.paddingLarge

            model: imageModel

            delegate: Image {
                source: imgSource
                height: parent.height
                fillMode: Image.PreserveAspectFit
            }
        }

        Button {
            id: addPhotoButton
            text: "Выберите фото"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                console.log("add button clicked")
                pageStack.push(multiImagePickerDialog)
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

    Component {
        id: multiImagePickerDialog
        MultiImagePickerDialog {
            onAccepted: addUrlsToModel(selectedContent)
        }
    }

    function addUrlsToModel(selectedContent) {
        for (var i = 0; i < selectedContent.count; ++i) {
            var url = selectedContent.get(i).url

            console.log(url)

            if (!isImageAlreadyExists(url)) {
                imageModel.append({
                                      "imgSource": url
                                  })
            }
        }
    }

    function isImageAlreadyExists(url) {
        for (var i = 0; i < imageModel.count; i++) {
            if (imageModel.get(i).imgSource === url) {
                return true
            }
        }
        return false
    }

    onAccepted: {

    }
}
