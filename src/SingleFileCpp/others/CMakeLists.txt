file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
foreach(source ${sources})
    get_filename_component(program ${source} NAME_WE)
    add_executable(${program} ${source})
    target_compile_options(${program}
            PRIVATE
            "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>"
            "$<$<CXX_COMPILER_ID:MSVC>:/Zc:strictStrings->"
    )
    IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
        target_link_libraries(${program} m)
    ENDIF (CMAKE_SYSTEM_NAME MATCHES "Linux")
endforeach()