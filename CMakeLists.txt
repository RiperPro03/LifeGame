cmake_minimum_required(VERSION 3.29)
project(LifeGame)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)


set(CMAKE_CXX_STANDARD 20)

add_executable(LifeGame main.cpp
        Controller/Controller.cpp
        Controller/Controller.h
        Model/Cell/Cell.cpp
        Model/Cell/Cell.h
        Model/Grid/Grid.cpp
        Model/Grid/Grid.h
        Model/Game/Game.cpp
        Model/Game/Game.h
        View/ConsoleView/ConsoleView.cpp
        View/ConsoleView/ConsoleView.h
        View/GraphicView/GraphicView.cpp
        View/GraphicView/GraphicView.h)

target_link_libraries(LifeGame sfml-graphics sfml-window sfml-system)