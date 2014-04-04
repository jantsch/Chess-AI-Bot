
#include <iostream>
#include <winsock2.h>


class Cliente
{
    sockaddr_in serv_end;
    // OBS: nao precisa ser definido o endereço do cliente
    sockaddr_in meu_end;
    SOCKET sock;
public:
    Cliente();
    ~Cliente();
    /*-----------------------------------------------*/
    // A função que não recebe parâmetros pergunta ao usuario a porta e o ip do server
    void conectar(char *ip, unsigned short porta);
    void conectar( void );
    /*----------------------------------------------*/
    // efetua o bind do socket a uma porta
    // É DESNECESSÁRIO FAZER ISSO NO CLIENTE
    void bindSock();
    // envia uma string de texto
    void enviaString();
    // envia um buffer contendo os dados referentes a um aluno;
    void cadastraAluno(char *nome, int RA, int ID);
    void Cliente::cadastraProfessor(char *nome, float sal, float bp);
    // rotina principal de envio de dados
    void rotinaPrincipal();
};
