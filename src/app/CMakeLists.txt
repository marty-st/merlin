set(THIS_TARGET_NAME Merlin)

add_executable(${THIS_TARGET_NAME} 
               ./src/main.cpp

               ./include/app/engine.hpp
               ./src/engine.cpp
               )

target_link_libraries(${THIS_TARGET_NAME}
                      ${MERLIN_LIBRARIES_TO_LINK_WITH}
                      ${MERLIN_EXTERNAL_LIBRARIES_TO_LINK_WITH})
