import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.0
import Sailfish.Pickers 1.0
import "../assets"
import com.current.project 1.0

// TODO добавить координаты
// TODO добавить валидацию полей
Dialog {
    objectName: "aboutPage"
    allowedOrientations: Orientation.All

    property variant imageUrls: []
    property string title: "test1"
    property string description: "test2"

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

            delegate: Item {
                height: parent.height
                width: mainImage.width

                Rectangle {
                    id: container
                    width: parent.width
                    height: parent.height
                    color: "lightblue"

                    Image {
                        id: mainImage
                        source: imgSource
                        height: parent.height
                        fillMode: Image.PreserveAspectFit
                    }

                    Image {
                        id: removeIcon
                        anchors.right: parent.right
                        anchors.top: parent.top
                        source: "image://theme/icon-m-delete"
                        MouseArea {
                            anchors.fill: parent
                            onClicked: imageModel.remove(index)
                        }
                    }
                }
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
                imageUrls.push(url)
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

    AddMapPointListener {
        id: addMapPointListener
    }

    onAccepted: {
        addMapPointListener.onMapPointAddRequest(title.text,
                                                 descriptionText.text,
                                                 imageUrls, 0, 0)
        title = titleText.text
        description = descriptionText.text
    }
}
