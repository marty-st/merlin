include_directories(
    "${PROJECT_SOURCE_DIR}/src/app/include"
    "${PROJECT_SOURCE_DIR}/src/common/include"
    "${PROJECT_SOURCE_DIR}/src/file/include"
    "${PROJECT_SOURCE_DIR}/src/graphics/include"
    "${PROJECT_SOURCE_DIR}/src/gui/include"
    "${PROJECT_SOURCE_DIR}/src/osi/include"
    "${PROJECT_SOURCE_DIR}/src/physics/include"
    "${PROJECT_SOURCE_DIR}/src/util/include"
    )

set(MERLIN_LIBRARIES_TO_LINK_WITH
    # app # is executable
    common
    file
    graphics
    gui
    osi
    physics
    util
    )

message("Including the following libraries to the build:")
add_subdirectory(./common)
message("-- common")
add_subdirectory(./file)
message("-- file")
add_subdirectory(./graphics)
message("-- graphics")
add_subdirectory(./gui)
message("-- gui")
add_subdirectory(./osi)
message("-- osi")
add_subdirectory(./physics)
message("-- physics")
add_subdirectory(./util)
message("-- util")

message("Including the following executables to the build:")
add_subdirectory(./app)
message("-- app")
