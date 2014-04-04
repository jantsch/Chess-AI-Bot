#include "BitBoard.h"

#include <windows.h>
#include <iostream>
#include <stdio.h>

BitBoard::BitBoard()
{
    //ctor
}

BitBoard::~BitBoard()
{
    //dtor
}

void BitBoard::ConverteFormatoServBit(string msgServ)
{
    setWho_moves(msgServ);
    setBad_move(msgServ);
    setWhite_infractions(msgServ);
    setBlack_infractions(msgServ);
    setWinner(msgServ); // 1 ,0 ou -1
    setFiftyMoves(msgServ);

}
/* FOrmato da String que chega
{"draw": false, "bad_move": false, "board": "r.b..b.rpppppppp.....
P............PPP.PPPPR.B..B.R", "black_infractions": 0, "50moves":
r": 0, "enpassant": null, "who_moves": -1, "white_infractions": 0}
*/
void BitBoard::setWho_moves(string msgServ)
{

}

void BitBoard::setBad_move(string msgServ)
{

}
void BitBoard::setWhite_infractions(string msgServ)
{

}
void BitBoard::setBlack_infractions(string msgServ)
{

}
void BitBoard::setWinner(string msgServ)
{

}
void BitBoard::setFiftyMoves(string msgServ)
{

}


