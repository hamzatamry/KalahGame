#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include "manip_pile.h"

void Empiler(pile *creux) //Depot de la piece dans le creux
{
    if(creux -> nb_element >= creux -> nb_max)
    {
        printf("La pile est pleine\n");
        Sleep(1000);
    }     
    else
    {
         creux -> T = (int *)realloc(creux -> T, (creux -> nb_element + 1) * sizeof(int)); //Reallocation de l'espace necessaire pour depose la piece
         creux -> T[creux -> nb_element] = 0; //deposer la piece (ecrire dans la case l'entier 0)

         /*gestion d'erreur*/
         if(creux -> T == NULL)
         {
             perror("Erreur d'allocation de l'espace memoire");
             exit(EXIT_FAILURE);
         }

         creux -> T[creux -> nb_element] = 0; //Deposer l'element dans le creux (représenté par le num 0)
        (creux -> nb_element)++;   //Incrementer le nombre d'elements du creux
    }
}

bool Estvide(pile creux) //Tester si le creux est vide
{
    return creux.nb_element == 0 ? true : false; //Si le creux est vide elle retourne TRUE sinon elle retourne FALSE
}

void Vider_Pile(pile *creux)   //Vider le creux
{
    if(creux -> nb_element == 0)   //Tester si le creux est deja vide
    {
        printf("La pile est vide\n");
        Sleep(1000);
    }   
    else
        (creux -> nb_element) = 0; //Si le creux n'est pas vide on remet son nombre d'elements e nul
}


