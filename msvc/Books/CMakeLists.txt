find_package(unofficial-libmysql CONFIG REQUIRED)

add_executable (Books books.cpp)

target_link_libraries(Books PRIVATE unofficial::libmysql::libmysql)

target_compile_options(Books
        PRIVATE
        "$<$<CXX_COMPILER_ID:MSVC>:/Zc:strictStrings->"
)

