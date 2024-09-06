find_package(libmysql CONFIG REQUIRED)

add_executable (Books "books.cpp")

target_link_libraries(Books PRIVATE libmysql)

