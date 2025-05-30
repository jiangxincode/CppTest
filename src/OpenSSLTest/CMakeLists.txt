find_package(OpenSSL REQUIRED)

add_executable(AES_Test AES_Test.cpp)
target_compile_options(AES_Test
        PRIVATE
        "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>"
)
target_link_libraries(AES_Test PRIVATE OpenSSL::SSL OpenSSL::Crypto)


add_executable(AES_cbc_Test AES_cbc_Test.cpp)
target_compile_options(AES_cbc_Test
        PRIVATE
        "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>"
)
target_link_libraries(AES_cbc_Test PRIVATE OpenSSL::SSL OpenSSL::Crypto)

add_executable(X25519Test X25519Test.cpp)
target_compile_options(X25519Test
        PRIVATE
        "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>"
)
target_link_libraries(X25519Test PRIVATE OpenSSL::SSL OpenSSL::Crypto)
