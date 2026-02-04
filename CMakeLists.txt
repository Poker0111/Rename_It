cmake_minimum_required(VERSION 3.10)
project(Rename_It-1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(wxWidgets_USE_STATIC ON)


if(WIN32)
    if(EXISTS "D:/biblioteki_kod/wxWidgets-3.3.1")
        set(wxWidgets_ROOT_DIR "D:/biblioteki_kod/wxWidgets-3.3.1")
        set(wxWidgets_LIB_DIR "${wxWidgets_ROOT_DIR}/lib/gcc_lib")
        set(wxWidgets_USE_STATIC ON)
    endif()
endif()

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

include_directories(include)
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

if(WIN32)
    set(RESOURCES "resources/resource.rc")
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS} ${RESOURCES})
else()
    add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
endif()

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

if(WIN32)
    target_include_directories(${PROJECT_NAME} PRIVATE ${wxWidgets_INCLUDE_DIRS})
endif()
