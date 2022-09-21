cmake_minimum_required(VERSION 3.5)

project(JsonSample VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(qjson EXCLUDE_FROM_ALL)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

#set(PROJECT_SOURCES
#        main.cpp
#        mainwindow.cpp
#        mainwindow.h
#        mainwindow.ui
#        person.cpp
#        person.h
#)
file(GLOB SOURCE CMAKE_CONFIGURE_DEPENDS *.cpp)
file(GLOB HEADER CMAKE_CONFIGURE_DEPENDS *.h)
file(GLOB FORM CMAKE_CONFIGURE_DEPENDS *.ui)
source_group("FORM" FILES ${FORM})
source_group("HEADER" FILES ${HEADER})
source_group("SOURCE" FILES ${SOURCE})
set(PROJECT_SOURCES ${SOURCE} ${HEADER} ${FORM})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(JsonSample
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET JsonSample APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(JsonSample SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(JsonSample
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(JsonSample
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    PRIVATE qjson-qt5
)

set_target_properties(JsonSample PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(JsonSample)
endif()

target_include_directories(JsonSample PRIVATE ./qjson/include)
