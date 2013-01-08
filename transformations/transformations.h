/*
 * transformations.h
 * Author: Axel GUILMIN
 * Developpement : Ubuntu 8.10 / Eclipse Galileo / C ANSI
 *
 * Fonctions internes à AES
 */

#ifndef TRANSFORMATIONS_H_
#define TRANSFORMATIONS_H_

typedef	unsigned char byte ;

#define Nb 4 // Nombre de colonnes dans un etat, 1 colonne = 4 octets
#define Nk 4 // Nombre de colonnes pour la clé, 1 colonne = 4 octets
#define Nr 10 // Nombre de tours

int i ;
byte temp[Nb * 4] ;

// Transformation d'un octet
// ShiftRows.c
void ShiftRows( byte* state ) ;
void InvShiftRows( byte* state ) ;

// SubBytes.c
void SubBytes( byte* state ) ;
void InvSubBytes( byte* state ) ;

// Mixcolumns.c
void MixColumns( byte* state ) ;
void InvMixColumns( byte* state ) ;

// AddRoundKey.c
void AddRoundKey( byte* state, byte* K ) ;
// AddRoundKey est son propre inverse ( opération XOR )

// Transformation de la clé de chiffrement
// KeyExpansion.c
void KeyExpansion( byte* K, byte* w ) ;
void RotWord( byte* input ) ;

// Chiffrement / Déchiffrement
// Cipher.c
void Cipher( byte* state, byte* w ) ;
void InvCipher( byte* state, byte* w ) ;

#endif /* TRANSFORMATIONS_H_ */
