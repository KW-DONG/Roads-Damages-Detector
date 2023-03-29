cmake_minimum_required(VERSION 3.14)

project(Monitor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Qml Quick QuickControls2 REQUIRED)
find_package(OpenCV REQUIRED)
#find_package(Threads REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories(./src ./src/data ./src/model ./src/driver ./qml)


set(PROJECT_SOURCES
        src/driver/camera.h src/driver/camera.cpp
        src/main.cpp
        src/monitor.h src/monitor.cpp
        src/qpaintitem.h src/qpaintitem.cpp
        src/data/tasklistdata.h src/data/tasklistdata.cpp
        src/data/resultlistdata.h src/data/resultlistdata.cpp
        src/model/tasklistmodel.h src/model/tasklistmodel.cpp
        src/model/resultlistmodel.h src/model/resultlistmodel.cpp
        qml.qrc
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Monitor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Monitor APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Monitor SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Monitor
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Monitor PUBLIC ${OpenCV_LIBS}
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::QuickControls2)

set_target_properties(Monitor PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Monitor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(Monitor)
    qt_finalize_executable(Monitor)
endif()
