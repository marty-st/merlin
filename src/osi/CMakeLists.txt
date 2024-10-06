set(THIS_TARGET_NAME osi)

add_library(${THIS_TARGET_NAME}
            ./include/osi/sdl.hpp
            ./src/sdl.cpp
            )