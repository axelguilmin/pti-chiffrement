#include "interface.h"

int main( int argc, char *argv[] )
{
	/* Elements du menu
	struct GtkItemFactoryEntry {
		gchar *path;
	    gchar *accelerator;
	    GtkItemFactoryCallback callback;
	    guint callback_action;
	    gchar *item_type;
	    gconstpointer extra_data;
	}; */
	static GtkItemFactoryEntry MenuItem[] = {
	    { "/Fichier", 						NULL, 	NULL, 				0, "<Branch>" 						},
	    { "/Fichier/Choisir Source", 		NULL, 	file_selection_in, 	0, "<StockItem>", GTK_STOCK_OPEN 	}, // callback data = pInputEntry ??
	    { "/Fichier/Choisir Destination", 	NULL, 	file_selection_out,	0, "<StockItem>", GTK_STOCK_NEW 	}, // Idem
	    { "/Fichier/Voir Mot De Passe", 	NULL, 	voir_mdp, 			0, "<CheckItem>", 				 	},
	    { "/Fichier/Sep1", 					NULL, 	NULL, 				0, "<Separator>" 					},
	    { "/Fichier/Fermer", 				NULL, 	fermer, 			0, "<StockItem>", GTK_STOCK_CLOSE 	},
	    { "/Chiffrement", 					NULL, 	NULL, 				0, "<Branch>" 						},
	    { "/Chiffrement/Chiffrer (AES)", 	NULL, 	chiffrement, 		0, "<StockItem>", GTK_STOCK_ADD 	},
	    { "/Chiffrement/Dechiffrer (AES)", 	NULL, 	dechiffrement, 		0, "<StockItem>", GTK_STOCK_REMOVE 	},
	    { "/Chiffrement/Sep1", 				NULL, 	NULL, 				0, "<Separator>" 					},
	    { "/Chiffrement/Chiffrer (XOR)", 	NULL, 	NULL, 				0, "<StockItem>", GTK_STOCK_ADD 	},
	    { "/Chiffrement/Dechiffrer (XOR)", 	NULL, 	NULL, 				0, "<StockItem>", GTK_STOCK_REMOVE 	},
	    { "/Aide", 							NULL, 	NULL, 				0, "<Branch>" 						},
	    { "/Aide/A Propos", 				NULL, 	NULL, 				0, "<StockItem>", GTK_STOCK_ABOUT	}
	} ;
	/* Nombre d elements du menu */
	static gint iNbMenuItem = sizeof( MenuItem ) / sizeof( MenuItem[0] ) ;

	/* Initialisation de GTK+ */
    gtk_init( &argc, &argv ) ;

    /* Creation de la fenetre principale, GTK_WINDOWS_TOPLEVEL = Normale */
    pFenetrePrincipale = gtk_window_new( GTK_WINDOW_TOPLEVEL ) ;
    /* Titre de la fenetre principale */
    gtk_window_set_title( GTK_WINDOW( pFenetrePrincipale ), "Chiffrer un fichier" ) ;
    /* Taille par défaut de la fenetre principale */
    /* La macro GTK_WINDOW() "transforme" un GTK widget en windows */
    gtk_window_set_default_size( GTK_WINDOW( pFenetrePrincipale ), 450, 150 ) ;
    /* Position de la fenetre principale */
    gtk_window_set_position( GTK_WINDOW( pFenetrePrincipale ), GTK_WIN_POS_CENTER ) ;
    /* Icone de la fenetre principale */
    gtk_window_set_icon_from_file( GTK_WINDOW( pFenetrePrincipale ), "/media/Axel/3---PTI/Chiffrement/workspace/Interface/Debug/30.png", NULL ) ;

    /* Creation du tableau vertical qui va contenir les widgets */
    pTabH = gtk_vbox_new( FALSE, 5 ) ;
    gtk_container_add( GTK_CONTAINER( pFenetrePrincipale ), pTabH ) ;

	/* Menu */
	// pAccel = gtk_accel_group_new( ) ; Creation de la table d acceleration pour les raccourcis clavier
	/* Creation du menu */
	pItemFactory = gtk_item_factory_new( GTK_TYPE_MENU_BAR, "<main>", NULL ) ;
	/* Recuperation des elements du menu */
	gtk_item_factory_create_items( pItemFactory, iNbMenuItem, MenuItem, GTK_WIDGET( pTabH ) ) ;
	/* Recuperation du widget pour l affichage du menu */
	pMenuBar = gtk_item_factory_get_widget( pItemFactory, "<main>" ) ;
	/* Ajout du menu en haut de la fenetre */
	gtk_container_add( GTK_CONTAINER( pTabH ), pMenuBar ) ;
	//gtk_window_add_accel_group( GTK_WINDOW( pFenetrePrincipale ), pAccel ) ; Association des raccourcis clavier avec la fenetre

    /* Ligne fichier source */
    pTabVInput = gtk_hbox_new( TRUE, 0 ) ;
    gtk_container_add( GTK_CONTAINER( pTabH ), pTabVInput ) ;
    pInputLabel = gtk_label_new( "Fichier a (de)chiffrer : "  ) ;
    gtk_misc_set_alignment( GTK_MISC( pInputLabel ), 1, 0.5 ) ;
    gtk_container_add( GTK_CONTAINER( pTabVInput ), pInputLabel ) ;
    pInputEntry = gtk_entry_new( ) ;
    gtk_container_add( GTK_CONTAINER( pTabVInput ), pInputEntry ) ;
    pInputB = gtk_button_new_from_stock( GTK_STOCK_OPEN ) ;
    gtk_container_add( GTK_CONTAINER( pTabVInput ), pInputB ) ;

    /* Ligne fichier destination */
    pTabVOutput = gtk_hbox_new( TRUE, 0 ) ;
    gtk_container_add( GTK_CONTAINER( pTabH ), pTabVOutput ) ;
    pOutputLabel = gtk_label_new( "Destination : " ) ;
    gtk_misc_set_alignment( GTK_MISC( pOutputLabel ), 1, 0.5 ) ;
    gtk_container_add( GTK_CONTAINER( pTabVOutput ), pOutputLabel ) ;
    pOutputEntry = gtk_entry_new() ;
    gtk_container_add( GTK_CONTAINER( pTabVOutput ), pOutputEntry ) ;
    pOutputB = gtk_button_new_from_stock( GTK_STOCK_OPEN ) ;
    gtk_container_add( GTK_CONTAINER( pTabVOutput ), pOutputB ) ;

    /* Ligne mot de passe */
    pTabVKey = gtk_hbox_new( TRUE, 0 ) ;
    gtk_container_add( GTK_CONTAINER( pTabH ), pTabVKey ) ;
    pKeyLabel = gtk_label_new( "Mot de passe : " ) ;
    gtk_misc_set_alignment( GTK_MISC( pKeyLabel ), 1, 0.5 ) ;
    gtk_container_add( GTK_CONTAINER( pTabVKey ), pKeyLabel ) ;
    pKeyEntry = gtk_entry_new_with_max_length( 16 ) ;
    // gtk_entry_set_icon_from_stock( pKeyEntry, GTK_ENTRY_ICON_PRIMARY, GTK_STOCK_ADD ) ; icone dans un Entry, necessite gtk2.16 ... Dépots pas à jour =(
    gtk_container_add( GTK_CONTAINER( pTabVKey ), pKeyEntry ) ;
    gtk_entry_set_visibility( GTK_ENTRY( pKeyEntry ), FALSE ) ;
    pKeyEntry2 = gtk_entry_new_with_max_length( 16 ) ;
    // gtk_entry_set_icon_from_stock( pKeyEntry, GTK_ENTRY_ICON_PRIMARY, GTK_STOCK_ADD ) ; icone dans un Entry, necessite gtk2.16 ... Dépots pas à jour =(
    gtk_container_add( GTK_CONTAINER( pTabVKey ), pKeyEntry2 ) ;
    gtk_entry_set_visibility( GTK_ENTRY( pKeyEntry2 ), FALSE ) ;

    /* Ligne Chiffrement */
    pTabVBouton = gtk_hbox_new( TRUE, 0 ) ;
    gtk_container_add( GTK_CONTAINER( pTabH ), pTabVBouton ) ;
    pAlgoCBox = gtk_combo_box_new_text( ) ;
    gtk_combo_box_append_text( GTK_COMBO_BOX( pAlgoCBox ), nomAES ) ;
    gtk_combo_box_append_text( GTK_COMBO_BOX( pAlgoCBox ), nomXOR ) ;
    /* La combo box est par défaut sur AES */
    gtk_combo_box_set_active( GTK_COMBO_BOX( pAlgoCBox ), 0 ) ;
    gtk_container_add( GTK_CONTAINER( pTabVBouton ), pAlgoCBox ) ;
    pBChiffrer = gtk_button_new_with_label( "Chiffrer" ) ;
    gtk_container_add( GTK_CONTAINER( pTabVBouton ), pBChiffrer ) ;
    pBDechiffrer = gtk_button_new_with_label( "Dechiffrer" ) ;
    gtk_container_add( GTK_CONTAINER( pTabVBouton ), pBDechiffrer ) ;

    /* Barre de statut */
    pBarreStatut = gtk_statusbar_new( ) ;
    gtk_container_add( GTK_CONTAINER( pTabH ), pBarreStatut ) ;
    /* Pour modifier le contenu de la barre de statut
     * guint IdBarreStatut = gtk_statusbar_get_context_id( GTK_STATUSBAR( pBarreStatut ), "Nom du contexte" ) ;
     * gtk_statusbar_push( GTK_STATUSBAR( pBarreStatut ), GPOINTER_TO_INT( IdBarreStatut ), "Message" ) ;
     */

    /* Afficher la fenetre principale et tout les widgets qu'elle contient */
    gtk_widget_show_all( pFenetrePrincipale ) ;

    /* Liaison des callback*/
    g_signal_connect( G_OBJECT( pFenetrePrincipale ), "delete-event", G_CALLBACK( gtk_main_quit ), NULL ) ;
    g_signal_connect( G_OBJECT( pInputB ), "clicked", G_CALLBACK( file_selection ), pInputEntry ) ;
    g_signal_connect( G_OBJECT( pOutputB ), "clicked", G_CALLBACK( file_selection ), pOutputEntry) ;
    g_signal_connect( G_OBJECT( pBChiffrer ), "clicked", G_CALLBACK( chiffrement ), NULL ) ;
    g_signal_connect( G_OBJECT( pBDechiffrer ), "clicked", G_CALLBACK( dechiffrement ), NULL ) ;

    /* Boucle principale dans laquelle gtk apelle les callback */
    gtk_main() ;
    return EXIT_SUCCESS;
}
void file_selection_in( GtkWidget* pWidget, gpointer data )
{
	file_selection( pWidget, pInputEntry ) ;
}
void file_selection_out( GtkWidget* pWidget, gpointer data )
{
	file_selection( pWidget, pOutputEntry ) ;
}
void file_selection( GtkWidget* pWidget, gpointer data )
{
    GtkWidget* pFileSelection ;
    GtkWidget* pEntry = GTK_WIDGET( data ) ;
    const gchar* chemin ;

    /* Creation de la fenetre de selection */
    pFileSelection = gtk_file_chooser_dialog_new(
    		"Choisir un fichier",
    		NULL,
    		GTK_FILE_CHOOSER_ACTION_SAVE,
    		GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
    		GTK_STOCK_OPEN, GTK_RESPONSE_OK,
    		NULL ) ;

    /* On limite les actions a cette fenetre */
    gtk_window_set_modal( GTK_WINDOW( pFileSelection ), TRUE ) ;

    /* Affichage fenetre, et attente de la sortie */
    switch( gtk_dialog_run( GTK_DIALOG( pFileSelection ) ) )
    {
        case GTK_RESPONSE_OK:
            /* Recuperation du chemin */
            chemin = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( pFileSelection ) ) ;
            /* Adresse du fichier dans la Textbox passé en parametre */
            gtk_entry_set_text( GTK_ENTRY( pEntry ), chemin ) ;
            break ;
        default :
            break ;
    }
    gtk_widget_destroy( pFileSelection ) ;
}

void chiffrement( GtkWidget* pWidget, gpointer data )
{
	int retour ;
	char* input = ( char* ) gtk_entry_get_text( GTK_ENTRY( pInputEntry ) ) ;
	char* output = ( char* ) gtk_entry_get_text( GTK_ENTRY( pOutputEntry ) ) ;
	char* key = ( char* ) gtk_entry_get_text( GTK_ENTRY( pKeyEntry ) ) ;
	char* key2 = ( char* ) gtk_entry_get_text( GTK_ENTRY( pKeyEntry2 ) ) ;
	char* algo = ( char* ) gtk_combo_box_get_active_text( GTK_COMBO_BOX( pAlgoCBox ) ) ;

	/* Chiffrement XOR */
	if( strcmp( algo, nomXOR ) == 0 )
	{
		retour = ChiffrerXOR( input, output, key, key2 ) ;
		/* Affiche des eventuelles erreurs */
		afficher_retour( retour ) ;
	}
	/* Chiffrement AES */
	else
	{
		retour = ChiffrerAES( input, output, key, key2 ) ;
		/* Affiche des eventuelles erreurs */
		afficher_retour( retour ) ;
	}
}
void dechiffrement( GtkWidget* pWidget, gpointer data )
{
	int retour ;
	char* input = ( char* ) gtk_entry_get_text( GTK_ENTRY( pInputEntry ) ) ;
	char* output = ( char* ) gtk_entry_get_text( GTK_ENTRY( pOutputEntry ) ) ;
	char* key = ( char* ) gtk_entry_get_text( GTK_ENTRY( pKeyEntry ) ) ;
	char* algo = ( char* ) gtk_combo_box_get_active_text( GTK_COMBO_BOX( pAlgoCBox ) ) ;
	/* Dechiffrement XOR */
	if( strcmp( algo, nomXOR ) == 0 )
	{
		retour = ChiffrerXOR( input, output, key, key ) ;
		/* Affiche des eventuelles erreurs */
		afficher_retour( retour ) ;
	}
	/* Dechiffrement AES */
	else
	{
		retour = DechiffrerAES( input, output, key ) ;
		/* Affiche des eventuelles erreurs */
		afficher_retour( retour ) ;
	}
}

void voir_mdp( GtkWidget* pWidget, gpointer data )
{
	gboolean mdp_visible = gtk_entry_get_visibility( GTK_ENTRY( pKeyEntry ) ) ;
	gtk_entry_set_visibility( GTK_ENTRY( pKeyEntry ), ! mdp_visible ) ;
	gtk_entry_set_visibility( GTK_ENTRY( pKeyEntry2 ), ! mdp_visible ) ;
}

void fermer( GtkWidget* pWidget, gpointer data )
{
	gtk_main_quit() ;
}

void afficher_retour( int num )
{
	/* Recupere l'id de la barre de statut */
	guint IdBarreStatut = gtk_statusbar_get_context_id( GTK_STATUSBAR( pBarreStatut ), "Chiffrement Déchiffrement" ) ;
	switch( num )
	{
	case 11 :
		gtk_statusbar_push( GTK_STATUSBAR( pBarreStatut ), GPOINTER_TO_INT( IdBarreStatut ), ERREUR_11 ) ;
		break ;
	case 12 :
		gtk_statusbar_push( GTK_STATUSBAR( pBarreStatut ), GPOINTER_TO_INT( IdBarreStatut ), ERREUR_12 ) ;
		break ;
	case 13 :
		gtk_statusbar_push( GTK_STATUSBAR( pBarreStatut ), GPOINTER_TO_INT( IdBarreStatut ), ERREUR_13 ) ;
		break ;
	case 14 :
		gtk_statusbar_push( GTK_STATUSBAR( pBarreStatut ), GPOINTER_TO_INT( IdBarreStatut ), ERREUR_14 ) ;
		break ;
	case 21 :
		gtk_statusbar_push( GTK_STATUSBAR( pBarreStatut ), GPOINTER_TO_INT( IdBarreStatut ), CHIFFREMENT_OK_21 ) ;
		break ;
	case 22 :
		gtk_statusbar_push( GTK_STATUSBAR( pBarreStatut ), GPOINTER_TO_INT( IdBarreStatut ), DECHIFFREMENT_OK_22 ) ;
		break ;
	case 23 :
		gtk_statusbar_push( GTK_STATUSBAR( pBarreStatut ), GPOINTER_TO_INT( IdBarreStatut ), OK_23 ) ;
	}
}
