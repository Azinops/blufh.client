#ifndef SOCKETS_H_INCLUDED
#define SOCKETS_H_INCLUDED

#define AFFICHER_MSG 0
#define PORT_EMETTEUR 29979
#define PORT_RECEPTEUR 33333
#define TAILLE_SOCKET 32000

void init_w(char adr_ip[]);
void init_soc_receptrice();
void fermer_socket();
void envoyer_msg(char msg[]);
char* recevoir_msg();
void fermer_socket_receptrice();
#endif // SOCKETS_H_INCLUDED
