cmake_minimum_required(VERSION 3.16)

project(LinuxDeepl VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)     # generiert ui_mainwindow.h aus mainwindow.ui

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

target_link_libraries(LinuxDeepl PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(LinuxDeepl PRIVATE Qt6::Network Qt6::TextToSpeech)

set_target_properties(LinuxDeepl PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS LinuxDeepl
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(LinuxDeepl)
endif()
