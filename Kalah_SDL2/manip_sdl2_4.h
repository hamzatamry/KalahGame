#ifndef MANIP_SDL2_4_H
#define MANIP_SDL2_4_H

extern void Position_menuJeu(SDL_Rect menu_Jeu[30]); //Definir la position des bouttons et diffenrents messages dans le menuJeu
extern int SDL_menuJeu(SDL_Window *Window, SDL_Renderer *Renderer, TTF_Font *Font, SDL_Rect menu_Jeu[30], 
                       pile plateau[2][8], char Donnee_Texte[4][30], int num_button_intersect);
extern int SDL_MouseIntersect_menuJeuButtons(SDL_Rect menu_Jeu[30], int mouse_x, int mouse_y);
extern int SDL_ScanEventFromMenuJeu(SDL_bool *App_Launched, SDL_Window *Window, SDL_Renderer *Renderer, TTF_Font *Font,
                        SDL_Rect menu_Jeu[30], SDL_Rect AnnulerContinuer[2], pile plateau[2][8], char Donnee_Texte[4][30], int num_joueur, int nb_moitie);
extern int SDL_Afficher_num_joueur(SDL_Renderer *Renderer, TTF_Font *Font, int num_joueur, char Donnee_Texte[4][30]);  //Afficher le numero du joueur qui a va jouer
extern int TesterCreuxChoisiJoueur(SDL_Renderer *Renderer, TTF_Font *Font, int num_button_clicked, int num_joueur); //Tester si le creux choisi correspond a son joueur

extern void Position_AnnulerContinuer(SDL_Rect AnnulerContinuer[2]);
extern int SDL_AfficherBouttonAnnulerCoup(SDL_Renderer *Renderer, SDL_Rect AnnulerContinuer[2], int num_button_intersect);
extern int SDL_MouseIntersect_AnnulerContinuer(SDL_Rect AnnulerContinuer[2], int mouse_x, int mouse_y);
extern int SDL_ScanEventContinuerAnnuler(SDL_bool *App_Launched, SDL_Window *Window, SDL_Renderer *Renderer, SDL_Rect AnnulerContinuer[2]);

#endif