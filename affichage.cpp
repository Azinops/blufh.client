#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "affichage.h"
#include "souris_clavier.h"
#include "fonctions.h"
#include "v_affichage.h"
#include "Classes.h"

void plein_ecran()
{
    if(!al_init())
        erreur("al_init()");
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    ALLEGRO_DISPLAY_MODE rec;
    al_get_display_mode(al_get_num_display_modes() - 1, &rec);
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    display = al_create_display(rec.width, rec.height);
    if(!display)\
        erreur("creation display");
    xfen=double(al_get_display_width(display));
    yfen=double(al_get_display_height(display));
    coeffx=xfen/XBASED;
    coeffy=yfen/YBASED;
}
//TOUT LE JEU EST BASE SUR LES DIMENSIONS XBASE ET YBASE ET SEULEMENT L'AFFICHAGE MULTIPLIE PAR COEF_PIXEL_X ET COEF_PIXEL_Y

//FONCTION DESSIN BASIQUES---
void afficher_image(ALLEGRO_BITMAP* image,double centre_x, double centre_y, double x,double y, double grandissement_x,double grandissement_y, double angle,int flags)
{
    x=(x-cam.get_x()-XBASED/2.00)*cam.get_zoom()+XBASED/2.00;
    y=(y-cam.get_y()-YBASED/2.00)*cam.get_zoom()+YBASED/2.00;
    al_draw_scaled_rotated_bitmap(image,centre_x,centre_y,x*COEF_PIXEL_X,y*COEF_PIXEL_Y,grandissement_x*COEF_PIXEL_X*cam.get_zoom(),grandissement_y*COEF_PIXEL_Y*cam.get_zoom(),angle,flags);
}
void afficher_image_custom(ALLEGRO_BITMAP* image,double centre_x, double centre_y, double x,double y, double grandissement_x,double grandissement_y, double angle,int flags,ALLEGRO_COLOR filtre)
{
    x=(x-cam.get_x()-XBASED/2.00)*cam.get_zoom()+XBASED/2.00;
    y=(y-cam.get_y()-YBASED/2.00)*cam.get_zoom()+YBASED/2.00;
    al_draw_tinted_scaled_rotated_bitmap(image,filtre,centre_x,centre_y,x*COEF_PIXEL_X,y*COEF_PIXEL_Y,grandissement_x*COEF_PIXEL_X*cam.get_zoom(),grandissement_y*COEF_PIXEL_Y*cam.get_zoom(),angle,flags);
}
void afficher_cercle(double x,double y,double rayon,ALLEGRO_COLOR couleur,double epaisseur)
{
    x-=cam.get_x();
    y-=cam.get_y();
    x=x*cam.get_zoom()-XBASED*(cam.get_zoom()-1.00)/2.00;
    y=y*cam.get_zoom()-YBASED*(cam.get_zoom()-1.00)/2.00;
    al_draw_ellipse(x*COEF_PIXEL_X,y*COEF_PIXEL_Y,rayon*COEF_PIXEL_X*cam.get_zoom(),rayon*COEF_PIXEL_Y*cam.get_zoom(),couleur,epaisseur*COEF_PIXEL_X*cam.get_zoom());
}
void afficher_ligne(double x1,double y1,double x2,double y2,ALLEGRO_COLOR couleur,double epaisseur)
{
    x1-=cam.get_x();
    y1-=cam.get_y();
    x2-=cam.get_x();
    y2-=cam.get_y();
    x1=x1*cam.get_zoom()-XBASED*(cam.get_zoom()-1.00)/2.00;
    x2=x2*cam.get_zoom()-XBASED*(cam.get_zoom()-1.00)/2.00;
    y1=y1*cam.get_zoom()-YBASED*(cam.get_zoom()-1.00)/2.00;
    y2=y2*cam.get_zoom()-YBASED*(cam.get_zoom()-1.00)/2.00;
    al_draw_line(x1*COEF_PIXEL_X,y1*COEF_PIXEL_Y,x2*COEF_PIXEL_X,y2*COEF_PIXEL_Y,couleur,epaisseur*COEF_PIXEL_X*cam.get_zoom());
}
void afficher_cercle_plein(double x,double y,double rayon,ALLEGRO_COLOR couleur)
{
    x-=cam.get_x();
    y-=cam.get_y();
    x=x*cam.get_zoom()-XBASED*(cam.get_zoom()-1.00)/2.00;
    y=y*cam.get_zoom()-YBASED*(cam.get_zoom()-1.00)/2.00;
    al_draw_filled_ellipse(x*COEF_PIXEL_X,y*COEF_PIXEL_Y,rayon*COEF_PIXEL_X*cam.get_zoom(),rayon*COEF_PIXEL_Y*cam.get_zoom(),couleur);
}
//------------CLASSE:CAMERA--------------
void camera::afficher_fondc()
{
    afficher_image_custom(fond,0.00,0.00,0.00,0.00,1.00,1.00,0.00,0,al_map_rgba(filtre_r,filtre_g,filtre_b,transparance));
}
void afficher_fond()
{
    cam.afficher_fondc();
}
void changer_fond(ALLEGRO_BITMAP* nv_fond)
{
    cam.changer_fondc(nv_fond);
}
void deplacer_camera(double dx,double dy)
{
    cam.deplacer_camerac(dx,dy);
}
void tp_camera(double nx,double ny)
{
    cam.tp_camerac(nx,ny);
}
void zoomer(double coeff_zoom)
{
    cam.zoomerc(coeff_zoom);
}
double cam_zoom()
{
    return cam.get_zoom();
}
void effet_fond(objet_static effet)
{
    effet.tp(cam.get_x()+XBASED/2.00,cam.get_y()+YBASED/2.00);
    effet.changer_taille_xy(XBASED/effet.get_taille_image_x()/cam.get_zoom(),YBASED/effet.get_taille_image_y()/cam.get_zoom());
    effet.afficher();
}
//----------CLASSE:OBJET FIXE---------

void objet_static::afficher()
{
    if(get_existence()==1)
    {
        afficher_image_custom(image,get_centre_x(),get_centre_y(),get_x(),get_y(),get_taille_x(),get_taille_y(),get_angle(),get_flag(),get_filtre());
    }
}
//------CLASSE:OBJET_ANIME----
void objet_anime::afficher()
{
    if(get_existence()==1)
    {
        afficher_image_custom(image[etat_anim],get_centre_x(),get_centre_y(),get_x(),get_y(),get_taille_x(),get_taille_y(),get_angle(),get_flag(),get_filtre());
    }
}
//--------AUCUNE CLASSE-------------
void fixer_zoom(double nv_zoom)
{
    cam.fixer_zoomerc(nv_zoom);
}

void changer_transparance_fond(int ntransparance)
{
    cam.fixer_transparance(ntransparance);
}
//-----CLASSE:LANCE_BOMBE--------
void lance_bombe::afficher()
{
    if(visible==1)
    {
        corps.tp(x,y);
    }
    if(visible!=0)
    {
        corps.afficher();
    }
}
void lance_bombe::afficher_explosions()
{
    int k;
    for(k=0;k<=NBRE_BOMBES_MAX-1;k++)
    {
        bombe_jet[k].afficher();
    }
    bombe_piege.afficher();
}
//-----CLASSE:BOMBE-----
void bombe::afficher()
{
    if(etat==2)
    {
        if(type==0)
        {
            ibombe.afficher();
        }
    }
    if(etat==3)
    {
        iexplo.afficher();
    }
    if(etat==4)
    {
        int k;
        for(k=0;k<=3;k++)
        {
            iexplo2[k].afficher();
        }
        iexplo.afficher();
    }
}
