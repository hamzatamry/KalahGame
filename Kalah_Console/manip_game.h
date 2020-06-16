#ifndef MANIP_GAME_H
#define MANIP_GAME_H

#ifndef struct_pile

//Définition de la structure pile qui représente les creux dans le jeu de KALAH
#define struct_pile
typedef struct pile                     
{
    int nb_element; //nombre d’éléments de pièces contenu dans le creux
    int nb_max; //nombre maximum de pièces que le creux peut contenir
    int *T; //tableau représente les pièces réellement dans la mémoire
    //chaque pièce est représenté par une case mémoire contenant l’entier 0                  
}pile;

#endif

extern bool Generer_Aleatoire(); //Choisir le joueur aleatoirement qui va commencer
extern bool Detecter_Fin(pile plateau[2][8], int nb_moitie, int dernier_joueur);  //Detecter si la partie est terminee
extern int Tester_Kalah(int creux_ligne, int creux_colonne);    //Tester si le creux est un kalah
extern void Initial_Plateau(pile plateau[2][8], int nb_piece); //plateau : Table sur laquelle on joue le KALAH, nb_piece : nombre de piece quand va initialier chaque creux
extern int Jouer_Mise_aJour(pile plateau[2][8], int dernier_jouer, int *num_creux, char Donnee_Partie[3][16]);   //Mise a jour du plateau apres le coup
extern void Prendre_Tout(pile plateau[2][8], int dernier_joueur, int ind_parc, int num_creux);  //lorsque le joueur depose sa derniere piece dans l'un de ces creux qui est vide il capture les pieces du creux en face et il rajoute avec la derniere piece deposee dans son kalah
extern void Allocation_Plateau(pile plateau[2][8]); //allouer la memoire necessaire pour chaque creux pour qu'il contient son nombre de piece  
extern void Copier_plateau(pile plateau1[2][8], pile plateau2[2][8]);  //Copie les donnees du plateau 2 dans plateau 1


#endif
