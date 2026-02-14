#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

   // LanguageManager langManager(&engine);
   // FileHandler fileHandler;

    // Udostępniamy obie usługi dla QML
    //engine.rootContext()->setContextProperty("languageService", &langManager);
   // engine.rootContext()->setContextProperty("fileService", &fileHandler);

    // Wczytujemy QML z folderu ui (przez zasoby qrc)
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}