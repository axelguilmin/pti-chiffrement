#include "transformations.h"

/*
 * Cipher.c
 *
 *  Created on: 30 oct. 2009
 *      Author: axel
 */

/* Cipher chiffre un block de 128Bits ( 4 octets ) */
void Cipher( byte* state, byte* w )
{
	int round ;

	AddRoundKey( state, w ) ;
	for( round = 1 ; round < Nr ; round++ )
	{
		SubBytes( state ) ;
		ShiftRows( state ) ;
		MixColumns( state ) ;
		AddRoundKey( state, w + round * Nb * 4 ) ;
	}
	SubBytes( state ) ;
	ShiftRows( state ) ;
	AddRoundKey( state, w + Nr * Nb * 4 ) ;
}

/* InvCipher dechiffre un block de 128Bits ( 4 octets ) */
void InvCipher( byte* state, byte* w )
{
	int round ;

	AddRoundKey( state, w + Nr * Nb * 4 ) ;
	for( round = Nr - 1 ; round > 0 ; round-- )
	{
		InvShiftRows( state ) ;
		InvSubBytes( state ) ;
		AddRoundKey( state, w + round * Nb * 4 ) ;
		InvMixColumns( state ) ;
	}
	InvShiftRows( state ) ;
	InvSubBytes( state ) ;
	AddRoundKey( state, w ) ;
}
