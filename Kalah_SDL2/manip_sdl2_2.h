#ifndef MANIP_SDL2_2_H
#define MANIP_SDL2_2_H

extern void Position_menu1buttons(SDL_Rect menu1_Buttons[3]); //Definir la position des differents bouttons du menu principal dans la fenetre 
extern int SDL_menu1(SDL_Window *Window, SDL_Renderer *Renderer, SDL_Rect menu1_Buttons[3], int num_button_intersect); //Afficher le menu principal du jeu (3 bouttons : Nouvelle partie, Charger partie, Quitter)
extern int SDL_MouseIntersect_menu1Buttons(SDL_Rect menu1_Buttons[3], int mouse_x, int mouse_y); //indique si la souris intersecte l'un des bouttons du menu principal (menu 1) et renvoie le numero de ce boutton 
extern int SDL_ScanEventFromMenu1(SDL_bool *App_Launched, SDL_Window *Window, SDL_Renderer *Renderer, SDL_Rect menu1_buttons[3]);  //Gere les evenements dans la fenetre du menu principal (evenement de la souris, evenement de la fenetre (fermer, reduire))

#endif