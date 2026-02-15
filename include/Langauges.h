#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include <QObject>
#include <QTranslator>
#include <QGuiApplication>
#include <QDebug>

class Languages : public QObject  // Poprawiłem literówkę w nazwie
{
    Q_OBJECT
    Q_PROPERTY(QString emptyString READ emptyString NOTIFY languageChanged)

public:
    explicit Languages(QObject *parent = nullptr) : QObject(parent) {}
    
    // KLUCZOWE: Dodaj ten destruktor, aby pozbyć się błędu vtable
    virtual ~Languages() {} 

    QString emptyString() const { return ""; }

    Q_INVOKABLE void setLanguage(QString langCode) {
    qApp->removeTranslator(&m_translator);

    // Pobieramy ścieżkę do folderu, w którym jest plik .exe
    QString baseDir = QCoreApplication::applicationDirPath();
    
    // Próbujemy w kilku miejscach (dla wygody podczas pracy w VSC)
    bool loaded = m_translator.load("app_" + langCode, baseDir + "/translations");
    
    if (!loaded) {
        // Jeśli nie w build/translations, sprawdź w folderze projektu (poziom wyżej)
        loaded = m_translator.load("app_" + langCode, baseDir + "/../translations");
    }

    if (loaded) {
        qApp->installTranslator(&m_translator);
        qDebug() << "Załadowano język:" << langCode;
        emit languageChanged();
    } else {
        qDebug() << "Nie udało się załadować pliku dla:" << langCode;
        qDebug() << "Szukana ścieżka:" << baseDir + "/translations/app_" + langCode + ".qm";
    }
}

signals:
    void languageChanged();

private:
    QTranslator m_translator;
};

#endif