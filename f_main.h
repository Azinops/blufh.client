#ifndef F_MAIN_H_INCLUDED
#define F_MAIN_H_INCLUDED
#include "Classes.h"
void Jouer(lance_bombe joueurs_s[NBRE_JOUEURS]);
void afficher_explosions(lance_bombe joueurs_s[NBRE_JOUEURS]);
void copier_joueurs(lance_bombe joueurs[NBRE_JOUEURS],lance_bombe joueurs_a_coller[NBRE_JOUEURS]);
void afficher_score(lance_bombe joueurs[NBRE_JOUEURS],ALLEGRO_FONT*font);
void afficher_joueurs(lance_bombe joueurs);
void afficher_joueurs(lance_bombe joueurs[NBRE_JOUEURS-1]);
#endif // F_MAIN_H_INCLUDED
