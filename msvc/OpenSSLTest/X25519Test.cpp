#include <iostream>
#include <string>

#include <openssl/evp.h>
#include <openssl/ec.h>

std::string byte_2_hex(unsigned char* pSrc, size_t length)
{
    std::string output;
    char ch[3];
    for (size_t i = 0; i < length; ++i)
    {
        sprintf_s(ch, 3, "%02x", pSrc[i]);
        output += ch;
    }
    return output;
}

int main(int argc, char* argv[]) {

    const size_t X25519_KEY_LENGTH = 32;

    // 生成我方密钥对
    EVP_PKEY* ours = EVP_PKEY_new();
    if (ours == nullptr) {
        std::cerr << "ours is nullptr" << std::endl;
        return -1;
    }
    EVP_PKEY_CTX* our_key_ctx = EVP_PKEY_CTX_new_id(NID_X25519, NULL);
    if (our_key_ctx == nullptr) {
        std::cerr << "our_key_ctx is nullptr" << std::endl;
        return -1;
    }
    if (EVP_PKEY_keygen_init(our_key_ctx) <= 0) {
        std::cerr << "EVP_PKEY_keygen_init failed" << std::endl;
        return -1;
    }
    if (EVP_PKEY_keygen(our_key_ctx, &ours) <= 0) {
        std::cerr << "EVP_PKEY_keygen failed" << std::endl;
        return -1;
    }
    EVP_PKEY_CTX_free(our_key_ctx);

    // 我方密钥对转换成unsigned char数组
    size_t ours_public_key_len = X25519_KEY_LENGTH;
    unsigned char* ours_public_key = new unsigned char[ours_public_key_len];
    EVP_PKEY_get_raw_public_key(ours, ours_public_key, &ours_public_key_len);
    printf("ours_public_key: %s\n", byte_2_hex(ours_public_key, ours_public_key_len).c_str());

    size_t ours_private_key_len = X25519_KEY_LENGTH;
    unsigned char* ours_private_key = new unsigned char[ours_public_key_len];
    EVP_PKEY_get_raw_private_key(ours, ours_private_key, &ours_private_key_len);
    printf("ours_private_key: %s\n", byte_2_hex(ours_private_key, ours_private_key_len).c_str());


    // 生成对方密钥对
    EVP_PKEY* theirs = EVP_PKEY_new();
    if (theirs == nullptr) {
        std::cerr << "theirs is nullptr" << std::endl;
        return -1;
    }
    EVP_PKEY_CTX* their_key_ctx = EVP_PKEY_CTX_new_id(NID_X25519, NULL);
    if (their_key_ctx == nullptr) {
        std::cerr << "their_key_ctx is nullptr" << std::endl;
        return -1;
    }
    if (EVP_PKEY_keygen_init(their_key_ctx) <= 0) {
        std::cerr << "EVP_PKEY_keygen_init failed" << std::endl;
        return -1;
    }
    if (EVP_PKEY_keygen(their_key_ctx, &theirs) <= 0) {
        std::cerr << "EVP_PKEY_keygen failed" << std::endl;
        return -1;
    }
    EVP_PKEY_CTX_free(their_key_ctx);

    // 对方密钥对转换成unsigned char数组
    size_t theirs_public_key_len = X25519_KEY_LENGTH;
    unsigned char* theirs_public_key = new unsigned char[theirs_public_key_len];
    EVP_PKEY_get_raw_public_key(theirs, theirs_public_key, &theirs_public_key_len);
    printf("theirs_public_key: %s\n", byte_2_hex(theirs_public_key, theirs_public_key_len).c_str());

    size_t theirs_private_key_len = X25519_KEY_LENGTH;
    unsigned char* theirs_private_key = new unsigned char[theirs_public_key_len];
    EVP_PKEY_get_raw_private_key(theirs, theirs_private_key, &theirs_private_key_len);
    printf("theirs_private_key: %s\n", byte_2_hex(theirs_private_key, theirs_private_key_len).c_str());

    EVP_PKEY* ours_recover = EVP_PKEY_new();

}

