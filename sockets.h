#ifndef SOCKETS_H_INCLUDED
#define SOCKETS_H_INCLUDED

#define AFFICHER_MSG 0
#define PORT 80
#define TAILLE_MSG_MAX 32000
#define NBRE_CHARACTERE_MAX 32000

void init_w();
void init_soc_receptrice();
void fermer_socket_emettrice();
void envoyer_msg_client_to_serveur(char msg[]);
char* recevoir_msg_serveur();
void fermer_socket_receptrice();
void init_socket_emettrice(char adr_ip[]);
void renvoyer_msg(char nmsg[TAILLE_MSG_MAX]);
char* recevoir_msg_client();
void envoyer_msg_server_to_client(char nmsg[TAILLE_MSG_MAX]);
#endif // SOCKETS_H_INCLUDED
