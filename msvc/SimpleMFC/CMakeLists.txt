﻿enable_language(RC)

file(GLOB CPP_ITEM "${CMAKE_CURRENT_SOURCE_DIR}/*cpp")
file(GLOB H_ITEM "${CMAKE_CURRENT_SOURCE_DIR}/*h")
file(GLOB RC_ITEM "${CMAKE_CURRENT_SOURCE_DIR}/*rc")

add_executable (SimpleMFC WIN32 ${CPP_ITEM} ${H_ITEM} ${RC_ITEM})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SimpleMFC PROPERTY CXX_STANDARD 20)
endif()

# 1: static MFC library, 2: shared MFC library
set(CMAKE_MFC_FLAG 2)
add_definitions(-D_UNICODE)
add_definitions(-DUNICODE)
add_definitions(-D_AFXDLL)

target_link_options(SimpleMFC PRIVATE /ENTRY:wWinMainCRTStartup)
