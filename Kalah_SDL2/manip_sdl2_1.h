#ifndef MANIP_SDL2_1_H
#define MANIP_SDL2_1_H

#define WINDOW_WIDTH 800      //Definir la largeur de la fenetre 
#define WINDOW_HEIGHT 640    //Definir la hauteur de la fenetre

extern int SDL_Initial(SDL_Window **Window, SDL_Renderer **Renderer); //Window : fenetre de l'application , Renderer : le Rendu de la fenetre, Initialise la SDL2, cree la fenetre et le rendu de la fenetre
extern int TTF_Initial(TTF_Font **Font);  //Initialise la TTF et ouvre le font d'ecriture
extern void SDL_Refraichir(SDL_Renderer *Renderer); //Effacer la fenetre en noir (la refraichir)
extern void SDL_RefraichirRect(SDL_Renderer *Renderer, SDL_Rect Rect_Refraichi);  //Refraichi que la le Rect_Refraichi il le colore en noire
extern int SDL_AfficherMessage(SDL_Renderer *Renderer, TTF_Font *Font, SDL_Rect Barre_Message, char message[50]); //Affiche un message
#endif