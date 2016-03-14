#ifndef AES_H
#define AES_H

typedef unsigned char uchar;
typedef unsigned int uint;

// Variables **************************************
// SBox	
// uchar SBox[256];
// uchar InvSBox[256];
// Extended key
uchar exdKey[11][4][4];
// Round constant	
// uchar Rcon[10];

// Key expansion **********************************
void RotWord(uchar key[][4]);
void SubWord(uchar key[][4]);
void KeyExpansion(uchar * key);

// Encrypt ****************************************
void SubBytes(uchar state[][4]);
void ShiftRows(uchar state[][4]);
void MixColumns(uchar state[][4]);
void AddRoundKey(uchar state[][4], uchar key[][4]);
uchar * encrypt(uchar * cipher, uchar * key);
// Finite field multiplication
uchar XTime(uchar x);
uchar FFmul(uchar a, uchar b);

// Decrypt ****************************************
void InvSubBytes(uchar state[][4]);
void InvShiftRows(uchar state[][4]);
void InvMixColumns(uchar state[][4]);
uchar * decrypt(uchar * cipher, uchar * key);


// Final Encryt and Decrypt Function **************
uchar * Cipher(uint * length, uchar * cipher, uchar * key);
uchar * InvCipher(uint * length, uchar * cipher, uchar * key);

#endif