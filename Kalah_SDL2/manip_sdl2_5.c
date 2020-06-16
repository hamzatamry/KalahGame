#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "manip_data.h"
#include "manip_sdl2_1.h"
#include "manip_sdl2_4.h"
#include "manip_sdl2_5.h"


void Position_menuSauvegarde(SDL_Rect menu_Sauvegarde[4])
{   
    /*definir la position du message "nom de fichier"*/
    menu_Sauvegarde[0].x = 40;
    menu_Sauvegarde[0].y = 280;
    menu_Sauvegarde[0].w = 200;
    menu_Sauvegarde[0].h = 80;

    /*definir la position de champ de saisie du nom de fichier*/
    menu_Sauvegarde[1].x = 250;
    menu_Sauvegarde[1].y = 280;
    menu_Sauvegarde[1].w = 300;
    menu_Sauvegarde[1].h = 80;

    /*definir la position du boutton Jouer*/
    menu_Sauvegarde[2].x = 40;
    menu_Sauvegarde[2].y = 550;
    menu_Sauvegarde[2].w = 160;
    menu_Sauvegarde[2].h = 50;

    /*definir la position du boutton retour*/
    menu_Sauvegarde[3].x = 650;
    menu_Sauvegarde[3].y = 550;
    menu_Sauvegarde[3].w = 130;
    menu_Sauvegarde[3].h = 50;

}

int SDL_MouseIntersect_menuSauvegardeButtons(SDL_Rect menu_Sauvegarde[4], int mouse_x, int mouse_y)
{
    for(int i = 1; i < 4; i++)
    {
        if((menu_Sauvegarde[i].x <= mouse_x) && (mouse_x <= (menu_Sauvegarde[i].x + menu_Sauvegarde[i].w))
        && (menu_Sauvegarde[i].y <= mouse_y) && (mouse_y <= (menu_Sauvegarde[i].y + menu_Sauvegarde[i].h)))
        {
            return i;
        }
    }

    /*si l'intersection ne se fait avec aucun des bouttons ou champ de saisie*/
    return 0;
}

void SDL_SaisirChamp_menuSauvegarde(SDL_Renderer *Renderer, TTF_Font *Font, SDL_Rect menu_Sauvegarde[4], char Donnee_Texte[4][30], int num_button_intersect)
{
    
    SDL_Color TextColor = {255, 0, 0, 255}; //Choix du couleur du texte (dans ce cas rouge)
    int Texte_Lenght;
    
    Texte_Lenght = strlen(Donnee_Texte[0]); //Donnee_Texte[0] c'est le nom de la partie et aussi le nom de fichier 

    SDL_Rect Curseur;
    SDL_Rect Barre;
    SDL_Surface *Curseur_Surface = NULL;
    SDL_Texture *Curseur_Texture = NULL;

    /*rectangle de champ de saisie plus petit que la barre de saisie car il sera refraichi et on veut bien que la barre de saisie reste visible*/
    Barre.x = menu_Sauvegarde[1].x + 1;            
    Barre.y = menu_Sauvegarde[1].y + 1;
    Barre.w = menu_Sauvegarde[1].w - 2; 
    Barre.h = menu_Sauvegarde[1].h - 2;

    //Positionner le curseur dans la barre de saisie
    Curseur.x = Barre.x;            
    Curseur.y = Barre.y;
    Curseur.w = 28; 
    Curseur.h = Barre.h;

    if(num_button_intersect == 1)  //si la souris interset le champ de saisie (nom de fichier)
        SDL_RefraichirRect(Renderer, Barre);

        int j; //compteur
        for(j = 0; j < Texte_Lenght && Curseur.x < 550 ; j++) //Passer a la lettre suivante avec limitation de l'espace de saisie
        {
            char word_to_string[2];
            word_to_string[0] = Donnee_Texte[0][j];
            word_to_string[1] = '\0';
            Curseur_Surface = TTF_RenderText_Solid(Font, word_to_string, TextColor);
            Curseur_Texture = SDL_CreateTextureFromSurface(Renderer, Curseur_Surface);
            SDL_FreeSurface(Curseur_Surface); /*liberation de la surface*/
            SDL_RenderCopy(Renderer, Curseur_Texture, NULL, &Curseur); /*Coller le texte dans le champ de saisie*/
            SDL_DestroyTexture(Curseur_Texture); /*Destruction de la texture*/
            Curseur.x += 30;
        }
}



int SDL_menuSauvegarde(SDL_Window *Window, SDL_Renderer *Renderer, TTF_Font *Font, SDL_Rect menu_Sauvegarde[4], char Donnee_Texte[4][30]
                                , int num_button_intersect)
{
    SDL_Color Rouge = {255, 0, 0, 255};

    SDL_Surface *menu_SauvegardeSurface[4];
    SDL_Texture *menu_SauvegardeTexture[4];

    /*creation des surfaces*/
    menu_SauvegardeSurface[0] = TTF_RenderText_Solid(Font, "Nom du fichier : ", Rouge);
    menu_SauvegardeSurface[2] = SDL_LoadBMP("SDL2\\images\\Front_End_images2\\Jouer.bmp");
    menu_SauvegardeSurface[3] = SDL_LoadBMP("SDL2\\images\\Front_End_images3\\Retour.bmp");
    //il reste d'afficher le texte dans le champ de saisie*/

    switch(num_button_intersect)
    {
        case 2 : menu_SauvegardeSurface[2] = SDL_LoadBMP("SDL2\\images\\Front_End_images2\\JouerColoree.bmp");
                 break;
        case 3 : menu_SauvegardeSurface[3] = SDL_LoadBMP("SDL2\\images\\Front_End_images3\\RetourColoree.bmp");
                 break;
    }

    /*Gestion d'erreur de creation des surfaces*/
    for(int i = 0; i < 4; i++)
    {
        if(i != 1 && menu_SauvegardeSurface[i] == NULL)
        {
            fprintf(stderr, "Erreur : creation des surfaces\n %s", SDL_GetError());
            return -1;
        }
    }

    /*Creation des textures*/
    for(int i = 0; i < 4; i++)
    {
        if(i != 1)
        {
            menu_SauvegardeTexture[i] = SDL_CreateTextureFromSurface(Renderer, menu_SauvegardeSurface[i]);
        }
            
    }

    /*liberation des surface*/
    for(int i = 0; i < 4; i++)
    {
        if(i != 1)
            SDL_FreeSurface(menu_SauvegardeSurface[i]);
    }



    /*Gestion d'erreur de creation des textures*/
    for(int i = 0; i < 4; i++)
    {
        if(i != 1 && menu_SauvegardeTexture[i] == NULL)
        {
            fprintf(stderr, "Erreur : creation des textures\n %s", SDL_GetError());
            return -1;
        }

    }

    SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 0);
    /*collage des textures*/
    for(int i = 0; i < 4; i++)
    {
        if(i != 1) //Au cas ou ce n'est pas le champ de saisie
            SDL_RenderCopy(Renderer, menu_SauvegardeTexture[i], NULL, &menu_Sauvegarde[i]);
        else
            SDL_RenderDrawRect(Renderer, &menu_Sauvegarde[i]);
    }

    SDL_SaisirChamp_menuSauvegarde(Renderer, Font, menu_Sauvegarde, Donnee_Texte, num_button_intersect);

    /*destruction des textures*/
    for(int i = 0; i < 4; i++)
    {
        if(i != 1) 
            SDL_DestroyTexture(menu_SauvegardeTexture[i]);
    }

    /*mise a jour du rendu*/
    SDL_RenderPresent(Renderer);

    return 0; //valeur de succes
}


int SDL_ScanEventFromMenuSauvegarde(SDL_bool *App_Launched, SDL_Window *Window, SDL_Renderer *Renderer, TTF_Font *Font, SDL_Rect menu_Sauvegarde[4],
                        char Donnee_Texte[4][30], pile plateau[2][8], int *dernier_joueur, int *nb_moitie, bool *chargee)
{
    int num_button_intersect = 0;
    int num_button_clicked = 0;
    SDL_bool MenuSauvegarde_Launched = SDL_TRUE;
    SDL_Rect Message_Rect = {250, 550, 350, 50};
    
    /*definir les positions des rectangles du menu de sauvegarde*/
    Position_menuSauvegarde(menu_Sauvegarde); 

    SDL_StartTextInput();
    while(MenuSauvegarde_Launched)
    {
        SDL_Event Event;
        while(SDL_PollEvent(&Event))
        {
            SDL_menuSauvegarde(Window, Renderer, Font, menu_Sauvegarde, Donnee_Texte, num_button_intersect);
            switch(Event.type)
            {
                case SDL_MOUSEMOTION : num_button_intersect = SDL_MouseIntersect_menuSauvegardeButtons(menu_Sauvegarde, Event.motion.x, Event.motion.y);  
                                       break;
                case SDL_MOUSEBUTTONDOWN : num_button_clicked = SDL_MouseIntersect_menuSauvegardeButtons(menu_Sauvegarde, Event.button.x, Event.button.y);
                                           switch(num_button_clicked)
                                           {
                                               /*au cas ou il a clique su le champ de saisie*/
                                               case 1 : break; 
                                               
                                               /*au cas ou il a cliqué sur charger*/
                                               
                                               case 2 : /*au cas ou il a clique sur jouer*/
                                                        /*si le chargement de fichier echouee*/
                                                        if(Charger(Donnee_Texte, plateau, dernier_joueur, nb_moitie) != 0)
                                                        {
                                                            SDL_AfficherMessage(Renderer, Font, Message_Rect, "Nom de fichier inexistant");
                                                            SDL_Delay(1000); //bloquer l'affichage du message pour 1 sec
                                                            SDL_RefraichirRect(Renderer, Message_Rect);
                                                        }
                                                        else
                                                        {
                                                            *chargee = true;
                                                            return 0;
                                                        }
                                                        break;

                                               /*au cas ou il a cliqué sur retour*/
                                               case 3 : return 0; 
                                                        break;
                                           }
                                           break;
                case SDL_KEYDOWN :   
                                         /*Au cas ou tape la touche backspace on doit supprimer a chaque clique une lettre du texte*/
                                       if(Event.key.keysym.sym == SDLK_BACKSPACE && strlen(Donnee_Texte[0]) > 0)
                                       {
                                           Donnee_Texte[0][strlen(Donnee_Texte[0]) - 1] = '\0';
                                       }
                                       /*Au cas ou il a tapé ctrl + c il faut sauvegarder le texte en attente d'etre copier*/
                                       if(Event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
                                            SDL_SetClipboardText(Donnee_Texte[0]);
                                       /*Au cas ou il a tapé ctrl + v il faut copier le texte dans la barre*/
                                       if(Event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
                                            strcpy(Donnee_Texte[0], SDL_GetClipboardText());
                                       /*Au cas ou il a tapé ctrl + d il faut supprimer le texte dans la barre de saisie*/
                                       if(Event.key.keysym.sym == SDLK_d && SDL_GetModState() & KMOD_CTRL)
                                            strcpy(Donnee_Texte[0], "");
                                     break;

                case SDL_TEXTINPUT : //Au cas ou c'est l'un des quatres champs de saisie et le texte ne depace pas l'espace necessaire
                                     if(strlen(Donnee_Texte[0]) < 10)
                                     {
                                         strcat(Donnee_Texte[0], Event.text.text);
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