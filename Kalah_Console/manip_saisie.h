#ifndef MANIP_SAISIE_H
#define MANIP_SAISIE_H

extern char *saisir_chaine();  //Permet de saisir une chaine de caractere de n'importe quelle taille avec allocation de l'espace necessaire
extern int Gerer_ErreurSaisie(char *Chaine_saisie);  //Gere les donnees saisies et verifie s'elles sont valides
extern bool Verification_ChaineNombre(char *Chaine_saisie);//Verifie si la chaine de caractere represente un nombre
extern bool Verification_ChaineLongueur(char *Chaine_saisie);//Verifie si la chaine de caratere n'est pas trop longue (ne depasse pas les 49 caracteres)
extern bool Verification_ChaineTexte(char *Chaine_saisie); //Verifie si la chaine de caractere est du texte alphabetique

#endif