find_package(unofficial-libmysql CONFIG REQUIRED)

add_executable (Books "books.cpp")

target_link_libraries(Books PRIVATE unofficial::libmysql::libmysql)

