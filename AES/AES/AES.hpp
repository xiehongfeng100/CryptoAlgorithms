#ifndef AES_H
#define AES_H

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

typedef unsigned char uchar;
typedef unsigned int uint;

class AES
{
public:
	AES();
	virtual ~AES();
	uchar * Cipher(uint & length, uchar * cipher, uchar * key);
	uchar * InvCipher(uint & length, uchar * cipher, uchar * key);

public:
	// key expansion
	void KeyExpansion(uchar * key);

	// encrypt
	void SubBytes(uchar state[][4]);
	void ShiftRows(uchar state[][4]);
	void MixColumns(uchar state[][4]);
	void AddRoundKey(uchar state[][4], uchar key[][4]);

	// decrypt
	void InvSubBytes(uchar state[][4]);
	void InvShiftRows(uchar state[][4]);
	void InvMixColumns(uchar state[][4]);

	// to check Key
	friend uchar * retRoundKey(uint round, const AES & retKey);

private:
	uchar SBox[256];
	uchar InvSBox[256];
	uchar exdKey[11][4][4];

	// Round constant
	uchar Rcon[10];

	// key expansion
	void RotWord(uchar key[][4]);
	void SubWord(uchar key[][4]);

	// encrypt
	uchar * encrypt(uchar * cipher, uchar * key);

	// decrypt
	uchar * decrypt(uchar * cipher, uchar * key);

	// finite field multiplication
	uchar XTime(uchar x);
	uchar FFmul(uchar a, uchar b);

};

AES::AES()
{
	uchar sBox[] =
	{ /* 0	   1     2     3     4     5     6     7     8     9     a     b     c     d     e     f  */
		0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, /*0*/
		0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, /*1*/
		0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, /*2*/
		0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, /*3*/
		0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, /*4*/
		0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, /*5*/
		0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, /*6*/
		0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, /*7*/
		0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, /*8*/
		0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, /*9*/
		0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, /*a*/
		0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, /*b*/
		0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, /*c*/
		0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, /*d*/
		0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, /*e*/
		0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16  /*f*/
	};

	uchar invsBox[256] =
	{ /*  0    1     2     3     4     5     6     7     8     9     a     b     c     d     e     f  */
		0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb, /*0*/
		0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, /*1*/
		0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e, /*2*/
		0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25, /*3*/
		0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, /*4*/
		0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84, /*5*/
		0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06, /*6*/
		0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, /*7*/
		0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73, /*8*/
		0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e, /*9*/
		0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, /*a*/
		0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4, /*b*/
		0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f, /*c*/
		0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef, /*d*/
		0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61, /*e*/
		0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d  /*f*/
	};

	uchar rcon[10] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };

	memcpy(SBox, sBox, 256);
	memcpy(InvSBox, invsBox, 256);
	memcpy(Rcon, rcon, 10);

	// exdKey[10][3][3] = {};

}

AES::~AES()
{

}

/******************************** Key Expansion ********************************/
void AES::RotWord(uchar key[][4])
{
	uchar temp[4];
	for (int r = 0; r < 4; r++)
	{
		temp[r] = key[r][0];
	}

	for (int r = 0; r < 4; r++)
	{
		key[r][0] = temp[(r + 1) % 4];
	}

}

void AES::SubWord(uchar key[][4])
{
	// RotWord(key);
	for (int r = 0; r < 4; r++)
	{
		key[r][0] = SBox[key[r][0]];
	}
}

void AES::KeyExpansion(uchar * key)
{
	for (int c = 0; c < 4; c++)
	{
		for (int r = 0; r < 4; r++)
		{
			exdKey[0][r][c] = key[c * 4 + r];
		}
	}

	for (int round = 1; round < 11; round++)
	{
		for (int c = 0; c < 4; c++)
		{
			if (c == 0)
			{
				for (int r = 0; r < 4; r++)
				{
					exdKey[round][r][0] = exdKey[round - 1][r][3];
				}
				RotWord(exdKey[round]);
				SubWord(exdKey[round]);
				
				for (int r = 0; r < 4; r++)
				{
					if (r == 0)
					{
						exdKey[round][r][0] = exdKey[round][r][0] ^ exdKey[round - 1][r][0] ^ Rcon[round - 1];
					}
					else
					{
						exdKey[round][r][0] = exdKey[round][r][0] ^ exdKey[round - 1][r][0];
					}
				}

			}
			else
			{
				for (int r = 0; r < 4; r++)
				{
					exdKey[round][r][c] = exdKey[round][r][c - 1] ^ exdKey[round - 1][r][c];
				}
			}
		}
	}
}

uchar * retRoundKey(uint round, const AES & retKey)
{
	uchar * ret = new uchar[16];
	for (int c = 0; c < 4; c++)
	{
		for (int r = 0; r < 4; r++)
		{
			ret[c * 4 + r] = (retKey.exdKey[round])[r][c];
		}
	}
	return ret;
}

/********************************* Encryption *********************************/

uchar * AES::Cipher(uint & length, uchar * text, uchar * key)
{
	KeyExpansion(key);
	uint divide = length / 16;
	uint remain = length % 16;
	uint padNum = 0;
	if (remain != 0)
	{
		padNum = 16 - remain;
		divide++;
	}

	uchar * cipher = new uchar[divide * 16];
	// uchar bk[32];
	for (int i = 0; i < divide; i++)
	{
		uchar temp[16];
		for (int j = 0; j < 16; j++)
		{
			if ((i * 16 + j) < length)
			{
				temp[j] = text[i * 16 + j];
			}
			else
			{
				// follow padding standard ANSI X.923 :http://en.wikipedia.org/wiki/Padding_(cryptography)
				if (j == 15)
				{
					temp[j] = padNum;
				}
				else
				{
					temp[j] = 0;
				}
			}
		}

		uchar * out = encrypt(temp, key);
		for (int j = 0; j < 16; j++)
		{
			cipher[i * 16 + j] = out[j];
			// bk[i * 16 + j] = out[j];
		}
		delete out;
	}

	length = divide * 16;
	return cipher;
}

uchar * AES::encrypt(uchar * text, uchar * key)
{
	uchar roundState[4][4];
	uchar roundKey[4][4];

	for (int c = 0; c < 4; c++)
	{
		for (int r = 0; r < 4; r++)
		{
			roundState[r][c] = text[c * 4 + r];
			roundKey[r][c] = key[c * 4 + r];
		}
	}

	AddRoundKey(roundState, roundKey);
	for (int i = 1; i < 10; i++)
	{
		SubBytes(roundState);
		ShiftRows(roundState);
		MixColumns(roundState);
		AddRoundKey(roundState, exdKey[i]);
	}
	SubBytes(roundState);
	ShiftRows(roundState);
	AddRoundKey(roundState, exdKey[10]);

	// uchar ret[16];
	uchar * ret = new uchar[16];
	for (int c = 0; c < 4; c++)
	{
		for (int r = 0; r < 4; r++)
		{
			ret[c * 4 + r] = roundState[r][c];
		}
	}

	return ret;
}

void AES::SubBytes(uchar state[][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			state[i][j] = SBox[state[i][j]];
		}
	}
}

void AES::ShiftRows(uchar state[][4])
{
	uchar temp[4];
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			temp[c] = state[r][(c + r) % 4];
		}
		for (int c = 0; c < 4; c++)
		{
			state[r][c] = temp[c];
		}
	}
}

// Ref: http://blog.chinaunix.net/uid-20680669-id-3194364.html
void AES::MixColumns(uchar state[][4])
{
	uchar temp[4];
	for (int c = 0; c < 4; c++)
	{
		for (int r = 0; r < 4; r++)
		{
			temp[r] = state[r][c];
		}
		for (int r = 0; r < 4; r++)
		{
			state[r][c] = FFmul(0x02, temp[r])
				^ FFmul(0x03, temp[(r + 1) % 4])
				^ FFmul(0x01, temp[(r + 2) % 4])
				^ FFmul(0x01, temp[(r + 3) % 4]);
		}
	}
}

// Ref of XTime & FFmul: http://blog.csdn.net/bupt073114/article/details/27382533
uchar AES::XTime(uchar x)
{
	return ((x << 1) ^ ((x & 0x80) ? 0x1b : 0x00));
}

uchar AES::FFmul(uchar a, uchar b)
{
	uchar temp[8] = { a };
	uchar tempmultiply = 0x00;
	int i = 0;
	for (i = 1; i < 8; i++)
	{
		temp[i] = XTime(temp[i - 1]);
	}

	tempmultiply = (b & 0x01) * a;
	for (i = 1; i <= 7; i++) 
	{
		tempmultiply ^= (((b >> i) & 0x01)* temp[i]);
	}
	return tempmultiply;
}

void AES::AddRoundKey(uchar state[][4], uchar key[][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			state[i][j] ^= key[i][j];
		}
	}

}

/********************************* Decryption *********************************/
uchar * AES::InvCipher(uint & length, uchar * cipher, uchar * key)
{
	KeyExpansion(key);
	uint divide = length / 16;	// length must be times of 16

	uchar * text = new uchar[length];
	for (int i = 0; i < divide; i++)
	{
		uchar temp[16];
		for (int j = 0; j < 16; j++)
		{
			temp[j] = cipher[i * 16 + j];
		}

		uchar * out = decrypt(temp, key);
		for (int j = 0; j < 16; j++)
		{
			text[i * 16 + j] = out[j];
		}
		delete out;
	}

	// deal with padding
	uint count = 1;
	for (int i = 1; i < text[length - 1]; i++)
	{
		if (text[length - 1] >= 16)
		{
			break;
		}
		if (text[length - i - 1] == 0)
		{
			count++;
		}
	}
	if (count == text[length - 1])
	{
		length = length - count;
	}

	return text;
}

uchar * AES::decrypt(uchar * cipher, uchar * key)
{
	uchar roundState[4][4];

	for (int c = 0; c < 4; c++)
	{
		for (int r = 0; r < 4; r++)
		{
			roundState[r][c] = cipher[c * 4 + r];
		}
	}

	AddRoundKey(roundState, exdKey[10]);
	for (int i = 9; i > 0; i--)
	{
		InvShiftRows(roundState);
		InvSubBytes(roundState);
		AddRoundKey(roundState, exdKey[i]);
		InvMixColumns(roundState);
	}
	InvShiftRows(roundState);
	InvSubBytes(roundState);
	AddRoundKey(roundState, exdKey[0]);

	uchar * ret = new uchar[16];
	for (int c = 0; c < 4; c++)
	{
		for (int r = 0; r < 4; r++)
		{
			ret[c * 4 + r] = roundState[r][c];
		}
	}

	return ret;
}

void AES::InvSubBytes(uchar state[][4])
{
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			state[r][c] = InvSBox[state[r][c]];
		}
	}
}

void AES::InvShiftRows(uchar state[][4])
{
	uchar temp[4];
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			temp[c] = state[r][(c - r + 4) % 4];
		}
		for (int c = 0; c < 4; c++)
		{
			state[r][c] = temp[c];
		}
	}
}

void AES::InvMixColumns(uchar state[][4])
{
	uchar temp[4];
	for (int c = 0; c < 4; c++)
	{
		for (int r = 0; r < 4; r++)
		{
			temp[r] = state[r][c];
		}
		for (int r = 0; r < 4; r++)
		{
			state[r][c] = FFmul(0x0e, temp[r])
				^ FFmul(0x0b, temp[(r + 1) % 4])
				^ FFmul(0x0d, temp[(r + 2) % 4])
				^ FFmul(0x09, temp[(r + 3) % 4]);
		}
	}
}


#endif