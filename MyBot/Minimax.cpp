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

void Minimax::exe(BitBoard bitboard)
{
    cout<< "Começando Minimax" <<endl;
    if(bitboard.who_moves == 1) //Eu SOu o BRanco
    {

     bitboard.tabuleiro.GeraListaBitboardsPossiveisPeao(); //ok
     bitboard.tabuleiro.GeraListaBitboardsPossiveisTorre(); // ok
     cout<< "Gerei Meus Movimentos 1-Nivel" <<endl;

     Tabuleiro *ptAux = bitboard.tabuleiro.filhos;
     while(ptAux != bitboard.tabuleiro.ptUltimo) //Gera Movimento do Inimigo
     {
         Tabuleiro *MovInvGerados = InverteTabuleiro(ptAux);
         DesinverteTabuleiro(MovInvGerados,ptAux);

         ptAux = ptAux->irmao;
         if(ptAux == bitboard.tabuleiro.ptUltimo)
         {
             Tabuleiro *MovInvGerados = InverteTabuleiro(ptAux);
             DesinverteTabuleiro(MovInvGerados,ptAux);
         }
     }

      cout<< "Gerei Movimentos Inimigos 1-Nivel" <<endl;
      ExpandeMeuSegundoNivel(bitboard.tabuleiro); // Nao Conferido!
      ExpandeSegundoNivelInimigo(bitboard.tabuleiro); // Nao Conferido!




     // Faz Segundo Nível meu

     IdentificaCOORD(bitboard.tabuleiro.filhos,bitboard.tabuleiro); // Elaborar uma forma de avaliar Último Nível
    }                                                               // PseudoFuncao de Avaliacao pronta!
    else //Eu sou o Preto
    {

    }

}
void Minimax::ExpandeMeuSegundoNivel(Tabuleiro tabuleiro)
{
    Tabuleiro *ptAux2 = tabuleiro.filhos;
    Tabuleiro *ptAux;


    while(ptAux2 != tabuleiro.ptUltimo)
    {
        ptAux = ptAux2->filhos;
        while(ptAux != ptAux2->ptUltimo) // Meus Movimentos do Segundo Nivel
        {

            ptAux->GeraListaBitboardsPossiveisPeao();
            ptAux->GeraListaBitboardsPossiveisTorre();
            ptAux = ptAux->irmao;
            if(ptAux == ptAux2->ptUltimo)
            {
                 ptAux->GeraListaBitboardsPossiveisPeao();
                 ptAux->GeraListaBitboardsPossiveisTorre();
            }
        }
        ptAux2 = ptAux2->irmao;

    }
    cout<< "Gerei Meus Movimentos 2-Nivel" <<endl;

}

void Minimax::ExpandeSegundoNivelInimigo(Tabuleiro tabuleiro)
{

    Tabuleiro *ptAux  = tabuleiro.filhos;
    Tabuleiro *ptAux2;
    Tabuleiro *ptAux3;
    cout<< "Cheguei 1" <<endl;
    while(ptAux != tabuleiro.ptUltimo)
    {   cout<< "Cheguei 2" <<endl;
        ptAux2 = ptAux->filhos;
        while(ptAux2 != ptAux->ptUltimo) // Meus Movimentos do Segundo Nivel
        {   cout<< "Cheguei 3" <<endl;
            ptAux3= ptAux2->filhos;
                while(ptAux3!= ptAux2->ptUltimo)
                {   cout<< "Cheguei 4" <<endl;
                    Tabuleiro *MovInvGerados = InverteTabuleiro(ptAux3);
                    cout<< "Cheguei 5" <<endl;
                    DesinverteTabuleiro(MovInvGerados,ptAux3); // Pau!
                    cout<< "Cheguei 6" <<endl;
                    ptAux3 = ptAux3->irmao;
                    cout<< "Cheguei 7" <<endl;
                    if(ptAux3== ptAux2->ptUltimo)
                    {
                        cout<< "Cheguei 8" <<endl;
                        Tabuleiro *MovInvGerados = InverteTabuleiro(ptAux3);
                        DesinverteTabuleiro(MovInvGerados,ptAux3);
                    }
                }
            ptAux2 = ptAux2->irmao;
        }
    ptAux = ptAux->irmao;

    }
    cout<< "Gerei Movimentos Inimigos 2-Nivel" <<endl;

}
Tabuleiro* Minimax::InverteTabuleiro(Tabuleiro *tabuleiro) //OK
{
        Tabuleiro Buffer;
        Buffer.allPieces = InverteUint(tabuleiro->allPieces);
        Buffer.BlackPieces = InverteUint(tabuleiro->WhitePieces);
        Buffer.BlackPawns = InverteUint(tabuleiro->WhitePawns);
        Buffer.BlackBishops = InverteUint(tabuleiro->WhiteBishops);
        Buffer.BlackRooks = InverteUint(tabuleiro->WhiteRooks);
        Buffer.WhiteBishops = InverteUint(tabuleiro->BlackBishops);
        Buffer.WhitePawns = InverteUint(tabuleiro->BlackPawns);
        Buffer.WhiteRooks = InverteUint(tabuleiro->BlackRooks);
        Buffer.WhitePieces = InverteUint(tabuleiro->BlackPieces);
        Buffer.emptySpace = InverteUint(tabuleiro->emptySpace);
        Buffer.ptUltimo = NULL;
        Buffer.GeraListaBitboardsPossiveisPeao();
        Buffer.GeraListaBitboardsPossiveisTorre();

        return Buffer.filhos;


}
uint64_t Minimax::InverteUint(uint64_t inv)
{
    uint64_t saida=0;
    Tabuleiro chamador;
    for(int i=0;i<64;i++)
    {   if(chamador.Is_set(inv,i)==true)
        {
           if(i>=0 && i<=7)
           saida =chamador.Set(saida,i+56);
           if(i>=8 && i<=15)
           saida =chamador.Set(saida,i+40);
           if(i>=16 && i<=23)
           saida =chamador.Set(saida,i+24);
           if(i>=24 && i<=31)
           saida =chamador.Set(saida,i+8);
           if(i>=32 && i<=39)
           saida =chamador.Set(saida,i-8);
           if(i>=40 && i<=47)
           saida =chamador.Set(saida,i-24);
           if(i>=48 && i<=55)
           saida =chamador.Set(saida,i-40);
           if(i>=56 && i<=63)
           saida =chamador.Set(saida,i-56);
        }
    }
    return saida;
}


void Minimax::DesinverteTabuleiro(Tabuleiro *tabuleiro,Tabuleiro *EncadearNele)
{
        Tabuleiro *Buffer=NULL;
        Tabuleiro *ptAux = tabuleiro; // Percorrer uma lista encadeada gerada das jogadas invertidas
        Tabuleiro *ptAux2 = NULL; // Percorrer lista dos imrãos
        while(ptAux!=NULL)
        {
        Buffer = (Tabuleiro*) malloc(sizeof(Tabuleiro));
        Buffer->allPieces = InverteUint(ptAux->allPieces);
        Buffer->BlackPieces = InverteUint(ptAux->WhitePieces);
        Buffer->BlackPawns = InverteUint(ptAux->WhitePawns);
        Buffer->BlackBishops = InverteUint(ptAux->WhiteBishops);
        Buffer->BlackRooks = InverteUint(ptAux->WhiteRooks);
        Buffer->WhiteBishops = InverteUint(ptAux->BlackBishops);
        Buffer->WhitePawns = InverteUint(ptAux->BlackPawns);
        Buffer->WhiteRooks = InverteUint(ptAux->BlackRooks);
        Buffer->WhitePieces = InverteUint(ptAux->BlackPieces);
        Buffer->emptySpace = InverteUint(ptAux->emptySpace);

        if(EncadearNele->ptUltimo==NULL)
        {

            EncadearNele->filhos = Buffer;
            EncadearNele->ptUltimo = Buffer;
            ptAux= ptAux->irmao;
            ptAux2 = Buffer;
        }
        else
        {
            ptAux2->irmao = Buffer;
            ptAux2 = ptAux2->irmao;
            ptAux= ptAux->irmao;
            EncadearNele->ptUltimo = Buffer;
        }
        }
}


void Minimax::IdentificaCOORD(Tabuleiro *tabJogada,Tabuleiro tabuleiro)
{

     this->To.X = tabJogada->posTo/8;
     this->To.Y = tabJogada->posTo%8;
     this->From.X = tabJogada->posFrom/8;
     this->From.Y = tabJogada->posFrom%8;


}

