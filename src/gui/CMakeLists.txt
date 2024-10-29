set(THIS_TARGET_NAME gui)

add_library(${THIS_TARGET_NAME}
            ./include/gui/gui.hpp
            ./src/gui.cpp

            ./include/gui/engine_gui.hpp
            ./src/engine_gui.cpp
            )
