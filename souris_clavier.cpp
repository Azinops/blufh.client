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
#include "souris_clavier.h"
#include "Classes.h"
#include "v_souris_clavier.h"
#include "define_info.h"
#include "affichage.h"
#include "f_map.h"
using namespace std;

int Souris_clavier::clic_souris()
{
    OBTENIR_SOURIS
    if(mouse.buttons&1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int Souris_clavier::passer_souris_sur_cercle(double x_centre,double y_centre, double rayon)
{
    OBTENIR_SOURIS
    if(distance(mouse.x,mouse.y,x_centre,y_centre)<=rayon)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int Souris_clavier::clic_sur_cercle(double x_centre,double y_centre, double rayon)
{
    OBTENIR_SOURIS
    if(passer_souris_sur_cercle(x_centre,y_centre,rayon)==1 && mouse.buttons&1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int Souris_clavier::passer_souris_sur_carre(double x1_carre, double y1_carre, double x2_carre, double y2_carre)
{
    OBTENIR_SOURIS
    if(mouse.x>=x1_carre && mouse.x<=x2_carre && mouse.y>=y1_carre && mouse.y<=y2_carre)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int Souris_clavier::clic_sur_carre(double x1_carre, double y1_carre, double x2_carre, double y2_carre)
{
    OBTENIR_SOURIS
    if(passer_souris_sur_carre(x1_carre,x2_carre,y1_carre,y2_carre)==1 && mouse.buttons&1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int Souris_clavier::appuye_sur_touche(int touche)
{
    static int appuye=0;
    OBTENIR_CLAVIER
    if(al_key_down(&key,touche) && appuye==0)
    {
        appuye=1;
        return 1;
    }
    if(!al_key_down(&key,touche))
    {
        appuye=0;
    }
    return 0;
}
int Souris_clavier::touche_appuyee(int touche)
{
    OBTENIR_CLAVIER
    return (al_key_down(&key,touche));
}
double Souris_clavier::get_x()
{
    return mouse.x;
}
double Souris_clavier::get_y()
{
    return mouse.y;
}
double x_souris()
{
    return moukey.get_x();
}
double y_souris()
{
    return moukey.get_y();
}
bool touche_appuyee(int touche)
{
    if(moukey.touche_appuyee(touche))
    {
        return true;
    }
    else
    {
        return false;
    }
}
//----------------CLASSE:CAMERA----------------
void controle_camera_fleches()
{
    if(moukey.touche_appuyee(ALLEGRO_KEY_UP))
    {
        deplacer_camera(0.00,-VITESSE_CAMERA/FPS/cam_zoom());
    }
    if(moukey.touche_appuyee(ALLEGRO_KEY_DOWN))
    {
        deplacer_camera(0.00,VITESSE_CAMERA/FPS/cam_zoom());
    }
    if(moukey.touche_appuyee(ALLEGRO_KEY_RIGHT))
    {
        deplacer_camera(VITESSE_CAMERA/FPS/cam_zoom(),0.00);
    }
    if(moukey.touche_appuyee(ALLEGRO_KEY_LEFT))
    {
        deplacer_camera(-VITESSE_CAMERA/FPS/cam_zoom(),0.00);
    }
    if(moukey.touche_appuyee(ALLEGRO_KEY_PAD_0))
    {
        zoomer(V_ZOOM);
    }
    if(moukey.touche_appuyee(ALLEGRO_KEY_PAD_1))
    {
        zoomer(1/V_ZOOM);
    }
}
int passer_souris_dans_rectangle(double x1,double y1,double x2, double y2)
{
    if(moukey.passer_souris_sur_carre(x1,y1,x2,y2))
    {
        return 1;
    }
    return 0;
}
//--------lance_bombe-----

void lance_bombe::controle()
{
    double Xa=x;
    double Ya=y;
    if(l_touche_apuyee(haut))
    {
        y-=vitesse/double(FPS);
        if(!moukey.touche_appuyee(touche_position))
            corps.changer_angle(0.00);
    }
    else
    {
        if(l_touche_apuyee(bas))
        {
            y+=vitesse/double(FPS);
            if(!moukey.touche_appuyee(touche_position))
                corps.changer_angle(-PI);
        }
        else
        {
            if(l_touche_apuyee(gauche))
            {
                x-=vitesse/double(FPS);
                if(!moukey.touche_appuyee(touche_position))
                    corps.changer_angle(-PI/2.00);
            }
            else
            {
                if(l_touche_apuyee(droite))
                {
                    x+=vitesse/double(FPS);
                    if(!moukey.touche_appuyee(touche_position))
                        corps.changer_angle(PI/2.00);
                }
            }
        }
    }
    if(collision_mur_object_carre(x,y,corps.get_taille_reellex(),corps.get_taille_reelley()))
    {
        x=Xa;
        y=Ya;
    }
}
