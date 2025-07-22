cmake_minimum_required(VERSION 3.31)
project(work_shooting_simulator)

set(CMAKE_CXX_STANDARD 23)

#for downloading
include(FetchContent)

#download glm
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

#download entt
FetchContent_Declare(
        EnTT
        GIT_REPOSITORY https://github.com/skypjack/entt.git
        GIT_TAG v3.15.0
)
FetchContent_MakeAvailable(EnTT)

#download catch2
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.8.1
)
FetchContent_MakeAvailable(Catch2)

#main
add_executable(work_shooting_simulator main.cpp
        simulator/simulate.hpp
        simulator/simulate.hpp
        simulator/entt_components.hpp
        simulator/simulate.cpp
        tests/test_simulation.cpp
)

#add glm
target_include_directories(work_shooting_simulator PRIVATE ${glm_SOURCE_DIR})
#add entt
target_link_libraries(work_shooting_simulator PRIVATE EnTT)