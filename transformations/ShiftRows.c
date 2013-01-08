#include "transformations.h"

/* Si l'on représente un block dans un tableau de 4x4,
 * La premiere ligne ne bouge pas
 * La deuxieme subit une rotation de 2 octet
 * La troisieme de 2 octets
 * La derniere de 3 octets
 */

void ShiftRows( byte* state )
{
	/* Copie les éléments un à un */
	for( i = 0 ; i < 16 ; i++ )
		temp[i] = *( state + i ) ;

	/* La première ligne ne change pas */

	/* Rotation de la deuxieme ligne */
	*( state + 1 ) 	= temp[5] ;
	*( state + 5 ) 	= temp[9] ;
	*( state + 9 ) 	= temp[13] ;
	*( state + 13 ) = temp[1] ;

	/* Rotation de la troisieme ligne */
	*( state + 2 ) 	= temp[10] ;
	*( state + 6 ) 	= temp[14] ;
	*( state + 10 ) = temp[2] ;
	*( state + 14 ) = temp[6] ;

	/* Rotation de la quatrieme ligne */
	*( state + 3 ) 	= temp[15] ;
	*( state + 7 ) 	= temp[3] ;
	*( state + 11 ) = temp[7] ;
	*( state + 15 ) = temp[11] ;
}

/* Procédure inverse */
void InvShiftRows( byte* state )
{
	/* Copie les element un a un */
	for( i = 0 ; i < 16 ; i++ )
		temp[i] = *( state + i ) ;

	/* La premiere ligne ne change pas */

	/* Rotation de la deuxieme ligne */
	*( state + 1 ) 	= temp[13] ;
	*( state + 5 ) 	= temp[1] ;
	*( state + 9 ) 	= temp[5] ;
	*( state + 13 ) = temp[9] ;

	/* Rotation de la troisieme ligne */
	*( state + 2 ) 	= temp[10] ;
	*( state + 6 ) 	= temp[14] ;
	*( state + 10 ) = temp[2] ;
	*( state + 14 ) = temp[6] ;

	/* Rotation de la quatrieme ligne */
	*( state + 3 ) 	= temp[7] ;
	*( state + 7 ) 	= temp[11] ;
	*( state + 11 ) = temp[15] ;
	*( state + 15 ) = temp[3] ;
}
