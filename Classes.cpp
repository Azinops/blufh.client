#include "Classes.h"
#include "affichage.h"
#include "define_info.h"
#include "f_map.h"

//------CLASSE:CAMERA-----------------------

void camera::deplacer_camerac(double dx,double dy)
{
    x+=dx;
    y+=dy;
}
void camera::tp_camerac(double nx,double ny)
{
    x=nx;
    y=ny;
}
void camera::changer_fondc(ALLEGRO_BITMAP* nv_fond)
{
    fond=nv_fond;
    taille_fond_x=double(al_get_bitmap_width(nv_fond));
    taille_fond_y=double(al_get_bitmap_height(nv_fond));
}

void camera::zoomerc(double coef_zoom)
{
    zoom=zoom*coef_zoom;
}
void camera::fixer_zoomerc(double nv_zoom)
{
    zoom=nv_zoom;
}
void camera::fixer_transparance(int ntransparance)
{

    transparance=ntransparance;
    filtre_r=ntransparance;
    filtre_g=ntransparance;
    filtre_b=ntransparance;
}
//---------------------CLASSE:OBJET--------------------
void objet::tp(double nx,double ny)
{
    x=nx;
    y=ny;
}
void objet::changer_taille(double ntaille)
{
    taille_x=ntaille;
    taille_y=ntaille;
}
void objet::changer_taille_xy(double ntaillex,double ntailley)
{
    taille_x=ntaillex;
    taille_y=ntailley;
}
void objet::deplacer(double dx,double dy)
{
    x+=dx;
    y+=dx;
}
void objet::changer_flag(int nflag)
{
    flag=nflag;
}
void objet::exister()
{
    existence=1;
}
void objet::tuer()
{
    existence=0;
}
void objet::mouvoir()
{
    if(soumis_gravite=1)
    {
        if(au_sol==0)
        {
            ay+=GRAVITE;
            au_sol=2;
        }
    }
    vx+=ax/FPS;
    vy+=ay/FPS;
    x+=vx/FPS;
    y+=vy/FPS;
}
void objet::soumettre_gravite()
{
    soumis_gravite=1;
}
void objet::atterir()
{
    au_sol=1;
    ay=0.00;
    vy=0.00;
}
void objet::collision_sol()
{
    if(y-(y_centre-taille_image_y)*taille_y>YBASED)
    {
        atterir();
        y=YBASED+(y_centre-taille_image_y)*taille_y;
    }
}
void objet::en_lair()
{
    au_sol=0;
}
void objet::stoper()
{
    vx=0.00;
    vy=0.00;
    ax=0.00;
    ay=0.00;
}
void objet::dimensionner(ALLEGRO_BITMAP* imagei)
{
    taille_image_x=double(al_get_bitmap_width(imagei));
    taille_image_y=double(al_get_bitmap_height(imagei));
    x_centre=taille_image_x/2.00;
    y_centre=taille_image_y/2.00;
}
void objet::fixer_transparance(int ntransparance)
{

    transparance=ntransparance;
    filtre_r=ntransparance;
    filtre_g=ntransparance;
    filtre_b=ntransparance;
}
void objet::changer_angle(double nv_angle)
{
    angle=nv_angle;
}
void objet::changer_centre(double nx,double ny)
{
    x_centre=nx;
    y_centre=ny;
}
void objet::changer_taille_x(double ntaille_x)
{
    taille_x=ntaille_x;
}
void objet::changer_taille_y(double ntaille_y)
{
    taille_y=ntaille_y;
}
//----------CLASSE:objet_static---------
//----------CLASSE:objet_anime---------
void objet_anime::animer_1()
{
    if(get_existence()==1)
    {
        compteur_anim+=vitesse_anim/double(FPS);
        int i=int(compteur_anim)+1;
        if(i>=n_images)
        {
            tuer();
            compteur_anim=0.00;
            etat_anim=1;
        }
        else
        {
            etat_anim=i;
        }
    }
}
int objet_anime::get_etat_anim()
{
    return etat_anim;
}
void objet_anime::set_anim()
{
    etat_anim=1;
    compteur_anim=0.00;
}
void objet_anime::changer_etat_anim(int netat)
{
    etat_anim=netat;
}
//----------CLASSE lance_bombe-----
void lance_bombe::tp(double xt,double yt)
{
    x=xt;
    y=yt;
    corps.tp(xt,yt);
}
int lance_bombe::jouer()
{
    int j_touche=-1;
    j_touche=gestion_bombes();
    if(vivant==1)
    {
        controle();
        afficher();
    }
    if(j_touche!=-1)
    {
        kills+=1;
    }
    return j_touche;
}
int lance_bombe::gestion_bombes()
{
    int j_touche=-1;
    if(bombe_prete==0)
    {
        compteur_recharge_bombe_jet=temps_recharge_bombe_jet;
        bombe_prete=2;
    }
    if(bombe_prete==2)
    {
        compteur_recharge_bombe_jet-=1.00/double(FPS);
        if(compteur_recharge_bombe_jet<=0.00)
        {
            compteur_recharge_bombe_jet=0.00;
            bombe_prete=1;
        }
    }
    if(bombe_prete==1)
    {
        if(l_touche_apuyee(touche_lance_bombe) && vivant==1)
        {
            bombe_prete=0;
            bombe_jet[n_bombe_a_lancer].activation(id,corps.get_angle(),portee_bombe,x,y,vitesse_bombe_jet);

            n_bombe_a_lancer=retablisseur(n_bombe_a_lancer+1,NBRE_BOMBES_MAX-1,0);
        }
    }
    int j_touche1=-1;
    int j_touche2=-1;
    int k;
    j_touche2=bombe_piege.comporter();
    for(k=0;k<=NBRE_BOMBES_MAX-1;k++)
    {
        j_touche1=bombe_jet[k].comporter();
        if(j_touche1!=-1)
        {
            j_touche=j_touche1;
        }
        if(j_touche2!=-1)
        {
            j_touche=j_touche2;
        }
    }
    if(vivant==1)
    {
        if(l_touche_apuyee(touche_pose_bombe_croix) && bombe_croix_pose==0)
        {
            bombe_croix_pose=2;
            bombe_piege.tp(x,y);
            bombe_piege.activation(id,0.00,portee_bombe,x,y,0.00);
        }
        if(bombe_croix_pose==2 && l_touche_apuyee(touche_pose_bombe_croix)==false)
        {
            bombe_croix_pose=1;
        }
        if(l_touche_apuyee(touche_pose_bombe_croix) && bombe_croix_pose==1)
        {
            bombe_piege.exploser_2();
            bombe_croix_pose=-1;
        }
        if(l_touche_apuyee(touche_pose_bombe_croix)==false && bombe_croix_pose==-1)
        {
            bombe_croix_pose=0;
        }
    }
    if(j_touche==id)
    {
        kills-=2;
    }
    return j_touche;
}
void lance_bombe::disparaitre()
{
    visible=0;
}
void lance_bombe::tuer()
{
    vivant=0;
}
//----CLASSE:bombe-----
void bombe::tp(double nx,double ny)
{
    ibombe.tp(nx,ny);
    iexplo.tp(nx,ny);
    int k;
    for(k=0;k<=3;k++)
    {
        iexplo2[k].tp(nx,ny);
    }
    x=nx;
    y=ny;
}
int bombe::comporter()
{
    int k;
    int j_v_touche=-1;
    if(type==0 || type==1)
    {
        int j_touche;
        if(etat==2)
        {
            if(distance_bombe_jet_proche(x,y)<=portee)
            {
                exploser_2();
            }
            x+=vx/double(FPS);
            y+=vy/double(FPS);
            tp(x,y);
            j_touche=collision_spherique_joueur_ennemi(x,y,expediteur,portee);
            if(j_touche!=-1)
            {
                exploser_1();
                j_v_touche=j_touche;
            }
            if(collision_mur_object_carre_destr(x,y,ibombe.get_taille_reellex(),ibombe.get_taille_reelley()))
            {
                if(explo2_mur==0)
                {
                    exploser_1();
                }
                if(explo2_mur==1)
                {
                    x-=vx/double(FPS);
                    y-=vy/double(FPS);
                    exploser_2();
                    portee_croix=N_CASES_X;
                }
                if(explo2_mur==2)
                {
                    x-=vx/double(FPS);
                    y-=vy/double(FPS);
                    exploser_2();
                }
            }
        }
        if(etat==3)
        {
            iexplo.animer_1();
            if(iexplo.get_existence()==0)
            {
                etat=0;
            }
            if(FRIENDLY_FIRE==0)
            {
                j_touche=collision_spherique_joueur_ennemi(x,y,expediteur,portee);
                if(etat==0)
                {
                    j_touche=-1;
                }
            }
            else
            {
                j_touche=collision_spherique_joueur_ennemi(x,y,-1,portee);
                if(etat==0)
                {
                    j_touche=-1;
                }
            }
            if(j_touche!=-1 && iexplo.get_etat_anim()<=DERNIER_ETAT_LETHAL_ANIM_EXPLO1)
            {
                j_v_touche=j_touche;
            }
        }
        if(etat==4)
        {
            if(etat!=0)
            {
                if(FRIENDLY_FIRE==0)
                {
                    j_touche=collision_spherique_joueur_ennemi(x,y,expediteur,portee);
                }
                else
                {
                    j_touche=collision_spherique_joueur_ennemi(x,y,-1,portee);
                }
                if(j_touche!=-1 && iexplo.get_etat_anim()<=DERNIER_ETAT_LETHAL_ANIM_EXPLO1)
                {
                    j_v_touche=j_touche;
                }
                if(j_v_touche==-1)
                {
                    double xe=(double(i_map(x))+0.50)*TAILLE_BLOCX;
                    double ye=(double(j_map(y))+0.50)*TAILLE_BLOCY;
                    tp(xe,ye);
                    iexplo.animer_1();
                    for(k=0;k<=3;k++)
                    {
                        iexplo2[k].animer_1();
                    }
                    j_touche=collision_explo_croix_joueur();
                    if(j_touche!=-1 && iexplo2[0].get_etat_anim()<=DERNIER_ETAT_LETHAL_ANIM_EXPLO2)
                    {
                        j_v_touche=j_touche;
                    }
                }
            }
            if(iexplo.get_existence()==0 && iexplo2[0].get_existence()==0)
            {
                etat=0;
            }

        }
    }
    return j_v_touche;
}
void bombe::activation(int expediteuri,double angle_tir,double portee_explosion,double nx,double ny,double vitesse_tir)
{
    if(type==0)
    {
        etat=2;
        ibombe.exister();
        iexplo.exister();
        int k;
        for(k=0;k<=3;k++)
        {
            iexplo2[k].exister();
        }
        tp(nx,ny);
        expediteur=expediteuri;
        vx=vitesse_tir*sin(angle_tir);
        vy=-vitesse_tir*cos(angle_tir);
        portee=portee_explosion;
    }
    if(type==1)
    {
        etat=2;
        ibombe.exister();
        iexplo.exister();
        int k;
        for(k=0;k<=3;k++)
        {
            iexplo2[k].exister();
        }
        tp(nx,ny);
        expediteur=expediteuri;
        vx=0.00;
        vy=0.00;
        portee=portee_explosion;
    }
}
void bombe::exploser_1()
{
    iexplo.set_anim();
    etat=3;
}
void bombe::exploser_2()
{
    etat=4;
    iexplo.set_anim();
    int k;
    for(k=0;k<=3;k++)
    {
        iexplo2[k].set_anim();
    }
    double tx=iexplo2[0].get_taille_image_x();
    double ty=iexplo2[0].get_taille_image_y();
    iexplo2[0].changer_centre(tx-DISTANCE_DEBUT_CENTRE_EXPLO_CROIX,ty/2.00);
    iexplo2[0].changer_angle(-PI/2.00);
    iexplo2[1].changer_centre(tx-DISTANCE_DEBUT_CENTRE_EXPLO_CROIX,ty/2.00);
    iexplo2[1].changer_angle(PI/2.00);
    iexplo2[2].changer_centre(tx-DISTANCE_DEBUT_CENTRE_EXPLO_CROIX,ty/2.00);
    iexplo2[2].changer_angle(0.00);
    iexplo2[3].changer_centre(tx-DISTANCE_DEBUT_CENTRE_EXPLO_CROIX,ty/2.00);
    iexplo2[3].changer_angle(PI);
    int i=i_map(x);
    int j=j_map(y);
    double xe=(double(i)+0.50)*TAILLE_BLOCX;
    double ye=(double(j)+0.50)*TAILLE_BLOCY;
    int dx;
    int dy;
    int xp;
    int yp;
    int d;
    for(k=0;k<=3;k++)
    {
        if(k==0)
        {
            dx=0;
            dy=1;
        }
        if(k==1)
        {
            dx=0;
            dy=-1;
        }
        if(k==2)
        {
            dx=-1;
            dy=0;
        }
        if(k==3)
        {
            dx=1;
            dy=0;
        }
        xp=i;
        yp=j;
        if(TYPE_EXPLO_MUR!=2)
        {
            portee_croix=N_CASES_X;
        }
        if(type==1)
        {
            portee_croix=N_CASES_X;
        }
        while(case_vise(xp,yp)==true && abs(xp-i)<=portee_croix && abs(yp-j)<=portee_croix)
        {
            xp+=dx;
            yp+=dy;
        }
        if(k==0 || k==1)
        {
            d=abs(yp-j)-1;
        }
        else
        {
            d=abs(xp-i)-1;
        }
        n_cases_explosees[k]=d;
        iexplo2[k].changer_taille_x(double(d)*TAILLE_BLOCX/(iexplo2[k].get_taille_image_x()*COEFF_FIN_CENTRE_EXPLO_CROIX));
    }
    tp(xe,ye);
}
bool lance_bombe::l_touche_apuyee(int touche)
{
    if(origine==0)
    {
        return touche_appuyee(touche);
    }
    else
    {

    }
}
void lance_bombe::fixer_nkills(int n_kills)
{
    kills=n_kills;
}

