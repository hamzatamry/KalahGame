#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "manip_sdl2_1.h"
#include "manip_sdl2_3.h"

void Position_menuDonnee(SDL_Rect menu_Donnee[11])
{
    //Definir la position du message en haut de la fenetre "Saisir les donnees de la partie"
    menu_Donnee[0].x = 225;
    menu_Donnee[0].y = 50;
    menu_Donnee[0].w = 350;
    menu_Donnee[0].h = 80; 

    int y_passage = 160; //variable indiquant les coordonnes y des bouttons 

    //Definir les differentes positions des messages indicateurs a l'utilisateur et des champs de saisie
    for(int i = 1; i < 9; i++)
    {
        if(i % 2 == 1)
        {
            menu_Donnee[i].x = 40;
            menu_Donnee[i].y = y_passage;
            menu_Donnee[i].w = 200;
            menu_Donnee[i].h = 80;
        }
        else
        {
            menu_Donnee[i].x = 250;
            menu_Donnee[i].y = y_passage;
            menu_Donnee[i].w = 300;
            menu_Donnee[i].h = 80;
            y_passage += 100;      
        }
    }

    //Definir la position du boutton Jouer
    menu_Donnee[9].x = 40;
    menu_Donnee[9].y = 550;
    menu_Donnee[9].w = 200;
    menu_Donnee[9].h = 80;
    
    //Definir la position du boutton Retour
    menu_Donnee[10].x = 560;
    menu_Donnee[10].y = 550;
    menu_Donnee[10].w = 200;
    menu_Donnee[10].h = 80;
}

int SDL_menuDonnee(SDL_Window *Window, SDL_Renderer *Renderer, TTF_Font *Font, SDL_Rect menu_Donnee[11], 
                char Donnee_Texte[4][30], int num_button_intersect) //Affichage des donnes partie , Saisie des donnes de la partie (avec verification)
{
    //Donne_Texte : Les donnees de la partie (nom de la partie (0), nom du joueur 1 (1), nom du joueur 2 (2), nombre de piece (3))
    //num_button_intersect : numero de boutton que la souris a intersecté (le boutton Jouer : 1, le boutton retour : 2

    SDL_Surface *menu_DonneeSurface[11]; //Les surfaces des champs de donnees apparus dans la fenetre
    SDL_Texture *menu_DonneeTexture[11]; //Les Textures des champs de donnees apparus dans la fenetre

    SDL_Color TextColor = {255, 0, 0, 255}; //Choix du couleur du texte (dans ce cas rouge)
    SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 0);// mettre la couleur du dessin rouge pour afficher les barres de saisie (un rectangle rouge)

    /*creation des surfaces contenant du texte indiquant a l'utilisateur les donnees a saisir*/
    menu_DonneeSurface[0] = TTF_RenderText_Solid(Font, "Saisir les donnees de la partie", TextColor); //Commentaire en haut de la fenetre
    menu_DonneeSurface[1] = TTF_RenderText_Solid(Font, "Nom de la partie : ", TextColor);    //Commentaire affichant Nom de la partie
    menu_DonneeSurface[3] = TTF_RenderText_Solid(Font, "Nom du 1er joueur : ", TextColor);   //Commentaire affichant Nom du 1er joueur
    menu_DonneeSurface[5] = TTF_RenderText_Solid(Font, "Nom du 2eme joueur : ", TextColor);  //Commentaire affichant Nom du 2eme joueur
    menu_DonneeSurface[7] = TTF_RenderText_Solid(Font, "Nombre de piece intial : ", TextColor);  //Commentaire affichant Nombre de piece intial
    
    menu_DonneeSurface[9] = SDL_LoadBMP("SDL2\\images\\Front_End_images2\\Jouer.bmp");         //Le boutton Jouer 
    menu_DonneeSurface[10] = SDL_LoadBMP("SDL2\\images\\Front_End_images2\\Retour.bmp");       //Le boutton Retour
    switch(num_button_intersect)  //Au cas ou la souris a intersecté on change la couler du boutton intersecté
    {
        case 9 : menu_DonneeSurface[9] = SDL_LoadBMP("SDL2\\images\\Front_End_images2\\JouerColoree.bmp");
                 break;
        case 10 : menu_DonneeSurface[10] = SDL_LoadBMP("SDL2\\images\\Front_End_images2\\RetourColoree.bmp");
                 break;
        default : break;
    }

    //Gestion d'erreur de creation des surfaces
    for(int i = 0; i < 11; i++)
    {
        if(i != 2 && i != 4 && i != 6 && i != 8)
        {
            if(menu_DonneeSurface[i] == NULL)
            {
                fprintf(stderr, "Erreur : Creation des surfaces echouee : %s\n", SDL_GetError());
                return -1; //Retourner une valeur d'erreur
            }
        }
    }

    /*transformation des textures en surfaces contenant du texte indiquant a l'utilisateur les donnees a saisir et liberation des surfaces utilisees */
    for(int i = 0; i < 11; i++)
    {
        if(i != 2 && i != 4 && i != 6 && i != 8)
        {
            menu_DonneeTexture[i] = SDL_CreateTextureFromSurface(Renderer, menu_DonneeSurface[i]);
            SDL_FreeSurface(menu_DonneeSurface[i]);
        }
    }

    //Gestion d'erreur de creation des textures
    for(int i = 0; i < 11; i++)
    {
        if(i != 2 && i != 4 && i != 6 && i != 8)
        {
            if(menu_DonneeTexture[i] == NULL)
            {
                fprintf(stderr, "Erreur : Creation des textures echouee : %s\n", SDL_GetError());
                return -1; //Retourner une valeur d'erreur
            }
        }
    }

    /*Dessin des differentes messages ,barres de saisie et des champ de saisie et destruction des textures utilisee*/
    for(int i = 0; i < 11; i++)
    {
        if(i == 2 || i == 4 || i == 6 || i == 8)    //Dessin des barres de saisie (2, 4, 6, 8)
        {
           SDL_RenderDrawRect(Renderer, &menu_Donnee[i]); 
        }
        else
        {
            SDL_RenderCopy(Renderer, menu_DonneeTexture[i], NULL, &menu_Donnee[i]); //Dessin des messages , de champ de saisie et des bouttons (jouer et retour)       
        }    
    }

    SDL_SaisirChamp(Renderer, Font, menu_Donnee, Donnee_Texte, num_button_intersect); //Saisir les champ de saisie

    for(int i = 0; i < 11; i++)
    {
        if(i != 2 && i != 4 && i != 6 && i != 8)
        {
            SDL_DestroyTexture(menu_DonneeTexture[i]);
        }
    }
    

    SDL_RenderPresent(Renderer); //Mise a jour du rendu de la fenetre
    return 0; //Valeur de succes (tout s'est fait correctement)
}

int SDL_MouseIntersect_menuDonneeButtons(SDL_Rect menu_Donnee[11], int mouse_x, int mouse_y)
{
    for(int i = 2; i < 10; i += 2)
    {
        if((menu_Donnee[i].x <= mouse_x) && (mouse_x <= (menu_Donnee[i].x + menu_Donnee[i].w))
        && (menu_Donnee[i].y <= mouse_y) && (mouse_y <= (menu_Donnee[i].y + menu_Donnee[i].h)))
        {
            return i;  //Valeur indique qu'on a clique sur le champ de saisie correspondant
        }

    }
    //2 si le clique se fait dans le champ de saisie 1 (nom de la partie)
    //4 si le clique se fait dans le champ de saisie 2 (nom du joueur 1)
    //6 si le clique se fait dans le champ de saisie 3 (nom du joueur 2)
    //8 si le clique se fait dans le champ de saisie 4 (nombre de piece initial)

    for(int i = 9; i < 11; i++)
    {
        if((menu_Donnee[i].x <= mouse_x) && (mouse_x <= (menu_Donnee[i].x + menu_Donnee[i].w))
        && (menu_Donnee[i].y <= mouse_y) && (mouse_y <= (menu_Donnee[i].y + menu_Donnee[i].h)))
        {
            return i;  //Valeur indique qu'on a clique sur le champ de saisie correspondant
        }

    }
    //9 si l'intersection s'est faite avec le boutton joue
    //10 si l'intersection s'est faite avec le boutton retour

    return 0; //l'intersection ne se fait avec aucun boutton ou aucun clique sur un champ
}

SDL_bool SDL_Champvide(char Donnee_Texte[4][30])
{
    int i;
    for(i = 0; i < 4 && strcmp(Donnee_Texte[i], "") != 0; i++)
    {}
    if(i == 4)  //Aucun des champ n'est vide
        return SDL_FALSE;
    else      //au moins un champ est vide
        return SDL_TRUE; 
}

SDL_bool SDL_Nbpiecevalide(char Donnee_Texte[4][30])
{
    int nb_piece = atoi(Donnee_Texte[3]);     //conversion du nombre de piece initial (champ de saisie 4) du texte en un nombre
    if(nb_piece <= 0 || nb_piece > 10)  //Si le nombre de piece n'est pas compris entre 1 et 10
        return SDL_FALSE;
    else
        return SDL_TRUE;  
}

/*Pour la decomposition du texte (pour que le texte soit repartie d'une maniere coherente) dans la barre de saisie on va decomposer 
    la barre de saisie (de largeur 300) en 30 cases chaque case contiendra une lettre */
void SDL_SaisirChamp(SDL_Renderer *Renderer, TTF_Font *Font, SDL_Rect menu_Donnee[11], char Donnee_Texte[4][30], int num_button_intersect)
{
    
    SDL_Color TextColor = {255, 0, 0, 255}; //Choix du couleur du texte (dans ce cas rouge)
    int Texte_Lenght[4];
    for(int i = 0; i < 4; i++)  /*on remplit le tableau avec les longueurs des champ de saisie*/
    {
        Texte_Lenght[i] = strlen(Donnee_Texte[i]);
    }

    SDL_Rect Curseur;
    SDL_Rect Barre;
    SDL_Surface *Curseur_Surface = NULL;
    SDL_Texture *Curseur_Texture = NULL;

    for(int i = 0, k = 2; i < 4 && k < 10; i++, k += 2)
    {
        //Positionner le curseur dans la barre de saisie le decaller car si on refrachit le curseur la barre de saisie disparaitra
        Curseur.x = menu_Donnee[k].x + 2;            
        Curseur.y = menu_Donnee[k].y + 2;
        Curseur.w = 28; 
        Curseur.h = menu_Donnee[k].h - 4;

        /*rectangle de champ de saisie plus petit que la barre de saisie car il sera refraichi et on veut bien que la barre de saisie reste visible*/
        Barre.x = menu_Donnee[k].x + 1;            
        Barre.y = menu_Donnee[k].y + 1;
        Barre.w = menu_Donnee[k].w - 2; 
        Barre.h = menu_Donnee[k].h - 2;

        if(k == num_button_intersect) //on refraichit la saisie que dans la barre qu'on a cliqué sur
            SDL_RefraichirRect(Renderer, Barre);

        int j; //compteur
        for(j = 0; j < Texte_Lenght[i] && Curseur.x < 550 ; j++) //Passer a la lettre suivante avec limitation de l'espace de saisie
        {
            char word_to_string[2];
            word_to_string[0] = Donnee_Texte[i][j];
            word_to_string[1] = '\0';
            Curseur_Surface = TTF_RenderText_Solid(Font, word_to_string, TextColor);
            Curseur_Texture = SDL_CreateTextureFromSurface(Renderer, Curseur_Surface);
            SDL_FreeSurface(Curseur_Surface); /*liberation de la surface*/
            SDL_RenderCopy(Renderer, Curseur_Texture, NULL, &Curseur); /*Coller le texte dans le champ de saisie*/
            SDL_DestroyTexture(Curseur_Texture); /*Destruction de la texture*/
            Curseur.x += 30;
        }
    }
}

SDL_bool SDL_DonneeVerification(SDL_Renderer *Renderer, TTF_Font *Font, char Donnee_Texte[4][30])
{
    SDL_Rect Message_erreur = {250, 550, 300, 80};  //Le rectangle (position du message d'erreur dans la fenetre)
    SDL_Surface *Message_erreurSurface = NULL;  //Surface correspondante au message d'erreur
    SDL_Texture *Message_erreurTexture = NULL;  //Texture correspondante au message d'erreur
    SDL_Color TextColor = {255, 0, 0, 255}; //Choix du couleur du texte (dans ce cas rouge)


    if(SDL_Champvide(Donnee_Texte) == SDL_TRUE) //si l'un des champs est encore non saisi
    {
        SDL_AfficherMessage(Renderer, Font, Message_erreur, "Les donnees non saisies");
        SDL_Delay(1000);
        SDL_RefraichirRect(Renderer, Message_erreur);
        return SDL_FALSE;
    }
    else
    {   
        if(SDL_Nbpiecevalide(Donnee_Texte) == SDL_FALSE)  //si le nombre de piece saisi est valide
        {
            SDL_AfficherMessage(Renderer, Font, Message_erreur, "Le nombre de piece invalide");
            SDL_Delay(1000);
            SDL_RefraichirRect(Renderer, Message_erreur);
            return SDL_FALSE;
        } 
        else     //Sinon tous les champs sont correctement saisis
        {
            return SDL_TRUE;
        }      
    }
}

int SDL_ScanEventFromMenuDonnee(SDL_bool *App_Launched, SDL_Window *Window, SDL_Renderer *Renderer, TTF_Font *Font,
                SDL_Rect menu_Donnee[11], char Donnee_Texte[4][30])
{
    SDL_bool MenuDonnee_Launched = SDL_TRUE;
    int num_texte = -1; //Indique le numero du texte du champ de saisie (par exemple 1 indique le texte du 2eme champ de saisie)
    int num_button_intersect = 0; //indique le numero de boutton que la souris a intersecté (0 indique par de clique sur aucun des bouttons)
    int num_button_clicked = 0;  //indique le numero de boutton cliqué par la souris (0 indique par de clique sur aucun des bouttons)
    SDL_StartTextInput(); 
    while(MenuDonnee_Launched)
    {
        SDL_Event Event;
        while(SDL_PollEvent(&Event))
        {   
            Position_menuDonnee(menu_Donnee);
            SDL_menuDonnee(Window, Renderer, Font, menu_Donnee, Donnee_Texte, num_button_intersect);
                
            switch(Event.type)
            {
                case SDL_MOUSEMOTION : num_button_intersect = SDL_MouseIntersect_menuDonneeButtons(menu_Donnee, Event.motion.x, Event.motion.y);
                                       break;
                case SDL_MOUSEBUTTONDOWN : num_button_clicked = SDL_MouseIntersect_menuDonneeButtons(menu_Donnee, Event.button.x, Event.button.y);
                                           switch(num_button_clicked) //Determiner le numero de champ ou s'est fait le clique                                           
                                           {
                                               case 2 : num_texte = 0;   //1er champ de saisie
                                                        break;
                                               case 4 : num_texte = 1;  //2eme champ de saisie
                                                        break; 
                                               case 6 : num_texte = 2;
                                                        break;
                                               case 8 : num_texte = 3;
                                                        break;
                                               case 9 : /*Si les donnees sont correcte apres clique sur joueur*/
                                                        if(SDL_DonneeVerification(Renderer, Font, Donnee_Texte) == true)
                                                        {
                                                            return 1; //Valeur indiquant que le la boucle du jeu est lancé
                                                        }
                                                         break;
                                               case 10 : return 0; //retourner du menu de donne au menu principal
                                               default : continue;
                                           }
                                           break;
                case SDL_KEYDOWN : if(num_texte != -1)  //Au cas ou c'est l'un des quatres champs de saisie
                                   {
                                       /*Au cas ou tape la touche backspace on doit supprimer a chaque clique une lettre du texte*/
                                       if(Event.key.keysym.sym == SDLK_BACKSPACE && strlen(Donnee_Texte[num_texte]) > 0)
                                       {
                                           Donnee_Texte[num_texte][strlen(Donnee_Texte[num_texte]) - 1] = '\0';
                                       }
                                       /*Au cas ou il a tapé ctrl + c il faut sauvegarder le texte en attente d'etre copier*/
                                       if(Event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
                                            SDL_SetClipboardText(Donnee_Texte[num_texte]);
                                       /*Au cas ou il a tapé ctrl + v il faut copier le texte dans la barre*/
                                       if(Event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
                                            strcpy(Donnee_Texte[num_texte], SDL_GetClipboardText());
                                       /*Au cas ou il a tapé ctrl + d il faut supprimer le texte dans la barre de saisie*/
                                       if(Event.key.keysym.sym == SDLK_d && SDL_GetModState() & KMOD_CTRL)
                                            strcpy(Donnee_Texte[num_texte], "");
                                   }
                                   break;
                         
                case SDL_TEXTINPUT : //Au cas ou c'est l'un des quatres champs de saisie et le texte ne depace pas l'espace necessaire
                                     if(num_texte != -1 && strlen(Donnee_Texte[num_texte]) < 10)
                                     {
                                         strcat(Donnee_Texte[num_texte], Event.text.text);
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
                case SDL_QUIT : *App_Launched = SDL_FALSE; //Fermer la fenetre
                                return 0;
                                break;

            }
        }
    }
    SDL_StopTextInput();  //arreter le textinput
}

