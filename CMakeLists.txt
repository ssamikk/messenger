cmake_minimum_required (VERSION 3.8)

project (messenger)

IF(NOT DEFINED Qt5Core_DEFINITIONS)
        find_package(Qt5 COMPONENTS Widgets REQUIRED)
ENDIF()

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

set(messenger_SRCS
    src/main.cpp
    src/client.h
    src/client.cpp
    src/client.ui
    src/server.h
    src/server.cpp
    src/messenger.h
    src/messenger.cpp
    )

add_executable (${PROJECT_NAME} ${messenger_SRCS})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
