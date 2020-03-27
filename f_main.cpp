#include "f_main.h"
#include "Classes.h"
void Jouer(lance_bombe joueurs_s[NBRE_JOUEURS])
{
    int r=-1;
    int k;
    int nr;
    int i=-1;
    int j=-1;
    for(k=0;k<=NBRE_JOUEURS-1;k++)
    {
        nr=joueurs_s[k].jouer();
        if(nr!=-1)
        {
            r=nr;
            if(i==-1)
            {
                i=k;
            }
            else
            {
                j=k;
            }
            if(j!=-1)
            {
                joueurs_s[i].fixer_nkills(joueurs_s[i].get_kills()-1);
            }
        }
    }
    if(r!=-1)
    {
        joueurs_s[r].tuer();
    }
}
void afficher_explosions(lance_bombe joueurs_s[NBRE_JOUEURS])
{
    int k;
    for(k=0;k<=NBRE_JOUEURS-1;k++)
    {
        joueurs_s[k].afficher_explosions();
    }
}
void copier_joueurs(lance_bombe joueurs[NBRE_JOUEURS],lance_bombe joueurs_a_coller[NBRE_JOUEURS])
{
    int k;
    int score;
    for(k=0;k<=NBRE_JOUEURS-1;k++)
    {
        score=joueurs[k].get_kills();
        joueurs[k]=joueurs_a_coller[k];
        joueurs[k].fixer_nkills(score);
    }
}
void afficher_score(lance_bombe joueurs[NBRE_JOUEURS],ALLEGRO_FONT*font)
{
    char scores[NBRE_CHARACTERES_MAX];
    int k;
    sprintf(scores,"Score:  %d",joueurs[0].get_kills());
    for(k=1;k<=NBRE_JOUEURS-1;k++)
    {
        sprintf(scores,"%s  -  %d",scores,joueurs[k].get_kills());
    }
    al_draw_text(font,COULEUR_SCORE,XBASED/2.00,0.00,ALLEGRO_ALIGN_CENTER,scores);
}
void afficher_joueurs(lance_bombe joueurs[NBRE_JOUEURS-1])
{
    int k;
    for(k=0;k<=NBRE_JOUEURS-1;k++)
    {
        if(joueurs[k].get_vivant()==1)
        {
            joueurs[k].afficher();
        }
    }
}
