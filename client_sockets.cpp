#include "client_sockets.h"
#include "sockets.h"
void init_w()
{
    erreur=WSAStartup(MAKEWORD(2,2),&initialisation_win32);
      if(AFFICHER_MSG)
      {
          if (erreur!=0)
                printf("\nDesole, je ne peux pas initialiser Winsock du a l'erreur : %d %d",erreur,WSAGetLastError());
          else
                printf("\nWSAStartup  : OK");
      }

}
void init_socket_emettrice(char adr_ip[])
{
    information_sur_la_destination.sin_family=AF_INET;
    information_sur_la_destination.sin_addr.s_addr=inet_addr(adr_ip); // Indiquez l'adresse IP de votre serveur
    information_sur_la_destination.sin_port=htons(PORT); // Port écouté du serveur (33333)
}
void init_soc_receptrice()
{
    id_de_la_socket2=socket(AF_INET,SOCK_STREAM,0);
      if(AFFICHER_MSG)
      {
          if (id_de_la_socket2==INVALID_SOCKET)
                printf("\nDesole, je ne peux pas creer la socket du a l'erreur : %d",WSAGetLastError());
          else
                printf("\nsocket      : OK");
      }

      // ********************************************************
      // Activation de l'option permettant d'activer l'algorithme de Nagle
      // ********************************************************
      tempo=1;
      erreur=setsockopt(id_de_la_socket2,IPPROTO_TCP,TCP_NODELAY,(char *)&tempo,sizeof(tempo));
      if(AFFICHER_MSG)
      {
          if (erreur!=0)
                printf("\nDesole, je ne peux pas configurer cette options du à l'erreur : %d %d",erreur,WSAGetLastError());
          else
                printf("\nsetsockopt  : OK");
      }

      // ********************************************************
      // Lie la socket à une ip et un port d'écoute
      // ********************************************************
      information_sur_la_source.sin_family=AF_INET;
      information_sur_la_source.sin_addr.s_addr=INADDR_ANY; // Ecoute sur toutes les IP locales
      information_sur_la_source.sin_port=htons(PORT); // Ecoute sur le port 33333
      erreur=bind(id_de_la_socket2,(struct sockaddr*)&information_sur_la_source,sizeof(information_sur_la_source));
      if(AFFICHER_MSG)
      {
          if (erreur!=0)
                printf("\nDesole, je ne peux pas ecouter ce port : %d %d",erreur,WSAGetLastError());
          else
                printf("\nbind        : OK");
      }
}
void envoyer_msg_client_to_serveur(char msg[])
{
    id_de_la_socket=socket(AF_INET,SOCK_STREAM,0);
    if(AFFICHER_MSG)
          {
              if (id_de_la_socket==INVALID_SOCKET)
                    printf("\nDesole, je ne peux pas creer la socket du a l'erreur : %d",WSAGetLastError());
              else
                    printf("\nsocket      : OK");
          }
          // ********************************************************
          // Activation de l'option permettant d'activer l'algorithme de Nagle
          // ********************************************************
          tempo=1;
          erreur=setsockopt(id_de_la_socket,IPPROTO_TCP,TCP_NODELAY,(char *)&tempo,sizeof(tempo));
          if(AFFICHER_MSG)
          {
              if (erreur!=0)
                    printf("\nDesole, je ne peux pas configurer cette options du à l'erreur : %d %d",erreur,WSAGetLastError());
              else
                    printf("\nsetsockopt  : OK");
          }
          erreur=connect(id_de_la_socket,(struct sockaddr*)&information_sur_la_destination,sizeof(information_sur_la_destination));
          if(AFFICHER_MSG)
          {
              if (erreur!=0)
                    printf("\nDesole, je n'ai pas pu ouvrir la session TCP : %d %d",erreur,WSAGetLastError());
              else
                    printf("\nsetsockopt  : OK");
          }
              nombre_de_caractere=send(id_de_la_socket,msg,strlen(msg),0);
              if(AFFICHER_MSG)
              {
                  if (nombre_de_caractere==SOCKET_ERROR)
                        printf("\nDesole, je n'ai pas envoyer les donnees du a l'erreur : %d",WSAGetLastError());
                  else
                        printf("\nsend        : OK");
              }
}
void envoyer_msg_server_to_client(char nmsg[TAILLE_MSG_MAX])
{
    nombre_de_caractere=send(id_de_la_nouvelle_socket,nmsg,strlen(nmsg),0);
              if(AFFICHER_MSG)
              {
                  if (nombre_de_caractere==SOCKET_ERROR)
                        printf("\nDesole, je n'ai pas envoyer les donnees du a l'erreur : %d",WSAGetLastError());
                  else
                        printf("\nsend        : OK");
              }
}
char* recevoir_msg_client()
{
    nombre_de_caractere=recv(id_de_la_socket,buffer,NBRE_CHARACTERE_MAX,0);
    if (nombre_de_caractere==SOCKET_ERROR)
    {
        if(AFFICHER_MSG)
        {
            printf("\nDesole, je n'ai pas recu de donnee");
        }
    }
    else
    {
        buffer[nombre_de_caractere]=0; // Permet de fermer le tableau après le contenu des data, car la fonction recv ne le fait pas
    }
    closesocket(id_de_la_socket);
    return buffer;
}
char* recevoir_msg_serveur()
{
    erreur=99; // Initiation de erreur pour être sur que l'on va rentrer dans la boucle
    while(erreur!=0) // Boucle tant qu'une demande de session (SYN) tcp n'a pas été reçu
        erreur=listen(id_de_la_socket2,NBRE_CHARACTERE_MAX);
    if(AFFICHER_MSG)
    {
        printf("\nlisten      : OK");
    }
    if(AFFICHER_MSG)
    {
        printf("\nAttente de la reception de demande d'ouverture de session tcp (SYN)");
    }
    tempo=sizeof(information_sur_la_source); // Passe par une variable afin d'utiliser un pointeur
    id_de_la_nouvelle_socket=accept(id_de_la_socket2,(struct sockaddr*)&information_sur_la_source,&tempo);
    if(AFFICHER_MSG)
    {
        if(id_de_la_nouvelle_socket==INVALID_SOCKET)
            printf("\nDesole, je ne peux pas accepter la session TCP du a l'erreur : %d",WSAGetLastError());
        else
            printf("\naccept      : OK");
    }
    nombre_de_caractere=recv(id_de_la_nouvelle_socket,buffer,1515,0);
    if (nombre_de_caractere==SOCKET_ERROR)
    {
        if(AFFICHER_MSG)
        {
            printf("\nDesole, je n'ai pas recu de donnee");
        }
    }
    else
    {
        buffer[nombre_de_caractere]=0; // Permet de fermer le tableau après le contenu des data, car la fonction recv ne le fait pas
    }
    return buffer;
}
void fermer_socket_emettrice()
{
    erreur=shutdown(id_de_la_socket,2); // 2 signifie socket d'émission et d'écoute
      if(AFFICHER_MSG)
      {
          if (erreur!=0)
                printf("\nDesole, je ne peux pas fermer la session TCP du a l'erreur : %d %d",erreur,WSAGetLastError());
          else
                printf("\nshutdown    : OK");
      }
      // ********************************************************
      // Fermeture de la socket correspondant à la commande socket()
      // ********************************************************
      erreur=closesocket(id_de_la_socket);
      if(AFFICHER_MSG)
      {
          if (erreur!=0)
                printf("\nDesole, je ne peux pas liberer la socket du a l'erreur : %d %d",erreur,WSAGetLastError());
          else
                printf("\nclosesocket : OK");
      }
      // ********************************************************
      // Quitte proprement le winsock ouvert avec la commande WSAStartup
      // ********************************************************
      erreur=WSACleanup(); // A appeler autant de fois qu'il a été ouvert.
      if(AFFICHER_MSG)
      {
          if (erreur!=0)
                printf("\nDesole, je ne peux pas liberer winsock du a l'erreur : %d %d",erreur,WSAGetLastError());
          else
                printf("\nWSACleanup  : OK");
      }
}
void fermer_socket_receptrice()
{
     // ********************************************************
      // Fermeture de la session TCP Correspondant à la commande connect()
      // ********************************************************
      erreur=shutdown(id_de_la_nouvelle_socket,2); // 2 signifie socket d'émission et d'écoute
      if(AFFICHER_MSG)
      {
          if (erreur!=0)
                printf("\nDesole, je ne peux pas fermer la session TCP du a l'erreur : %d %d",erreur,WSAGetLastError());
          else
                printf("\nshutdown    : OK");
      }

      // ********************************************************
      // Fermeture des deux socket correspondant à la commande socket() et accept()
      // ********************************************************
      erreur=closesocket(id_de_la_nouvelle_socket);
      if(AFFICHER_MSG)
      {
          if (erreur!=0)
                printf("\nDesole, je ne peux pas liberer la socket du a l'erreur : %d %d",erreur,WSAGetLastError());
          else
                printf("\nclosesocket : OK");
      }
      erreur=closesocket(id_de_la_socket2);
      if(AFFICHER_MSG)
      {
          if (erreur!=0)
                printf("\nDesole, je ne peux pas liberer la socket du a l'erreur : %d %d",erreur,WSAGetLastError());
           else
                printf("\nclosesocket : OK");
      }

      // ********************************************************
      // Quitte proprement le winsock ouvert avec la commande WSAStartup
      // ********************************************************
      erreur=WSACleanup(); // A appeler autant de fois qu'il a été ouvert.
      if(AFFICHER_MSG)
      {
          if (erreur!=0)
                printf("\nDesole, je ne peux pas liberer winsock du a l'erreur : %d %d",erreur,WSAGetLastError());
          else
                printf("\nWSACleanup  : OK");
      }
}
