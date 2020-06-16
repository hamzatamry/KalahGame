#ifndef MANIP_DATA_H
#define MANIP_DATA_H

#ifndef struct_pile
#define struct_pile
typedef struct pile                     //Definition de la structure pile qui represente les creux dans le jeu de KALAH
{
    int nb_element;
    int nb_max;
    int *T;
}pile;
#endif

int Sauvegarder(char Donnee_partie[3][16], pile plateau[2][8], int dernier_joueur, int nb_moitie); //Sauvegarder la partie jouee dans un fichier binaire portant le nom de la partie
int Charger(char Donnee_partie[3][16], pile plateau[2][8], int *dernier_joueur, int *nb_moitie); //Charger le contenu du fichier binaire qui contient les informations sur la partie a chargee


#endif // MANIP_DATA_H




