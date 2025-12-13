cmake_minimum_required(VERSION 3.16)

project(Calculator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Multimedia MultimediaWidgets)

set(PROJECT_SOURCES
    main.cpp
    logindialog.cpp
    logindialog.h
    calculatorwindow.cpp
    calculatorwindow.h
)

add_executable(Calculator ${PROJECT_SOURCES})

target_link_libraries(Calculator PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Multimedia
    Qt5::MultimediaWidgets
)
