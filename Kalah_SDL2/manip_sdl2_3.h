#ifndef MANIP_SDL2_3_H
#define MANIP_SDL2_3_H

extern void Position_menuDonnee(SDL_Rect menu_Donnee[11]); //Definir la position des differents bouttons , barres de saisie et message associe au barre de saisie
extern int SDL_menuDonnee(SDL_Window *Window, SDL_Renderer *Renderer, TTF_Font *Font, 
                SDL_Rect menu_Donnee[11], char Donnee_Texte[4][30], int num_button_intersect);  //Afficher le menu des donnees (Nom de la partie, nom de joueur1, nom du joueur 2, nombre de piece initial dans chaque creux) 
extern int SDL_MouseIntersect_menuDonneeButtons(SDL_Rect menu_Donnee[11], int mouse_x, int mouse_y);//Indique si la souris a intersecté les bouttons du menu donnee
extern int SDL_ScanEventFromMenuDonnee(SDL_bool *App_Launched, SDL_Window *Window, SDL_Renderer *Renderer, TTF_Font *Font,
                SDL_Rect menu_Donnee[11], char Donnee_Texte[4][30]);  //Gere les evenement de la fenetre relatif au menu de donne (saisir les donnees du champ de saisie, fermer fenetre, reduire fenetre, cliquer sur boutton)
extern SDL_bool SDL_DonneeVerification(SDL_Renderer *Renderer, TTF_Font *Font, char Donnee_Texte[4][30]); //Verifie si les donnees saisie dans les champs sont correctes
extern SDL_bool SDL_Champvide(char Donnee_Texte[4][30]);  //Test si l'un des champ de saisie est vide
extern SDL_bool SDL_Nbpiecevalide(char Donnee_Texte[4][30]); //Verifier si le nombre de piece est valide
extern void SDL_SaisirChamp(SDL_Renderer *Renderer, TTF_Font *Font, SDL_Rect menu_Donnee[11], 
                    char Donnee_Texte[4][30], int num_button_intersect); //Saisir les champ

#endif