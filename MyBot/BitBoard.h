
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include "Tabuleiro.h"

using namespace std;

class BitBoard
{
    public:
    bool draw;
    COORD enpassant;
    int who_moves; //  -1 pretas ou 1 brancas
    bool bad_move;
    int white_infractions;
    int black_infractions;
    int winner; // 1 ,0 ou -1
    bool fiftyMoves;
    Tabuleiro tabuleiro;

    //Definir tipo da Matriz ou bitboard


    public:
        BitBoard();
        virtual ~BitBoard();
        void ConverteFormatoServBit(string msgServ);
        Tabuleiro* AvaliaArvoreBranca(Tabuleiro tabuleiro);
        Tabuleiro* AvaliaArvorePreta(Tabuleiro tabuleiro);


    private:
        void setDraw(string msgServ); //ok
        void setWho_moves(string msgServ); //ok
        void setBad_move(string msgServ); //ok
        void setWhite_infractions(string msgServ); //ok
        void setBlack_infractions(string msgServ); // ok
        void setWinner(string msgServ); // 1 ,0 ou -1 //ok
        void setFiftyMoves(string msgServ); //ok
        void setTabuleiro(string msgServ);

};



