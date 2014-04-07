#include "BitBoard.h"

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

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
    setDraw(msgServ);
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
void BitBoard::setDraw(string msgServ)
{
    int location = msgServ.find("draw");
    int locationVirgula = msgServ.find_first_of(",");
    int num = locationVirgula -  (location+7);
    string draw  = msgServ.substr (location+7,num);
    if(draw.compare("false")==0)
        this->draw = false;
    else
        this->draw = true;

    // OK
}

void BitBoard::setWho_moves(string msgServ)
{

    int location = msgServ.find("who_moves");
    int locationVirgula = msgServ.find(",",location);
    int num = locationVirgula -  (location+9);
    string who_moves  = msgServ.substr (location+9,num);
    int  who_movesINT = atoi(who_moves.c_str());
    this->who_moves = who_movesINT;
}

void BitBoard::setBad_move(string msgServ)
{

    int location = msgServ.find("bad_move");
    int locationVirgula = msgServ.find(",",location);
    int num = locationVirgula -  (location+11);
    string bad_move = msgServ.substr (location+11,num);
    if(bad_move.compare("false")==0)
        this->bad_move = false;
    else
        this->bad_move = true;

}
void BitBoard::setWhite_infractions(string msgServ)
{
    int location = msgServ.find("white_infractions");
    int locationVirgula = msgServ.find(",",location);
    int num = locationVirgula -  (location+17);
    string white_infractions  = msgServ.substr (location+17,num);
    int  white_infractionsINT = atoi(white_infractions.c_str());
    this->white_infractions = white_infractionsINT;


}
void BitBoard::setBlack_infractions(string msgServ)
{


    int location = msgServ.find("black_infractions");
    int locationVirgula = msgServ.find(",",location);
    int num = locationVirgula -  (location+17);
    string Black_infractions  = msgServ.substr (location+17,num);
    int  Black_infractionsINT = atoi(Black_infractions.c_str());
    this->black_infractions = Black_infractionsINT;

}
void BitBoard::setWinner(string msgServ)
{
    int location = msgServ.find("winner");
    int locationVirgula = msgServ.find(",",location);
    int num = locationVirgula -  (location+6);
    string winner  = msgServ.substr (location+6,num);
    int  winnerINT = atoi(winner.c_str());
    this->winner = winnerINT;

}
void BitBoard::setFiftyMoves(string msgServ)
{
    int location = msgServ.find("50moves");
    int locationVirgula = msgServ.find(",",location);
    int num = locationVirgula -  (location+7);
    string FiftyMoves = msgServ.substr (location+7,num);
    if(FiftyMoves.compare("false")==0)
        this->fiftyMoves = false;
    else
        this->fiftyMoves = true;
}


