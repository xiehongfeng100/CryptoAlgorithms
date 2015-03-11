
#ifndef DES_H
#define DES_H

#include <iostream>
#include <bitset>
using namespace std;

typedef unsigned char uchar;
typedef unsigned int uint;
class DES
{
public:
	DES(){}
	virtual ~DES(){}
	uchar * Cipher(uint lenth, uchar * cipher, uchar * key);
	uchar * InvCipher(uint & length, uchar * cipher, uchar * key);

	bitset<64> encrypt(bitset<64> text, bitset<64> key);
	bitset<64> decrypt(bitset<64> cipher, bitset<64> key);

public:
	// key expansion
	void KeyExpansion(bitset<64> key);
	bitset<28> ringleftShift(bitset<28> k, uint shift);
	friend bitset<48> getSubKey(const DES & des, int round);

	// initial permutation
	bitset<64> iniPermutaion(bitset<64> state);

	// last permutation
	bitset<64> lastPermutation(bitset<64> state);

	// round function
	bitset<32> f(bitset<32> roundRcol, bitset<48> roundKey);
	bitset<4> intTobin(int tempInt);

private:
	bitset<48> subKey[16];

};

uchar * DES::Cipher(uint lenth, uchar * cipher, uchar * key)
{
	uchar * ret = new uchar;

	return ret;
}

uchar * DES::InvCipher(uint & length, uchar * cipher, uchar * key)
{
	uchar * ret = new uchar;

	return ret;
}

// key expansion
void DES::KeyExpansion(bitset<64> key)
{
	// 密钥置换表，将64位密钥变成56位
	int PC_1[] = { 57, 49, 41, 33, 25, 17, 9,
		1, 58, 50, 42, 34, 26, 18,
		10, 2, 59, 51, 43, 35, 27,
		19, 11, 3, 60, 52, 44, 36,
		63, 55, 47, 39, 31, 23, 15,
		7, 62, 54, 46, 38, 30, 22,
		14, 6, 61, 53, 45, 37, 29,
		21, 13, 5, 28, 20, 12, 4 };

	// 压缩置换，将56位密钥压缩成48位子密钥
	int PC_2[] = { 14, 17, 11, 24, 1, 5,
		3, 28, 15, 6, 21, 10,
		23, 19, 12, 4, 26, 8,
		16, 7, 27, 20, 13, 2,
		41, 52, 31, 37, 47, 55,
		30, 40, 51, 45, 33, 48,
		44, 49, 39, 56, 34, 53,
		46, 42, 50, 36, 29, 32 };

	// 每轮左移的位数
	int shiftBits[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

	bitset<56> keyPermutated;
	bitset<28> CKey, DKey;

	// permutate original key
	for (int i = 0; i < 56; i++)
	{
		keyPermutated[i] = key[PC_1[i] - 1];
		if (i < 28)
		{
			CKey[i] = keyPermutated[i];
		}
		else
		{
			DKey[i - 28] = keyPermutated[i];
		}
	}

	// expand the key
	bitset<56> combine;
	for (int round = 0; round < 16; round++)
	{
		int tempShift = shiftBits[round];
		CKey = ringleftShift(CKey, shiftBits[round]);
		DKey = ringleftShift(DKey, shiftBits[round]);

		// combine CKey & DKey
		for (int i = 0; i < 56; i++)
		{
			if (i < 28)
			{
				combine[i] = CKey[i];
			}
			else
			{
				combine[i] = DKey[i - 28];
			}
		}

		// permutation for the subkey
		bitset<48> tempKey;
		for (int i = 0; i < 48; i++)
		{
			tempKey[i] = combine[PC_2[i] - 1];
		}
		subKey[round] = tempKey;
	}

}

bitset<28> DES::ringleftShift(bitset<28> k, uint shift)
{
	bitset<28> temp = k;
	for (int i = 0; i < 28; i++)
	{
		if (27 - i < shift)
		{
			k[i] = temp[i + shift - 28];
		}
		else
		{
			k[i] = temp[i+shift];
		}
	}
	return k;
}

bitset<48> getSubKey(const DES & des, int round)
{
	return des.subKey[round];
}

// encrypt & decrypt
bitset<64> DES::encrypt(bitset<64> text, bitset<64> key)
{
	KeyExpansion(key);
	bitset<32> LText, RText;
	text = iniPermutaion(text);
	for (int i = 0; i < 64; i++)
	{
		if (i < 32)
			LText[i] = text[i];
		else
			RText[i - 32] = text[i];
	}

	bitset<32> temp32;
	for (int round = 0; round < 16; round++)
	{
		bitset<32> temp32_2;
		temp32_2 = f(RText, subKey[round]);
		for (int i = 0; i < 32; i++)
		{
			temp32[i] = LText[i] ^ temp32_2[i];
		}
		LText = RText;
		RText = temp32;
	}

	temp32 = LText;
	LText = RText;
	RText = temp32;
	
	bitset<64> temp64;
	for (int i = 0; i < 64; i++)
	{
		if (i < 32)
			temp64[i] = LText[i];
		else
			temp64[i] = RText[i - 32];
	}

	bitset<64> cipher = lastPermutation(temp64);

	return cipher;
}

bitset<64> DES::decrypt(bitset<64> cipher, bitset<64> key)
{
	KeyExpansion(key);
	bitset<32> LText, RText;
	cipher = iniPermutaion(cipher);
	for (int i = 0; i < 64; i++)
	{
		if (i < 32)
			LText[i] = cipher[i];
		else
			RText[i - 32] = cipher[i];
	}

	bitset<32> temp32;
	for (int round = 0; round < 16; round++)
	{
		bitset<32> temp32_2;
		temp32_2 = f(RText, subKey[15 - round]);
		for (int i = 0; i < 32; i++)
		{
			temp32[i] = LText[i] ^ temp32_2[i];
		}
		LText = RText;
		RText = temp32;
	}

	temp32 = LText;
	LText = RText;
	RText = temp32;

	bitset<64> temp64;
	for (int i = 0; i < 64; i++)
	{
		if (i < 32)
			temp64[i] = LText[i];
		else
			temp64[i] = RText[i - 32];
	}

	bitset<64> text = lastPermutation(temp64);

	return text;
}

// initial permutation
bitset<64> DES::iniPermutaion(bitset<64> state)
{
	bitset<64> temp = state;
	// 初始置换表
	int IP[] = { 58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17, 9, 1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7 };

	for (int i = 0; i < 64; i++)
	{
		state[i] = temp[IP[i] - 1];
	}

	return state;
}

// last permutation
bitset<64> DES::lastPermutation(bitset<64> state)
{
	bitset<64> temp = state;
	// 尾置换表
	int IP_1[] = { 40, 8, 48, 16, 56, 24, 64, 32,
		39, 7, 47, 15, 55, 23, 63, 31,
		38, 6, 46, 14, 54, 22, 62, 30,
		37, 5, 45, 13, 53, 21, 61, 29,
		36, 4, 44, 12, 52, 20, 60, 28,
		35, 3, 43, 11, 51, 19, 59, 27,
		34, 2, 42, 10, 50, 18, 58, 26,
		33, 1, 41, 9, 49, 17, 57, 25 };

	for (int i = 0; i < 64; i++)
	{
		state[i] = temp[IP_1[i] - 1];
	}

	return state;
}

// round function
bitset<32> DES::f(bitset<32> roundRcol, bitset<48> roundKey)
{
	// 扩展置换表，将 32位 扩展至 48位
	int E[] = { 32, 1, 2, 3, 4, 5,
		4, 5, 6, 7, 8, 9,
		8, 9, 10, 11, 12, 13,
		12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21,
		20, 21, 22, 23, 24, 25,
		24, 25, 26, 27, 28, 29,
		28, 29, 30, 31, 32, 1 };

	// S盒，每个S盒是4x16的置换表，6位 -> 4位
	int S_BOX[8][4][16] = {
		{
			{ 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 },
			{ 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
			{ 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
			{ 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 }
		},
		{
			{ 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 },
			{ 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 },
			{ 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 },
			{ 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 }
		},
		{
			{ 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 },
			{ 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 },
			{ 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 },
			{ 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 }
		},
		{
			{ 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 },
			{ 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 },
			{ 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4 },
			{ 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 }
		},
		{
			{ 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 },
			{ 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 },
			{ 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 },
			{ 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 }
		},
		{
			{ 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 },
			{ 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8 },
			{ 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6 },
			{ 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 }
		},
		{
			{ 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 },
			{ 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 },
			{ 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 },
			{ 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 }
		},
		{
			{ 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 },
			{ 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 },
			{ 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 },
			{ 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 }
		}
	};

	// P置换，32位 -> 32位
	int P[] = { 16, 7, 20, 21,
		29, 12, 28, 17,
		1, 15, 23, 26,
		5, 18, 31, 10,
		2, 8, 24, 14,
		32, 27, 3, 9,
		19, 13, 30, 6,
		22, 11, 4, 25 };

	bitset<48> expandRcol;
	for (int i = 0; i < 48; i++)
	{
		expandRcol[i] = roundRcol[E[i] - 1];
	}

	bitset<48> xorRcol_n_Key;
	for (int i = 0; i < 48; i++)
	{
		xorRcol_n_Key[i] = expandRcol[i] ^ roundKey[i];
	}

	bitset<32> out;
	for (int i = 0; i < 8; i++)
	{
		bitset<6> temp6;
		for (int j = 0; j < 6; j++)
		{
			temp6[j] = xorRcol_n_Key[i * 6 + j];
		}
		int row = temp6[0] * 2 + temp6[5];
		int col = temp6[1] * 8 + temp6[2] * 4 + temp6[3] * 2 + temp6[4];

		int tempInt = S_BOX[i][row][col];
		bitset<4> tempBin = intTobin(tempInt);
		for (int j = 0; j < 4; j++)
		{
			out[i * 4 + j] = tempBin[j];
		}
	}

	bitset<32> temp32 = out;
	for (int i = 0; i < 32; i++)
	{
		out[i] = temp32[P[i] - 1];
	}

	return out;
}

bitset<4> DES::intTobin(int tempInt)
{
	bitset<4> out;
	int div = 0;
	int rem = 0;
	div = tempInt;
	for (int i = 0; i < 4; i++)
	{
		rem = div % 2;
		div = div / 2;
		out[3 - i] = rem;
	}

	return out;
}


#endif


