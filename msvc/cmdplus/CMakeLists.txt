add_executable (cmdplus "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET cmdplus PROPERTY CXX_STANDARD 20)
endif()
