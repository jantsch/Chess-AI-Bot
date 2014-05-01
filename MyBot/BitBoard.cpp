
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "BitBoard.h"

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
    setTabuleiro(msgServ);


}
/* FOrmato da String que chega
{"draw": false, "bad_move": false, "board": "r.b..b.rpppppppp.....
P............PPP.PPPPR.B..B.R", "black_infractions": 0, "50moves":
r": 0, "enpassant": null, "who_moves": -1, "white_infractions": 0}
*/
//Testado OK!
void BitBoard::setTabuleiro(string msgServ)
{
     int location = msgServ.find("board");
     string board = msgServ.substr(location+9,64);
     int correct;

    for(int i=0;i<64;i++)
    {   if(i>=0 && i<=7)
            correct = 56;
        if(i>=8 && i<=15)
            correct = 48;
        if(i>=16 && i<=23)
            correct = 40;
        if(i>=24 && i<=31)
            correct = 32;
        if(i>=32 && i<=39)
            correct = 24;
        if(i>=40 && i<=47)
            correct = 16;
        if(i>=48 && i<=55)
            correct = 8;
         if(i>=56 && i<=63)
            correct = 0;

        if(board[i]=='r')
          {
                    this->tabuleiro.BlackRooks = tabuleiro.Set(this->tabuleiro.BlackRooks,correct+(i%8));
                    this->tabuleiro.BlackPieces = tabuleiro.Set(this->tabuleiro.BlackPieces,correct+(i%8));
                    this->tabuleiro.allPieces = tabuleiro.Set(this->tabuleiro.allPieces,correct+(i%8));


          }
        if(board[i]=='b')
          {
                    this->tabuleiro.BlackBishops = tabuleiro.Set(this->tabuleiro.BlackBishops,correct+(i%8));
                    this->tabuleiro.BlackPieces = tabuleiro.Set(this->tabuleiro.BlackPieces,correct+(i%8));
                    this->tabuleiro.allPieces = tabuleiro.Set(this->tabuleiro.allPieces,correct+(i%8));

          }
        if(board[i]=='p')
          {
                    this->tabuleiro.BlackPawns = tabuleiro.Set(this->tabuleiro.BlackPawns,correct+(i%8));
                    this->tabuleiro.BlackPieces = tabuleiro.Set(this->tabuleiro.BlackPieces,correct+(i%8));
                    this->tabuleiro.allPieces = tabuleiro.Set(this->tabuleiro.allPieces,correct+(i%8));

          }
        if(board[i]=='R')
          {
                    this->tabuleiro.WhiteRooks = tabuleiro.Set(this->tabuleiro.WhiteRooks,correct+(i%8));
                    this->tabuleiro.WhitePieces = tabuleiro.Set(this->tabuleiro.WhitePieces,correct+(i%8));
                    this->tabuleiro.allPieces = tabuleiro.Set(this->tabuleiro.allPieces,correct+(i%8));

          }
         if(board[i]=='B')
           {
                    this->tabuleiro.WhiteBishops = tabuleiro.Set(this->tabuleiro.WhiteBishops,correct+(i%8));
                    this->tabuleiro.WhitePieces = tabuleiro.Set(this->tabuleiro.WhitePieces,correct+(i%8));
                    this->tabuleiro.allPieces = tabuleiro.Set(this->tabuleiro.allPieces,correct+(i%8));

           }
          if(board[i]=='P')
            {
                    this->tabuleiro.WhitePawns = tabuleiro.Set(this->tabuleiro.WhitePawns,correct+(i%8));
                    this->tabuleiro.WhitePieces = tabuleiro.Set(this->tabuleiro.WhitePieces,correct+(i%8));
                    this->tabuleiro.allPieces = tabuleiro.Set(this->tabuleiro.allPieces,correct+(i%8));

            }
           if(board[i]=='.')
            {
                    this->tabuleiro.emptySpace = tabuleiro.Set(this->tabuleiro.emptySpace,correct+(i%8));
            }

        }



}

void BitBoard::AvaliaFolhas(int level)
{

    Tabuleiro *pt= &this->tabuleiro;
    int contadorNivel =0;
    while(contadorNivel != level)
    {
        pt = pt->filhos;
        contadorNivel++;
    }

    while(pt!=NULL)
    {
        pt->AvaliaTabuleiroBranco();
        pt = pt->irmao;
    }
}
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
    int num = locationVirgula -  (location+11);
    string who_moves  = msgServ.substr (location+11,num);
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


