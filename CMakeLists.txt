cmake_minimum_required(VERSION 3.26)

project(Merlin)

find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

set(MERLIN_EXTERNAL_LIBRARIES_TO_LINK_WITH
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    glad::glad
    glm::glm
    imgui::imgui
    )

set(MERLIN_VCPKG_INCLUDE_DIR "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include")
include_directories(${MERLIN_VCPKG_INCLUDE_DIR})
# target_link_libraries(Merlin
#     PRIVATE
#     $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
#     $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
# )
# target_link_libraries(Merlin PRIVATE glad::glad)
# target_link_libraries(Merlin PRIVATE glm::glm)
# target_link_libraries(Merlin PRIVATE imgui::imgui)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(./src)