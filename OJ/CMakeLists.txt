find_package(CppUnit CONFIG REQUIRED)

get_filename_component(CppUnit_INCLUDE_DIR_NEW "${CppUnit_INCLUDE_DIR}" PATH)

include_directories(${CppUnit_INCLUDE_DIR_NEW})

message("CppUnit_INCLUDE_DIR_NEW: ${CppUnit_INCLUDE_DIR_NEW}")

file(GLOB ITEMS "${CMAKE_CURRENT_SOURCE_DIR}/*")

foreach(ITEM ${ITEMS})
  if(IS_DIRECTORY ${ITEM})
    get_filename_component(ITEM_NAME "${ITEM}" NAME)
    message("ITEM_NAME: ${ITEM_NAME}")
    file(GLOB_RECURSE SOURCE_DIR "${ITEM_NAME}/*.cpp")
    add_executable(${ITEM_NAME} ${SOURCE_DIR})
    target_link_libraries(${ITEM_NAME} PRIVATE CppUnit)
  endif()
endforeach()
