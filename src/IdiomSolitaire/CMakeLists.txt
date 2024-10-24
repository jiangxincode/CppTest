add_executable(IdiomSolitaire
        main.c
        tailor.h
        getopt.h
        getopt.c)

target_compile_options(IdiomSolitaire
        PRIVATE
        "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>"
)

add_custom_command(TARGET IdiomSolitaire  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/idiom.txt
        $<TARGET_FILE_DIR:IdiomSolitaire>)