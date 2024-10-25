enable_language(RC)

file(GLOB CPP_ITEM "${CMAKE_CURRENT_SOURCE_DIR}/*cpp")
file(GLOB H_ITEM "${CMAKE_CURRENT_SOURCE_DIR}/*h")
file(GLOB RC_ITEM "${CMAKE_CURRENT_SOURCE_DIR}/*rc")

add_executable (BthCxn WIN32 ${CPP_ITEM} ${H_ITEM} ${RC_ITEM})

set(CMAKE_MFC_FLAG 2)

add_definitions(-D_UNICODE)
add_definitions(-DUNICODE)
add_definitions(-D_AFXDLL)

target_link_options(BthCxn PRIVATE /ENTRY:wmainCRTStartup)

target_link_libraries(BthCxn Ws2_32)

target_compile_options(BthCxn
        PRIVATE
        "$<$<CXX_COMPILER_ID:MSVC>:/Zc:strictStrings->"
)