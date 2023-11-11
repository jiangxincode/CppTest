#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>
#define AES_BITS 128
#define MSG_LEN 128

int aes_encrypt(char* in, AES_KEY aes, char* out)//, int olen)���ܻ�����buf����
{
	
	unsigned char iv[AES_BLOCK_SIZE];//���ܵĳ�ʼ������
	for (int i = 0; i < AES_BLOCK_SIZE; ++i) {
		iv[i] = 0;
	}
	
	int len = strlen(in);//����ĳ�����char*in�ĳ��ȣ��������in�м����'\0'�ַ��Ļ�

	//��ô��ֻ�����ǰ��'\0'ǰ���һ�Σ����ԣ����len������Ϊ��������������¼in�ĳ���

	//���ڽ���Ҳ��һ����������'\0'���ж��ַ������ȣ�ȷ�в��ף����涼��һ������
	AES_cbc_encrypt((unsigned char*)in, (unsigned char*)out, len, &aes, iv, AES_ENCRYPT);
	return 1;
}
int aes_decrypt(char* in, AES_KEY aes, char* out)
{
	
	unsigned char iv[AES_BLOCK_SIZE];//���ܵĳ�ʼ������
	for (int i = 0; i < AES_BLOCK_SIZE; ++i)//ivһ������Ϊȫ0,�����������������Ǽ��ܽ���Ҫһ������
		iv[i] = 0;
	
	int len = strlen(in);
	AES_cbc_encrypt((unsigned char*)in, (unsigned char*)out, len, &aes, iv, AES_DECRYPT);
	return 1;
}

int main_AES_cbc_Test(int argc, char* argv[])
{
	char plainText[MSG_LEN];
	char encryptText[MSG_LEN];
	char key[AES_BLOCK_SIZE];
	unsigned char iv[AES_BLOCK_SIZE];

	memset((char*)plainText, 0, MSG_LEN);
	memset((char*)encryptText, 0, MSG_LEN);
	memset(key, 0, AES_BLOCK_SIZE);
	memset((unsigned char*)iv, 0, AES_BLOCK_SIZE);

	strcpy_s((char*)plainText, MSG_LEN, "hello world ssss");

	AES_KEY aes;
	if (AES_set_encrypt_key((unsigned char*)key, AES_BLOCK_SIZE * 8, &aes) < 0)
	{
		perror("AES_set_encrypt_key failed");
		return 0;
	}

	printf("plainText: ");
	for (int i = 0; plainText[i]; i++) {
		printf("%x", (unsigned char)plainText[i]);
	}
	printf("\n");

	printf("key: ");
	for (int i = 0; i < AES_BLOCK_SIZE; i++) {
		printf("%x", (unsigned char)key[i]);
	}
	printf("\n");

	printf("iv: ");
	for (int i = 0; i < AES_BLOCK_SIZE; i++) {
		printf("%x", (unsigned char)iv[i]);
	}
	printf("\n");

	AES_cbc_encrypt((unsigned char*)plainText, (unsigned char*)encryptText, 16, &aes, iv, AES_ENCRYPT);

	printf("encryptText: ");
	for (int i = 0; encryptText[i]; i++) {
		printf("%x", (unsigned char)encryptText[i]);
	}
	printf("\n");

	memset((char*)plainText, 0, MSG_LEN);
	AES_cbc_encrypt((unsigned char*)encryptText, (unsigned char*)plainText, strlen(encryptText), &aes, iv, AES_DECRYPT);

	printf("plainText: ");
	for (int i = 0; plainText[i]; i += 1) {
		printf("%x", (unsigned char)plainText[i]);
	}
	printf("\n");

	return 0;
}