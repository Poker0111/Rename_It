#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <vector>
#include <filesystem>
#include "tasks.h" // Upewnij się, że ten plik istnieje w projekcie

namespace fs = std::filesystem;

class FileHandler : public QObject {
    Q_OBJECT
public:
    explicit FileHandler(QObject *parent = nullptr);

    // Ta nazwa musi być identyczna w .cpp i wywołaniu w QML
    Q_INVOKABLE void startProcess(QString qPath, QString qLang);
};

#endif // FILEHANDLER_H