#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include <sstream>

#define VIOLET al_map_rgb(130,80,200)
#define VERTC al_map_rgb(165,230,20)
#define NOIR al_map_rgb(0,0,0)
#define CYAN al_map_rgb(0,255,255)
#define ROUGE al_map_rgb(255,0,0)

#define XBASE 1920
#define YBASE 1080
#define XBASED 1920.00
#define YBASED 1080.00

#define LIMITE_IMAGES 999

#define TAILLE_ECRITUR_SCORE 42

#define FPS 50.00

#define OBTENIRMOUSEETKEY al_get_mouse_state(&mouse);\
                         al_get_keyboard_state(&key);
#define OBTENIR_SOURIS al_get_mouse_state(&mouse);
#define OBTENIR_CLAVIER al_get_keyboard_state(&key);

#define EVENT ALLEGRO_EVENT event;\
        al_wait_for_event(queue,&event);

#define VOIRSISABUG(variable) std::cout << variable << " ";
#define VOIRSISABUG_DOUBLE(variable) std::cout << std::fixed << variable << " ";
#define INITIALISER_FONT(nom,style,taille) ALLEGRO_FONT*nom;\
    sprintf(chemin,"./tff/%s.ttf",style);\
    nom = al_load_font(chemin,taille,0);\
    if(!nom)\
        erreur("al_load_font()");
#define INITIALISER_BIBLIOTHEQUE ALLEGRO_FONT*arial72;\
    ALLEGRO_FONT*arial36;\
    ALLEGRO_FONT*arial22;\
    ALLEGRO_FONT*arial66;\
    ALLEGRO_EVENT_QUEUE*queue;\
    ALLEGRO_TIMER*timer;\
    if(!al_init_image_addon())\
        erreur("al_init_image_addon()");\
    if(!al_install_keyboard())\
        erreur("al_install_keyboard()");\
    if(!al_install_mouse())\
        erreur("al_install_mouse()");\
    al_init_font_addon();\
    if(!al_init_ttf_addon())\
        erreur("al_init_ttf_addon()");\
    arial36 = al_load_font("./tff/arial.ttf",36,0);\
    if(!arial36)\
        erreur("al_load_font()");\
    arial22 = al_load_font("./tff/arial.ttf",22,0);\
    if(!arial22)\
        erreur("al_load_font()");\
    arial66 = al_load_font("./tff/arial.ttf",66,0);\
    if(!arial66)\
        erreur("al_load_font()");\
    if(!al_init_primitives_addon())\
        erreur("al_primitives_addon()");\
    queue=al_create_event_queue();\
    if(!queue)\
        erreur("al_create_event_queue()");\
    timer=al_create_timer((1.0/FPS));\
    if(!timer)\
        erreur("al_create_timer()");\
    ALLEGRO_KEYBOARD_STATE key;\
    ALLEGRO_MOUSE_STATE mouse;\
    ALLEGRO_COLOR vertc =al_map_rgba(165,230,20,255);\
    ALLEGRO_COLOR rouge =al_map_rgba(255,0,0,255);\
    ALLEGRO_COLOR rougefonce =al_map_rgba(80,0,0,255);\
    ALLEGRO_COLOR noir =al_map_rgba(0,0,0,255);\
    ALLEGRO_COLOR bleuClair =al_map_rgba(51,204,255,255);\
    ALLEGRO_COLOR bleu =al_map_rgba(0,0,255,255);\
    ALLEGRO_COLOR bleu_fonce =al_map_rgba(0,0,80,255);\
    ALLEGRO_COLOR vert =al_map_rgba(51,153,0,255);\
    ALLEGRO_COLOR blancbi =al_map_rgba(230,230,230,255);\
    ALLEGRO_COLOR blanc =al_map_rgba(255,255,255,255);\
    ALLEGRO_COLOR violet =al_map_rgba(130,80,200,255);\
    ALLEGRO_COLOR jaune =al_map_rgba(255,255,0,255);\
    ALLEGRO_COLOR jaune_fonce =al_map_rgba(100,100,100,255);\
    ALLEGRO_COLOR jaunetrans =al_map_rgba(255,255,0,0);\
    ALLEGRO_COLOR gris =al_map_rgba(150,150,150,255);\
    ALLEGRO_COLOR orange =al_map_rgba(255,102,0,150);\
    ALLEGRO_COLOR beige =al_map_rgba(234,193,138,255);\
    ALLEGRO_COLOR beigef =al_map_rgba(200,160,100,255);\
    al_register_event_source(queue,al_get_keyboard_event_source());\
    al_register_event_source(queue,al_get_timer_event_source(timer));\
    al_register_event_source(queue,al_get_mouse_event_source());\
    al_clear_to_color(noir);\
    al_flip_display();\
    al_get_mouse_state(&mouse);\
    al_get_keyboard_state(&key);\

#define INITIALISER_IMAGE(nom,passage) ALLEGRO_BITMAP*nom;\
                                    nom=al_load_bitmap(passage); \
                                    if (!nom)\
                                    {\
                                        std::cout << passage << ":   ERREUR:BITMAP PAS CHARGE" << endl;\
                                        erreur("al_load_bitmap()");\
                                    }\
                                    else\
                                    {\
                                        std::cout << passage <":   loaded"<< endl;\
                                    }
#define INITIALISER_IMAGE_EN_MASSE(nom,nombreImages,passage)   ALLEGRO_BITMAP*nom[nombreImages];\
                                                            for(i=1; i<=nombreImages; i++)\
                                                            {\
                                                                sprintf(chemin,"%s%d.png",passage,i);\
                                                                std::cout<<"-";\
                                                                nom[i]=al_load_bitmap(chemin);\
                                                                if (!nom[i])\
                                                                {\
                                                                    std::cout<<":   ERREUR:BITMAP PAS CHARGE"<<endl;\
                                                                    erreur("al_load_bitmap()");\
                                                                }\
                                                            }
#define ESCAPE if(al_key_down(&key,ALLEGRO_KEY_F4)){\
                fin=1;fermer_socket();fermer_socket_receptrice();}
#define TOUCHE_QUITTER ALLEGRO_KEY_F4

int roundi(double variable);
void erreur(const char*txt);
int retablisseur(int valeur,int valeur_max,int valeur_min);
double retablisseurD(double valeur,double valeur_max,double valeur_min);
double distance(double x1,double y1, double x2, double y2);
int random(int a, int b);
int modulo(double x,int maxi);
int borne_inf(int a,int borne);
double arrondi(double nombre,int nbre_chiffres);
int n_ieme_chiffre(double nombre,int n);
int n_ieme_chiffrem(double nombre,int n);
int n_ieme_chiffremi(int nombre,int n);
double absd(double a);
int bool_to_int(bool v);
#endif // FONCTIONS_H_INCLUDED

