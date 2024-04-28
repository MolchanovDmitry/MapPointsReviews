import QtQuick 2.6
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.0
import Sailfish.Pickers 1.0
import "../assets"

// TODO добавить координаты
// TODO добавить валидацию полей
Dialog {
    id: addMapPointPage
    objectName: "aboutPage"
    allowedOrientations: Orientation.All

    property variant imageUrls: []
    property real latitude
    property real longitude

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

        TextField {
            id: titleText
            placeholderText: "Введите наименование заведения"
            validator: RegExpValidator {
                regExp: /^[A-Za-zА-Яа-я0-9\s\-_,\.;:()]+$/
            }
            onErrorHighlightChanged: {
                canAccept = !errorHighlight
            }
        }

        TextArea {
            id: descriptionText
            placeholderText: "Введите описание заведения"
            Component.onCompleted: {
                text = "Received number: " + latitude
            }
        }
    }

    Component.onCompleted: {
        canAccept = false
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

    onAccepted: {
        console.log("Намерение создания точки: latitude = " + latitude
                    + " longitude = " + longitude)
        addMapPointHandler.onMapPointAddRequest(titleText.text,
                                                descriptionText.text,
                                                imageUrls, latitude, longitude)
    }
}
