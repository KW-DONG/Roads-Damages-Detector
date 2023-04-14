cmake_minimum_required(VERSION 3.14)
project(SmartCam)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(ncnn_DIR "/home/lochcliff/ProgramFiles/ncnn/build/install/lib/cmake/ncnn")
    find_package(ncnn REQUIRED)
    set(NCNN_INCLUDE_PATH "/home/lochcliff/ProgramFiles/ncnn/src"
                         "/home/lochcliff/ProgramFiles/ncnn/build/src")
    set(NCNN_LIB ncnn)
    set(SERIALPORT_SRC "driver/serial.h" "driver/serial_linux.cpp")
else()
    set(NCNN_INCLUDE_PATH "C:/ncnn/src" "C:/ncnn/build/src")
    set(NCNN_LIB "C:/ncnn/build/src/Release/ncnn.lib")
    set(SERIALPORT_SRC "driver/serial.h" "driver/serial_win.cpp")
endif()


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick SerialPort)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick SerialPort)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Qml Quick QuickControls2 SerialPort REQUIRED)
find_package(OpenCV REQUIRED)
#find_package(Threads REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )

include_directories(./
                    ./data
                    ./model
                    ./driver
                    ../qml
                    ./algorithm
                    ${NCNN_INCLUDE_PATH}
                    )

#build objects for testing as static libs

add_library(CusNCNN algorithm/cusncnn.h algorithm/cusncnn.cpp)
target_link_libraries(CusNCNN ${NCNN_LIB} ${OpenCV_LIBS})
target_compile_definitions(CusNCNN PRIVATE UNIT_TEST)

add_library(ResultListData data/resultlistdata.h data/resultlistdata.cpp)
target_link_libraries(ResultListData Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui)
target_compile_definitions(ResultListData PRIVATE UNIT_TEST)

add_library(TaskListData data/tasklistdata.h data/tasklistdata.cpp)
target_link_libraries(TaskListData Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui)
target_compile_definitions(TaskListData PRIVATE UNIT_TEST)

add_library(Camera driver/camera.h driver/camera.cpp)
target_link_libraries(Camera ${OpenCV_LIBS})
target_compile_definitions(Camera PRIVATE UNIT_TEST)

add_library(Serial ${SERIALPORT_SRC})
target_compile_definitions(Serial PRIVATE UNIT_TEST)

add_library(GTU7 driver/gtu7.h driver/gtu7.cpp)
target_link_libraries(GTU7 Serial)
target_compile_definitions(GTU7 PRIVATE UNIT_TEST)

add_library(ResultListModel model/resultlistmodel.h model/resultlistmodel.cpp)
target_link_libraries(ResultListModel PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui)
target_compile_definitions(ResultListModel PRIVATE UNIT_TEST)

add_library(TaskListModel model/tasklistmodel.h model/tasklistmodel.cpp)
target_link_libraries(TaskListModel PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui)
target_compile_definitions(TaskListModel PRIVATE UNIT_TEST)

add_library(PaintItem qpaintitem.h qpaintitem.cpp)
target_link_libraries(PaintItem PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)
target_compile_definitions(PaintItem PRIVATE UNIT_TEST)

add_library(Monitor monitor.h monitor.cpp)
target_link_libraries(Monitor PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui)

set(PROJECT_SOURCES
    ${SERIALPORT_SRC}
    driver/gtu7.h driver/gtu7.cpp
    driver/camera.h driver/camera.cpp
    main.cpp
    monitor.h monitor.cpp
    qpaintitem.h qpaintitem.cpp
    data/tasklistdata.h data/tasklistdata.cpp
    data/resultlistdata.h data/resultlistdata.cpp
    model/tasklistmodel.h model/tasklistmodel.cpp
    model/resultlistmodel.h model/resultlistmodel.cpp
    algorithm/cusncnn.h algorithm/cusncnn.cpp
    ../qml.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SmartCam
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(SmartCam
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(SmartCam PUBLIC ${OpenCV_LIBS} ${NCNN_LIB}
    PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::QuickControls2
    Qt${QT_VERSION_MAJOR}::SerialPort)



install(TARGETS SmartCam
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(SmartCam)
    qt_finalize_executable(SmartCam)
endif()
