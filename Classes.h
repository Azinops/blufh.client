#ifndef CLASSES_H_INCLUDED
#define CLASSES_H_INCLUDED
#include "souris_clavier.h"
#include "define_info.h"
class objet
{
public:
    objet();
    objet(double xi,double yi,ALLEGRO_BITMAP* imagei,double taillei);
    void stoper();
    void en_lair();
    void collision_sol();
    void soumettre_gravite();
    void mouvoir();
    void exister();
    void tuer();
    void tp(double nx,double ny);
    void changer_flag(int nflag);
    void changer_taille(double ntaille);
    void changer_taille_xy(double ntaillex,double ntailley);
    void atterir();
    void deplacer(double dx,double dy);
    void dimensionner(ALLEGRO_BITMAP* imagei);
    void initialiser(double xi,double yi,ALLEGRO_BITMAP* imagei,double taillei);
    void fixer_transparance(int ntransparance);
    void changer_angle(double nv_angle);
    void changer_centre(double nx,double ny);
    void changer_taille_x(double ntaille_x);
    void changer_taille_y(double ntaille_y);

    double get_x();
    double get_y();
    double get_taille_image_x();
    double get_taille_image_y();
    double get_centre_x();
    double get_centre_y();
    int get_flag();
    double get_taille_x();
    double get_taille_y();
    int get_existence();
    int get_transparance();
    ALLEGRO_COLOR get_filtre();
    double get_angle();
    double get_taille_reellex();
    double get_taille_reelley();
private:
    double x;
    double y;
    double vx;
    double vy;
    double ax;
    double ay;
    double taille_image_x;
    double taille_image_y;
    double x_centre;
    double y_centre;
    double taille_x;
    double taille_y;
    double angle;
    int flag;
    int transparance;
    int filtre_r;
    int filtre_g;
    int filtre_b;
    int existence;
    int au_sol;
    int soumis_gravite;
};
class objet_static : public objet
{
public:
    objet_static();
    objet_static(double xi,double yi,ALLEGRO_BITMAP* imagei,double taillei);
    void initialiser_stat(double xi,double yi,ALLEGRO_BITMAP* imagei,double taillei);
    void afficher();
    ALLEGRO_BITMAP* get_image();
private:
    ALLEGRO_BITMAP* image;
};
class objet_anime: public objet
{
public:
    objet_anime();
    objet_anime(double xi,double yi,ALLEGRO_BITMAP* imagei[NBRE_ANIM_MAX],double taillei,int nbre_anim,double vitesse_anim_i);
    void afficher();
    void animer_1(); //animation du début à la fin puis disparaitre
    int get_etat_anim();
    void set_anim();
    void changer_etat_anim(int netat);
private:
    ALLEGRO_BITMAP* image[NBRE_ANIM_MAX];
    int etat_anim;
    int n_images;
    double vitesse_anim;
    double compteur_anim;
};

class bombe
{
public:
    bombe();
    bombe(ALLEGRO_BITMAP* ibomei,ALLEGRO_BITMAP* iexplo1[],int typei,ALLEGRO_BITMAP* iexplo_croix[],double taille_explo,double taille_explo_croix
          ,int nbre_anim_explo1,int nbre_anim_explo_croix,double vitesse_anim_explo,double vitesse_anim_explo_croix);
    void afficher();
    void tp(double x,double y);
    int comporter();//renvoie -1 en cas normal et renvoie i€N si le joueur i est touché par une bombe
    void exploser_1();//explosion sphérique
    void exploser_2();//Explosion en croix
    void activation(int expediteuri,double angle_tir,double portee_explosion,double nx,double ny,double vitesse_tir);
    double get_angle();
    int collision_explo_croix_joueur();

    double get_x();
    double get_y();
    int get_etat();
    int get_etat_anim_bombe_explo();
//private:
    objet_static ibombe;
    objet_anime iexplo;//explosion sphérique
    objet_anime iexplo2[4];//explosion croix 0:bas  1:haut  2:gauche  3:droite
    int n_cases_explosees[4];//0:y+  1:y-  2:x-  3:x+
    int type;//0: bombe à lancer  1:bombe piege (explosion croix)
    int etat;//0:ne pas afficher    1:pret à etre activée   2:état intermédiaire  3: explose(sphérique)   4:explose (croix)
    double x;
    double y;
    double vx;
    double vy;
    int expediteur;
    double portee;
    int explo2_mur;//0: explo_scphérique si mur touche 1:explo croix si mur touche 2:explo croix limite si mur touche
    int portee_croix;
};

class lance_bombe
{
public:
    lance_bombe();
    lance_bombe(ALLEGRO_BITMAP* i_corps,double taille_i,int touche_haut,int touche_bas,int touche_gauche,int touche_droite,int touche_lance_bombei,int id_joueur,
                bombe bombe_jet_i,bombe bombe_piege_i,int touche_bombe_croix,int touche_positioni);
    void afficher();
    void tp(double xt,double yt);
    void controle();
    int jouer();//renvoie -1 en cas normal et i€N si le joueur i est tué
    int gestion_bombes(); //renvoie -1 en cas normal et i€N si le joueur i est tué
    void afficher_explosions();
    void disparaitre();
    void tuer();
    void fixer_nkills(int n_kills);

    double get_x_bombe_jet(int n_bombe_jet);
    double get_y_bombe_jet(int n_bombe_jet);
    int get_etat_bombe_jet(int n_bombe_jet);
    int get_etat_anim_bombe_jet(int n_bombe_jet);
    double get_x();
    double get_y();
    bool l_touche_apuyee(int touche);
    int get_vivant();
    int get_kills();
//private:
    bombe bombe_jet[NBRE_BOMBES_MAX+1];
    bombe bombe_piege;
    objet_static corps;
    double x;
    double y;
    int haut;
    int bas;
    int gauche;
    int droite;
    int touche_lance_bombe;
    int touche_pose_bombe_croix;
    int touche_position;
    int visible;
    double vitesse;
    double portee_bombe;
    double compteur_recharge_bombe_jet;
    double temps_recharge_bombe_jet;
    int bombe_prete;//0:non 1:oui 2:en rechargement
    int id;
    int n_bombe_a_lancer;
    double vitesse_bombe_jet;
    int vivant;
    int origine;//0:local   1:en ligne
    int bombe_croix_pose;//0:pas posée  2:en cours de pose 1:posée -1: en cours d'explosion
    int kills;
};


class camera
{
public:
    camera();
    camera(double xi,double yi,double zoomi,double vitesse_camera);
    void changer_fondc(ALLEGRO_BITMAP* nv_fond);
    void afficher_fondc();
    void tp_camerac(double nx,double ny);
    void deplacer_camerac(double dx,double dy);
    void zoomerc(double coef_zoom);
    void controle_fleches();
    double get_x();
    double get_y();
    double get_v();
    double get_zoom();
    void fixer_zoomerc(double nv_zoom);
    void fixer_transparance(int ntransparance);
private:
    double x;
    double y;
    double position_molette;
    double vitesse;
    double taille_fond_x;
    double taille_fond_y;
    double zoom;
    int flag;
    ALLEGRO_BITMAP* fond;
    Souris_clavier mks;
    int transparance;
    int filtre_r;
    int filtre_g;
    int filtre_b;
};
#endif // CLASSES_H_INCLUDED
