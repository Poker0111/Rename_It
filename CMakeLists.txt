cmake_minimum_required(VERSION 3.16)
project(Rename_It LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# AUTOMOC jest niezbędny dla klas używających Q_OBJECT (jak Twoje serwisy)
set(CMAKE_AUTOMOC ON)

# Wymuszamy wyłączenie generowania metatypów przed definicją modułów
# To rozwiązuje błąd "Error 5 / illegal value" w GitHub Actions
set(QT_QML_GENERATE_METATYPES OFF)

# Szukamy potrzebnych bibliotek Qt6
find_package(Qt6 REQUIRED COMPONENTS 
    Core 
    Gui 
    Qml 
    Quick 
    QuickControls2 
    Widgets 
    QuickLayouts 
    LinguistTools
)

# Pliki tłumaczeń
set(TS_FILES 
    translations/app_pl.ts
    translations/app_en.ts
    translations/app_ja.ts
)

# 1. Tworzymy główny plik wykonywalny
# Jeśli masz plik .rc (ikonka), dodaj go tutaj
qt_add_executable(${PROJECT_NAME}
    resources/resource.rc
)

# 2. Definiujemy moduł QML i dodajemy WSZYSTKIE pliki źródłowe
# UWAGA: Pliki .cpp i .h dodajemy TYLKO TUTAJ, nie w add_executable
qt_add_qml_module(${PROJECT_NAME}
    URI Rename_It
    VERSION 1.0
    QML_FILES 
        ui/main.qml
    SOURCES
        include/fileservice.h
        include/Langauges.h
        include/tasks.h
        src/main.cpp
        src/fileservice.cpp
        src/tasks.cpp
)

# 3. Dodajemy folder z nagłówkami
target_include_directories(${PROJECT_NAME} PRIVATE include)

# 4. Linkujemy biblioteki Qt
target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt6::Core 
    Qt6::Gui 
    Qt6::Qml 
    Qt6::Quick 
    Qt6::QuickControls2 
    Qt6::Widgets 
    Qt6::QuickLayouts
)

# 5. Obsługa tłumaczeń (automatycznie generuje pliki .qm)
qt_add_translations(${PROJECT_NAME}
    TS_FILES ${TS_FILES}
)

# Dodatkowe ustawienie na wszelki wypadek, gdyby wersja Qt była starsza
set_target_properties(${PROJECT_NAME} PROPERTIES 
    QT_QML_GENERATE_METATYPES OFF
)