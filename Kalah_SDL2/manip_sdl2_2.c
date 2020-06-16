#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "manip_sdl2_2.h"


void Position_menu1buttons(SDL_Rect menu1_Buttons[3]) //Definir la position des bouttons du menu principal 
{
    int y_passage = 100; //variable indiquant les coordonne y du boutton 

    for(int i = 0; i < 3; i++)   //i : un compteur
    {
        menu1_Buttons[i].x = 300;
        menu1_Buttons[i].y = y_passage;
        menu1_Buttons[i].w = 200;
        menu1_Buttons[i].h = 80;
        y_passage += 180;     //Changer les coordonnes y du boutton suivant d'un pas de 180
    }
}

int SDL_menu1(SDL_Window *Window, SDL_Renderer *Renderer, SDL_Rect menu1_Buttons[3], int num_button_intersect) //num_button_intersect : numero du boutton que la souris a intersecté
{
    SDL_Surface *ImageFond = NULL, *NouvellePartie = NULL, *ChargerPartie = NULL, *Quitter = NULL;
    SDL_Texture *ImageFondTex = NULL, *NouvellePartieTex = NULL, *ChargerPartieTex = NULL, *QuitterTex = NULL;

    /*Charger les images non coloree dans les surfaces*/
    ImageFond = IMG_Load("SDL2\\images\\Front_End_images1\\ImageFond.png");
    NouvellePartie = SDL_LoadBMP("SDL2\\images\\Front_End_images1\\NouvellePartie.bmp");
    ChargerPartie = SDL_LoadBMP("SDL2\\images\\Front_End_images1\\ChargerPartie.bmp");
    Quitter = SDL_LoadBMP("SDL2\\images\\Front_End_images1\\Quitter.bmp");

    switch(num_button_intersect)  //S'assurer si la souris a intersecté l'un des bouttons si oui on colore le boutton 
    {
        case 1 : //le cas ou l'intersection s'est faite avec le boutton NouvellePartie (1er boutton)
                 NouvellePartie = SDL_LoadBMP("SDL2\\images\\Front_End_images1\\NouvellePartieColoree.bmp"); //Charger l'image NouvellePartieColoree
                 break;
        case 2 : //le cas ou l'intersection s'est faite avec le boutton ChargerPartie (2eme boutton)
                 ChargerPartie = SDL_LoadBMP("SDL2\\images\\Front_End_images1\\ChargerPartieColoree.bmp");  //Charger l'image ChargerPartieColoree
                 break;
        case 3 : //le cas ou l'intersection s'est faite avec le boutton Quitter (3eme boutton)
                 Quitter = SDL_LoadBMP("SDL2\\images\\Front_End_images1\\QuitterColoree.bmp"); //Charger l'image QuitterColoree
                 break;
        
        default : break;
                 
    }

    /*gestion d'erreur de creation des surfaces*/
    if(ImageFond == NULL)
    {
        fprintf(stderr, "Erreur : SDL_LoadBMP() : %s", IMG_GetError());
        return -1;
    }
    if(NouvellePartie == NULL || ChargerPartie == NULL || Quitter == NULL) //Si le chargement des images dans les surfaces echoue
    {
        fprintf(stderr, "Erreur : SDL_LoadBMP() : %s", SDL_GetError());
        return -1;           //Valeur d'erreur 
    }

    /*Transformation des surfaces en textures*/
    ImageFondTex = SDL_CreateTextureFromSurface(Renderer, ImageFond);
    NouvellePartieTex = SDL_CreateTextureFromSurface(Renderer, NouvellePartie);
    ChargerPartieTex = SDL_CreateTextureFromSurface(Renderer, ChargerPartie);
    QuitterTex = SDL_CreateTextureFromSurface(Renderer, Quitter);

    /*Liberation des surfaces utilisees*/
     SDL_FreeSurface(ImageFond);
     SDL_FreeSurface(NouvellePartie);
     SDL_FreeSurface(ChargerPartie);
     SDL_FreeSurface(Quitter);

    if(ImageFond == NULL || NouvellePartie == NULL || ChargerPartie == NULL || Quitter == NULL) //Si la transformation des surfaces en textures echoue
    {
        fprintf(stderr, "Erreur : SDL_CreateTextureFromSurface() : %s", SDL_GetError());
        return -1;    //Valeur d'erreur
    }

    //collage des textures dans la fenetre 
    SDL_RenderCopy(Renderer, ImageFondTex, NULL, NULL);         
    SDL_RenderCopy(Renderer, NouvellePartieTex, NULL, &menu1_Buttons[0]);
    SDL_RenderCopy(Renderer, ChargerPartieTex, NULL, &menu1_Buttons[1]);
    SDL_RenderCopy(Renderer, QuitterTex, NULL, &menu1_Buttons[2]);

    /*Destruction des textures utilisees*/
    SDL_DestroyTexture(ImageFondTex);
    SDL_DestroyTexture(NouvellePartieTex);
    SDL_DestroyTexture(ChargerPartieTex);
    SDL_DestroyTexture(QuitterTex);

    SDL_RenderPresent(Renderer);  //Mise a jour du render 

    return 0; //Valeur de succes 
}

/*Renvoie le numero du boutton du menu principal que la souris a intersecté ou celui que l'utilisateur a cliqué*/
int SDL_MouseIntersect_menu1Buttons(SDL_Rect menu1_Buttons[3], int mouse_x, int mouse_y) //mouse_x : coordonne x de du point (pointe de la souris), mouse_y : coordonne y du point (pointe de la souris)
{
    for(int i = 1; i < 4; i++)
    {
        if((menu1_Buttons[i - 1].x <= mouse_x) && (mouse_x <= (menu1_Buttons[i - 1].x + menu1_Buttons[i - 1].w))
        && (menu1_Buttons[i - 1].y <= mouse_y) && (mouse_y <= (menu1_Buttons[i - 1].y + menu1_Buttons[i - 1].h)))
        {
            return i;
        }
    }
    //i = 1 si l'intersection ou le clique se fait avec le boutton 1 (NouvellePartie)
    //i = 2 si l'intersection se fait avec le boutton 2 ou le clique (ChargerPartie)
    //i = 3 si l'intersection se fait avec le boutton 3 ou le clique (Quitter)

    //Si l'intersection ou le clique ne se fait avec aucun des bouttons
    return 0;     //Valeur indiquant il n'y a aucune intersection avec aucun boutton
}

/*il gere les evenements pour le menu principal (menu1)*/
int SDL_ScanEventFromMenu1(SDL_bool *App_Launched, SDL_Window *Window, SDL_Renderer *Renderer, SDL_Rect menu1_buttons[3])
{
    int num_button_intersect = 0; //indique le numero de boutton que la souris a intersecté (0 indique par de clique sur aucun des bouttons)
    int num_button_clicked = 0;  //indique le numero de boutton cliqué par la souris (0 indique par de clique sur aucun des bouttons)
    while(*App_Launched)    //Passage par adresse de la variable qui controle la boucle de l'application au cas ou il a choisi le boutton quitter ou la croix rouge (pour fermer)
    {
        SDL_Event Event;
        while(SDL_PollEvent(&Event))
        {
            SDL_menu1(Window, Renderer, menu1_buttons, num_button_intersect);  //Affichage du menu principal
            switch(Event.type)
            {
                case SDL_MOUSEMOTION : //On recupere le numero de boutton que la souris a intersecté
                                       num_button_intersect = SDL_MouseIntersect_menu1Buttons(menu1_buttons, Event.motion.x, Event.motion.y);
                                       break; 
                case SDL_MOUSEBUTTONDOWN :  //On recupere le numero de boutton avec lequel la souris s'est intersecté apres clique
                                            num_button_clicked = SDL_MouseIntersect_menu1Buttons(menu1_buttons, Event.button.x, Event.button.y);
                                            if(num_button_clicked != 0)  //Si il a clique sur l'un des 3 bouttons du menu principal
                                            {
                                                return num_button_clicked;  //On renvoie le numero du boutton cliqué
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
                                break;
                        
            }
        }
    }
}