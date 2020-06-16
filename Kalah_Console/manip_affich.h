#ifndef MANIP_AFFICH_H
#define MANIP_AFFICH_H

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

extern void menu1(); //Donner a l'utilisateur le choix de choisir quelque fonctionnalite principale
extern void nb_piece_initial(int *nb_piece); //Nombre initial de piece dans chaque creux (a demander à l'utilisateur avec respect des limites posées)
extern void menu2(); //Donner a l'utiliseur le choix de choisir quelque fonctionnalite secondaire (au cours du jeu)
extern void Afficher_Plateau(pile plateau[2][8], char Donnee_Partie[3][16]); //Afficher l'etat du plateau
extern void Choisir_Coup(pile plateau[2][8], int dernier_joueur, int *num_creux); //Choisir un creux
extern int Annuler_Coup(pile plateau[2][8], int dernier_joueur, int *num_creux); //Annuler le dernier coup joue ou cas on s'est trompe
extern void Gagnant(pile kalah1, pile kalah2); //Declarer le gagnant de la partie jouee
extern void Donnee(char Donnee_Partie[3][16]); //Saisir les donnees de la partie a jouer (nom de la partie, nom du 1er joueur, nom du 2eme joueur)


#endif