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
#include <windows.h>
#include <math.h>
#include "fonctions.h"
#include "affichage.h"
#include "variables_main.h"
#include "souris_clavier.h"
#include "Classes.h"
#include "f_map.h"
#include "f_main.h"
#include "sockets.h"
#define IP "192.168.1.12"
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

int main()
{
    plein_ecran();
    INITIALISER_BIBLIOTHEQUE
    srand(time(NULL));
    Souris_clavier moukey;

    cout<<"CHARGEMENT"<<endl;
    INITIALISER_IMAGE_EN_MASSE(iLance_bombe,NI_LANCES_BOMBES,"./images/lances_bombes/")
    INITIALISER_IMAGE_EN_MASSE(iBlocs,NI_BLOCS,"./images/blocs/")
    INITIALISER_IMAGE_EN_MASSE(iExplo1,NI_EXPLO1,"./images/explosion_bombe_jetable/")
    INITIALISER_IMAGE_EN_MASSE(iExplo3,NI_EXPLO3,"./images/explosion_centre_bombe_croix/")
    INITIALISER_IMAGE_EN_MASSE(iBombes,NI_BOMBES,"./images/bombes/")
    INITIALISER_IMAGE_EN_MASSE(iExplo2,NI_EXPLO2,"./images/explosion_croix/")
    INITIALISER_IMAGE_EN_MASSE(iExplo4,NI_EXPLO4,"./images/explosion_croix2/")
    cout<<endl<<"Fini"<<endl;

    bombe bombe_de_jet(iBombes[1],iExplo1,0,iExplo4,TAILLE_EXPLO3I,TAILLE_EXPLO4I,NI_EXPLO1,NI_EXPLO4,VITESSE_ANIM_BOMBE,VITESSE_ANIM_BOMBE_CROIX2);
    bombe bombe_pieges(iBombes[1],iExplo3,1,iExplo2,TAILLE_EXPLO3I,TAILLE_EXPLO2I,NI_EXPLO3,NI_EXPLO2,VITESSE_ANIM_BOMBE2,VITESSE_ANIM_BOMBE_CROIX);

    init_map(iBlocs);

    lance_bombe joueurs[NBRE_JOUEURS];
    lance_bombe joueurs_i[NBRE_JOUEURS];
    joueurs[0]=lance_bombe(iLance_bombe[1],TAILLEC_LB_I,ALLEGRO_KEY_Z,ALLEGRO_KEY_S,ALLEGRO_KEY_Q,ALLEGRO_KEY_D,ALLEGRO_KEY_SPACE,0,bombe_de_jet,bombe_pieges,ALLEGRO_KEY_E,ALLEGRO_KEY_LSHIFT);
    joueurs[0].tp(TAILLE_BLOCX*1.50,TAILLE_BLOCY*1.50);
    joueurs[1]=lance_bombe(iLance_bombe[2],TAILLEC_LB_I,ALLEGRO_KEY_Z,ALLEGRO_KEY_S,ALLEGRO_KEY_Q,ALLEGRO_KEY_D,ALLEGRO_KEY_SPACE,1,bombe_de_jet,bombe_pieges,ALLEGRO_KEY_E,ALLEGRO_KEY_LSHIFT);
    joueurs[1].tp(XBASED-TAILLE_BLOCX*1.50,YBASED-TAILLE_BLOCY*1.50);
    copier_joueurs(joueurs_i,joueurs);

    INITIALISER_FONT(font_scores,"ALGER",int(TAILLE_BLOCY));

    char test[256]="Connexion_reussie";

    init_w(IP);
    init_soc_receptrice();

    envoyer_msg(test);
    decoder_map(recevoir_msg());
    cout<<test<<endl;

    al_start_timer(timer);
    while(!fin)
    {
        ESCAPE
        OBTENIRMOUSEETKEY
        al_clear_to_color(beigef);
        recevoir_packet(recevoir_msg());
        fin=decoder_packet(joueurs);
        if(!fin)
        {
            coder_touches(joueurs[1]);
            envoyer_msg(get_pack_touche());

            afficher_map();
            afficher_joueurs(joueurs);
            afficher_score(joueurs,font_scores);
            afficher_explosions(joueurs);

            al_flip_display();
        }
    }
    fermer_socket();
    fermer_socket_receptrice();
    return 0;
}
