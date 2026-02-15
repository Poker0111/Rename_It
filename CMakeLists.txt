cmake_minimum_required(VERSION 3.16)
project(Rename_It LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# Całkowite wyłączenie metatypów na poziomie globalnym
set(QT_QML_GENERATE_METATYPES OFF CACHE BOOL "" FORCE)

find_package(Qt6 REQUIRED COMPONENTS 
    Core Gui Qml Quick QuickControls2 Widgets QuickLayouts LinguistTools
)

set(TS_FILES 
    translations/app_pl.ts
    translations/app_en.ts
    translations/app_ja.ts
)

qt_add_executable(${PROJECT_NAME} resources/resource.rc)

# Używamy NO_GENERATE_METATYPES jako parametru funkcji
qt_add_qml_module(${PROJECT_NAME}
    URI Rename_It
    VERSION 1.0
    NO_GENERATE_METATYPES
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

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::QuickControls2 Qt6::Widgets Qt6::QuickLayouts
)

qt_add_translations(${PROJECT_NAME} TS_FILES ${TS_FILES})