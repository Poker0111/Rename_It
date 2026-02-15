#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>
#include "fileservice.h"
#include "Langauges.h" // Upewnij się, że nazwa pliku jest poprawna (małe/wielkie litery)

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    
    // 1. Stwórz managera (Poprawiona nazwa klasy na Languages)
    Languages langManager; 
    
    // Opcjonalnie: Załaduj domyślny język na starcie
    langManager.setLanguage("en"); 

    QQmlApplicationEngine engine;

    // 2. Udostępnij obiekty do QML
    engine.rootContext()->setContextProperty("LangManager", &langManager);

    FileHandler fileHandler;
    engine.rootContext()->setContextProperty("fileService", &fileHandler);

    // 3. Ładowanie QML
    const QUrl url(QStringLiteral("qrc:/RenameModule/ui/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}