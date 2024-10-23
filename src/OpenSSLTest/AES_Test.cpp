#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>
#define AES_BITS 128
#define MSG_LEN 128

int aes_encrypt(char* in, char* key, char* out)//, int olen)
{
	if (!in || !key || !out) return 0;
	AES_KEY aes;
	if (AES_set_encrypt_key((unsigned char*)key, 128, &aes) < 0)
	{
		return 0;
	}
	int len = strlen(in), en_len = 0;
	while (en_len < len)//输入输出字符串够长，并且是AES_BLOCK_SIZE的整数倍，需要严格限制
	{
		AES_encrypt((unsigned char*)in, (unsigned char*)out, &aes);
		in += AES_BLOCK_SIZE;
		out += AES_BLOCK_SIZE;
		en_len += AES_BLOCK_SIZE;
	}
	return 1;
}
int aes_decrypt(char* in, char* key, char* out)
{
	if (!in || !key || !out) return 0;
	AES_KEY aes;
	if (AES_set_decrypt_key((unsigned char*)key, 128, &aes) < 0)
	{
		return 0;
	}
	int len = strlen(in), en_len = 0;
	while (en_len < len)
	{
		AES_decrypt((unsigned char*)in, (unsigned char*)out, &aes);
		in += AES_BLOCK_SIZE;
		out += AES_BLOCK_SIZE;
		en_len += AES_BLOCK_SIZE;
	}
	return 1;
}

int main(int argc, char* argv[])
{
	char srcStringTemp[MSG_LEN];
	char dstStringTemp[MSG_LEN];
	memset((char*)srcStringTemp, 0, MSG_LEN);
	memset((char*)dstStringTemp, 0, MSG_LEN);
	strcpy((char*)srcStringTemp, "hello world");
	printf("%s\n", srcStringTemp);

	char key[AES_BLOCK_SIZE];
	for (int i = 0; i < AES_BLOCK_SIZE; i++)//可自由设置密钥
	{
		key[i] = 32 + i;
	}
	if (!aes_encrypt(srcStringTemp, key, dstStringTemp))
	{
		printf("encrypt error\n");
		return -1;
	}
	for (int i = 0; dstStringTemp[i]; i++) {
		printf("%x", (unsigned char)dstStringTemp[i]);
	}
	printf("\n");
	memset((char*)srcStringTemp, 0, MSG_LEN);
	if (!aes_decrypt(dstStringTemp, key, srcStringTemp))
	{
		printf("decrypt error\n");
		return -1;
	}
	printf("%s\n", srcStringTemp);
	for (int i = 0; srcStringTemp[i]; i += 1) {
		printf("%x", (unsigned char)srcStringTemp[i]);
	}
	printf("\n");
	return 0;
}