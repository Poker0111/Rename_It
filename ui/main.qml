import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts

ApplicationWindow {
    id: window
    width: 600
    height: 500
    visible: true
    // Używamy + LangManager.emptyString, aby wymusić odświeżenie przy zmianie języka
    title: qsTr("Rename It") + LangManager.emptyString

    menuBar: MenuBar {
        Menu {
            title: qsTr("Edit") + LangManager.emptyString
            Action {
                text: qsTr("Undo") + LangManager.emptyString
                shortcut: "Ctrl+Z"
                onTriggered: fileService.undo()
            }
        }
        Menu {
            title: qsTr("Languages") + LangManager.emptyString

            ActionGroup { id: langGroup }

            Action {
                text: "English"
                checkable: true
                checked: true
                ActionGroup.group: langGroup
                onTriggered: LangManager.setLanguage("en")
            }
            Action {
                text: "Polski"
                checkable: true
                ActionGroup.group: langGroup
                onTriggered: LangManager.setLanguage("pl")
            }
            Action {
                text: "日本語"
                checkable: true
                ActionGroup.group: langGroup
                onTriggered: LangManager.setLanguage("ja")
            }
        }
    }

    ListModel { id: filesModel }

    Connections {
        target: fileService
        function onFilesParsed(fileList) {
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
            placeholderText: qsTr("Wpisz tag języka (np. pl, jp)") + LangManager.emptyString
            Layout.fillWidth: true
        }

        Button {
            text: qsTr("1. Wybierz folder") + LangManager.emptyString
            Layout.fillWidth: true
            onClicked: folderDialog.open()
        }

        Text {
            text: (qsTr("Ścieżka: ") + LangManager.emptyString) + folderDialog.selectedFolder.toString().replace("file:///", "")
            font.bold: true
            Layout.fillWidth: true
            elide: Text.ElideMiddle
        }

        // --- SEKCJA FRAME Z LISTĄ PLIKÓW ---
        Frame {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true

            ListView {
                id: listView
                anchors.fill: parent
                clip: true
                model: filesModel
                rightMargin: 15 

                ScrollBar.vertical: ScrollBar {
                    policy: ScrollBar.AsNeeded
                }

                delegate: CheckDelegate {
                    width: listView.width - listView.rightMargin
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

        // --- PRZYCISKI NA DOLE ---
        RowLayout {
            Layout.fillWidth: true
            
            Button {
                text: qsTr("2. Apply (Rename)") + LangManager.emptyString
                enabled: filesModel.count > 0
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
                text: qsTr("Reset") + LangManager.emptyString
                Layout.fillWidth: true
                onClicked: {
                    filesModel.clear();
                    field.clear();
                }
            }
        }
    }
}