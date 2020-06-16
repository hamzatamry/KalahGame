#ifndef MANIP_PILE_H
#define MANIP_PILE_H

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

#endif // struct_pile

extern void Empiler(pile *creux);                         //Depot de la piece dans le creux
extern bool Estvide(pile creux);                          //tester si le creux est vide
extern void Vider_Pile(pile *creux);                      //vider creux

#endif // MANIP_PILE
