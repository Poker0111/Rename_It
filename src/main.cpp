#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "fileservice.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    FileHandler fileHandler;
    // To sprawia, że w QML piszesz 'fileService.startProcess(...)'
    engine.rootContext()->setContextProperty("fileService", &fileHandler);

    // Upewnij się, że main.qml jest w zasobach pod tą ścieżką
    const QUrl url(QStringLiteral("qrc:/main.qml")); 
    engine.load(url);

    return app.exec();
}