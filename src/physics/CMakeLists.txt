set(THIS_TARGET_NAME physics)

add_library(${THIS_TARGET_NAME}
            ./include/physics/physical_object.hpp
            ./src/physical_object.cpp
            )
