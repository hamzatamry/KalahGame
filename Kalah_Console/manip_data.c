#include <stdio.h>
#include <string.h>
#include "manip_data.h"

int Sauvegarder(char Donnee_partie[3][16], pile plateau[2][8], int dernier_joueur, int nb_moitie) //nom_partie : le nom de la partie et aussi le nom de fichier ou on va sauvegarder, plateau : table du jeu, entier qui represente le num de dernier joueur qui a joue
{
    char path[72] = "PartiesSauvegardees\\";        //le path ou on a va sauvegarder le fichier dans le dossier (PartiesSauvegardees)
    strcat(path, Donnee_partie[0]);    //Ajouter au path le nom de fichier a sauvegarder

    FILE *f;
    f = fopen(path, "wb"); //Ouvrir le flux en mode ecriture du fichier binaire qui porte le nom de la partie dans le path

    /*gestion d'erreur*/
    if(f == NULL)
    {
        return -1;
    }
    
    else
    {
        fwrite(Donnee_partie[0], sizeof(Donnee_partie[0]), 1, f); //On ecrit dans le fichier le nom de la partie
        fwrite(Donnee_partie[1], sizeof(Donnee_partie[1]), 1, f); //On ecrit dans le fichier le nom du joueur 1
        fwrite(Donnee_partie[2], sizeof(Donnee_partie[2]), 1, f); //On ecrit dans le fichier le nom du joueur 2
        fwrite(&dernier_joueur, sizeof(int), 1, f); //On ecrit dans le fichier le num du dernier joueur qui a joue
        fwrite(&nb_moitie, sizeof(int), 1, f);   //On ecreit dans le fichier le nb_moitie
        for(int i = 0; i < 2; i++)  //Indices de parcours du plateau (i ligne, j colonne)
        {
            for(int j = i; j < 7 + i; j++)    //Vu la structure du plateau pour eviter les deux cases non utilisables dans le jeu (j = i; j < 7 + i)
            {
                fwrite(&(plateau[i][j].nb_element), sizeof(int), 1, f);    //On ecrit les donnees du plateau dans le fichier
                fwrite(&(plateau[i][j].nb_max), sizeof(int), 1, f);    
            }
        }
        fclose(f);
        return 0;       //Valeur indiquant que le sauvegarde s'est fait correctement
    }
}

int Charger(char Donnee_partie[3][16], pile plateau[2][8], int *dernier_joueur, int *nb_moitie)//Charger le contenu du fichier binaire qui contient les informations sur la partie a chargee
{
    char path[72] = "PartiesSauvegardees\\";        //le path ou on a va charger le fichier du dossier (PartiesSauvegardees)
    strcat(path, Donnee_partie[0]);    //Ajouter au path le nom de fichier a charger

    FILE *f;
    f = fopen(path, "rb"); //Ouvrir le flux en mode lecture du fichier binaire qui porte le nom de la partie dans le path

    /*gestion d'erreur*/
    if(f == NULL)
    {
        return -1;        //Valeur d'erreur;
    }
        
    else
    {
        fread(Donnee_partie[0], sizeof(Donnee_partie[0]), 1, f);//On lit dans le fichier le nom de la partie
        fread(Donnee_partie[1], sizeof(Donnee_partie[1]), 1, f); //On lit dans le fichier le nom du joueur 1
        fread(Donnee_partie[2], sizeof(Donnee_partie[2]), 1, f); //On lit dans le fichier le nom du joueur 2
        fread(dernier_joueur, sizeof(int), 1, f); //On lit dans le fichier le num du dernier joueur qui a joue
        fread(nb_moitie, sizeof(int), 1, f); //On lit du fichier le nb_moitie
        for(int i = 0; i < 2; i++) //Indices de parcours du plateau (i ligne, j colonne)
        {
            for(int j = i; j < 7 + i; j++)    //Vu la structure du plateau pour eviter les deux case non utilisables dans le jeu
            {
                fread(&(plateau[i][j].nb_element), sizeof(int), 1, f);    //On lit les donnees du plateau du fichier
                fread(&(plateau[i][j].nb_max), sizeof(int), 1, f);    
            }
        }
        fclose(f);
        return 0;          //Valeur indiquant que le chargement s'est fait correctement
    }
}




