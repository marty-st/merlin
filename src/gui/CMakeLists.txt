set(THIS_TARGET_NAME gui)

add_library(${THIS_TARGET_NAME}
            ./include/gui/gui.hpp

            ./src/fps.cpp
            
            ./src/render.cpp
            )
