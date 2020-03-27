#ifndef V_AFFICHAGE_H_INCLUDED
#define V_AFFICHAGE_H_INCLUDED

#define XFENETRE xfen
#define YFENETRE yfen

#define COEF_PIXEL_X coeffx
#define COEF_PIXEL_Y coeffy

#include "Classes.h"
#include "define_info.h"
ALLEGRO_DISPLAY* display;
ALLEGRO_DISPLAY_MODE rec;
double xfen;
double yfen;
double coeffx;
double coeffy;

//CAMERA
camera cam(XI_CAM,YI_CAM,ZOOM_INITIAL,VITESSE_CAMERA);

#endif // V_AFFICHAGE_H_INCLUDED
