
#include "Tabuleiro.h"
#include <iostream>
#include <cstdlib>
Tabuleiro::Tabuleiro()
{
    //ctor
    this->BlackBishops = 2594073385365405696;
    this->BlackPawns = 71776119061217280;
    this->BlackPieces = -6485464938390224896;
    this->BlackRooks = -9151314442816847872;
    this->WhiteBishops = 36;
    this->WhitePawns = 65280;
    this->WhitePieces = 65535; // número em decimal correspondente as pecas brancas
    this->WhiteRooks = 129;
    this->allPieces = -6485464938390159451;
    this->emptySpace = 0;

    this->filhos = NULL;
    this->irmao = NULL;
    this->ptAux = this->filhos;

}

Tabuleiro::~Tabuleiro()
{
    //dtor
}

uint64_t Tabuleiro::Set (uint64_t bitboard, Squares square)
{
      return  bitboard | SetMasksField(square);
}

uint64_t Tabuleiro::Set (uint64_t bitboard, int numSquare)
{
      return  bitboard | SetMasksField(numSquare);
}

uint64_t Tabuleiro::Clear (uint64_t bitboard, Squares square)
{
      return bitboard & ClearMasksField(square);
}
uint64_t Tabuleiro::Clear (uint64_t bitboard, int numSquare)
{
      return bitboard & ClearMasksField(numSquare);
}

uint64_t Tabuleiro::SetMasksField(Squares square)
{
    uint64_t mask = 0;
    mask = 1 << (int)square;
    return mask;

}

uint64_t Tabuleiro::SetMasksField(int numSquare)
{
    uint64_t mask = 0;
    mask = 1 << numSquare;
    return mask;

}

uint64_t Tabuleiro::ClearMasksField(Squares square)
{
    uint64_t mask = ~(1 << (int)square);
    return mask;
}


uint64_t Tabuleiro::ClearMasksField(int numSquare)
{
    uint64_t mask = ~(1 << numSquare);
    return mask;
}

bool Tabuleiro::Is_set(uint64_t bitboard,Squares square)
{
    int x = bitboard >> (int)square;
    int  mask = (1 << 1) - 1;
    int y = x & mask;

    if(y==1)
        return true;
    else
        return false;
}

bool Tabuleiro::Is_set(uint64_t bitboard,int numSquare)
{
    int x = bitboard >> numSquare;
    int  mask = (1 << 1) - 1;
    int y = x & mask;

    if(y==1)
        return true;
    else
        return false;
}


uint64_t Tabuleiro::GetPawnMovMaskCima(Squares square)
{
    uint64_t maskMovCima=0;
    maskMovCima = Set(maskMovCima,(int)square +8);
    maskMovCima = Set(maskMovCima,(int)square +16); // movimento pra cima


    return maskMovCima;
}

uint64_t Tabuleiro::GetPawnMovMaskCome(Squares square)
{
    uint64_t maskMovCome=0;
     if(((int)square +9) /8 == ((int)square /8)+1)   // confere movimenos pros lados.
      maskMovCome = Set(maskMovCome,(int)square +9);
     if(((int)square +7) /8 == ((int)square /8)+1)
      maskMovCome = Set(maskMovCome,(int)square +7);

      return maskMovCome;
}

uint64_t Tabuleiro::GeraMovValidoPeaoCima(uint64_t maskMovCima,Squares square)
{
    uint64_t maskMovPossiveisCima=0;

    if(Is_set(this->emptySpace,((int)square+8))==true)
    {
        maskMovPossiveisCima = maskMovCima & this->emptySpace;
        return maskMovPossiveisCima;
    }
    else
        return maskMovPossiveisCima;
}

uint64_t Tabuleiro::GeraMovValidoPeaoCome(uint64_t maskMovCome)
{
    uint64_t maskMovPossiveisCome = maskMovCome & this->BlackPieces;
    return maskMovPossiveisCome;
}

uint64_t Tabuleiro::GeraListaBitboardsPossiveis(uint64_t maskMovPossiveisCome,uint64_t maskMovPossiveisCima,Squares square)
{
    //Lista encadeada com todas bitboards possíveis de peão; Ver n tree

   for(int i=0;i<64;i++)
   {
          if(Is_set(maskMovPossiveisCima,i)==true)
           {
               this->ptAux = (Tabuleiro*) malloc(sizeof(Tabuleiro)); // cria um nodo;
               this->ptAux->BlackBishops = this->BlackBishops;
               this->ptAux->BlackPawns = this->BlackPawns;
               this->ptAux->BlackPieces = this->BlackPieces;
               this->ptAux->BlackRooks = this->BlackRooks;
               this->ptAux->WhitePawns = this->WhitePawns;
               this->ptAux->WhitePawns = Set(this->ptAux->WhitePawns,i);
               this->ptAux->WhitePawns = Clear(this->ptAux->WhitePawns,(int)square);
               this->ptAux->WhiteRooks =  this->WhiteRooks;
               this->ptAux->WhiteBishops = this->WhiteBishops;
               this->ptAux->WhitePieces = this->WhitePieces;
               this->ptAux->WhitePieces = Set(this->ptAux->WhitePieces,i);
               this->ptAux->WhitePieces = Clear(this->ptAux->WhitePieces,(int)square);
               this->ptAux->emptySpace  = this->emptySpace;
               this->ptAux->emptySpace = Set(this->ptAux->emptySpace,(int)square);
               this->ptAux->emptySpace = Clear(this->ptAux->emptySpace,i);

               this->ptAux = this->ptAux->irmao;
            }

            if(Is_set(maskMovPossiveisCome,i)==true)
            {

               this->ptAux = (Tabuleiro*) malloc(sizeof(Tabuleiro)); // cria um nodo;
               this->ptAux->BlackBishops = this->BlackBishops;
               this->ptAux->BlackPawns = this->BlackPawns;
               this->ptAux->BlackPieces = this->BlackPieces;
               this->ptAux->BlackRooks = this->BlackRooks;
               this->ptAux->WhitePawns = this->WhitePawns;
               this->ptAux->WhitePawns = Set(this->ptAux->WhitePawns,i);
               this->ptAux->WhitePawns = Clear(this->ptAux->WhitePawns,(int)square);
               this->ptAux->WhiteRooks =  this->WhiteRooks;
               this->ptAux->WhiteBishops = this->WhiteBishops;
               this->ptAux->WhitePieces = this->WhitePieces;
               this->ptAux->WhitePieces = Set(this->ptAux->WhitePieces,i);
               this->ptAux->WhitePieces = Clear(this->ptAux->WhitePieces,(int)square);
               this->ptAux->emptySpace  = this->emptySpace;
               this->ptAux->emptySpace = Set(this->ptAux->emptySpace,(int)square);
               this->ptAux->emptySpace = Clear(this->ptAux->emptySpace,i);
               VeQualPecaFoiComida(i); // ver qual peça está comento para tirar da bitboard black
            }



}
}
void Tabuleiro::VeQualPecaFoiComida(int i)
{
    if(Is_set(this->BlackPawns,i))
    {
        this->filhos->BlackPawns = Clear(this->filhos->BlackPawns,i);
    }
    if(Is_set(this->BlackBishops,i))
    {
        this->filhos->BlackBishops = Clear(this->filhos->BlackBishops,i);
    }
    if(Is_set(this->BlackRooks,i))
    {
          this->filhos->BlackRooks = Clear(this->filhos->BlackRooks,i);
    }
}
