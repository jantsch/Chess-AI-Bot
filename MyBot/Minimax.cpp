#include "BitBoard.h"
#include "Minimax.h"

Minimax::Minimax()
{
    //ctor
}

Minimax::~Minimax()
{
    //dtor
}

COORD Minimax::exe(BitBoard bitboard)
{

    COORD x;
    bitboard.tabuleiro.GeraListaBitboardsPossiveisPeao();
    /*
    char binario[64];
    itoa(bitboard.tabuleiro.filhos->emptySpace,binario,2);
    cout << binario <<endl;
    */
    return x;
}
