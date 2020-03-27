#include "Classes.h"
#include "affichage.h"
#include "define_info.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
//------------CLASSE:CAMERA------------
double camera::get_x()
{
    return x;
}
double camera::get_y()
{
    return y;
}
double camera::get_v()
{
    return vitesse;
}
double camera::get_zoom()
{
    return zoom;
}
//---------CLASSE:OBJET---------------
double objet::get_x()
{
    return x;
}
double objet::get_y()
{
    return y;
}
double objet::get_taille_image_x()
{
    return taille_image_x;
}
double objet::get_taille_image_y()
{
    return taille_image_y;
}
double objet::get_centre_x()
{
    return x_centre;
}
double objet::get_centre_y()
{
    return y_centre;
}
int objet::get_flag()
{
    return flag;
}
double objet::get_angle()
{
    return angle;
}
double objet::get_taille_x()
{
    return taille_x;
}
double objet::get_taille_y()
{
    return taille_y;
}
int objet::get_existence()
{
    return existence;
}
int objet::get_transparance()
{
    return transparance;
}
ALLEGRO_COLOR objet::get_filtre()
{
    return al_map_rgba(filtre_r,filtre_g,filtre_b,transparance);
}
double objet::get_taille_reellex()
{
    return taille_image_x*taille_x;
}
double objet::get_taille_reelley()
{
    return taille_image_y*taille_y;
}
//-----------CLASSE:OBJET_STATIC-----------
ALLEGRO_BITMAP* objet_static::get_image()
{
    return image;
}

//-----CLASSE:bombe----
double bombe::get_angle()
{
    return ibombe.get_angle();
}
double bombe::get_x()
{
    return x;
}
double bombe::get_y()
{
    return y;
}
int bombe::get_etat()
{
    return etat;
}
int bombe::get_etat_anim_bombe_explo()
{
    return iexplo.get_etat_anim();
}
//-------CLASSE:lance_bombe-----
double lance_bombe::get_x()
{
    return x;
}
double lance_bombe::get_y()
{
    return y;
}
double lance_bombe::get_x_bombe_jet(int n_bombe_jet)
{
    return bombe_jet[n_bombe_jet].get_x();
}
double lance_bombe::get_y_bombe_jet(int n_bombe_jet)
{
    return bombe_jet[n_bombe_jet].get_y();
}
int lance_bombe::get_etat_bombe_jet(int n_bombe_jet)
{
    return bombe_jet[n_bombe_jet].get_etat();
}
int lance_bombe::get_etat_anim_bombe_jet(int n_bombe_jet)
{
    return bombe_jet[n_bombe_jet].get_etat_anim_bombe_explo();
}
int lance_bombe::get_vivant()
{
    return vivant;
}
int lance_bombe::get_kills()
{
    return kills;
}
