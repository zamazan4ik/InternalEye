cmake_minimum_required(VERSION 2.8)
project(InternalEye)


add_definitions(-std=c++14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

include_directories(
        ${CMAKE_SOURCE_DIR}/headers
        ${CMAKE_SOURCE_DIR}/headers/gui
)

set(HEADERS
    headers/Computer.h
    headers/Application.h
    headers/Network.h
    headers/Devices.h
    headers/DateDifference.h
    headers/Constants.h
    headers/Vendor.h
    headers/Benchmarks.h
    headers/Util.h
    headers/cpu.h

    headers/gui/MenuBar.h
    headers/gui/MainWindow.h
)

set(SOURCES
    src/Application.cpp
    src/cpu.cpp
    src/DateDifference.cpp
    src/main.cpp
    src/Util.cpp
    src/Vendor.cpp

    src/gui/MainWindow.cpp
    src/gui/MenuBar.cpp

    src/modules/benchmark/Benchmarks.cpp

    src/modules/computer/Boot.cpp
    src/modules/computer/Computer.cpp
    src/modules/computer/DevTools.cpp
    src/modules/computer/DisplayInfo.cpp
    src/modules/computer/Filesystem.cpp
    src/modules/computer/Group.cpp
    src/modules/computer/Language.cpp
    src/modules/computer/LoadInfo.cpp
    src/modules/computer/MemoryInfo.cpp
    src/modules/computer/OperatingSystem.cpp
    src/modules/computer/UptimeInfo.cpp
    src/modules/computer/User.cpp

    src/modules/devices/Devices.cpp
    src/modules/devices/InputDevices.cpp
    src/modules/devices/Module.cpp

    src/modules/network/Network.cpp
)



add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

qt5_use_modules(${PROJECT_NAME} Widgets Core Gui)
