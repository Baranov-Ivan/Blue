
cmake_minimum_required(VERSION 3.1.0)

project(client)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(graph
    mainwindow.ui
    mainwindow.cpp
    main.cpp
    edge.cpp
    graphwidget.cpp
    node.cpp
    sockettest.cpp
    parser.cpp
    dijkstrasalg.cpp
)

target_link_libraries(graph Qt5::Network)
target_link_libraries(graph Qt5::Widgets)
target_link_libraries(graph Qt5::Core)
target_link_libraries(graph Qt5::Gui)