cmake_minimum_required(VERSION 3.5)

project(SmartCalc_Front VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(../SmartCalcBack/)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        plot.cpp
        plot.h
        plot.ui
        qcustomplot.cpp
        qcustomplot.h
)

set(C_SOURCES
    smart_calc.h
    smart_calc.c
    list_operations/list.h
    list_operations/free_list.c
    list_operations/peep.c
    list_operations/pop.c
    list_operations/push.c
    list_operations/reverse_list.c
    operation_functions/operation_functions.h
    operation_functions/calculate_station.c
    operation_functions/parser.c
    operation_functions/validator.c
)
list(TRANSFORM C_SOURCES PREPEND "../SmartCalcBack/")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SmartCalcFront
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${C_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SmartCalcFront APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SmartCalcFront SHARED
            ${PROJECT_SOURCES}
            ${C_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SmartCalcFront
            ${PROJECT_SOURCES}
            ${C_SOURCES}
        )
    endif()
endif()

target_link_libraries(SmartCalcFront PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(SmartCalcFront PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS SmartCalcFront
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SmartCalcFront)
endif()
