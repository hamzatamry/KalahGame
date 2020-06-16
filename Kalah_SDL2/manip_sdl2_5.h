#ifndef MANIP_SDL2_5_H
#define MANIP_SDL2_5_H

extern void Position_menuSauvegarde(SDL_Rect menu_Sauvegarde[4]);  //Definit les positions de bouttons de menu de sauvegarde
extern int SDL_menuSauvegarde(SDL_Window *Window, SDL_Renderer *Renderer, TTF_Font *Font, SDL_Rect menu_Sauvegade[4], char Donnee_Texte[4][30]
                                , int num_button_intersect);
extern void SDL_SaisirChamp_menuSauvegarde(SDL_Renderer *Renderer, TTF_Font *Font, 
                        SDL_Rect menu_Sauvegarde[4], char Donnee_Texte[4][30], int num_button_intersect); //permet de saisir le champ (nom de fichier)
extern int SDL_MouseIntersect_menuSauvegardeButtons(SDL_Rect menu_Sauvegarde[4], int mouse_x, int mouse_y); //verifier s'il ya une intersection avec l'un des bouttons
extern int SDL_ScanEventFromMenuSauvegarde(SDL_bool *App_Launched, SDL_Window *Window, SDL_Renderer *Renderer, TTF_Font *Font, SDL_Rect menu_Sauvegarde[4],
    char Donnee_Texte[4][30], pile plateau[2][8], int *dernier_joueur, int *nb_moitie, bool *chargee); //gere les evenements du menu sauvegarde

#endif 