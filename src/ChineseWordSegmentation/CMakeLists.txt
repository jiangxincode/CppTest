add_executable(ChineseWordSegmentation
        ChineseWordSegmentation.cpp)

target_compile_options(ChineseWordSegmentation
        PRIVATE
        "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>"
)

add_custom_command(TARGET ChineseWordSegmentation POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/article.txt
        $<TARGET_FILE_DIR:ChineseWordSegmentation>)

add_custom_command(TARGET ChineseWordSegmentation POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/word.txt
        $<TARGET_FILE_DIR:ChineseWordSegmentation>)