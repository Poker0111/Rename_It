import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

Window {
    width: 400; height: 300
    visible: true
    title: "Rename It"

    FolderDialog {
        id: folderDialog
        onAccepted: {
            // Wywołanie Twojej logiki C++
            fileService.startProcess(folderDialog.selectedFolder, "pl")
        }
    }

    Button {
        text: "Wybierz folder do zmiany nazw"
        anchors.centerIn: parent
        onClicked: folderDialog.open()
    }
}