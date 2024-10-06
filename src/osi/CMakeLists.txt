set(THIS_TARGET_NAME osi)

add_library(${THIS_TARGET_NAME}
            ./include/osi/run.hpp
            ./src/run.cpp
            
            ./include/osi/sdl.hpp
            ./src/sdl.cpp
            )