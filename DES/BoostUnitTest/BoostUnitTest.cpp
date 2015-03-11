#define BOOST_TEST_MODULE DES_Test_Module

#include "stdafx.h"
#include "../DES/DES.hpp"

struct DES_Fixture
{
	DES_Fixture()
	{
		testDES = new DES;
	}
	~DES_Fixture()
	{
		delete testDES;
	}

	DES * testDES;
};


BOOST_FIXTURE_TEST_SUITE(DES_Test_Suite, DES_Fixture)

BOOST_AUTO_TEST_CASE( KeyExpansion )  
{
	// KeyExpansion
	bitset<64> key = 0x133457799BBCDFF1, temp64;
	temp64 = key;
	for (int i = 0; i < 64; i++)
	{
		key[i] = temp64[63 - i];
	}
	testDES->KeyExpansion(key);

	bitset<48> lastSubKey = 0xCB3D8B0E17F5, subKey, temp48;
	temp48 = lastSubKey;
	for (int i = 0; i < 48; i++)
	{
		lastSubKey[i] = temp48[47 - i];
	}

	subKey = getSubKey(*testDES, 15);
	for (int i = 0; i < 48; i++)
	{
		BOOST_REQUIRE(lastSubKey[i] == subKey[i]);
	}
	
}

BOOST_AUTO_TEST_CASE( Encrypt )
{
	// intTobin
	int tempInt = 15;
	bitset<4> tempBin;
	bitset<4> comBin;
	comBin[0] = 1; comBin[1] = 1; comBin[2] = 1; comBin[3] = 1;
	tempBin = testDES->intTobin(tempInt);
	for (int i = 0; i < 4; i++)
	{
		BOOST_REQUIRE(tempBin[i] == comBin[i]);
	}

	tempInt = 5;
	comBin[0] = 0; comBin[1] = 1; comBin[2] = 0; comBin[3] = 1;
	tempBin = testDES->intTobin(tempInt);
	for (int i = 0; i < 4; i++)
	{
		BOOST_REQUIRE(tempBin[i] == comBin[i]);
	}

	// encrypt
	bitset<64> key = 0x133457799BBCDFF1, temp64_key;
	bitset<64> text = 0x0123456789ABCDEF, temp64_text;
	temp64_key = key;
	temp64_text = text;
	for (int i = 0; i < 64; i++)
	{
		key[i] = temp64_key[63 - i];
		text[i] = temp64_text[63 - i];
	}

	bitset<64> cipher;
	cipher = testDES->encrypt(text, key);

	bitset<64> comCipher, temp64;
	comCipher = 0x85E813540F0AB405;
	temp64 = comCipher;
	for (int i = 0; i < 64; i++)
	{
		comCipher[i] = temp64[63 - i];
	}

	for (int i = 0; i < 64; i++)
	{
		BOOST_REQUIRE(cipher[i] == comCipher[i]);
	}

}

BOOST_AUTO_TEST_CASE( Decrypt )
{
	bitset<64> key = 0x133457799BBCDFF1, temp64_key;
	bitset<64> cipher = 0x85E813540F0AB405, temp64_cipher;
	temp64_key = key;
	temp64_cipher = cipher;
	for (int i = 0; i < 64; i++)
	{
		key[i] = temp64_key[63 - i];
		cipher[i] = temp64_cipher[63 - i];
	}

	bitset<64> text;
	text = testDES->decrypt(cipher, key);

	bitset<64> comText, temp64;
	comText = 0x0123456789ABCDEF;
	temp64 = comText;
	for (int i = 0; i < 64; i++)
	{
		comText[i] = temp64[63 - i];
	}

	for (int i = 0; i < 64; i++)
	{
		BOOST_REQUIRE(text[i] == comText[i]);
	}

}

BOOST_AUTO_TEST_SUITE_END()