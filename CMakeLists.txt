cmake_minimum_required(VERSION 3.10)
project(Rename_It-1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(wxWidgets_USE_STATIC ON)

# --- KONFIGURACJA ŚCIEŻEK (Tylko dla Windows, jeśli nie używasz vcpkg/msys2) ---
if(WIN32)
    # Jeśli folder istnieje na Twoim dysku, CMake go użyje. 
    # Na innym komputerze po prostu pominie te linie lub nadpisze je z terminala.
    if(EXISTS "D:/biblioteki_kod/wxWidgets-3.3.1")
        set(wxWidgets_ROOT_DIR "D:/biblioteki_kod/wxWidgets-3.3.1")
        set(wxWidgets_LIB_DIR "${wxWidgets_ROOT_DIR}/lib/gcc_lib")
        set(wxWidgets_USE_STATIC ON)
    endif()
endif()

# --- ZNAJDOWANIE BIBLIOTEK ---
# Na Linux/macOS find_package zadziała automatycznie bez powyższych ścieżek
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

# --- PLIKI ŹRÓDŁOWE ---
include_directories(include)
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

# --- ZASOBY I WYGLĄD (WINDOWS) ---
if(WIN32)
    set(RESOURCES "resources/resource.rc")
    # WIN32 po PROJECT_NAME sprawia, że na Windows nie otwiera się konsola w tle
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS} ${RESOURCES})
else()
    # Na Linux/macOS standardowy start
    add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
endif()

# --- LINKOWANIE ---
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

# Sprawiamy, że kompilator zasobów (rc.exe/windres) widzi nagłówki wxWidgets
if(WIN32)
    target_include_directories(${PROJECT_NAME} PRIVATE ${wxWidgets_INCLUDE_DIRS})
endif()