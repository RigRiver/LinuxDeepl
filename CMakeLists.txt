cmake_minimum_required(VERSION 3.16)

project(LinuxDeepl VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network TextToSpeech)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

qt_add_executable(LinuxDeepl
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(LinuxDeepl PRIVATE
    Qt6::Widgets
    Qt6::Network
    Qt6::TextToSpeech
)

qt_finalize_executable(LinuxDeepl)