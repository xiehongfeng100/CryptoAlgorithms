#include <stdio.h>
#include "AES.h"

int main()
{
	// Key
	uchar key[16] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
	uchar plain[] = "If you do not learn to think when you are young, you may never learn."; 
	uint len = sizeof(plain) / sizeof(uchar);

	printf("------------------------------- Initialization -------------------------------\n");
	printf("Length of plain text = %d\n", len);
	printf("Plain text : ");
	for (int i = 0; i < len; i++)
	{
		printf("%c", plain[i]);
	}
	printf("\n");

	printf("------------------------------- Encryption -------------------------------\n");
	uchar * cipher = Cipher(&len, plain, key);
	printf("Length of encryted text = %d\n", len);
	printf("Encrypted text : ");
	for (int i = 0; i < len; i++)
	{
		printf("%c", cipher[i]);
	}
	printf("\n");

	printf("------------------------------- Decryption -------------------------------\n");
	uchar * outText = InvCipher(&len, cipher, key);
	printf("Length of decrypted text = %d\n", len);
	printf("Decrypted text : ");
	for (int i = 0; i < len; i++)
	{
		printf("%c", outText[i]);
	}
	printf("\n");

	return 0;
}