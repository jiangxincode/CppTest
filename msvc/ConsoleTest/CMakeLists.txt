﻿file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
foreach(source ${sources})
    get_filename_component(program ${source} NAME_WE)
    add_executable(${program} ${source})
endforeach()
