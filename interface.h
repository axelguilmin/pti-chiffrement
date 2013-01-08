/*
 * interface.h
 *
 * Created on: 10 nov. 2009
 * Author: Axel GUILMIN
 * Developpement : Ubuntu 8.10 / Eclipse Galileo / C ANSI
 * Bibliothèques :
 *  	gtk+ 2.16 :
 *  	Installer le paquet deb : libgtk2.0-dev et ses dépendances
 *  	Ajouter `pkg-config --cflags --libs gtk+-2.0` au Command line pattern
 *
 * Interface graphique pour AES et XOR
 *
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

#include "XOR.h"
#include "AES.h"

/* Constantes */
const char nomAES[] = "AES ( Fiable )" ;
const char nomXOR[] = "XOR ( Rapide )" ;

/* Widgets utilises dans le prog principal */
/* En global pour que les callbacks y aient acces */
GtkWidget* pFenetrePrincipale 			= NULL ;
	GtkWidget* pTabH 					= NULL ;
		GtkWidget* pMenuBar				= NULL ;
			GtkItemFactory*pItemFactory = NULL ;
		GtkWidget* pTabVInput 			= NULL ;
			GtkWidget* pInputLabel 		= NULL ;
			GtkWidget* pInputEntry 		= NULL ;
			GtkWidget* pInputB 			= NULL ;
		GtkWidget* pTabVOutput			= NULL ;
			GtkWidget* pOutputLabel 	= NULL ;
			GtkWidget* pOutputEntry 	= NULL ;
			GtkWidget* pOutputB 		= NULL ;
		GtkWidget* pTabVKey				= NULL ;
			GtkWidget* pKeyLabel		= NULL ;
			GtkWidget* pKeyEntry 		= NULL ;
			GtkWidget* pKeyEntry2 		= NULL ;
		GtkWidget* pTabVBouton			= NULL ;
			GtkWidget* pAlgoCBox 		= NULL ;
			GtkWidget* pBChiffrer 		= NULL ;
			GtkWidget* pBDechiffrer 	= NULL ;
	GtkWidget* pBarreStatut				= NULL ;

/* Callbacks */
void file_selection( GtkWidget* pWidget, gpointer data ) ;
void file_selection_in( GtkWidget* pWidget, gpointer data ) ;
void file_selection_out( GtkWidget* pWidget, gpointer data ) ;
void chiffrement( GtkWidget* pWidget, gpointer data ) ;
void dechiffrement( GtkWidget* pWidget, gpointer data ) ;
void voir_mdp( GtkWidget* pWidget, gpointer data ) ;
void cacher_mdp( GtkWidget* pWidget, gpointer data ) ;
void fermer( GtkWidget* pWidget, gpointer data ) ;

void afficher_retour( int num ) ;

#endif /* INTERFACE_H_ */
