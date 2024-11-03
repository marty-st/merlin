set(THIS_TARGET_NAME osi)

add_library(${THIS_TARGET_NAME}
            ./include/osi/run.hpp
            ./src/run.cpp
            
            ./include/osi/sdl.hpp
            ./src/sdl.cpp

            ./include/osi/imgui.hpp
            ./src/imgui.cpp

            ./include/osi/application.hpp
            ./src/application.cpp

            ./include/osi/config.hpp

            ./include/osi/gui.hpp

            ./include/osi/keyboard.hpp

            ./include/osi/mouse.hpp

            ./include/osi/opengl.hpp

            ./include/osi/stb_image.h

            ./include/osi/timer.hpp
            
            ./include/osi/window.hpp
            )
