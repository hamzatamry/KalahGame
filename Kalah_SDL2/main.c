#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#include "manip_data.h"
#include "manip_pile.h"
#include "manip_game.h"
#include "manip_sdl2_1.h"
#include "manip_sdl2_2.h"
#include "manip_sdl2_3.h"
#include "manip_sdl2_4.h"
#include "manip_sdl2_5.h"

    /*Pour ne pas afficher le terminal il suffit lors de la compilation d'ajouter -mwindows*/
    /*la commande de compilation : gcc *.c -o kalah -mwindows -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image*/

int main(int argc, char *argv[])
{    
    

    int statut = EXIT_FAILURE;  //valeur de retour la fonction main
    pile plateau[2][8]; //Plateau du jeu

    TTF_Font *Font = NULL; //Le font d'ecriture

    SDL_bool App_Launched = SDL_TRUE; //Variable qui controle la boucle de l'application

    SDL_Window *Window = NULL;      //La fenetre du jeu
    SDL_Renderer *Renderer = NULL;  //Le rendu de le fenetre

    SDL_Rect menu1_Buttons[3];  //Les rectangles contenant les bouttons du menu principal (Les rectangles ou on va coller les images des bouttons)
    SDL_Rect menu_Sauvegarde[4]; //Les rectangles du menu sauvegarde
    SDL_Rect menu_Donnee[11]; /*Les rectangles contenant les bouttons et les champ de saisie et les commentaires du menu de donnee*/
    SDL_Rect menu_Jeu[30]; /*Les rectangles contenant les bouttons et messages du menu jeu*/
    SDL_Rect AnnulerContinuer[2];  //Les deux bouttons AnnulerCoup et Continuer
    
    /*Les donnees saisis dans le menu de donnee (initialises au caratere nul)*/ 
    char Donnee_Texte[4][30] = {"", "", "", ""};
    //Donnee_Texte[0] : nom de la partie, Donnee_Texte[1] : nom du 1er joueur , Donnee_Texte[2] : nom du 2eme joueur, Donnee_Texte[3] : nombre de piece initial dans les creux*/
     
    int num_button_clicked = 0; //indique le numero du boutton clique (0 indique que l'utilisateur n'as cliqué sur aucun boutton)
    
    int num_joueur;     //num_joueur : le numero du joueur qui va jouer le coup
    int nb_moitie;     //la moitie du nombre total des pieces dans tous les creux

    bool chargee = false; //Variable indique si le jeu est lancé apres chargement d'une partie deja sauvegardée
    

    if(SDL_Initial(&Window, &Renderer) != 0) //Initialiser la SDL2 , Creer la fenetre et son rendu avec gestion d'erreur   
    {
        fprintf(stderr, "Erreur : SDL_Initial()");
        goto Quit;
    }

    if(TTF_Initial(&Font) != 0) //Initialisation de la TTF avec choix du font (arial)
    {
        goto Quit;
    }

    if(IMG_Init(IMG_INIT_PNG || IMG_INIT_JPG) == 0)   //Initialisation de la IMG avec choix des extensions d'images gérees
    {
        fprintf(stderr, "Erreur : IMG_Init() : %s", IMG_GetError());
        goto Quit;
    }

    /*mettre une icon de fenetre*/
    SDL_Surface *icon = NULL;
    icon = IMG_Load("SDL2\\images\\Front_End_images1\\Icon.png"); //creation de la surface
    if(icon == NULL) //gestion d'erreur
        fprintf(stderr, "Erreur : echec de chargement de l'icon : %s", IMG_GetError());
    else
    {
        SDL_SetWindowIcon(Window, icon); //mettre icon dans la fenetre
        SDL_FreeSurface(icon); //liberation de la surface
    }
        
    /*Definir les positions des differentes rectangles des differentes menu (definir la position du boutton continuer et AnnulerCoup*/
    Position_menu1buttons(menu1_Buttons); /*Definir les positions des bouttons de menu principal (menu 1)*/
    Position_menuDonnee(menu_Donnee); //Definir les positions des messages , des champs des saisie et des bouttons du menu donnee  
    Position_menuJeu(menu_Jeu); /*Definir les positions des bouttons et message du menu jeu*/
    Position_AnnulerContinuer(AnnulerContinuer); /*Definir la position des bouttons Continuer et AnnulerCoup*/

    while(App_Launched)         //La boucle de l'application
    {
        /*Proposer le menu principal de l'application*/
        if(chargee == false)   //au cas ou la partie n'est pas chargée d'un fichier
            num_button_clicked = SDL_ScanEventFromMenu1(&App_Launched, Window, Renderer, menu1_Buttons); //Recuperer le boutton clique par l'utilisateur
        
        switch(num_button_clicked)
        {
            case 1 : SDL_Refraichir(Renderer); //Effacer la fenetre en noir
                     if(chargee == false) //Au cas ou la partie jouee n'est pas chargé d'un fichier de sauvegarde c'est le cas ou l'utilisateur a cliqué sur NouvellePartie
                     {
                         
                         Position_menuDonnee(menu_Donnee); //Definir les positions des messages , des champs des saisie et des bouttons du menu donnee
                         
                         /*Proposer le menu de donnee avec gestion des evenements correspondants*/
                         if(SDL_ScanEventFromMenuDonnee(&App_Launched, Window, Renderer, Font, menu_Donnee, Donnee_Texte) == 0)
                            continue; //reboucler pour proposer le menu principal 
                         
                         /*initialiser le plateau par les numero de piece (Donnee_Texte[3]) saisie dans le menu de donnee*/
                         int nb_piece = atoi(Donnee_Texte[3]); //Conversion du nombre de piece saisi d'une chaine a un nombre
                         Initial_Plateau(plateau, nb_piece);   //Initialisation du plateau
                         nb_moitie = (nb_piece * 12) / 2;   //la moitie du nombre total des pieces dans tous les creux
                         num_joueur = Generer_Aleatoire();    //Generer aleatoirement le numero du joueur qui va commencer la partie (0 ou 1)
                     }
                     
                     Allocation_Plateau(plateau);  //Remplir les creux avec le nombre d'elements intialises
                     
                     SDL_Refraichir(Renderer); //Effacer la fenetre en noir
                     SDL_ScanEventFromMenuJeu(&App_Launched, Window, Renderer, Font, menu_Jeu, AnnulerContinuer, plateau, Donnee_Texte, num_joueur, nb_moitie);//Proposer le menu de Jeu avec gestion des evenements correspondants
                     chargee = false;
                     break;
            case 2 : //Au cas ou l'utilisateur a cliqué sur ChargerPartie
                     SDL_Refraichir(Renderer);
                     SDL_ScanEventFromMenuSauvegarde(&App_Launched, Window, Renderer, Font, menu_Sauvegarde, Donnee_Texte, plateau,
                     &num_joueur, &nb_moitie, &chargee);
                     num_button_clicked = 1; //pour entrer dans le
                     break;

            case 3 : //Au cas ou l'utilisateur a cliqué su Quitter
                     App_Launched = SDL_FALSE;
                     break;
            default : break;

        }
    }

    /*Tout c'est passé avec succes*/
    statut = EXIT_SUCCESS;

Quit:

    /*liberation des ressources*/
    IMG_Quit(); //Desallouer l'espace memoire alloue par la fonction IMG_Init()
    TTF_Quit(); //Desallouer l'espace memoire alloue par la fonction TTF_Init()
    if(Renderer != NULL)
        SDL_DestroyRenderer(Renderer); //detruire le rendu de la fenetre
    if(Window != NULL)
        SDL_DestroyWindow(Window);  //detruire la fenetre
    SDL_Quit();

    return statut; //Renvoyer la valeur de la fonction main
}
