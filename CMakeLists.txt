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

# Dependency: QtKeychain
SET(BUILD_WITH_QT6 ON)
add_subdirectory(${GWD_INCLUDE_DIR}/qtkeychain)


# Core Google WiFi API Target
file(GLOB_RECURSE GWD_CORE_HEADERS
        ${GWD_SOURCE_DIR}/core/*.h
        ${GWD_SOURCE_DIR}/core/*.hpp
        )

file(GLOB_RECURSE GWD_CORE_SOURCES
        ${GWD_SOURCE_DIR}/core/*.cpp
        ${GWD_SOURCE_DIR}/core/*.c
        )

add_library(gwd_core ${GWD_CORE_HEADERS} ${GWD_CORE_SOURCES})

# Google WiFi Desktop -- User Interface Application Target
file(GLOB_RECURSE GWD_UI_HEADERS
        ${GWD_SOURCE_DIR}/ui/*.h
        ${GWD_SOURCE_DIR}/ui/*.hpp
        )

file(GLOB_RECURSE GWD_UI_SOURCES
        ${GWD_SOURCE_DIR}/ui/*.cpp
        ${GWD_SOURCE_DIR}/ui/*.c
        )

add_executable(gwd_ui ${GWD_UI_HEADERS} ${GWD_UI_SOURCES})
target_include_directories(gwd_ui PUBLIC ${GWD_INCLUDE_DIR})
target_link_libraries(gwd_ui PRIVATE
        gwd_core
        ${QTKEYCHAIN_TARGET_NAME}
        Qt${QT_VERSION_MAJOR}::Widgets
        )

if(APPLE)
    set_target_properties(gwd_ui PROPERTIES
            MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
            MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
            MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
            )
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(gwd_ui)
endif()

