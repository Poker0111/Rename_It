cmake_minimum_required(VERSION 3.15)
project(Rename_It)

set(CMAKE_CXX_STANDARD 17)
add_compile_definitions(_UCRT)

set(wxWidgets_USE_STATIC ON)
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

file(GLOB SOURCES "src/*.cpp" "resources/resource.rc")

add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${INCLUDE})

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES})

if(MINGW)
    target_link_options(${PROJECT_NAME} PRIVATE -static -lucrt)
endif()