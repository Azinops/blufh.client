#ifndef CLIENT_SOCKETS_H_INCLUDED
#define CLIENT_SOCKETS_H_INCLUDED
#include <winsock2.h> // pour les fonctions socket
#include <cstdio> // Pour les Sprintf
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
#include "sockets.h"

WSADATA initialisation_win32; // Variable permettant de récupérer la structure d'information sur l'initialisation
int erreur; // Variable permettant de récupérer la valeur de retour des fonctions utilisées
int tempo; // Variable temporaire de type int
int nombre_de_caractere; // Indique le nombre de caractères qui a été reçu ou envoyé
char buffer[NBRE_CHARACTERE_MAX]; // Tampon contennant les données reçues ou envoyées
SOCKET id_de_la_socket; // Identifiant de la socket
SOCKET id_de_la_socket2; // Identifiant de la socket
SOCKADDR_IN information_sur_la_destination; // Déclaration de la structure des informations lié au serveur
SOCKET id_de_la_nouvelle_socket; // Identifiant de la nouvelle socket
SOCKADDR_IN information_sur_la_source; // Déclaration de la structure des informations lié à l'écoute

#endif // CLIENT_SOCKETS_H_INCLUDED
