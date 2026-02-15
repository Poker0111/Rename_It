#include "fileservice.h"
#include <QUrl>
#include <QDebug>
#include <QVariantList>
#include <QVariantMap>
#include <algorithm>

namespace fs = std::filesystem;

FileHandler::FileHandler(QObject *parent) : QObject(parent) {
}

void FileHandler::startProcess(QString qPath, QString qLang) {
    pathlist.clear(); 
    results.clear();
    fs::path nativePath = QUrl(qPath).toLocalFile().toStdWString();
    std::wstring nativeLang = qLang.toStdWString();
    if (!fs::exists(nativePath)) return;
    results = start(nativePath, nativeLang);
    for(const auto& i : results){
        QVariantMap item;
        item.insert("oldName", QString::fromStdWString(i.first.filename().wstring()));
        item.insert("newName", QString::fromStdWString(i.second.filename().wstring()));
        item.insert("checked", true); 
        pathlist.append(item);
    }
    emit filesParsed(pathlist); 
}

void FileHandler::rename(const QVariantList &checkedStates){
    if (results.empty() || checkedStates.size() != results.size()) return;
    std::vector<std::pair<fs::path, fs::path>> toRename;
    for (int i = 0; i < results.size(); ++i) {
        if (checkedStates[i].toBool()) {
            toRename.push_back(results[i]);
        }
    }
    if (!toRename.empty()) {
        try {
            renameALL(toRename);
        } catch (const std::exception& e) {
            qDebug() << e.what();
        }
    }
}

void FileHandler::undo(){
   if (!results.empty()) {
        UndoAll(results);
        results.clear();
        pathlist.clear();
        emit filesParsed(pathlist);
   }
}