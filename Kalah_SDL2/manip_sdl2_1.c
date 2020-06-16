#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "manip_sdl2_1.h"


int SDL_Initial(SDL_Window **Window, SDL_Renderer **Renderer)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)  //Initialisation de la SDL2 (pour utiliser les fonctions d'affichage de la SDL2) avec gestion d'erreur
    {
        fprintf(stderr, "Erreur : SDL_Init() : %s", SDL_GetError());
        return -1;     //Valeur d'erreur
    }
     /*Creation de la fenetre de taille 800 * 640 */ 
    *Window = SDL_CreateWindow("KALAH GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if(*Window == NULL)    //Verification si la fenetre s'est cree correctement
    {
        fprintf(stderr, "Erreur : SDL_CreateWindow() : %s", SDL_GetError());
        return -1;   //Valeur d'erreur
    }
    
    /*Creation du rendu de la fenetre utilisant l'acceleration materielle (GPU)*/
    *Renderer = SDL_CreateRenderer(*Window, -1, SDL_RENDERER_ACCELERATED);

    if(*Renderer == NULL) //Verification si le rendu de la fenetre s'est cree correctement
    {
        fprintf(stderr, "Erreur ; SDL_CreateRenderer() : %s", SDL_GetError());
        return -1;
    }

    return 0; //Valeur de succes (Initialisation correcte de la SDL2, creation reussie de la fenetre et de son rendu)
}

int TTF_Initial(TTF_Font **Font)
{
    if(TTF_Init() != 0)
    {
        fprintf(stderr, "Erreur : TTF_Init() : %s", TTF_GetError());
        return -1;
    }

    *Font = TTF_OpenFont("SDL2\\font\\arial.ttf", 72); //ouverture du font

    if(*Font == NULL)  //gestion d'erreur
    {
        fprintf(stderr, "Erreur : TTF_Open() : %s", TTF_GetError());
        return -1;
    }
    else
    {
        return 0;
    }
}



void SDL_Refraichir(SDL_Renderer *Renderer)         //Pour effacer la fenetre (en noir)
{
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);   //Choix de la couleur noir
    SDL_RenderClear(Renderer);           //Effacement de la fenetre en noir
    SDL_RenderPresent(Renderer);         //Mise a jour du rendu 
}

void SDL_RefraichirRect(SDL_Renderer *Renderer, SDL_Rect Rect_Refraichi)  //Refraichir que le rectangle (on le colore en noire)
{
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(Renderer, &Rect_Refraichi);
    SDL_RenderPresent(Renderer);
}

int SDL_AfficherMessage(SDL_Renderer *Renderer, TTF_Font *Font, SDL_Rect Barre_Message, char message[50])
{
    SDL_Color TextColor = {255, 0, 0, 255}; //couleur du texte rouge

    SDL_RefraichirRect(Renderer, Barre_Message);   //Refraichir la barre de message

    SDL_Surface *Barre_MessageSurface = NULL;
    SDL_Texture *Barre_MessageTexture = NULL;

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
    
    /*Collage de la texture*/
    SDL_RenderCopy(Renderer, Barre_MessageTexture, NULL, &Barre_Message);
    SDL_RenderPresent(Renderer);

    /*Destruction de la texture*/
    SDL_DestroyTexture(Barre_MessageTexture);

    return 0; 
}


