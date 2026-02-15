#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QVariantList>
#include <vector>
#include <filesystem>
#include "tasks.h"

class FileHandler : public QObject {
    Q_OBJECT
public:
    explicit FileHandler(QObject *parent = nullptr);

    Q_INVOKABLE void startProcess(QString qPath, QString qLang);
    Q_INVOKABLE void rename(const QVariantList &checkedStates);
    Q_INVOKABLE void undo();
    Q_INVOKABLE void reset() {
    results.clear();
    pathlist.clear();
    emit filesParsed(pathlist);
}

signals:
    void filesParsed(QVariantList fileList);

private:
    std::vector<std::pair<fs::path, fs::path>> results;
    std::vector<std::pair<fs::path, fs::path>> finalselection;
    QVariantList pathlist;
};

#endif