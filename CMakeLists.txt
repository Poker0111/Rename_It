cmake_minimum_required(VERSION 3.16)
project(Rename_It LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2 Widgets QuickLayouts)

include_directories(include)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/fileservice.cpp
    src/tasks.cpp
)

qt_add_qml_module(${PROJECT_NAME}
    URI RenameModule
    VERSION 1.0
    QML_FILES 
        ui/main.qml
    SOURCES
        include/fileservice.h
        include/tasks.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::QuickControls2 Qt6::Widgets Qt6::QuickLayouts
)