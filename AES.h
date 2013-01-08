/*
 * AES.h
 * Author: Axel GUILMIN
 * Developpement : Ubuntu 8.10 & + / Eclipse Galileo / C ANSI
 *
 * Fonctions de chiffrement AES
 */

#ifndef AES_H_
#define AES_H_

/* Bibliotheques */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./transformations/transformations.h"
#include "retour.h"

int LireAjouterPadding( FILE* fichierSource, byte* block ) ;
int LireAvecPadding( FILE* fichierSource, byte* block ) ;
void EcrireBlock( FILE* fichier, byte* block, int taillePadding ) ;
int ChiffrerAES( char* entree, char* sortie, char* mdp, char* mdp2 ) ;
int DechiffrerAES( char* entree, char* sortie, char* mdp ) ;

#endif /* AES_H_ */
