cmake_minimum_required(VERSION 3.5)

project(Group28_AMNEsIAGames VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        #UI
        src/main.cpp
        src/mainwindow.cpp
        include/mainwindow.h
        src/mainwindow.ui

        src/loginwindow.cpp
        include/loginwindow.h
        src/loginwindow.ui

        src/createuserform.cpp
        include/createuserform.h
        src/createuserform.ui

        src/gamesearchform.cpp
        include/gamesearchform.h
        src/gamesearchform.ui

        #Source code
        src/login_handler.cpp
        include/login_handler.h

        src/database.cpp
        include/database.h
        include/sqlite3.h
        #src/amnesiaGames.db

        src/GameList.cpp
        include/GameList.h
        src/Game.cpp
        include/Game.h

        src/pass_protect.cpp
        include/pass_protect.h
        src/User.cpp
        include/User.h

        src/Subject.cpp
        include/Subject.h
        include/Observer.h
        src/ListObserver.cpp
        include/ListObserver.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Group28_AMNEsIAGames
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Group28_AMNEsIAGames APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Group28_AMNEsIAGames SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Group28_AMNEsIAGames
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(
    Group28_AMNEsIAGames PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    sqlite3
)

set_target_properties(Group28_AMNEsIAGames PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Group28_AMNEsIAGames
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Group28_AMNEsIAGames)
endif()

