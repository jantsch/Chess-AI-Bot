

#include <iostream>
#include <cstdlib>
#include "Tabuleiro.h"
using std::cout;
using std::endl;
Tabuleiro::Tabuleiro()
{
    //ctor
    this->BlackBishops = 0;
    this->BlackPawns = 0;
    this->BlackPieces = 0;
    this->BlackRooks = 0;
    this->WhiteBishops = 0;
    this->WhitePawns = 0;
    this->WhitePieces = 0; // número em decimal correspondente as pecas brancas
    this->WhiteRooks = 0;
    this->allPieces = 0;
    this->emptySpace = 0;
    this->valAvalia = 0;

    this->filhos = NULL;
    this->irmao = NULL;
    this->ptAux = this->filhos; // ERRADO REVER!

}

Tabuleiro::~Tabuleiro()
{
    //dtor
}


uint64_t Tabuleiro::Set (uint64_t bitboard, int numSquare)
{
      return  bitboard | SetMasksField(numSquare);
}


uint64_t Tabuleiro::Clear (uint64_t bitboard, int numSquare)
{
      return bitboard & ClearMasksField(numSquare);
}



uint64_t Tabuleiro::SetMasksField(int numSquare)
{
    uint64_t mask = 0;
    mask = 1ULL << numSquare;
    return mask;

}




uint64_t Tabuleiro::ClearMasksField(int numSquare)
{
    uint64_t mask = ~(1ULL << numSquare);
    return mask;
}



bool Tabuleiro::Is_set(uint64_t bitboard,int numSquare)
{
    uint64_t x = bitboard >> numSquare;
    uint64_t  mask = (1 << 1) - 1;
    uint64_t y = x & mask;

    if(y==1)
        return true;
    else
        return false;
}


uint64_t Tabuleiro::GetPawnMovMaskCima(int  square)
{

    uint64_t maskMovCima=0;
    maskMovCima = Set(maskMovCima,square +8);
    maskMovCima = Set(maskMovCima,square +16); // movimento pra cima --> Muito estranho

    return maskMovCima;
}

uint64_t Tabuleiro::GetPawnMovMaskCome(int square)
{
     uint64_t maskMovCome=0;
     if((square +9) /8 == (square /8)+1)   // confere movimenos pros lados.
      maskMovCome = Set(maskMovCome,square +9);
     if((square +7) /8 == (square /8)+1)
      maskMovCome = Set(maskMovCome,square +7);

      return maskMovCome;
}

uint64_t Tabuleiro::GeraMovValidoPeaoCima(uint64_t maskMovCima,int square)
{
    uint64_t maskMovPossiveisCima=0;

    if(Is_set(this->emptySpace,(square+8))==true)
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

void Tabuleiro::GeraListaBitboardsPossiveisPeao()
{
    //k = bit do peão ligado e i bit da mascara ligado
    uint64_t maskMovCome = 0;
    uint64_t maskMovCima = 0;
    uint64_t maskMovPossiveisCome = 0;
    uint64_t maskMovPossiveisCima = 0;

    for(int k=0;k<64;k++)
    {
        if(Is_set(this->WhitePawns,k))
        {
            maskMovCome = GetPawnMovMaskCome(k);
            maskMovCima = GetPawnMovMaskCima(k);
            maskMovPossiveisCome = GeraMovValidoPeaoCome(maskMovCome);
            maskMovPossiveisCima = GeraMovValidoPeaoCima(maskMovCima,k);


            bool IsFirst = true;
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
                           this->ptAux->WhitePawns = Clear(this->ptAux->WhitePawns,k);
                           this->ptAux->WhiteRooks =  this->WhiteRooks;
                           this->ptAux->WhiteBishops = this->WhiteBishops;
                           this->ptAux->WhitePieces = this->WhitePieces;
                           this->ptAux->WhitePieces = Set(this->ptAux->WhitePieces,i);
                           this->ptAux->WhitePieces = Clear(this->ptAux->WhitePieces,k);
                           this->ptAux->emptySpace  = this->emptySpace;
                           this->ptAux->emptySpace = Set(this->ptAux->emptySpace,k);
                           this->ptAux->emptySpace = Clear(this->ptAux->emptySpace,i);
                            if(IsFirst==true)
                            {
                                this->filhos = this->ptAux;
                                IsFirst=false;
                            }
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
                           this->ptAux->WhitePawns = Clear(this->ptAux->WhitePawns,k);
                           this->ptAux->WhiteRooks =  this->WhiteRooks;
                           this->ptAux->WhiteBishops = this->WhiteBishops;
                           this->ptAux->WhitePieces = this->WhitePieces;
                           this->ptAux->WhitePieces = Set(this->ptAux->WhitePieces,i);
                           this->ptAux->WhitePieces = Clear(this->ptAux->WhitePieces,k);
                           this->ptAux->emptySpace  = this->emptySpace;
                           this->ptAux->emptySpace = Set(this->ptAux->emptySpace,k);
                           this->ptAux->emptySpace = Clear(this->ptAux->emptySpace,i);
                           VeQualPecaFoiComida(i); // ver qual peça está comento para tirar da bitboard black
                           if(IsFirst==true)
                            {
                                this->filhos = this->ptAux;
                                IsFirst=false;
                            }
                           this->ptAux = this->ptAux->irmao;
                        }



            }

}

}
}
void Tabuleiro::VeQualPecaFoiComida(int i)
{
    if(Is_set(this->BlackPawns,i))
    {
        this->ptAux->BlackPawns = Clear(this->ptAux->BlackPawns,i);
    }
    if(Is_set(this->BlackBishops,i))
    {
        this->ptAux->BlackBishops = Clear(this->ptAux->BlackBishops,i);
    }
    if(Is_set(this->BlackRooks,i))
    {
          this->ptAux->BlackRooks = Clear(this->ptAux->BlackRooks,i);
    }
}
