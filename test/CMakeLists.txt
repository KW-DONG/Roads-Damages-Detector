cmake_minimum_required(VERSION 3.5)

project(SmartCam)

enable_testing()
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_definitions(-DGTEST_LANGUAGE_CXX11)

find_package(Threads REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick SerialPort)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick SerialPort)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Qml Quick QuickControls2 SerialPort REQUIRED)
find_package(OpenCV REQUIRED)

if ($ENV{GOOGLETEST_DIR})
    set(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
else ()
    if (NOT "C:/googletest" STREQUAL "")
        message(WARNING "Using googletest src dir specified at Qt Creator wizard")
    endif ()
    set(GOOGLETEST_DIR "C:/googletest")
endif ()
if (EXISTS ${GOOGLETEST_DIR})
    set(GTestSrc ${GOOGLETEST_DIR}/googletest)
    set(GMockSrc ${GOOGLETEST_DIR}/googlemock)
elseif (UNIX AND EXISTS /usr/src/gtest)
    set(GTestSrc /usr/src/gtest)
    message(WARNING "Using gtest from system")
    if (EXISTS /usr/src/gmock)
        set(GMockSrc /usr/src/gmock)
    endif ()
else ()
    message( FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
endif ()

set(GTestFiles ${GTestSrc}/src/gtest-all.cc)
set(GTestIncludes ${GTestSrc} ${GTestSrc}/include)
if (NOT ${GMockSrc} STREQUAL "")
    list(APPEND GTestFiles ${GMockSrc}/src/gmock-all.cc)
    list(APPEND GTestIncludes ${GMockSrc} ${GMockSrc}/include)
endif ()

include_directories(${GTestIncludes})
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories(../src
                    ../src/data
                    ../src/model
                    ../src/driver
                    ../qml
                    ../src/algorithm
                    ${NCNN_INCLUDE_PATH}
            )

add_executable(utest main.cpp
               gtest_camera.h
               gtest_cusncnn.h
               gtest_gtu7.h
               gtest_monitor.h
               gtest_paintitem.h
               gtest_resultlistdata.h
               gtest_resultlistmodel.h
               gtest_serial.h
               gtest_tasklistdata.h
               gtest_tasklistmodel.h
               ${GTestFiles})

target_compile_definitions(utest PRIVATE UNIT_TEST)

add_test(NAME utest COMMAND utest)
target_link_libraries(utest PRIVATE Threads::Threads
                                    CusNCNN
                                    ResultListData
                                    TaskListData
                                    Camera
                                    Serial
                                    GTU7
                                    ResultListModel
                                    TaskListModel
                                    PaintItem
                                    Monitor)

