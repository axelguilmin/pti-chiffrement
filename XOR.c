#include "XOR.h"

int ChiffrerXOR( char* entree, char* sortie, char* cle, char* cle2 )
{
	/* Variables */
	int i = 0 ;
	int car = 0x00 ;
	int keySize = 0 ;
	FILE* pFichierSource = NULL ;
	FILE* pFichierDest = NULL ;
	
	/* Teste si la clé a bien été renseignée */
	keySize = strlen( cle ) ;
	if( keySize < 6 )
		return 13 ;

	/* Teste si les deux clés sont identiques ( erreur de frappe ... ) */
	if( strcmp( cle, cle2 ) != 0 )
		return 14 ;

	/* Ouverture et test du fichier a chiffrer */
	pFichierSource = fopen( entree, "rb" ) ;
	if( pFichierSource == NULL )
		return 11 ;
	
	/* Ouverture et test du fichier destination */
	pFichierDest = fopen( sortie, "wb" ) ;
	if( pFichierDest == NULL )
		return 12 ;

	/* Lecture pour le premier passage */
	car = fgetc( pFichierSource ) ; 
	
	/* Tant que la fin du fichier n'est pas atteinte */
	do
	{	
		/* "^" applique un OU exclusif sur chaque bit et renvoie le décimal */
		/* L'indice de du tableau contenant la clé est i modulo (%) la taille de la clé */
		car ^= cle[ i % keySize ] ;
		fwrite( &car, 1, 1, pFichierDest ) ;
		i++ ;
		car = fgetc( pFichierSource ) ;
	} while( car != EOF ) ;
	
	/* On vide le tampon */
	fflush( pFichierDest ) ;
	/* On ferme les flux */
	fclose( pFichierSource ) ;
	fclose( pFichierDest ) ; 
	return 23 ;
}
