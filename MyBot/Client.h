
#include <iostream>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib,"libwsock32.a")

class Cliente
{
    sockaddr_in serv_end;
    sockaddr_in meu_end;
    SOCKET sock;
public:
    Cliente();
    ~Cliente();
    /*-----------------------------------------------*/
    //Inicia Conexão
    void conectar( void );
    /*----------------------------------------------*/
    // envia uma string de texto
    void enviaNome();
    // envia nova jogada
    void enviaMovimento(COORD From,COORD To);

    void rotinaPrincipal();
};
