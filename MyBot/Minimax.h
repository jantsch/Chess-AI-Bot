#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <stdio.h>


class Minimax
{
    public:
        COORD From;
        COORD To;

    public:
        Minimax();
        virtual ~Minimax();
        void exe(BitBoard bitboard);
    protected:
    private:
        Tabuleiro* InverteTabuleiro(Tabuleiro *tabuleiro);
        void ExpandeMeuSegundoNivel(Tabuleiro tabuleiro);
        void ExpandeSegundoNivelInimigo(Tabuleiro tabuleiro);
        void DesinverteTabuleiro(Tabuleiro *tabuleiro,Tabuleiro *EncadearNele);
        uint64_t InverteUint(uint64_t inv);
        void IdentificaCOORD(Tabuleiro *tabJogada,Tabuleiro tabuleiro);


};
