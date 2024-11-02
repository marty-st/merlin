set(THIS_TARGET_NAME graphics)

add_library(${THIS_TARGET_NAME}
            ./include/graphics/graphical_object.hpp
            ./src/graphical_object.cpp

            ./include/graphics/light_object.hpp
            ./src/light_object.cpp
            
            ./include/graphics/material.hpp
            ./src/material.cpp
            
            ./include/graphics/mesh.hpp
            ./src/mesh.cpp
            
            ./include/graphics/ogl_bo.hpp
            ./src/ogl_bo.cpp
            
            ./include/graphics/camera_object.hpp

            ./include/graphics/ebo.hpp

            ./include/graphics/light_object.hpp

            ./include/graphics/texture.hpp
            ./src/texture.cpp

            ./include/graphics/vao.hpp

            ./include/graphics/vbo.hpp
        )
