#include "transformations.h"

/* Si l'on représente un block dans un tableau de 4x4,
 * AddRoundKey applique un ou logique avec la clé de chiffrement
 * colone par colone
 */
 
void AddRoundKey( byte* state, byte* key )
{
	for( i=0; i<16; i++ )
		*( state + i ) ^= *( key + i ) ;
}
