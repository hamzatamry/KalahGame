#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>      
#include <windows.h>
#include "manip_data.h"
#include "manip_pile.h"
#include "manip_game.h"
#include "manip_affich.h"
#include "manip_saisie.h"

int main()
{
    system("color 70"); //Colorer invite de commande
    pile plateau[2][8]; //C’est le plateau du jeu qui contient tous les creux
    pile plateauSecours[2][8]; //le plateau necessaire au cas ou le joueur a annuler son coup

    bool Program_Launched = true;      //variable qui controle la boucle de l'application
    bool Game_Launched = true;  //Variable qui controle la boucle du jeu
    int num_creux;  //numero du creux choisi
    int option; //option choisie du menu 1 ou du menu 2 sous forme d'entier;
    char *option_chaine; //option sous forme de chaine de caractere;
    int nb_piece;  //nb_piece qu'on va intialiser chacun des creux (sauf les kalah)
    int num_joueur;     //num_joueur : le numero du joueur qui va jouer le coup
    int nb_moitie;     //la moitie du nombre total des pieces dans tous les creux
    int ind_parc;   //indice ligne du creux d'arret apres le jeu du coup
    int AnnulCoup = 0; //variable indique si le joueur veut annuler son coup (0 : pas d'annulation du coup, 1 : annulation du coup)
    char Donnee_Partie[3][16];  //tableau de chaines de caracteres contenant le nom de la partie (0), nom du 1er joueur (1), nom du 2eme joueur (2)
    bool chargee = false; //Variable indique si le jeu est lancé apres chargement d'une partie deja sauvegardée
    char *nomdefichier;  //nom du fichier a saisir

    
    while(Program_Launched)     //Boucle de l'application
    {
        if(chargee == false)   //Au cas ou la partie jouee n'est pas chargé d'un fichier de sauvegarde
        {
            menu1();              //Proposer le 1er menu a l'utilisateur
            option_chaine = saisir_chaine();    //Saisir la chaine de caractere par l'utilisateur
            option = Gerer_ErreurSaisie(option_chaine);   //Gestion d'erreur (verification si la chaine represente un nombre)
            if(option == -1)    //Si la chaine ne represente pas un nombre
            {
                printf("!!! La saisie n'est pas un nombre\n");
                Sleep(1000); //Bloquer l'affichage pour 1 sec
                continue; //reproposer le menu principal
            }
        }       
        switch(option)
        {
            case 1 : if(chargee == false) //Au cas ou la partie jouee n'est pas chargé d'un fichier de sauvegarde (nouvelle partie)
                     {
                         Donnee(Donnee_Partie);    //Entrer les donnees de la partie
                         nb_piece_initial(&nb_piece);        //initialiser les creux par un nombre de piece
                         nb_moitie = (nb_piece * 12) / 2;   //la moitie du nombre total des pieces dans tous les creux
                         Initial_Plateau(plateau, nb_piece);     //Initialisation du plateau du jeu avec initialisation des creux et des kalahs sans allocation memoire
                         num_joueur = Generer_Aleatoire();    //Generer aleatoirement le numero du joueur qui va commencer la partie (0 (joueur1) ou 1 (joueur2))
                     }

                     Allocation_Plateau(plateau); //Allocation de la memoire dans chaque creux (ca depend du nombre d'elements de chaque creux) cad remplir les creux avec les cailloux
                     Game_Launched = true;            //On lance le jeu
                     while(Game_Launched)                  //Boucle du jeu 
                     {
                         Afficher_Plateau(plateau, Donnee_Partie);  //Afficher le plateau du jeu
                         printf("C'est le tour du joueur %d (%s)\n\n", num_joueur + 1, Donnee_Partie[num_joueur + 1]);

                         if(Detecter_Fin(plateau, nb_moitie, num_joueur) ==  true)  //Detection de fin de la partie
                         {
                             Gagnant(plateau[0][0], plateau[1][7]);  //On declare le gagnant de la partie (ou egalite)
                             system("pause");                      //On bloque l'affichage pour voir le message du gagnant;
                             break;                     //On sort de la boucle du jeu
                         }

                         menu2();   //Proposer un 2eme menu
                         option_chaine = saisir_chaine();    //Saisir la chaine de caractere par l'utilisateur
                         option = Gerer_ErreurSaisie(option_chaine);   //Gestion d'erreur (verification si la chaine represente un nombre)
                         if(option == -1)    //Si la chaine ne represente pas un nombre
                         {
                            printf("!!! La saisie n'est pas un nombre\n");
                            Sleep(1000);      //Bloquer l'affichage pour 1 sec
                            continue; //reproposer le menu 2
                         }

                         switch(option)
                         {
                             case 1 : /*Au cas ou il choisit choisir coup du menu2*/
                                      /*Choisir le coup*/
                                      Choisir_Coup(plateau, num_joueur, &num_creux); 

                                      /*copie plateau dans plateauSecours comme (une sorte de sauvegarde de l'etat du plateau ancien)*/
                                      Copier_plateau(plateauSecours, plateau);

                                      /*mise a jour du plateauSecours*/
                                      ind_parc = Jouer_Mise_aJour(plateauSecours, num_joueur, &num_creux, Donnee_Partie);
                                      
                                      /*Si apres le jeu du coup le joueur tombe sur l'un de ses creux vide (sauf son kalah) il capture au cas ou 
                                      le creux face a celui du creux d'arret n'est pas vide ses pieces puis les rajoute a la derniere piece deposee 
                                      dans le creux vide et il rajoute le tout dans son propre kalah*/
                                      Prendre_Tout(plateauSecours, num_joueur, ind_parc, num_creux);

                                      AnnulCoup = Annuler_Coup(plateau, num_joueur, &num_creux);

                                      //si le joueur ne veux paz annuler son dernier coup joue
                                      if(AnnulCoup == 0)
                                      {
                                          /*on copie le plateauSecours dans plateau pour remise a jour du plateau car il n'a pas annulé le coup*/
                                          Copier_plateau(plateau, plateauSecours);
                                      }

                                      else  //si le joueur veut annuler son coup
                                      {
                                          continue;         //reboucler pour reproposer le menu2 (boucle du jeu)
                                      }
                                       
                                      //Si il tombe dans son kalah il rejoue
                                      if(Tester_Kalah(num_joueur, num_creux) == num_joueur) 
                                      {
                                          printf("play again :)\n");
                                          Sleep(1000);
                                          continue; //reboucler pour que le joueur rejoue son coup
                                      }
                                      break;

                             case 2 : /*Au cas ou il choisit sauvegarder du menu2*/
                                      /*Si la sauvegarde se fait sans erreur*/
                                      if(Sauvegarder(Donnee_Partie, plateau, num_joueur, nb_moitie) == 0)
                                      {
                                          printf("Partie Sauvegardee :)\n");
                                      }
                                      else 
                                      {
                                          printf("Sauvegarde echouee :(\n");
                                      }
                                      Sleep(1000); //Bloquer l'affichage pour 1 sec               
                                      continue;                  //Reboucler pour reproposer le menu2 a l'utilisateur apres sauvegarde

                             case 3 : /*Au cas ou il choisit de revenir au menu principal*/
                                      Game_Launched = false;  //Quitter la boucle du jeu 
                                      continue;

                             default : /*au cas ou il a choisi un nombre non existant dans le menu 2*/
                                       printf("!!! Taper un choix compris entre 1 et 3\n");    
                                       Sleep(1000);  //Bloquer l'affichage pour 1 sec
                                       continue;  //reprose
                         }
                         num_joueur = (num_joueur + 1) % 2;        //Pour passer au joueur suivant
                     }
                     chargee = false;
                     continue;                              //Reboucler pour reproposer le menu1 a l'utilisateur

            case 2 : //Pour charger une partie deja sauvegardée
                     printf("Donner le nom du fichier a ouvrir : ");     
                     nomdefichier = saisir_chaine();          //Saisir le nom du fichier
                     /*Si la longueur du nom de fichier est valide*/
                     if(Verification_ChaineLongueur(nomdefichier) == true)
                        strcpy(Donnee_Partie[0], nomdefichier);        //on copie le nom de fichier dans nom de partie (Donnee_partie[0])
                     
                     if(Charger(Donnee_Partie, plateau, &num_joueur, &nb_moitie) == 0)  //Verification si le fichier existe ou nn
                     {
                         chargee = true;
                     }
                     else
                     {
                         printf("!!! Nom de fichier inexistant ou trop long (faut pas depasser 15 caracteres)\n");
                         Sleep(1000);
                     }
                     option = 1;   //Pour entrer dans la boucle du jeu apres chargement de donnee du fichier
                     continue;  //entrer dans la boucle de l'application

            case 3 : Program_Launched = false;       //Arret de la boucle d'application (sortir completement du jeu)
                     break;

            default : /*au cas ou il a choisi un nombre non existant dans le menu1*/
                      printf("!!! Taper un choix compris entre 1 et 3\n");
                      Sleep(1000);
                      continue; //reproposer le menu principal

        }
    }
}
