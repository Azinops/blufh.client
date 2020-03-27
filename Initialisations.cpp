#include "Classes.h"
#include "affichage.h"
#include "define_info.h"

camera::camera(double xi,double yi,double zoomi,double vitesse_camera)
{
    x=xi;
    y=yi;
    flag=0;
    zoom=zoomi;
    position_molette=0.00;
    vitesse=vitesse_camera;
    transparance=TRANSPARANCE_INITIALE;
    filtre_r=ROUGE_I;
    filtre_g=VERT_I;
    filtre_b=BLEU_I;
}

objet::objet()
{

}
objet::objet(double xi,double yi,ALLEGRO_BITMAP* imagei,double taillei)
{
    x=xi;
    y=yi;
    angle=0.00;
    taille_x=taillei;
    taille_y=taillei;
    flag=0;
    dimensionner(imagei);
    transparance=TRANSPARANCE_INITIALE;
    filtre_r=ROUGE_I;
    filtre_g=VERT_I;
    filtre_b=BLEU_I;
}
void objet::initialiser(double xi,double yi,ALLEGRO_BITMAP* imagei,double taillei)
{
    x=xi;
    y=yi;
    taille_x=taillei;
    taille_y=taillei;
    dimensionner(imagei);
    angle=0.00;
    flag=0;
    vx=0.00;
    vy=0.00;
    ax=0.00;
    ay=0.00;
    existence=0;
    au_sol=0;
    soumis_gravite=0;
    transparance=TRANSPARANCE_INITIALE;
    filtre_r=ROUGE_I;
    filtre_g=VERT_I;
    filtre_b=BLEU_I;
}
objet_static::objet_static()
{

}
objet_static::objet_static(double xi,double yi,ALLEGRO_BITMAP* imagei,double taillei)
{
    initialiser(xi,yi,imagei,taillei);
    image=imagei;
}
void objet_static::initialiser_stat(double xi,double yi,ALLEGRO_BITMAP* imagei,double taillei)
{
    initialiser(xi,yi,imagei,taillei);
    image=imagei;
}
objet_anime::objet_anime()
{

}
objet_anime::objet_anime(double xi,double yi,ALLEGRO_BITMAP* imagei[NBRE_ANIM_MAX],double taillei,int nbre_anim,double vitesse_anim_i)
{
    initialiser(xi,yi,imagei[1],taillei);
    int k;
    for(k=1;k<=nbre_anim;k++)
    {
        image[k]=imagei[k];
    }
    etat_anim=1;
    compteur_anim=0.00;
    vitesse_anim=vitesse_anim_i;
    n_images=nbre_anim;
}
bombe::bombe()
{

}
bombe::bombe(ALLEGRO_BITMAP* ibomei,ALLEGRO_BITMAP* iexplo1[],int typei,ALLEGRO_BITMAP* iexplo_croix[],double taille_explo,double taille_explo_croix,
             int nbre_anim_explo1,int nbre_anim_explo_croix,double vitesse_anim_explo,double vitesse_anim_explo_croix)
{
    ibombe.initialiser_stat(0.00,0.00,ibomei,1.00);
    ibombe.changer_taille_xy(TAILLE_BOMBESI*TAILLE_BLOCX/ibombe.get_taille_image_x(),TAILLE_BOMBESI*TAILLE_BLOCY/ibombe.get_taille_image_y());
    type=typei;
    iexplo=objet_anime(0.00,0.00,iexplo1,1.00,nbre_anim_explo1,vitesse_anim_explo);
    iexplo.changer_taille_xy(taille_explo*TAILLE_BLOCX/iexplo.get_taille_image_x(),taille_explo*TAILLE_BLOCY/iexplo.get_taille_image_y());
    int k;
    for(k=0;k<=3;k++)
    {
        iexplo2[k]=objet_anime(0.00,0.00,iexplo_croix,1.00,nbre_anim_explo_croix,vitesse_anim_explo_croix);
        iexplo2[k].changer_taille_xy(taille_explo_croix*TAILLE_BLOCX/iexplo2[k].get_taille_image_x(),taille_explo_croix*TAILLE_BLOCY/iexplo2[k].get_taille_image_y());
        iexplo2[k].exister();
    }
    ibombe.exister();
    iexplo.exister();
    x=0.00;
    y=0.00;
    vx=2.00*VITESSE_BOMBE_I/double(N_CASES_X+N_CASES_Y);
    vy=2.00*VITESSE_BOMBE_I/double(N_CASES_X+N_CASES_Y);
    expediteur=0;
    portee=PORTEE_BOMBE_I*(TAILLE_BLOCX+TAILLE_BLOCY)/2.00;
    explo2_mur=TYPE_EXPLO_MUR;
    portee_croix=PORTEE_CROIX;
}
lance_bombe::lance_bombe()
{

}
lance_bombe::lance_bombe(ALLEGRO_BITMAP* i_corps,double taille_i,int touche_haut,int touche_bas,int touche_gauche,int touche_droite,int touche_lance_bombei,int id_joueur,
                         bombe bombe_jet_i,bombe bombe_piege_i,int touche_bombe_croix,int touche_positioni)
{
    corps.initialiser_stat(XI_OBJ,YI_OBJ,i_corps,1.00);
    double tix=corps.get_taille_image_x();
    double tiy=corps.get_taille_image_y();
    corps.changer_taille_xy(TAILLE_LBX/tix*taille_i,TAILLE_LBY/tiy*taille_i);
    x=XBASED/2.00;
    y=YBASED/2.00;
    corps.exister();
    haut=touche_haut;
    bas=touche_bas;
    gauche=touche_gauche;
    droite=touche_droite;
    visible=1;
    vitesse=2.00*VITESSE_LB_I/double(N_CASES_X+N_CASES_Y);
    portee_bombe=PORTEE_BOMBE_I*(TAILLE_BLOCX+TAILLE_BLOCY)/2.00;
    touche_lance_bombe=touche_lance_bombei;
    compteur_recharge_bombe_jet=0.00;
    temps_recharge_bombe_jet=TEMP_RECHARGE_BOMBE_JET_I;
    bombe_prete=1;
    id=id_joueur;
    int k;
    for(k=0;k<=NBRE_BOMBES_MAX-1;k++)
    {
        bombe_jet[k]=bombe_jet_i;
    }
    bombe_piege=bombe_piege_i;
    n_bombe_a_lancer=0;
    vitesse_bombe_jet=2.00*VITESSE_BOMBE_I/double(N_CASES_X+N_CASES_Y);
    vivant=1;
    touche_pose_bombe_croix=touche_bombe_croix;
    origine=0;
    bombe_croix_pose=0;
    kills=0;
    touche_position=touche_positioni;
}


