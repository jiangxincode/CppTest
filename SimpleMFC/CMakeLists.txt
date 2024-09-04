enable_language(RC)

aux_source_directory(. DIR_SRCS)
add_executable (SimpleMFC WIN32 "SimpleMFC.cpp" "SimpleMFC.h" "SimpleMFC.rc" "MainFrm.cpp" "MainFrm.h" "ChildView.cpp" "ChildView.h" "framework.h" "Resource.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SimpleMFC PROPERTY CXX_STANDARD 20)
endif()

# 1: static MFC library, 2: shared MFC library
set(CMAKE_MFC_FLAG 2)
add_definitions(-D_UNICODE)
add_definitions(-DUNICODE)
add_definitions(-D_AFXDLL)

target_link_options(SimpleMFC PRIVATE /ENTRY:wWinMainCRTStartup)
