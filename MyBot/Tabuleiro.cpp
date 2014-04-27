

#include <iostream>
#include <cstdlib>
#include "Tabuleiro.h"
#define PEAOVALOR 4;
#define TORREVALOR 8;
#define BISPOVALOR 8;

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
    this->ptUltimo = NULL;
    this->posTo = 0;//váriave para saber para onde está indo;
    this->posFrom =0;
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
     if(square== 8 || square== 9 || square== 10 || square== 11 || square== 12 || square== 13 || square== 14 || square== 15) // restringe andar duas vezes depois da primeira jogada
    {
        maskMovCima = Set(maskMovCima,square +16); // movimento pra cima --> Muito estranho
    }
    return maskMovCima;
}

uint64_t Tabuleiro::GetRooksMovMask(int  square)
{

    uint64_t maskMov=0;
    bool canMoveUp = true;
    bool canMoveDown = true;
    int bufUp =square;
    while(canMoveUp==true && bufUp+8 <= 63 ) // Impede que fique em loop forever
    {
        if(Is_set(WhitePieces,bufUp+8)) // peça minha
        {
            canMoveUp =false;
        }
        if(Is_set(BlackPieces,bufUp+8)) // peça do Inimigo
        {
            maskMov = Set(maskMov,bufUp+8);
            canMoveUp = false;
        }
        if(Is_set(emptySpace,bufUp+8)) // peça do Inimigo
        {
            maskMov = Set(maskMov,bufUp+8);
        }
        bufUp = bufUp+ 8;

    }

    int bufDown = square;
    while(canMoveDown==true && bufDown-8 >= 0 ) // Impede que passe da linha mais debaixo
    {
        if(Is_set(WhitePieces,bufDown-8)) // peça minha
        {
            canMoveDown =false;
        }
        if(Is_set(BlackPieces,bufDown-8)) // peça do Inimigo
        {
            maskMov = Set(maskMov,bufDown-8);
            canMoveDown = false;
        }
        if(Is_set(emptySpace,bufDown-8)) // peça do Inimigo
        {
            maskMov = Set(maskMov,bufDown-8);
        }
        bufDown = bufDown- 8;
    }


    int bufRight = square-1;
    while(bufRight/8 == square/8 && bufRight >=0 ) // conferir se gera igual
    {
        if(Is_set(WhitePieces,bufRight)) // peça minha
        {
            break;
        }
        if(Is_set(BlackPieces,bufRight)) // peça do Inimigo
        {
             break;
        }
        if(Is_set(emptySpace,bufRight)) // peça do Inimigo
        {
             maskMov = Set(maskMov,bufRight);
        }
        bufRight = bufRight-1;
    }

    int bufLeft = square+1;
    while(bufLeft/8 == square/8)
    {

        if(Is_set(WhitePieces,bufLeft)) // peça minha
        {
            break;
        }
        if(Is_set(BlackPieces,bufLeft)) // peça do Inimigo
        {
            maskMov = Set(maskMov,bufLeft);
            break;
        }
        if(Is_set(emptySpace,bufLeft)) // peça do Inimigo
        {
            maskMov = Set(maskMov,bufLeft);
        }
        bufLeft = bufLeft+1;
    }

   return maskMov;
}
void Tabuleiro::GeraListaBitboardsPossiveisTorre()
{
    //k = bit da torre ligado e i bit da mascara ligado
    uint64_t maskMov=0;
    Tabuleiro *ptAux = NULL;

    for(int k=0;k<64;k++)
    {
        if(Is_set(this->WhiteRooks,k))
        {

            maskMov = GetRooksMovMask(k);

               for(int i=0;i<64;i++)
               {
                      if(Is_set(maskMov,i)==true)
                       {
                           ptAux = (Tabuleiro*) malloc(sizeof(Tabuleiro)); // cria um nodo;
                           ptAux->BlackBishops = this->BlackBishops;
                           ptAux->BlackPawns = this->BlackPawns;
                           ptAux->BlackPieces = this->BlackPieces;
                           ptAux->BlackRooks = this->BlackRooks;
                           ptAux->WhitePawns = this->WhitePawns;
                           ptAux->WhiteRooks =  this->WhiteRooks;
                           ptAux->WhiteRooks = Set(ptAux->WhiteRooks,i);
                           ptAux->WhiteRooks = Clear(ptAux->WhiteRooks,k);
                           ptAux->WhiteBishops = this->WhiteBishops;
                           ptAux->WhitePieces = this->WhitePieces;
                           ptAux->WhitePieces = Set(ptAux->WhitePieces,i);
                           ptAux->WhitePieces = Clear(ptAux->WhitePieces,k);
                           ptAux->emptySpace  = this->emptySpace;
                           ptAux->emptySpace = Set(ptAux->emptySpace,k);
                           ptAux->emptySpace = Clear(ptAux->emptySpace,i);
                           ptAux->allPieces = this->allPieces;
                           ptAux->allPieces = Set(ptAux->allPieces,i);
                           ptAux->allPieces = Clear(ptAux->allPieces,k);
                           VeQualPecaFoiComida(i,ptAux); // ver qual peça está comento para tirar da bitboard black
                           ptAux->posTo = i;
                           ptAux->posFrom =k;
                           ptAux->ptUltimo=NULL;

                        if(ptUltimo==NULL)
                        {
                            this->filhos = ptAux;
                            ptUltimo = ptAux;
                        }
                        else
                        {
                        ptUltimo ->irmao = ptAux;
                        ptUltimo  = ptUltimo->irmao;

                        }
                        }}}
}}

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
    Tabuleiro *ptAux = NULL;


    for(int k=0;k<64;k++)
    {
        if(Is_set(this->WhitePawns,k))
        {
            maskMovCome = GetPawnMovMaskCome(k);
            maskMovCima = GetPawnMovMaskCima(k);
            maskMovPossiveisCome = GeraMovValidoPeaoCome(maskMovCome);
            maskMovPossiveisCima = GeraMovValidoPeaoCima(maskMovCima,k);


               for(int i=0;i<64;i++)
               {
                      if(Is_set(maskMovPossiveisCima,i)==true)
                       {
                           ptAux = (Tabuleiro*) malloc(sizeof(Tabuleiro)); // cria um nodo;
                           ptAux->BlackBishops = this->BlackBishops;
                           ptAux->BlackPawns = this->BlackPawns;
                           ptAux->BlackPieces = this->BlackPieces;
                           ptAux->BlackRooks = this->BlackRooks;
                           ptAux->WhitePawns = this->WhitePawns;
                           ptAux->WhitePawns = Set(ptAux->WhitePawns,i);
                           ptAux->WhitePawns = Clear(ptAux->WhitePawns,k);
                           ptAux->WhiteRooks =  this->WhiteRooks;
                           ptAux->WhiteBishops = this->WhiteBishops;
                           ptAux->WhitePieces = this->WhitePieces;
                           ptAux->WhitePieces = Set(ptAux->WhitePieces,i);
                           ptAux->WhitePieces = Clear(ptAux->WhitePieces,k);
                           ptAux->emptySpace  = this->emptySpace;
                           ptAux->emptySpace = Set(ptAux->emptySpace,k);
                           ptAux->emptySpace = Clear(ptAux->emptySpace,i);
                           ptAux->allPieces = this->allPieces;
                           ptAux->allPieces = Set(ptAux->allPieces,i);
                           ptAux->allPieces = Clear(ptAux->allPieces,k);
                           ptAux->posTo = i;
                           ptAux->posFrom =k;
                           ptAux->ptUltimo=NULL;


                        if(ptUltimo==NULL)
                        {
                            this->filhos = ptAux;
                            ptUltimo = ptAux;
                            //IsFirst = false;
                        }
                        else
                        {
                        ptUltimo ->irmao = ptAux;
                        ptUltimo  = ptUltimo->irmao;

                        }
                        }

                        if(Is_set(maskMovPossiveisCome,i)==true)
                        {

                           ptAux = (Tabuleiro*) malloc(sizeof(Tabuleiro)); // cria um nodo;
                           ptAux->BlackBishops = this->BlackBishops;
                           ptAux->BlackPawns = this->BlackPawns;
                           ptAux->BlackPieces = this->BlackPieces;
                           ptAux->BlackRooks = this->BlackRooks;
                           ptAux->WhitePawns = this->WhitePawns;
                           ptAux->WhitePawns = Set(ptAux->WhitePawns,i);
                           ptAux->WhitePawns = Clear(ptAux->WhitePawns,k);
                           ptAux->WhiteRooks =  this->WhiteRooks;
                           ptAux->WhiteBishops = this->WhiteBishops;
                           ptAux->WhitePieces = this->WhitePieces;
                           ptAux->WhitePieces = Set(ptAux->WhitePieces,i);
                           ptAux->WhitePieces = Clear(ptAux->WhitePieces,k);
                           ptAux->emptySpace  = this->emptySpace;
                           ptAux->emptySpace = Set(ptAux->emptySpace,k);
                           ptAux->emptySpace = Clear(ptAux->emptySpace,i);
                           ptAux->allPieces = this->allPieces;
                           ptAux->allPieces = Set(ptAux->allPieces,i);
                           ptAux->allPieces = Clear(ptAux->allPieces,k);
                           ptAux->ptUltimo=NULL;
                           ptAux->posTo = i; //váriave para saber para onde está indo;
                           ptAux->posFrom =k;
                           VeQualPecaFoiComida(i,ptAux); // ver qual peça está comento para tirar da bitboard black

                               if(ptUltimo==NULL)
                                {
                                    this->filhos = ptAux;
                                    ptUltimo = ptAux;

                                }
                                else
                                {
                                ptUltimo ->irmao = ptAux;
                                ptUltimo  = ptUltimo->irmao;
                                }
                        }


            }
}
}
}

void Tabuleiro::VeQualPecaFoiComida(int i,Tabuleiro *ptAux)
{
    if(Is_set(this->BlackPawns,i))
    {
        ptAux->BlackPawns = Clear(ptAux->BlackPawns,i);
        ptAux->BlackPieces = Clear(ptAux->BlackPieces,i);

    }
    if(Is_set(this->BlackBishops,i))
    {
        ptAux->BlackBishops = Clear(ptAux->BlackBishops,i);
        ptAux->BlackPieces = Clear(ptAux->BlackPieces,i);

    }
    if(Is_set(this->BlackRooks,i))
    {
        ptAux->BlackRooks = Clear(ptAux->BlackRooks,i);
        ptAux->BlackPieces = Clear(ptAux->BlackPieces,i);

    }
}

void Tabuleiro::AvaliaTabuleiro()
{
    for(int i=0;i<64;i++)
       {
           if(Is_set(this->WhitePawns,i))
           {
               valAvalia = valAvalia + PEAOVALOR;
           }
           if(Is_set(this->WhiteRooks,i))
           {
              valAvalia = valAvalia + TORREVALOR;
           }
           if(Is_set(this->WhiteBishops,i))
           {
              valAvalia = valAvalia + BISPOVALOR;
           }
           if(Is_set(this->BlackBishops,i))
           {
              valAvalia = valAvalia - BISPOVALOR;
           }
           if(Is_set(this->BlackRooks,i))
           {
              valAvalia = valAvalia - TORREVALOR;
           }
           if(Is_set(this->BlackPawns,i))
           {
              valAvalia = valAvalia - PEAOVALOR;
           }
       }

}

