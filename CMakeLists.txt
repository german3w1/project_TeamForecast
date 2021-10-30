cmake_minimum_required(VERSION 3.1.0)

project(TeamForecast VERSION 2.0.3 LANGUAGES CXX)

#it's required to hide app console window behind gui when app starts outside the IDE(only windows)
if (${CMAKE_SYSTEM} MATCHES "Windows")
    set(CMAKE_WIN32_EXECUTABLE ON)
endif()

set(CMAKE_CXX_STANDART 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Gui Widgets Network Core REQUIRED)

include_directories(src)

file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE QRC *.qrc)

add_executable(TeamForecast ${SOURCES} ${HEADERS} ${QRC})

target_link_libraries(TeamForecast PRIVATE Qt6::Network Qt6::Gui Qt6::Core Qt6::Widgets)
