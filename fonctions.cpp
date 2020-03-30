#include <stdio.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include "fonctions.h"
#include "v_fonctions.h"
int roundi(double variable)
{
     return int(variable+0.5);
}
void erreur(const char*txt)
{
    ALLEGRO_DISPLAY*d;
    d=al_is_system_installed()?al_get_current_display():NULL;
    al_show_native_message_box(NULL,"ERREUR",txt,NULL,NULL,0);
    exit(EXIT_FAILURE);
}
int retablisseur(int valeur,int valeur_max,int valeur_min)
{
    if(valeur>valeur_max)
    {
        valeur=valeur_min;
    }
    return valeur;
}
double distance(double x1,double y1, double x2, double y2)
{
    return sqrt(pow(x1-x2,2.00)+pow(y1-y2,2.00));
}
int random(int a, int b)
{
    if(a<=0 && b<=0)
    {
        return -random(-b,-a);
    }
    else
    {
        return rand()%(b-a+1) + a;
    }
}
int modulo(double x,int maxi)
{
    int a=roundi(x);
    int r=a%(2*maxi);
    if(r>maxi)
    {
        r=maxi-a%maxi;
    }
    return r;
}
double retablisseurD(double valeur,double valeur_max,double valeur_min)
{
    if(valeur>valeur_max)
    {
        valeur=valeur_min;
    }
    return valeur;
}
int borne_inf(int a,int borne)
{
    if(a<borne)
    {
        a=borne;
    }
    return a;
}
double arrondi(double nombre,int nbre_chiffres)
{
    double p10=pow(10.00,double(nbre_chiffres));
    return double(int(nombre*p10))/p10;
}
int n_ieme_chiffre(double nombre,int n)
{
    int len=int(log10(nombre));
    return roundi((arrondi(nombre,-len+n)-arrondi(nombre,-len+n-1))/pow(10.00,double(len-n)));
}
int n_ieme_chiffrem(double nombre,int n)
{
    return roundi((arrondi(nombre,n)-arrondi(nombre,n-1))/pow(10.00,double(-n)));
}
int n_ieme_chiffremi(int nombre,int n)
{
    int a=nombre/roundi(pow(10.00,double(n)));
    return (a-10*(a/int(10)));
}
double absd(double a)
{
    if(a<0.00)
    {
        return (-a);
    }
    return a;
}
int bool_to_int(bool v)
{
    if(v)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
double get_fps()
{
    return fps;
}
int get_n_cases_x()
{
    return n_cases_x;
}
int get_n_cases_y()
{
    return n_cases_y;
}
void changer_fps(double nfps)
{
    fps=nfps;
}
void changer_n_cases_x(int nn_cases_x)
{
    n_cases_x=nn_cases_x;
}
void changer_n_cases_y(int nn_cases_y)
{
    n_cases_y=nn_cases_y;
}
