#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "manip_pile.h"
#include "manip_affich.h"
#include "manip_game.h"
#include "manip_saisie.h"


void menu1() //Donner a l'utilisateur le choix de choisir quelque fonctionnalite principale
{
    system("cls");
    printf("************************** WELCOME TO KALAH GAME **************************\n\n");
    printf("\t\t1 . Nouvelle partie\n\n");
    printf("\t\t2 . Charger partie\n\n");
    printf("\t\t3 . Quitter\n\n");
    printf("\n***************************************************************************\n\n");
    printf("Donner votre choix : ");
}

void nb_piece_initial(int *nb_piece) //Saisir le nombre intial de piece dans chaque creux
{
    char *nb_pieceChaine;   //Nombre de piece sous forme de chaine 
    printf("\nDonner le nombre initial de pierre dans chaque creux (min : 1 et max : 10): ");
    nb_pieceChaine = saisir_chaine(); //Saisir le nombre de piece sous forme chaine
    *nb_piece = Gerer_ErreurSaisie(nb_pieceChaine);     //Verification si la chaine represente un nombre

    while(*nb_piece <= 0 || *nb_piece > 10)      //Si la chaine saisie soit ne represente pas un nombre ou ce nombre n'est pas dans les limites
    {
        if(*nb_piece == -1)      //si la chaine ne represente pas un nombre
            printf("\t!!! Saisir invalide, Vous n'avez pas entrer un nombre\n");
        else                    //Si la chaine represente un nombre mais il n'est pas compris entre 1 et 10
            printf("\t!!! Saisir invalide Veuillez respecter les bornes\n");
        printf("\tDonner un nombre valide : ");
        nb_pieceChaine = saisir_chaine(); //Saisir le nombre de piece sous forme chaine
        *nb_piece = Gerer_ErreurSaisie(nb_pieceChaine);
    }
}

void menu2()   //Donner a l'utiliseur le choix de choisir quelque fonctionnalite secondaire (au cours du jeu)
{
    printf("1 . Choisir un creux (avec la possibilite d'annuler le coup)\n");
    printf("2 . Sauvegarder\n");
    printf("3 . Retour au menu principal\n\n");
    printf("Donner votre choix : ");
}

void Afficher_Plateau(pile plateau[2][8], char Donnee_Partie[3][16]) //Afficher l'etat du plateau 
{
    system("cls");
    int longueurNomJoueur[2];
    longueurNomJoueur[0] = strlen(Donnee_Partie[1]);
    longueurNomJoueur[1] = strlen(Donnee_Partie[2]);

    for(int k = 0; k < longueurNomJoueur[0]; k++)
    	printf(" ");
    printf("              1       2       3       4       5       6\n");

    for(int k = 0; k < longueurNomJoueur[0]; k++)
    	printf("-");
    printf("--------------------------------------------------------------------");
    for(int k = 0; k < longueurNomJoueur[1]; k++)
    	printf("-");
    printf("\n\n");
    printf("%s    ", Donnee_Partie[1]);

    for(int i = 0; i < 2; i++)               //i : indice de ligne, j : indice de colonne
    {
        if(i == 1)   
        {
            for(int k = 0; k < longueurNomJoueur[0]; k++)
                printf(" ");
            printf("            ");
        }  

        for(int j = i; j < 7 + i; j++)
            printf("[%2d]    ", plateau[i][j].nb_element); 
        
        if(i == 1)
            printf("%s", Donnee_Partie[2]);
        printf("\n\n");

    }

    for(int k = 0; k < longueurNomJoueur[0]; k++)
    	printf("-");
    printf("--------------------------------------------------------------------");
    for(int k = 0; k < longueurNomJoueur[1]; k++)
    	printf("-");
    printf("\n");
    for(int k = 0; k < longueurNomJoueur[0]; k++)
    	printf(" ");
    printf("              1       2       3       4       5       6\n\n");
}

void Choisir_Coup(pile plateau[2][8], int dernier_joueur, int *num_creux) //Saisir le coup du joueur       
{
    char *num_creuxChaine; //numero de creux saisie sous forme de chaine
    printf("\tDonner le numero de creux choisi : ");
    num_creuxChaine = saisir_chaine();
    *num_creux = Gerer_ErreurSaisie(num_creuxChaine);

    /*il n'y a pas de soucis d'appeler la fonction Estvide() avec un deuxieme argument egal a -1 car dans une condition ou il y'as des ou
      il suffit de trouver l'une des conditions verifiées sans verifier les autres (la verification se fait par ordre)*/

    //si le num de creux n'est pas compris entre 1 et 6 ou si le creux choisi est vide
    while(*num_creux <= 0 || *num_creux >= 7 || Estvide(plateau[dernier_joueur][*num_creux]) == true)
    {
        if(*num_creux == -1)  //si la chaine ne represente pas un nombre
            printf("\t!!! Saisir invalide, Vous n'avez pas entrer un nombre\n");
        else      //si la chaine represente un nombre mais qui n'est pas compris entre 0 et 
            printf("\t!!! Saisie erronee (le numero du creux doit etre compris entre 1 et 6) ou le creux choisi est vide\n");

        printf("\tVeuillez resaisir votre choix : ");
        num_creuxChaine = saisir_chaine();
        *num_creux = Gerer_ErreurSaisie(num_creuxChaine);
    }
}

int Annuler_Coup(pile plateau[2][8], int dernier_joueur, int *num_creux) //Annuler le dernier coup joue au cas ou l'utilisateur s'est trompe
{
    char *AnnulCoupChaine;   //une chaine representant le choix d'annuler le coup
    int AnnulCoup;    //variable entiere representant le choix d'annuler le coup
    char *num_creux_chaine;    //une chaine representant le choix du numero de creux

    printf("Voulez vous annuler votre coup !!! si oui taper 1 sinon taper autre nombre\n");
    printf("Taper votre choix : ");
    AnnulCoupChaine = saisir_chaine();
    AnnulCoup = Gerer_ErreurSaisie(AnnulCoupChaine);

    /*Si le choix n'est pas un nombre*/
    while(AnnulCoup == -1)
    {
        printf("\t!!! Vous n'avez pas entrer un nombre\n");
        printf("\tVeuillez resaisir votre choix : ");
        AnnulCoupChaine = saisir_chaine();
        AnnulCoup = Gerer_ErreurSaisie(AnnulCoupChaine);
    }

    /*Si le choix est 1 c'est a dire l'utilisateur veut annuler son coup*/
    if(AnnulCoup == 1)
    {
        return 1;  //Au cas ou il a annulé son coup on retourne 1
    }
    else
    {
        //Au cas ou il n'a pas annulé son coup on retourne 0
        return 0;
    }
}

void Gagnant(pile kalah1, pile kalah2) //Declarer le gagnant de la partie joueee
{
    if(kalah1.nb_element > kalah2.nb_element)
        printf("\t ********** Felicitation : Le joueur 1 a gagne la partie **********\n\n");
    else
    {
        if(kalah1.nb_element < kalah2.nb_element)
            printf("\t ********** Felicitation : Le joueur 2 a gagne la partie **********\n\n");
        else
            printf("\t ********** Partie terminee en egalite **********\n\n");
    }
}

void Donnee(char Donnee_Partie[3][16])  //Saisir les donnees  de la partie
{
    system("cls");
    char *DonnePartieChaine;         //chaine dynamique qui peut etre de n'importe quelle longueur

    printf("Entrer les donnees de la partie :\n");
    fflush(stdin);      //Pour vider le buffer
    /*l'utilisateur peut entrer une chaine de n'importe quelle longueur mais on va verifier si ca depasse pas les limites , si elle depasse
      les limites on affiche un message d'erreur puis on redonne la saisie a l'utilisateur sinon on copie la chaine dans Donnee_Partie*/

    for(int i = 0; i < 3; i++)
    {
        switch(i)  //pour afficher le message adequat 
        {
            case 0 : printf("\tDonnner le nom de la partie : ");
                     break;
            case 1 : printf("\tDonner le nom du 1er joueur : ");
                     break;
            case 2 : printf("\tDonner le nom du 2eme joueur : ");
            default : break;
        }

        DonnePartieChaine = saisir_chaine();            //Saisir la chaine 

        /*tant que la longueur de la chaine n'est pas valide ou la chaine n'est pas du texte alphabetique*/
        while(Verification_ChaineLongueur(DonnePartieChaine) == false || Verification_ChaineTexte(DonnePartieChaine) == false)   
        {   
            printf("\tla chaine n'est pas du texte alphabetique ou la longueur de la chaine saisie depasse 15\n"); //Message
            printf("\tResaisir la donnee : ");
            DonnePartieChaine = saisir_chaine(); //Resaisir la chaine
        }
        /*Apres verification on copie la chaine saisie dans Donnee_Partie (apres s'assurer de ca longueur)*/
        strcpy(Donnee_Partie[i], DonnePartieChaine); 
    }
}












