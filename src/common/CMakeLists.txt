set(THIS_TARGET_NAME common)

add_library(${THIS_TARGET_NAME}
            ./include/common/object.hpp
            ./src/object.cpp

            ./include/common/frame.hpp
            ./src/frame.cpp
            )
