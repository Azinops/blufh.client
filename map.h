#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <allegro5/allegro.h>
#include "define_info.h"
#include "Classes.h"

int MAP[N_CASES_Y+1][N_CASES_X+1];
ALLEGRO_BITMAP* iBlocs[NI_BLOCS+2];
double xim_bloc;
double yim_bloc;
lance_bombe joueurs[NBRE_JOUEURS];
int n_decode=0;
int n_encode=0;
char* PACKET_INFO=NULL;
char PACKET_TOUCHES[N_CARACTERES_PACKET_TOUCHE];
#endif // MAP_H_INCLUDED
