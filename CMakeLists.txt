cmake_minimum_required(VERSION 3.16)
project(Rename_It LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(TS_FILES 
    translations/app_pl.ts
    translations/app_en.ts
    translations/app_ja.ts
)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2 Widgets QuickLayouts LinguistTools)

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
        # Dodanie nagłówków tutaj jest KLUCZOWE dla AUTOMOC
        include/fileservice.h    
        include/Langauges.h      
        include/tasks.h
        
        # Pliki źródłowe
        src/main.cpp
        src/fileservice.cpp
        src/tasks.cpp
)
qt_add_translations(${PROJECT_NAME}
    TS_FILES ${TS_FILES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::QuickControls2 Qt6::Widgets Qt6::QuickLayouts
)
file(GLOB QM_FILES "${CMAKE_CURRENT_SOURCE_DIR}/translations/*.qm")
file(COPY ${QM_FILES} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/translations")