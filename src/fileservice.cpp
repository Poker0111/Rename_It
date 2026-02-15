#include "fileservice.h"
#include <QUrl>
#include <QDebug>
#include <algorithm>

FileHandler::FileHandler(QObject *parent) : QObject(parent) {
}

void FileHandler::startProcess(QString qPath, QString qLang) {
    // 1. Konwersja z QUrl (format QML) na lokalną ścieżkę systemową
    // toLocalFile() usuwa "file:///", a toStdWString() radzi sobie z polskimi znakami
    fs::path nativePath = QUrl(qPath).toLocalFile().toStdWString();

    // 2. Konwersja języka
    std::wstring nativeLang = qLang.toStdWString();

    // 3. Walidacja ścieżki przed wysłaniem do tasks.cpp
    if (!fs::exists(nativePath)) {
        qDebug() << "BŁĄD: Ścieżka nie istnieje:" << qPath;
        return;
    }

    // 4. Wywołanie Twojej funkcji start z tasks.cpp
    // Funkcja start(path, lang) zwraca std::vector<std::pair<fs::path, fs::path>>
    auto results = start(nativePath, nativeLang);

    qDebug() << "C++: Przetworzono" << results.size() << "elementów w:" << qPath;
}