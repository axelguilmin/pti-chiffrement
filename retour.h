/*
 * retour.h
 *
 * Created on: 18 nov. 2009
 * Author: axel GUILMIN
 *
 * Valeur de retours des fonctions de (dé)chiffrement
 */

#ifndef RETOUR_H_
#define RETOUR_H_

/* Retours normaux */
#define CHIFFREMENT_OK_21 "Chiffrement AES réussi"
#define DECHIFFREMENT_OK_22 "Déchiffrement réussi"
#define OK_23 "Opération réussie"

/* Erreurs */
#define ERREUR_11 "Erreur lors de l'ouverture du fichier source"
#define ERREUR_12 "Erreur lors de la creation du fichier destination"
#define ERREUR_13 "Merci de renseigner un mot de passe d'au moins 6 caractères"
#define ERREUR_14 "Les deux mots de passe doivent être identiques"

/* Aides --help */
#define HELP_AES "AES - Programme de chiffrement par Axel GUILMIN - 2009\nUtilisation: AES \"Fichier a chiffrer\" \"Nom du nouveau fichier\" \"Mot de passe\""
#define HELP_XOR "XOR - Programme de chiffrement par Axel GUILMIN - 2009\nUtilisation: XOR \"Fichier a chiffrer\" \"Nom du nouveau fichier\" \"Mot de passe\""



#endif /* RETOUR_H_ */
