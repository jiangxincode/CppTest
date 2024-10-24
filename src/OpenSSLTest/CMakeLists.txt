find_package(OpenSSL REQUIRED)

add_executable(AES_Test AES_Test.cpp)
add_executable(AES_cbc_Test AES_cbc_Test.cpp)
add_executable(X25519Test X25519Test.cpp)

target_link_libraries(AES_Test PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(AES_cbc_Test PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(X25519Test PRIVATE OpenSSL::SSL OpenSSL::Crypto)
