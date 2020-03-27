#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "Classes.h"

void plein_ecran();

void afficher_image(ALLEGRO_BITMAP* image,double centre_x, double centre_y, double x,double y, double grandissement_x,double grandissement_y, double angle,int flags);
void afficher_cercle(double x,double y,double rayon,ALLEGRO_COLOR couleur,double epaisseur);
void afficher_ligne(double x1,double y1,double x2,double y2,ALLEGRO_COLOR couleur,double epaisseur);
void afficher_cercle_plein(double x,double y,double rayon,ALLEGRO_COLOR couleur);

void changer_fond(ALLEGRO_BITMAP* nv_fond);
void init_camera(double xi,double yi,ALLEGRO_BITMAP* fondi,double zoomi);
void afficher_fond();
void deplacer_camera(double dx,double dy);
void tp_camera(double nx,double ny);
void zoomer(double coeff_zoom);
void fixer_zoom(double nv_zoom);
double cam_zoom();
void effet_fond(objet_static effet);
void afficher_image_custom(ALLEGRO_BITMAP* image,double centre_x, double centre_y, double x,double y, double grandissement_x,double grandissement_y, double angle,int flags,ALLEGRO_COLOR filtre);
void changer_transparance_fond(int ntransparance);
#endif // AFFICHAGE_H_INCLUDED
