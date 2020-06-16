#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "manip_data.h"
#include "manip_pile.h"
#include "manip_game.h"
#include "manip_sdl2_1.h"
#include "manip_sdl2_4.h"

void Position_menuJeu(SDL_Rect menu_Jeu[30])
{
    /*le rectangle qui contient le nom du joueur 1*/
    menu_Jeu[0].x = 20;
    menu_Jeu[0].y = 100;
    menu_Jeu[0].w = 180;
    menu_Jeu[0].h = 100;

    /*les rectangles qui contienent le numero des creux et le nombre de piece de chaque creux du joueur 1 sauf son kalah*/
    for(int i = 1, x_passage = 200; i < 7; i++, x_passage += 67)
    {
            /*Les rectangles contenant les numeros des creux du joueur 1*/
            menu_Jeu[i].x = x_passage;
            menu_Jeu[i].y = 60;
            menu_Jeu[i].w = 67;
            menu_Jeu[i].h = 40;

            /*Les rectangles contenant le nombre de piece dans chaque creux du joueur 1*/
            menu_Jeu[i + 6].x = x_passage;
            menu_Jeu[i + 6].y = 100;
            menu_Jeu[i + 6].w = 67;
            menu_Jeu[i + 6].h = 100;
    }

    /*le rectangle qui contient le nombre de piece dans le Kalah 1*/
    menu_Jeu[13].x = 100;
    menu_Jeu[13].y = 200;
    menu_Jeu[13].w = 100;
    menu_Jeu[13].h = 100;

    /*le rectangle qui contient le message suivant "KALAH GAME"*/
    menu_Jeu[14].x = 200;
    menu_Jeu[14].y = 200;
    menu_Jeu[14].w = 400;
    menu_Jeu[14].h = 100;

    /*le rectangle qui contient le nombre de piece dans le Kalah 2*/
    menu_Jeu[15].x = 600;
    menu_Jeu[15].y = 200;
    menu_Jeu[15].w = 100;
    menu_Jeu[15].h = 100;

    /*les rectangles qui contienent le numero des creux et le nombre de piece de chaque creux du joueur 2 sauf son kalah*/
    for(int i = 16, x_passage = 200; i < 22; i++, x_passage += 67)
    {
            /*Les rectangles contenant le nombre de piece dans chaque creux du joueur 1*/
            menu_Jeu[i].x = x_passage;
            menu_Jeu[i].y = 300;
            menu_Jeu[i].w = 67;
            menu_Jeu[i].h = 100;

            /*Les rectangles contenant les numeros des creux du joueur 1*/
            menu_Jeu[i + 6].x = x_passage;
            menu_Jeu[i + 6].y = 400;
            menu_Jeu[i + 6].w = 67;
            menu_Jeu[i + 6].h = 40;
    }

    /*le rectangle qui contient le nom du joueur 2*/
    menu_Jeu[28].x = 600;
    menu_Jeu[28].y = 300;
    menu_Jeu[28].w = 180;
    menu_Jeu[28].h = 100;

    /*le rectangle qui contient le boutton sauvegarder*/
    menu_Jeu[29].x = 20;
    menu_Jeu[29].y = 550;
    menu_Jeu[29].w = 160;
    menu_Jeu[29].h = 50;

    /*le rectangle qui continet le boutton retour*/
    menu_Jeu[30].x = 650;
    menu_Jeu[30].y = 550;
    menu_Jeu[30].w = 130;
    menu_Jeu[30].h = 50;

}

int SDL_menuJeu(SDL_Window *Window, SDL_Renderer *Renderer, TTF_Font *Font, SDL_Rect menu_Jeu[30], 
                pile plateau[2][8], char Donnee_Texte[4][30], int num_button_intersect)
{ 
    
    /*La couleur du texte qui sera saisi*/
    SDL_Color Rouge = {255, 0, 0, 255}, Jaune = {255, 150, 0, 255}, Bleu = {0, 0, 255, 255}, Vert = {0, 255, 0, 255}, Blanc = {255, 255, 255, 255};

    /*Les surfaces et les textures necessaires qui seront collees dans les rectangles*/
    SDL_Surface *menu_JeuSurface[30];
    SDL_Texture *menu_JeuTexture[30];

    /*Creation des surfaces correspondantes au nom des deux joueurs et au message "KALAH GAME"*/
    menu_JeuSurface[0] = TTF_RenderText_Solid(Font, Donnee_Texte[1], Rouge);  //Joueur 1
    menu_JeuSurface[14] = TTF_RenderText_Solid(Font, "KALAH GAME", Jaune);  //message "KALAH GAME"
    menu_JeuSurface[28] = TTF_RenderText_Solid(Font, Donnee_Texte[2], Bleu);  //Joueur 2

    /*Creation des surfaces correspondantes aux numero des creux et le nombre de piece dans chaque creux du joueur 1*/
    for(int i = 1; i < 7; i++)
    {
        /*Creation des surfaces correspondantes aux numero des creux du joueur 1*/
        char numero_creux[2];
        sprintf(numero_creux, "%d", i); //Tranformation du nombre entier en chaine de caratere
        menu_JeuSurface[i] = TTF_RenderText_Solid(Font, numero_creux, Blanc);

        /*Creation des surfaces correspondantes au nombre de piece dans chaque creux du joueur 1*/
        char nb_piece_creux[3];
        sprintf(nb_piece_creux, "%d", plateau[0][i].nb_element);//Transformation du nombre de piece dans un creux a une chaine de caractere

        if(i + 6 == num_button_intersect)
        {
            menu_JeuSurface[i + 6] = TTF_RenderText_Solid(Font, nb_piece_creux, Vert);

        }     
        else
        {
            menu_JeuSurface[i + 6] = TTF_RenderText_Solid(Font, nb_piece_creux, Jaune);
        }
        
    }

    /*Creation des surfaces correspondantes au kalah 1 et au kalah 2*/
    char nb_pieceKalah[3];

    /*kalah1*/
    sprintf(nb_pieceKalah, "%d", plateau[0][0].nb_element);
    menu_JeuSurface[13] = TTF_RenderText_Solid(Font , nb_pieceKalah, Rouge);

    /*kalah2*/
    sprintf(nb_pieceKalah, "%d", plateau[1][7].nb_element);
    menu_JeuSurface[15] = TTF_RenderText_Solid(Font , nb_pieceKalah, Bleu);

    /*Creation des surfaces correspondantes aux numero des creux et le nombre de piece dans chaque creux du joueur 2*/
    for(int i = 16; i < 22; i++)
    {
        /*Creation des surfaces correspondantes au nombre de piece dans chaque creux du joueur 2*/
        char nb_piece_creux[3];
        sprintf(nb_piece_creux, "%d", plateau[1][i - 15].nb_element);//Transformation du nombre de piece dans un creux a une chaine de caractere
        
        if(i == num_button_intersect)
            menu_JeuSurface[i] = TTF_RenderText_Solid(Font, nb_piece_creux, Vert);
        else
        {
            menu_JeuSurface[i] = TTF_RenderText_Solid(Font, nb_piece_creux, Jaune);
        }

        /*Creation des surfaces correspondantes aux numero des creux du joueur 2*/
        char numero_creux[2];
        sprintf(numero_creux, "%d", i - 15); //Tranformation du nombre du creux en chaine de caratere
        menu_JeuSurface[i + 6] = TTF_RenderText_Solid(Font, numero_creux, Blanc);
    }

    /*Creation des surfaces correspondantes au boutton Sauvegarder et boutton retour*/
    menu_JeuSurface[29] = SDL_LoadBMP("SDL2\\images\\Front_End_images3\\Sauvegarder.bmp");       //Boutton Sauvegarder
    menu_JeuSurface[30] = SDL_LoadBMP("SDL2\\images\\Front_End_images3\\Retour.bmp");       //Boutton Retour
    
    switch(num_button_intersect)  //Au cas ou la souris a intersecte l'un des bouttons ou creux
    {   
        case 29 :  //colorer le boutton Sauvegarder
                   menu_JeuSurface[29] = SDL_LoadBMP("SDL2\\images\\Front_End_images3\\SauvegarderColoree.bmp");//Boutton Sauvegarder
                   break;
        case 30 :  //colorer le boutton retour
                   menu_JeuSurface[30] = SDL_LoadBMP("SDL2\\images\\Front_End_images3\\RetourColoree.bmp"); //Boutton Retour
                   break;
    }

    /*Gestion d'erreur de creations des surfaces*/
    for(int i = 0; i < 31; i++)
    {
        if(menu_JeuSurface[i] == NULL)
        {
            fprintf(stderr, "Erreur : Creation des surfaces echouee : %s\n", SDL_GetError());
            return -1; //Valeur d'erreur
        }
    }

    /*Transformation des surfaces en textures*/
    for(int i = 0; i < 31; i++)
    {
        menu_JeuTexture[i] = SDL_CreateTextureFromSurface(Renderer, menu_JeuSurface[i]);
        /*Liberation des surfaces utilisees*/
        SDL_FreeSurface(menu_JeuSurface[i]);
    }

    /*Gestion d'erreur de creation des textures*/
    for(int i = 0; i < 31; i++)
    {
        if(menu_JeuTexture[i] == NULL)
        {
            fprintf(stderr, "Erreur : Creation des Textures echouee : %s\n", SDL_GetError());
            return -1; //Valeur d'erreur
        }
    }

    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    /*Collage des textures dans les rectangles correspondants*/
    for(int i = 0; i < 31; i++)
    {
        SDL_RenderCopy(Renderer, menu_JeuTexture[i], NULL, &menu_Jeu[i]);
        SDL_RenderDrawRect(Renderer, &menu_Jeu[i]);
    }

    /*Destruction des textures*/
    for(int i = 0; i < 31; i++)
    {
        SDL_DestroyTexture(menu_JeuTexture[i]);
    }

    /*Mise a jour du rendu de la fenetre*/
    SDL_RenderPresent(Renderer);
    return 0; //Valeur de succes
}

int SDL_MouseIntersect_menuJeuButtons(SDL_Rect menu_Jeu[30], int mouse_x, int mouse_y)
{
    /*si l'intersection ou le clique se fait avec l'un des creux du joueur 1*/
    for(int i = 7; i < 13; i++)
    {
        if((menu_Jeu[i].x <= mouse_x) && (mouse_x <= (menu_Jeu[i].x + menu_Jeu[i].w))
        && (menu_Jeu[i].y <= mouse_y) && (mouse_y <= (menu_Jeu[i].y + menu_Jeu[i].h)))
        {
            return i;
        }
    }

    /*si l'intersection ou le clique se fait avec l'un des creux du joueur 2*/
    for(int i = 16; i < 22; i++)
    {
        if((menu_Jeu[i].x <= mouse_x) && (mouse_x <= (menu_Jeu[i].x + menu_Jeu[i].w))
        && (menu_Jeu[i].y <= mouse_y) && (mouse_y <= (menu_Jeu[i].y + menu_Jeu[i].h)))
        {
            return i;
        }
    }

    /*Si l'intersection ou le clique se fait avec soit le boutton Sauvegarder ou Retour*/

    for(int i = 29; i < 31; i++)
    {
        if((menu_Jeu[i].x <= mouse_x) && (mouse_x <= (menu_Jeu[i].x + menu_Jeu[i].w))
        && (menu_Jeu[i].y <= mouse_y) && (mouse_y <= (menu_Jeu[i].y + menu_Jeu[i].h)))
        {
            return i;
        }
    }
    
    /*Si l'intersection ne se fait avec aucun des creux ou des bouttons*/
    return 0; 
}

int SDL_Afficher_num_joueur(SDL_Renderer *Renderer, TTF_Font *Font, int num_joueur, char Donnee_Texte[4][30])
{
    SDL_Color TextColor = {255, 0, 0, 255}; //couleur du texte rouge

    SDL_Rect Barre_Message = {200, 460, 400, 60};
    SDL_RefraichirRect(Renderer, Barre_Message);   //Refraichir la barre de message

    SDL_Surface *Barre_MessageSurface = NULL;
    SDL_Texture *Barre_MessageTexture = NULL;

    char message[40] = "C'est le tour du joueur ";
    char num_joueurChaine[2]; 
    sprintf(num_joueurChaine, "%d", num_joueur + 1); //conversion du nombre de joueur en une chaine
    strcat(message, num_joueurChaine);  //ajouter le nombre de joueur dans le message
    strcat(message, " ");  //ajouter un petit espace
    strcat(message, Donnee_Texte[num_joueur + 1]); //ajouter le nom de joueur dans le message

    /*Creation de la surface qui contient le message*/
    Barre_MessageSurface = TTF_RenderText_Solid(Font, message, TextColor);

    /*gestion d'erreur de creation de la surface*/
    if(Barre_MessageSurface == NULL)
    {
        fprintf(stderr, "Erreur : Creation de la surface : %s\n", TTF_GetError());
        return -1;
    }

    Barre_MessageTexture = SDL_CreateTextureFromSurface(Renderer, Barre_MessageSurface);
    SDL_FreeSurface(Barre_MessageSurface);

    /*gestion d'erreur de creation de la texture*/
    if(Barre_MessageTexture == NULL)
    {
        fprintf(stderr, "Erreur : Creation de la texture : %s\n", SDL_GetError());
        return -1;
    }

    //coller le message dans la barre de message
    SDL_RenderCopy(Renderer, Barre_MessageTexture, NULL, &Barre_Message);

    /*Destruction de la texture*/
    SDL_DestroyTexture(Barre_MessageTexture);

    SDL_RenderPresent(Renderer);  //mise a jour du rendu
}


int TesterCreuxChoisiJoueur(SDL_Renderer *Renderer, TTF_Font *Font, int num_button_clicked, int num_joueur)
{
    /*si le boutton clique correspond au creux du joueur 1*/
    if((7 <= num_button_clicked && num_button_clicked <= 12) && num_joueur == 0)
        return 1;

    /*si le boutton clique correspond au creux du joueur 2*/
    if((16 <= num_button_clicked && num_button_clicked <= 21) && num_joueur == 1)
        return 1;

    /*si le boutton clique est soit sauvegarder ou retour*/
    if(num_button_clicked == 29 || num_button_clicked == 30)
        return 0;
    

    /*si le creux n'est pas l'un du joueur qui a joué le coup*/
    /*Affichage d'un message d'erreur */
    SDL_Rect Barre_Message = {200, 550, 400, 50};
    SDL_AfficherMessage(Renderer, Font, Barre_Message, "Vous avez choisi un creux de l'autre joueur");
    SDL_Delay(1000);
    SDL_RefraichirRect(Renderer, Barre_Message);
    return 0;
}

void Position_AnnulerContinuer(SDL_Rect AnnulerContinuer[2])
{
    /*le rectangle qui contient le boutton Continuer*/
    AnnulerContinuer[0].x = 250;
    AnnulerContinuer[0].y = 550;
    AnnulerContinuer[0].w = 100;
    AnnulerContinuer[0].h = 50;

    /*le rectangle qui contient le boutton Annuler*/
    AnnulerContinuer[1].x = 400;
    AnnulerContinuer[1].y = 550;
    AnnulerContinuer[1].w = 100;
    AnnulerContinuer[1].h = 50;
}

int SDL_AfficherBouttonAnnulerCoup(SDL_Renderer *Renderer, SDL_Rect AnnulerContinuer[2], int num_button_intersect)
{
    SDL_Surface *AnnulerContinuerSurface[2];
    SDL_Texture *AnnulerContinuerTexture[2];

    /*creation des surfaces*/
    AnnulerContinuerSurface[0] = SDL_LoadBMP("SDL2\\images\\Front_End_images3\\Continuer.bmp");
    AnnulerContinuerSurface[1] = SDL_LoadBMP("SDL2\\images\\Front_End_images3\\AnnulerCoup.bmp");

    switch(num_button_intersect)
    {
        case 1 : AnnulerContinuerSurface[0] = SDL_LoadBMP("SDL2\\images\\Front_End_images3\\ContinuerColoree.bmp");
                 break;
        case 2 : AnnulerContinuerSurface[1] = SDL_LoadBMP("SDL2\\images\\Front_End_images3\\AnnulerCoupColoree.bmp");
                 break;
    }

    /*gestion d'erreur de creation des surfaces*/
    for(int i = 0; i < 2; i++)
    {
        if(AnnulerContinuerSurface[i] == NULL)
        {
            fprintf(stderr, "Erreur : Creation des surfaces", SDL_GetError());
            return -1;
        }
    }

    /*Creation des textures et Liberation des surface*/
    for(int i = 0; i < 2; i++)
    {
        AnnulerContinuerTexture[i] = SDL_CreateTextureFromSurface(Renderer, AnnulerContinuerSurface[i]);
        SDL_FreeSurface(AnnulerContinuerSurface[i]);
    }

    /*Collage des textures*/
    for(int i = 0; i < 2; i++)
    {
        SDL_RenderCopy(Renderer, AnnulerContinuerTexture[i], NULL, &AnnulerContinuer[i]);
    }
    
    /*Destruction des textures*/
    for(int i = 0; i < 2; i++)
    {
        SDL_DestroyTexture(AnnulerContinuerTexture[i]);
    }

    /*Mise a jour du rendu*/
    SDL_RenderPresent(Renderer);
    return 0;
}

int SDL_MouseIntersect_AnnulerContinuer(SDL_Rect AnnulerContinuer[2], int mouse_x, int mouse_y)
{
    /*si l'intersection ou le clique s'est fait le boutton continuer*/
    if((AnnulerContinuer[0].x <= mouse_x) && (mouse_x <= (AnnulerContinuer[0].x + AnnulerContinuer[0].w))
        && (AnnulerContinuer[0].y <= mouse_y) && (mouse_y <= (AnnulerContinuer[0].y + AnnulerContinuer[0].h)))
    {
        return 1;
    }

    /*si l'intersection ou le clique s'est fait le boutton AnnulerCoup*/
    if((AnnulerContinuer[1].x <= mouse_x) && (mouse_x <= (AnnulerContinuer[1].x + AnnulerContinuer[1].w))
        && (AnnulerContinuer[1].y <= mouse_y) && (mouse_y <= (AnnulerContinuer[1].y + AnnulerContinuer[1].h)))
    {
        return 2;
    }

    /*Si l'intersection ne se fait avec aucun des bouttons*/
    return 0;
}

int SDL_ScanEventContinuerAnnuler(SDL_bool *App_Launched, SDL_Window *Window, SDL_Renderer *Renderer, SDL_Rect AnnulerContinuer[2])
{
    /*definir les positions des bouttons Continuer Retour*/
    Position_AnnulerContinuer(AnnulerContinuer);

    SDL_bool MenuContinuerAnnuler_Launched = SDL_TRUE;       
    int num_button_intersect = 0; //indique le numero de boutton que la souris a intersecté (0 indique pas d'intersections avec aucun des bouttons)
    int num_button_clicked = 0; //indique le numero de boutton que la souris a cliqué sur (0 indique pas de clique sur aucun boutton)

    while(MenuContinuerAnnuler_Launched)
    {
        SDL_Event Event;
        while(SDL_PollEvent(&Event))
        {
            SDL_AfficherBouttonAnnulerCoup(Renderer, AnnulerContinuer, num_button_intersect);
            switch(Event.type)
            {
                case SDL_MOUSEMOTION : num_button_intersect = SDL_MouseIntersect_AnnulerContinuer(AnnulerContinuer, Event.motion.x, Event.motion.y);
                                       break;
                case SDL_MOUSEBUTTONDOWN : num_button_clicked = SDL_MouseIntersect_AnnulerContinuer(AnnulerContinuer, Event.button.x, Event.button.y);
                                           return num_button_clicked;
                case SDL_QUIT : *App_Launched = SDL_FALSE;
                                return -1;
            }
        }

    }
}


int SDL_ScanEventFromMenuJeu(SDL_bool *App_Launched, SDL_Window *Window, SDL_Renderer *Renderer, TTF_Font *Font,
                SDL_Rect menu_Jeu[30], SDL_Rect AnnulerContinuer[2], pile plateau[2][8], char Donnee_Texte[4][30], int num_joueur, int nb_moitie)
{
    Position_menuJeu(menu_Jeu); /*Definir les positions des bouttons et message du menu jeu*/
    SDL_bool MenuJeu_Launched = SDL_TRUE;       
    int num_button_intersect = 0; //indique le numero de boutton que la souris a intersecté (0 indique pas d'intersections avec aucun des bouttons)
    int num_button_clicked = 0; //indique le numero de boutton que la souris a cliqué sur (0 indique pas de clique sur aucun boutton)
    int num_creux;      //numero du creux choisi par le joueur
    int valeur_Scan;   //val
    int ind_parc; //indice ligne de creux d'arret apres le jeu du coup

    pile plateauSecours[2][8]; //le plateau au cas ou le joueur a annuler son coup

    SDL_Rect Message_Rect = {200, 550, 400, 50};

    while(MenuJeu_Launched)  //Boucle du menu de jeu
    {
        SDL_Event Event;
        while(SDL_PollEvent(&Event))
        {   
            /*affichage du menu deu jeu*/
            SDL_menuJeu(Window, Renderer, Font, menu_Jeu, plateau, Donnee_Texte, num_button_intersect);

            /*affichage du nom du joueur qui joue*/
            SDL_Afficher_num_joueur(Renderer, Font, num_joueur, Donnee_Texte);

            /*Detection du fin de jeu*/
            if(Detecter_Fin(plateau, nb_moitie, num_joueur) == true)
            {
                char ConcatMessageGagnant[40] = "Felicitation au joueur gagnant ";
                int DecidGagnant = DeciderGagnant(plateau[0][0], plateau[1][7]);
                if(DecidGagnant == 0)
                {
                    strcat(ConcatMessageGagnant, Donnee_Texte[1]);
                    SDL_AfficherMessage(Renderer, Font, Message_Rect, ConcatMessageGagnant);
                }
                else
                {
                    if(DecidGagnant == 1)
                    {
                        strcat(ConcatMessageGagnant, Donnee_Texte[2]);
                        SDL_AfficherMessage(Renderer, Font, Message_Rect, ConcatMessageGagnant);
                    }
                    else
                        SDL_AfficherMessage(Renderer, Font, Message_Rect, "Partie terminee en egalite");     
                }    
            }
            
            switch(Event.type)
            {
                case SDL_MOUSEMOTION : num_button_intersect = SDL_MouseIntersect_menuJeuButtons(menu_Jeu, Event.motion.x, Event.motion.y);
                                       break;
                case SDL_MOUSEBUTTONDOWN : num_button_clicked = SDL_MouseIntersect_menuJeuButtons(menu_Jeu, Event.button.x, Event.button.y);

                                           /*copie plateau dans plateauSecours comme (une sorte de sauvegarde de l'etat du plateau ancien)*/
                                            Copier_plateau(plateauSecours, plateau);     

                                           /*Si le joueur a choisir l'un des creux de joueur 1*/
                                           if(TesterCreuxChoisiJoueur(Renderer, Font, num_button_clicked, num_joueur) == 1)
                                           {
                                               
                                                 /*Si le joueur a choisir l'un des creux de joueur 1*/
                                                if(7 <= num_button_clicked && num_button_clicked <= 12)
                                                {
                                                   num_creux = num_button_clicked - 6; //num_creux correspondant dans le plateau
                                                }
                                                 /*Si le joueur a choisir l'un des creux de joueur 2*/
                                                if(16 <= num_button_clicked && num_button_clicked <= 21)
                                                {
                                                    num_creux = num_button_clicked - 15; //num_creux correspondant dans le plateau
                                                }

                                                /*si le creux choisi est vide*/
                                                if(Estvide(plateau[num_joueur][num_creux]) == true)
                                                {
                                                    SDL_AfficherMessage(Renderer, Font, Message_Rect, "Le creux choisi est vide");
                                                    SDL_Delay(1000);
                                                    SDL_RefraichirRect(Renderer, Message_Rect);
                                                    continue; //reboucler
                                                }
                                                else //Si n'est pas vide on doit afficher deux bouttons Annuler et continuer
                                                {
                                                    /*mise a jour du plateauSecours*/
                                                    ind_parc = Jouer_Mise_aJour(plateauSecours, num_joueur, &num_creux);
                                                    SDL_Refraichir(Renderer);
                                                    SDL_menuJeu(Window, Renderer, Font, menu_Jeu, plateauSecours, Donnee_Texte, num_button_intersect);


                                                    Prendre_Tout(plateauSecours, num_joueur, ind_parc, num_creux);
                                                    
                                                    do //il doit choisir l'un des bouttons soit annuler ou continuer 
                                                    {
                                                        valeur_Scan = SDL_ScanEventContinuerAnnuler(App_Launched, Window, Renderer, AnnulerContinuer);
                                                    }while(valeur_Scan == 0); //il doit choisir l'un des bouttons soit annuler ou continuer
                                                }

                                                /*refraichir les deux bouttons Annuler et retour*/ 
                                                SDL_RefraichirRect(Renderer, AnnulerContinuer[0]);
                                                SDL_RefraichirRect(Renderer, AnnulerContinuer[1]);

                                                switch(valeur_Scan)
                                                {
                                                    case 1 : /*si il a clique sur le Continuer*/
                                                             /*on copie le plateauSecours dans plateau pour remise a jour du plateau car il n'a pas annulé le coup*/
                                                             Copier_plateau(plateau, plateauSecours);
                                                             SDL_Refraichir(Renderer); //refraichir l'image
                                                             SDL_menuJeu(Window, Renderer, Font, menu_Jeu, plateau, Donnee_Texte, num_button_intersect);
                                                             break;
                                                    case 2 : /*si il a clique sur le Annuler*/
                                                             SDL_Refraichir(Renderer); //refraichir l'image
                                                             continue; //reboucler pour saisir un nouveau coup
                                                    default : break;
                                                }

                                                /*Si le joueur ne tombe pas dans son kalah*/
                                                if(Tester_Kalah(ind_parc, num_creux) != num_joueur)
                                                    num_joueur = (num_joueur + 1) % 2; //Passer au joueur suivant
                                           }
                                           
                                           else //Si l'utilisateur a clique sur autre boutton que les creux
                                           {
                                               /*si le boutton clique est Sauvegarder*/
                                               if(num_button_clicked == 29)
                                               {
                                                   Sauvegarder(Donnee_Texte, plateau, num_joueur, nb_moitie);
                                                   SDL_AfficherMessage(Renderer, Font, Message_Rect, "Partie Sauvegardee :)");
                                                   SDL_Delay(1000);
                                                   SDL_RefraichirRect(Renderer, Message_Rect);
                                               }

                                               /*si le boutton clique est Retour*/
                                               if(num_button_clicked == 30)
                                               {
                                                   return 0; 
                                               }
                                           }
                                           break;
                case SDL_WINDOWEVENT : /*gerer les evenements relatifs a la fenetre*/
                                        switch(Event.window.windowID)
                                        {
                                            case SDL_WINDOWEVENT_SHOWN : SDL_ShowWindow(Window);
                                                                             break;
                                            case SDL_WINDOWEVENT_RESTORED : SDL_RestoreWindow(Window);
                                                                             break;
                                            case SDL_WINDOWEVENT_HIDDEN : SDL_HideWindow(Window);
                                                                          break;
                                            default : break;
                                        }
                                        break;
                case SDL_QUIT : *App_Launched = SDL_FALSE;
                                return 0;
                                break;
            }
        }
    }
}



