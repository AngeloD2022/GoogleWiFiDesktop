cmake_minimum_required(VERSION 3.5)
project(GoogleWiFiDesktop VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Replace this with your qt cmake prefix path...
set(CMAKE_PREFIX_PATH /Users/angelodeluca/Qt/6.2.1/macos/lib/cmake)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(GWD_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(GWD_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

include_directories(${GWD_INCLUDE_DIR})

file(GLOB_RECURSE GWD_HEADERS
        ${GWD_SOURCE_DIR}/*.h
        ${GWD_SOURCE_DIR}/*.hpp
        )

file(GLOB_RECURSE GWD_SOURCES
        ${GWD_SOURCE_DIR}/*.cpp
        ${GWD_SOURCE_DIR}/*.c
        )

add_executable(gwd ${GWD_HEADERS} ${GWD_SOURCES})

target_link_libraries(gwd PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        )

set_target_properties(gwd PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        )

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(gwd)
endif()