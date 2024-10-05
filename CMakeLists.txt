cmake_minimum_required(VERSION 3.26)

project(Merlin)

find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(Merlin main.cpp)

target_link_libraries(Merlin
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
target_link_libraries(Merlin PRIVATE glad::glad)
target_link_libraries(Merlin PRIVATE glm::glm)
target_link_libraries(Merlin PRIVATE imgui::imgui)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)