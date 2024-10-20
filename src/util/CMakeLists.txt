set(THIS_TARGET_NAME util)

add_library(${THIS_TARGET_NAME}
            ./include/util/math.hpp
            ./include/util/assumption.hpp
            ./include/util/fail_message.hpp

            ./src/fail_message.cpp
            )
