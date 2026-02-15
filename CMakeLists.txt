cmake_minimum_required(VERSION 3.16)
project(Rename_It LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON) # Automatyczna obsługa plików zasobów

find_package(Qt6 REQUIRED COMPONENTS 
    Core Gui Qml Quick QuickControls2 Widgets QuickLayouts LinguistTools
)

# Definiujemy pliki źródłowe
set(SOURCES
    src/main.cpp
    src/fileservice.cpp
    src/tasks.cpp
    include/fileservice.h
    include/Langauges.h
    include/tasks.h
)

# Tworzymy plik zasobów "w locie" dla plików QML
qt_add_resources(RESOURCES
    PREFIX "/"
    FILES
        ui/main.qml
)

# Tworzymy aplikację
qt_add_executable(${PROJECT_NAME} 
    ${SOURCES}
    ${RESOURCES}
    resources/resource.rc
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::QuickControls2 Qt6::Widgets Qt6::QuickLayouts
)

# Tłumaczenia
set(TS_FILES translations/app_pl.ts translations/app_en.ts translations/app_ja.ts)
qt_add_translations(${PROJECT_NAME} TS_FILES ${TS_FILES})