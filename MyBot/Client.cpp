#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include "Client.h"
#include "BitBoard.h"
#include "Minimax.h"


using std::cout;
using std::endl;
using std::cin;





Cliente::Cliente()
{
    WSADATA tst;
    // teste para ver se o computador suporta e versão de winsocks utilizada
    // não deve dar problemas, já que todos os windows superiores ao 95 a suportam.
    if(WSAStartup(MAKEWORD(2,2), &tst))
    {
        cout << "O computador nao possui a versao 2.0 do Winsocks.";
        cout << "Nao sera possivel criar o servidor." << endl;
        return;
    }
    // cria o socket.
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock == SOCKET_ERROR)
    {
       cout << "Nao foi possivel criar o socket." << endl;
    }
    // define o endereço do cliente.
    // Existem funções que recuperam os ips reais de uma máquina
    // nas respectivas redes das quais participa
    /*
    meu_end.sin_family = AF_INET;
    meu_end.sin_port = htons(50001);
    meu_end.sin_addr.s_addr = inet_addr("127.0.0.1");
    */
}

Cliente::~Cliente()
{
    closesocket(sock);
}


void Cliente::conectar( void )
{
    char ip[10] = "127.0.0.1";
    cout << "Conectando ao Servidor..." << endl;
    fflush(stdin);
    serv_end.sin_family = AF_INET;
    serv_end.sin_addr.s_addr = inet_addr(ip);
    serv_end.sin_port = htons(50200);
    if(connect(sock, reinterpret_cast<SOCKADDR *>(&serv_end), sizeof(serv_end)) == -1)
    {
        cout << "Nao foi possivel conectar ao servidor, tente de novo." << endl;
        return;
    }
    cout << "Conexao estabelecida." << endl;


    rotinaPrincipal();
}

//rotina de envio, que contém o menu e a interface do usuario
void Cliente::rotinaPrincipal()
{
   char receivedData[5000];
   cout << "Enviando Nome... "<< endl;
   enviaNome();
   cout << "Nome Enviado "<< endl;
   cout << "Inicie o Jogo... "<< endl;




      while(1)
    {
        if(recv(sock, receivedData,5000 , 0) != -1)
        {
            //cout << receivedData << endl; // receiver data Contém string

            // Passa tudo pra bitboard e gera Tabuleiro.
             BitBoard bitboard;
             bitboard.ConverteFormatoServBit((string)receivedData);

             // Chama Algoritmo Algoritmo
             Minimax algMinimax;
             algMinimax.exe(bitboard);
            // Manda a jogada
             enviaMovimento(algMinimax.From,algMinimax.To);

        }

    }




}

void Cliente::enviaNome(void)
{
    char *msg = "{\"name\" : \"MagyverBot\"}";
    if(send(sock, msg , (int)strlen(msg), 0)== SOCKET_ERROR)
    {
           cout << "Problema ao Enviar Nome "<< endl;
    }


}
void Cliente::enviaMovimento(COORD From,COORD To)
{
     // movimento teste
     //Sleep(2000);
     char *str1 = "{\"from\": [";
     char *str2 = ",";
     char *str4 = "], \"to\": [";
     char *str5 = "]}";
     char resx1[2];
     char resy1[2];
     char resx2[2];
     char resy2[2];
    sprintf(resx1,"%d",From.X);
    sprintf(resy1,"%d",From.Y);
    sprintf(resx2,"%d",To.X);
    sprintf(resy2,"%d",To.Y);
    char *str3 = (char *)malloc(1+strlen(str1)+strlen(resx1)+strlen(str2)+strlen(resy1)+strlen(str4)
                                 +strlen(resx2)+strlen(str2)+strlen(resy2)+strlen(str5));
     strcpy(str3,str1);
     strcat(str3,resx1);
     strcat(str3,str2);
     strcat(str3,resy1);
     strcat(str3,str4);
     strcat(str3,resx2);
     strcat(str3,str2);
     strcat(str3,resy2);
     strcat(str3,str5);
     printf("%s",str3);
     //char *myMove = "{\"from\": [1,7], \"to\": [3,7]}";

     send(sock, str3 , (int)strlen(str3), 0);


                      /* FORMATO
                    {
                        "from": COORDENADA,
                        "to": COORDENADA
                    }*/


}

/* MENSAGEM DO SERVIDOR
{
    "board"             : STRING,
    "enpassant"         : COORDENADA,
    "who_moves"         : -1 OU 1,
    "bad_move"          : BOOLEAN,
    "white_infractions" : INTEGER,
    "black_infractions" : INTEGER,
    "winner"            : -1, 0 OU 1,
    "50moves"           : BOOLEAN,
    "draw"              : BOOLEAN
}
*/

