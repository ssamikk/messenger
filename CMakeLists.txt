cmake_minimum_required (VERSION 3.8)

project (messenger)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(messenger_SRCS
    src/main.cpp
    src/client.h
    src/client.cpp
    src/client.ui
    src/server.h
    src/server.cpp
    src/messenger.h
    src/messenger.cpp
    src/message.h
    src/message.cpp
    )

add_executable (${PROJECT_NAME} WIN32 ${messenger_SRCS})

target_link_libraries(${PROJECT_NAME} ${Qt5Widgets_LIBRARIES})
