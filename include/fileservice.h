#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QString>
#include <QUrl>
#include "tasks.h"

class FileHandler : public QObject {
    Q_OBJECT
public:
    explicit FileHandler(QObject *parent = nullptr) : QObject(parent) {}

    // Ta funkcja jest widoczna dla QML (przycisk ją wywoła)
    Q_INVOKABLE void start(QString path,QString langTag) {
        // 1. Zamieniamy ścieżkę z QML na taką, którą rozumie Twój C++
        std::string cleanPath = QUrl(path).toLocalFile().toStdString();
        std::wstring cleanLang = langTag.toStdWString();

        start(cleanPath,cleanLang);
        }
};

#endif