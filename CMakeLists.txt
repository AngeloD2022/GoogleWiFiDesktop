cmake_minimum_required(VERSION 3.5)

project(GoogleWiFiDesktopClient LANGUAGES CXX)


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/Users/angelodeluca/Qt/5.15.2/clang_64/lib/cmake")


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

include_directories(/usr/local/include/qt5keychain)

find_package(Qt5 COMPONENTS
        Widgets
        WebEngineWidgets
        REQUIRED)

if(ANDROID)
  add_library(GoogleWiFiDesktopClient SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
else()
  add_executable(GoogleWiFiDesktopClient
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
          GAPIS/Auth/RandomUtilities.h
          GAPIS/Auth/consentdialog.cpp
          GAPIS/Auth/consentdialog.h
          GAPIS/Auth/consentdialog.ui GAPIS/credentials.h
          )
endif()


target_link_libraries(GoogleWiFiDesktopClient PRIVATE /usr/local/lib/libqt5keychain.0.12.90.dylib)

target_link_libraries(GoogleWiFiDesktopClient PRIVATE Qt5::Widgets Qt5::WebEngineWidgets)
