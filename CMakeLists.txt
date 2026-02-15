cmake_minimum_required(VERSION 3.16)
project(Rename_It LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS 
    Core Gui Qml Quick QuickControls2 Widgets QuickLayouts LinguistTools
)

# 1. Ręcznie definiujemy zasoby QRC (to omija błąd z ostatniego screena)
set(QML_RESOURCES
    "ui/main.qml"
)

# 2. Tworzymy executable i dodajemy pliki bezpośrednio
qt_add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/fileservice.cpp
    src/tasks.cpp
    include/fileservice.h
    include/Langauges.h
    include/tasks.h
    resources/resource.rc
    ${QML_RESOURCES}
)

# Ta funkcja stworzy zasoby bez "magii" modułów QML
qt_add_resources(${PROJECT_NAME} "main_qml"
    PREFIX "/qt/qml/Rename_It"
    FILES ${QML_RESOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::QuickControls2 Qt6::Widgets Qt6::QuickLayouts
)

set(TS_FILES translations/app_pl.ts translations/app_en.ts translations/app_ja.ts)
qt_add_translations(${PROJECT_NAME} TS_FILES ${TS_FILES})