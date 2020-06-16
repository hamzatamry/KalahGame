#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include "manip_pile.h"
#include "manip_game.h"
#include "manip_affich.h"

#define NB_MAX 120          //NB_MAX : nombre maximum de piece dans un creux

bool Generer_Aleatoire()      //Generer aleatoirement le numero de joueur qui va commencer le jeu (soit 0 ou 1)
{
    time_t temps = time(NULL);
    srand(temps * rand() + rand());
    return rand() % 2;                //si le nombre généré est 0 c'est le 1er joueur qui va commencer sinon c'est le 2eme
}

bool Detecter_Fin(pile plateau[2][8], int nb_moitie, int dernier_joueur)//nb_moitie : la moitie du nombre total de toutes les pieces dans les creux, dernier_joueur : dernier joueur qui va jouer
{
    if(plateau[0][0].nb_element > nb_moitie || plateau[1][7].nb_element > nb_moitie) //si l'un des kalah des joueurs contient plus que nb_moitie
        return true;
    int j;
    for(j = 1; j < 7 && Estvide(plateau[dernier_joueur][j]) == 1; j++)         //Attention a ne pas tester les Kalah
    {}
    if(j == 7)                //Si tous les creux du dernier joueur (sauf son kalah) sont vides
        return true;
    else
        return false;
}

int Tester_Kalah(int ligne_creux, int colonne_creux)
{
    if(ligne_creux == 0 && colonne_creux == 0) //Tester si le creux est le kalah du 1er joueur
        return 0;
    else
    {
        if(ligne_creux == 1 && colonne_creux == 7) //Tester si le creux est le kalah du 2eme joueur
            return 1;
        else      //Tester si le creux n'est ni le kalah du 1er joueur ni du 2eme
            return -1;
    }
}

void Initial_Plateau(pile plateau[2][8], int nb_piece) //plateau : Table sur laquelle on joue le KALAH, NB_PIECE : nombre de piece quand va initialier chaque creux
{
    plateau[0][0].nb_element = 0; //initialiser le nombre d'elements de kalah 1 avec 0 pieces
    plateau[0][0].nb_max = NB_MAX; //initialiser le nombre maximimum de kalah 1 avec NB_MAX
    plateau[1][7].nb_element = 0; //initialiser le kalah 2 avec 0 pieces
    plateau[1][7].nb_max = NB_MAX; //initialiser le nombre maximimum de kalah 2 avec NB_MAX
    
    for(int i = 0; i < 2; i++)                            //i : indice ligne, j : indice colonne pour parcourir le plateau
    {
        for(int j = 1; j < 7; j++)
        {    
            plateau[i][j].nb_max = NB_MAX;                  //Définir le nombre maximum de pieces qu'un creux peut porter
            plateau[i][j].nb_element = nb_piece;            //Associer au differents creux leurs nombre de piece
        }
    }
}

void Allocation_Plateau(pile plateau[2][8])
{
    for(int i = 0; i < 2; i++)
    {
        for(int j = i; j < 7 + i; j++)
        {
            plateau[i][j].T = (int *)calloc(plateau[i][j].nb_element, sizeof(int)); //On remplit les creux par des zeros (representants les pierres)
            
            /*gestion d'erreur */
            if(plateau[i][j].T == NULL)
            {
                perror("Erreur d'allocation de memoire");
                exit(EXIT_FAILURE);
            }
        }
    }
}

void Copier_plateau(pile plateau1[2][8], pile plateau2[2][8])  //copie les donnees du plateau2 vers plateau1
{
    for(int i = 0; i < 2; i++)
    {
        for(int j = i; j < 7 + i; j++)
            plateau1[i][j] = plateau2[i][j]; //on copie les donnees du plateau 2 dans plateau1
    }
    Allocation_Plateau(plateau1); /*On remplit les creux par zeros representants les pierres (le nombre de zero
    depend de nombre d'elements de chaque creux */
}



int Jouer_Mise_aJour(pile plateau[2][8], int dernier_joueur, int *num_creux, char Donnee_Partie[3][16])  //dernier joueur : joueur qui a joueé le dernier coup
{
    int nb_piece_creux_choisi = plateau[dernier_joueur][(*num_creux)].nb_element; //conserver le nombre de piece du creux choisi

    Sleep(500); //Pour l'animation du jeu
    Vider_Pile(&plateau[dernier_joueur][(*num_creux)]); //vider le creux choisi
    int ind_parc = dernier_joueur;        //ind_par : indice de parcours du plateau
    

    while(nb_piece_creux_choisi != 0)       //parcourir le plateau dans le sens trigonometrique jusqu'a epuisement des pieces 
    {          
        if(ind_parc == 0)        //si on parcourt les creux du joueur 1 
        {
            (*num_creux)--;
            if((*num_creux) < 0)        //Au cas ou on atteint l'extremite on passe a la 2eme ligne 
            {
                (*num_creux) = 0;        //On passe a la 2eme ligne et au 1er creux (pas le kalah ,ca sera incremente de 1 par le 2eme if(ind_parc == 1))
                ind_parc = 1;
            }    
        }
        if(ind_parc == 1)                          //si on parcourt les creux du joueur 2
        {
            (*num_creux)++;
            if((*num_creux) > 7)              //Au cas ou on atteint l'extremite on passe a la 1ere ligne
            {
                (*num_creux) = 6;       //On revient a la 1ere ligne et au dernier creux (pas le kalah)
                ind_parc = 0;
            }    
        }
        int Test_Kalah = Tester_Kalah(ind_parc, (*num_creux));
        if(Test_Kalah == dernier_joueur || Test_Kalah == -1)       //A ne pas empiler le kalah de l'adversaire
        {
            Empiler(&plateau[ind_parc][(*num_creux)]);    //Empiler un creux a chaque passage dans le sens trigonometrique 
            nb_piece_creux_choisi--;                      //diminuer le nombre de piece pris de 1
        }

        //Pour l'animation du jeu
        Afficher_Plateau(plateau, Donnee_Partie);
        Sleep(500); 
           
    }
    return ind_parc;          //Retourner le numero de la ligne du creux d'arret (apres le coup)
}

void Prendre_Tout(pile plateau[2][8], int dernier_joueur, int ind_parc, int num_creux) //ind_parc : indice ligne du creux d'arret apres le coup du dernier joueur
{
    /*si la derniere piece qu'on posera appartient aux creux du joueur qui a joue le coup (sauf sans kalah) 
    et si la derniere piece est déposée dans un creux vide)*/
    if(dernier_joueur == ind_parc && Tester_Kalah(ind_parc, num_creux) == -1 && plateau[ind_parc][num_creux].nb_element == 1)
    {
        if(dernier_joueur == 0) //Au cas ou c'est le 1er joueur
        {
            if(Estvide(plateau[1][num_creux]) == false)   //Et le creux face (de l'adversaire) n'est pas vide
            {
                //Capturer les pieces du creux face puis les rajouter a la dernier piece deposée dans le creux vide et deposer le tout dans le kalah du 1er joueur  
                plateau[0][0].nb_element += plateau[1][num_creux].nb_element + 1; 
                plateau[0][0].T = (int *)calloc(plateau[0][0].nb_element + plateau[1][num_creux].nb_element + 1, sizeof(int));

                /*gestion d'erreur de l'allocation*/
                if(plateau[0][0].T == NULL)
                {
                     perror("Erreur d'allocation de l'espace memoire");
                     exit(EXIT_FAILURE);
                }

                Vider_Pile(&plateau[0][num_creux]); //Vider le creux face au creux d'arret
                Vider_Pile(&plateau[1][num_creux]); 
            }
        }
        else            // Au cas ou c'est le 2eme joueur
        {
            if(Estvide(plateau[0][num_creux]) == false)    //Et le creux face (de l'adversaire) n'est pas vide
            {
                //Capturer les pieces du creux face puis les rajouter a la dernier piece deposée dans le creux vide et deposer le tout dans le kalah du 2eme joueur
                plateau[1][7].nb_element += plateau[0][num_creux].nb_element + 1; 
                plateau[1][7].T = (int *)calloc(plateau[1][7].nb_element + plateau[1][num_creux].nb_element + 1, sizeof(int));

                /*gestion d'erreur*/
                if(plateau[1][7].T == NULL)
                {
                     perror("Erreur d'allocation de l'espace memoire");
                     exit(EXIT_FAILURE);
                }

                Vider_Pile(&plateau[1][num_creux]);  //Vider le creux face au creux d'arret 
                Vider_Pile(&plateau[0][num_creux]); //Vider le creux d'arret
            }
        }
    }
}

















