cmake_minimum_required(VERSION 3.16)
project(Rename_It LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

# Szukamy paczek Qt
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2 LinguistTools Widgets)

# 1. ODKOMENTUJ TO: Definicja plików tłumaczeń
set(TS_FILES 
    i18n/lang_pl.ts 
    i18n/lang_ja.ts
)
qt6_add_translations(${PROJECT_NAME} TS_FILES ${TS_FILES})

# Ścieżka do pliku zasobów (QML)
qt6_add_resources(RESOURCES ui/qml.qrc)

# 2. ODKOMENTUJ TO: Wszystkie pliki źródłowe muszą być na liście
add_executable(${PROJECT_NAME}
    src/main.cpp
    #src/LanguageManager.cpp  # Musi być odkomentowane
    #src/LanguageManager.h    # Musi być odkomentowane
    src/fileservice.cpp         # Musi być odkomentowane
    src/tasks.cpp
    ${RESOURCES}
)

# 3. Informujemy kompilator, gdzie szukać nagłówków (np. tasks.h w folderze src)
target_include_directories(${PROJECT_NAME} PRIVATE src include)

# Linkowanie bibliotek
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::QuickControls2
)