#include "AES.h"

int ChiffrerAES( char* entree, char* sortie, char* mdp, char* mdp2 )
{
	/* Variables */
	int 	finFichier 		= 0 ; /* Booleen 0 : false 1 : true */
	byte 	mdp16[16] 		= { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c } ;
	byte 	cle[Nb * ( Nr + 1 ) * 4] ;
	byte 	block[16] ;
	FILE* 	pFichierSource 	= NULL ;
	FILE* 	pFichierDest 	= NULL ;

	/* Teste si la clé a bien été renseignée */
	if( strlen( mdp ) < 6 )
		return 13 ;

	/* Teste si les deux clés sont identiques ( erreur de frappe ... ) */
	if( strcmp( mdp, mdp2 ) != 0 )
		return 14 ;
	/* Expansion de la cle */
	/* On ajoute des '0' apres le mot de passe */
	memcpy( &mdp16[0], &mdp[0], strlen( &mdp[0] ) ) ;
	KeyExpansion( &mdp16[0], &cle[0] ) ;


	/* Ouverture et test du fichier a chiffrer */
	pFichierSource = fopen( entree, "rb" ) ;
	if( pFichierSource == NULL )
		return 11 ;

	/* Ouverture et test du fichier destination */
	pFichierDest = fopen( sortie, "wb" ) ;
	if( pFichierDest == NULL )
		return 12 ;

	while( finFichier == 0 )
	{
		finFichier = LireAjouterPadding( pFichierSource, &block[0] ) ;
		Cipher( &block[0], &cle[0] ) ;
		EcrireBlock( pFichierDest, &block[0], 0 ) ;
	}

	/* Vide le tampon */
	fflush( pFichierDest ) ;
	/* Ferme les flux */
	fclose( pFichierSource ) ;
	fclose( pFichierDest ) ;

	return 21 ;
}

int DechiffrerAES( char* entree, char* sortie, char* mdp )
{
	/* Variables */
	int 	padding ;
	int 	finFichier 		= 0 ; /* Booleen 0 : false 1 : true */
	byte 	mdp16[16] 		= { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c } ;
	byte 	cle[Nb * ( Nr + 1 ) * 4] ;
	byte 	block[16] ;
	FILE* 	pFichierSource 	= NULL ;
	FILE* 	pFichierDest 	= NULL ;

	/* Teste si la clé a bien été renseignée */
	if( strlen( mdp ) < 6 )
		return 13 ;

	/* Expansion de la cle */
	/* On ajoute des '0' apres le mot de passe */
	memcpy( &mdp16[0], &mdp[0], strlen( &mdp[0] ) ) ;
	KeyExpansion( &mdp16[0], &cle[0] ) ;

	/* Ouverture et test du fichier a chiffrer */
	pFichierSource = fopen( entree, "rb" ) ;
	if( pFichierSource == NULL )
		return 11 ;

	/* Ouverture et test du fichier destination */
	pFichierDest = fopen( sortie, "wb" ) ;
	if( pFichierDest == NULL )
		return 12 ;

	finFichier = LireAvecPadding( pFichierSource, &block[0] ) ;
	while( finFichier == 0 )
	{
		InvCipher( &block[0], &cle[0] ) ;
		EcrireBlock( pFichierDest, &block[0], 0 ) ;
		finFichier = LireAvecPadding( pFichierSource, &block[0] ) ;
	}
	InvCipher( &block[0], &cle[0] ) ;
	/* On passe à ecrireBlock la taille du padding en parametre 3 */
	padding = block[15] ;
	EcrireBlock( pFichierDest, &block[0], padding ) ;

	/* Vide le tampon */
	fflush( pFichierDest ) ;
	/* Ferme les flux */
	fclose( pFichierSource ) ;
	fclose( pFichierDest ) ;

	return 22 ;
}

int LireAjouterPadding( FILE* fichierSource, byte* block )
{
	int i ;
	int NbPadding ;
	int octetLu ;
	int fin			= 0 ;

	/* Lire 16 * 1 Octet */
	octetLu = fread( block, 1, 16, fichierSource ) ;

	/* Fin du fichier, ajout du Padding PKCS7 */
	if( octetLu != 16 )
	{
		NbPadding = 16 - octetLu ;
		for( i = octetLu ; i < 16 ; i++ )
			*( block + i ) = NbPadding ;
		fin = 1 ;
	}

	return fin ;
}

int LireAvecPadding( FILE* fichierSource, byte* block )
{
	int octetLu ;
	int fin = 0 ;
	byte suivant ;

	/* Lire 16 * 1 Octet */
	octetLu = fread( block, 1, 16, fichierSource )  ;

	/* Teste si la fin du fichier est atteinte */
	if( octetLu != 16 || fread( &suivant, 1, 1, fichierSource ) == 0 )
		fin = 1 ;

	/* On remet le pointeur sur fichier a sa place pour prochaine lecture */
	fseek ( fichierSource , -1 , SEEK_CUR );
	return fin ;
}

void EcrireBlock( FILE* fichier, byte* block, int taillePadding )
{
	int longeur = 16 - taillePadding ;
	fwrite( block, 1, longeur, fichier ) ;
}
