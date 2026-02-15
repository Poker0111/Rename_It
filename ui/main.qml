import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts

Window {
    width: 600
    height: 500
    visible: true
    title: "Rename It"

    ListModel { id: filesModel }

    Connections {
        target: fileService
        function onFilesParsed(fileList) {
            console.log("Dane dotarły! Liczba plików: " + fileList.length)
            filesModel.clear()
            for (var i = 0; i < fileList.length; i++) {
                filesModel.append(fileList[i])
            }
        }
    }

    FolderDialog {
        id: folderDialog
        onAccepted: {
            fileService.startProcess(folderDialog.selectedFolder, field.text)
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        TextField {
            id: field
            placeholderText: "Wpisz tag języka (np. pl, ja)"
            Layout.fillWidth: true
        }

        Button {
            text: "1. Wybierz folder i parsuj pliki"
            Layout.fillWidth: true
            onClicked: folderDialog.open()
        }

        Frame {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true

            ListView {
                id: listView
                anchors.fill: parent
                model: filesModel
                delegate: CheckDelegate {
                    width: listView.width
                    text: model.oldName + " ➔ " + model.newName
                    checked: model.checked 

                    onCheckedChanged: {
                        if (filesModel.get(index).checked !== checked) {
                            filesModel.setProperty(index, "checked", checked)
                        }
                    }
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            
            Button {
                text: "2. Apply (Rename)"
                Layout.fillWidth: true
                onClicked: {
                    let states = []
                    for (let i = 0; i < filesModel.count; i++) {
                        states.push(filesModel.get(i).checked)
                    }
                    fileService.rename(states)
                    filesModel.clear()
                }
            }

            Button {
                text: "Undo"
                Layout.fillWidth: true
                onClicked: fileService.undo()
            }
        }
    }
}