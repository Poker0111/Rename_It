#include "fileservice.h"
#include <QUrl>
#include <QDebug>
#include <algorithm>

FileHandler::FileHandler(QObject *parent) : QObject(parent) {
}

void FileHandler::startProcess(QString qPath, QString qLang) {
   
    fs::path nativePath = QUrl(qPath).toLocalFile().toStdWString();
    std::wstring nativeLang = qLang.toStdWString();

    if (!fs::exists(nativePath)) {
        return;
    }
    
    results = start(nativePath, nativeLang);
}