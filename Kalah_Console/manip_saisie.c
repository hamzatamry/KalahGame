#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>      //Pour la fonction isalpha qui verifie si le caractere est un un caractere alphabetique
#include "manip_saisie.h"


char *saisir_chaine()
{
    char *CH, c;       //CH : pointeur sur chaine de caractere, c : variable de type char pour contenir temporairement le caractere saisi
    int i = 0;
    CH = (char *)malloc(sizeof(char));  //Allocation de l'espace memoire necessaire pour une lettre

    /*gestion d'erreur*/
    if(CH == NULL)
    {
        perror("Erreur d'allocation de la memoire");
        exit(EXIT_FAILURE); //Quitter le programme
    }


    while((c = getchar()) != '\n')   //Tant que le caractere saisie n'est pas le caractere entree
    {
        CH[i++] = c;        //placer le caratere dans la chaine
        CH = (char *)realloc(CH, (i + 1) * sizeof(char));   //Allouer l'espace memoire necessaire pour la lettre suivant

        /*gestion d'erreur*/
        if(CH == NULL)
        {
            perror("Erreur de reallocation de la memoire");
            exit(EXIT_FAILURE); //Quitter le programme
        }
    }
    CH[i] = '\0';
    return CH;
}

bool Verification_ChaineNombre(char *Chaine_saisie)  //Verifie si la chaine represente un nombre
{
    //Garder la longueur de la chaine dans une variable pour ne pas appeler dans la boucle plusieurs fois strlen()
    int string_lenght = strlen(Chaine_saisie);

    if(strcmp(Chaine_saisie, "") == 0) //si il a tape entree
        return false;

    /*verification caractere par caractere si le caractere est un caractere nombre*/
    int i; //compteur
    for(i = 0; i < string_lenght && ('0' <= Chaine_saisie[i] && Chaine_saisie[i] <= '9'); i++)
    {}
    if(i == string_lenght)  //Si la chaine represente un nombre    
        return true;
    else
        return false;
}

/*Dans les menu du jeu l'utilisateur doit entrer un nombre , il se peut qu'il entre une chaine de caractere ou un caractere (si on utilise
  le scanf("%d", ) avec le formatage %d ca creera une erreur c'est pour cela on considerera la saisie d'une chaine de caractere a la place d'un
  nombre , par la suite  ca sera facile de verifier si la chaine est un nombre valide (representant un nombre du menu)*/

int Gerer_ErreurSaisie(char *Chaine_saisie)    
{
    if(Verification_ChaineNombre(Chaine_saisie) == true)  //Si la chaine represente un nombre
        return atoi(Chaine_saisie); // On fait la conversion de la chaine en nombre puis on retourne ce nombre
    else
        return -1; //c'est une saisie invalide (-1 represente que la saisie n'est pas faite correctement)
}

bool Verification_ChaineLongueur(char *Chaine_saisie)
{
    int chaine_lenght = strlen(Chaine_saisie); //On recupere la longueur de la chaine saisie
    if(chaine_lenght > 15)            //si la longueur de la chaine execede 49 caracteres
        return false;        //On renvoie une valeur indiquant que la longueur de la chaine n'est pas valide
    else
        return true; //On renvoie une valeur indiquant que la longueur de la chaine est valide   
}

bool Verification_ChaineTexte(char *Chaine_saisie)
{
    int chaine_lenght = strlen(Chaine_saisie); //On recupere la longueur de la chaine saisie

    if(strcmp(Chaine_saisie, "") == 0) //si l'utilisateur a saisi le entree 
        return false;

    int i = 0; //Compteur
    //Parcourir la chaine est verifier caractere par caractere si c'est un caratere alphabetique ou nn
    for(i = 0; i < chaine_lenght && isalpha(Chaine_saisie[i]) != 0; i++) 
    {}

    if(i == chaine_lenght) //si la chaine est du texte alphabetique
        return true;
    else
        return false;
}