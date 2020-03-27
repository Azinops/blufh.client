#ifndef SOURIS_CLAVIER_H_INCLUDED
#define SOURIS_CLAVIER_H_INCLUDED
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include "fonctions.h"

class Souris_clavier
{
    public:

    int clic_souris();
    int passer_souris_sur_cercle(double x_centre,double y_centre, double rayon);
    int clic_sur_cercle(double x_centre,double y_centre, double rayon);
    int passer_souris_sur_carre(double x1_carre, double y1_carre, double x2_carre, double y2_carre);
    int clic_sur_carre(double x1_carre, double y1_carre, double x2_carre, double y2_carre);
    int appuye_sur_touche(int touche);
    int touche_appuyee(int touche);
    double get_x();
    double get_y();
    private:

    ALLEGRO_KEYBOARD_STATE key;
    ALLEGRO_MOUSE_STATE mouse;
};
void controle_camera_fleches();
int passer_souris_dans_rectangle(double x1,double y1,double x2, double y2);
double x_souris();
double y_souris();
bool touche_appuyee(int touche);
#endif // SOURIS_CLAVIER_H_INCLUDED
