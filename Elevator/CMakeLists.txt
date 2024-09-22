enable_language(RC)

file(GLOB CPP_ITEM "${CMAKE_CURRENT_SOURCE_DIR}/*cpp")
file(GLOB H_ITEM "${CMAKE_CURRENT_SOURCE_DIR}/*h")
file(GLOB RC_ITEM "${CMAKE_CURRENT_SOURCE_DIR}/*rc")

add_executable (Elevator WIN32 ${CPP_ITEM} ${H_ITEM} ${RC_ITEM})

# 1: static MFC library, 2: shared MFC library
set(CMAKE_MFC_FLAG 2)
add_definitions(-D_AFXDLL)

target_link_options(Elevator PRIVATE /ENTRY:WinMainCRTStartup)
