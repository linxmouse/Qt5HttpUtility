cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME Qt5HttpUtility)
project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置Debug和Release输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

# 为VS指定PATH，QtCreator自带
if(CMAKE_HOST_WIN32)
  if(CMAKE_CL_64)
    set(CMAKE_PREFIX_PATH "D:/Qt/5.12.12/msvc2017_64")
    set(QT_QMAKE_EXECUTABLE "D:/Qt/5.12.12/msvc2017_64/bin/qmake.exe")
  else()
    set(CMAKE_PREFIX_PATH "D:/Qt/5.12.12/msvc2017")
    set(QT_QMAKE_EXECUTABLE "D:/Qt/5.12.12/msvc2017/bin/qmake.exe")
  endif(CMAKE_CL_64)
endif(CMAKE_HOST_WIN32)

add_subdirectory(qjson EXCLUDE_FROM_ALL)

#find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
#find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

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
file(GLOB RESOURCE CMAKE_CONFIGURE_DEPENDS *.qrc)
source_group("FORM" FILES ${FORM})
source_group("HEADER" FILES ${HEADER})
source_group("SOURCE" FILES ${SOURCE})
source_group("RESOURCE" FILES ${RESOURCE})
set(PROJECT_SOURCES
    ${SOURCE}
    ${HEADER}
    ${FORM}
    ${RESOURCE}
)

#if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#    qt_add_executable(${PROJECT_NAME}
#        MANUAL_FINALIZATION
#        ${PROJECT_SOURCES}
#    )
## Define target properties for Android with Qt 6 as:
##    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
##                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
## For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
#else()
#    if(ANDROID)
#        add_library(${PROJECT_NAME} SHARED
#            ${PROJECT_SOURCES}
#        )
## Define properties for Android with Qt 5 after find_package() calls as:
##    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    else()
#        add_executable(${PROJECT_NAME}
#            ${PROJECT_SOURCES}
#        )
#    endif()
#endif()

if(ANDROID)
    add_library(${PROJECT_NAME} SHARED
        ${PROJECT_SOURCES}
    )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
else()
    add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(${PROJECT_NAME}
#    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    PRIVATE Qt5::Widgets Qt5::Network
    PRIVATE qjson-qt5
)

#set_target_properties(${PROJECT_NAME} PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#)

#if(QT_VERSION_MAJOR EQUAL 6)
#    qt_finalize_executable(${PROJECT_NAME})
#endif()
