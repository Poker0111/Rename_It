cmake_minimum_required(VERSION 3.10)
project(Rename_It)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Force static wxWidgets BEFORE find_package
set(wxWidgets_USE_STATIC ON)
add_definitions(-DwxWidgets_USE_STATIC)

# 2. Find wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

if(WIN32)
    set(RESOURCES "resources/resource.rc")
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS} ${RESOURCES})
else()
    add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
endif()

# 3. Apply the includes and link libraries
if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES})
endif()