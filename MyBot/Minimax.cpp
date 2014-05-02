#include "BitBoard.h"
#include "Minimax.h"



Minimax::Minimax()
{
    this->From.X = 0;
    this->From.Y = 0;
    this->To.X = 0;
    this->To.Y = 0;
    //ctor
}

Minimax::~Minimax()
{
    //dtor
}

void Minimax::exe(BitBoard bitboard)
{
    cout<< "Montando Arvore" <<endl;

    if(bitboard.who_moves == 1) //Eu SOu o BRanco
    {
         bitboard.tabuleiro.GeraListaBitboardsPossiveisPeao(); //ok
         bitboard.tabuleiro.GeraListaBitboardsPossiveisBispo(); //ok
         bitboard.tabuleiro.GeraListaBitboardsPossiveisTorre(); // ok

         cout<< "Gerei Meus Movimentos 1-Nivel" <<endl;
         //Printar1Nivel(bitboard.tabuleiro); // Testando OKEI só para debugar

         Tabuleiro *ptAux;
         for(ptAux = bitboard.tabuleiro.filhos;ptAux!=NULL; ptAux = ptAux->irmao)
         {
                 InverteTabuleiro(ptAux);

         }
          cout<< "Gerei Movimentos Inimigos 1-Nivel" <<endl;

          //Printar2Nivel(bitboard.tabuleiro);// Testando OKEI só para debugar
          ExpandeMeuSegundoNivel(bitboard.tabuleiro);
          //Printar3Nivel(bitboard.tabuleiro);// Testando OKEI só para debugar
          ExpandeSegundoNivelInimigo(bitboard.tabuleiro);
          //Printar4Nivel(bitboard.tabuleiro);

          Tabuleiro *Jogada = bitboard.AvaliaArvorePreta(bitboard.tabuleiro);

          IdentificaCOORD(Jogada);
    }
    else //Eu sou o Preto
    {
          InverteTabuleiro(&bitboard.tabuleiro);

          cout<< "Gerei Meus Movimentos 1-Nivel" <<endl;
          //Printar1Nivel(bitboard.tabuleiro);

          Tabuleiro *ptAux;
          for(ptAux = bitboard.tabuleiro.filhos;ptAux!=NULL; ptAux = ptAux->irmao)
            {
                 InverteTabuleiro(ptAux);
            }
          cout<< "Gerei Movimentos Inimigos 1-Nivel" <<endl;
          //Printar2Nivel(bitboard.tabuleiro);

          ExpandeMeuSegundoNivelPreto(bitboard.tabuleiro);
          //Printar3Nivel(bitboard.tabuleiro);

          ExpandeSegundoNivelInimigoPreto(bitboard.tabuleiro);


          Tabuleiro *Jogada = bitboard.AvaliaArvoreBranca(bitboard.tabuleiro);
          Jogada->InverteMovimento();

          IdentificaCOORD(Jogada);

    }

}

void Minimax::InverteTabuleiro(Tabuleiro *tabuleiro) //OK
{

        tabuleiro->allPieces = InverteUint(tabuleiro->allPieces);
        tabuleiro->BlackPieces = InverteUint(tabuleiro->WhitePieces);
        tabuleiro->BlackPawns = InverteUint(tabuleiro->WhitePawns);
        tabuleiro->BlackBishops = InverteUint(tabuleiro->WhiteBishops);
        tabuleiro->BlackRooks = InverteUint(tabuleiro->WhiteRooks);
        tabuleiro->WhiteBishops = InverteUint(tabuleiro->BlackBishops);
        tabuleiro->WhitePawns = InverteUint(tabuleiro->BlackPawns);
        tabuleiro->WhiteRooks = InverteUint(tabuleiro->BlackRooks);
        tabuleiro->WhitePieces = InverteUint(tabuleiro->BlackPieces);
        tabuleiro->emptySpace = InverteUint(tabuleiro->emptySpace);
        tabuleiro->GeraListaBitboardsPossiveisPeao();
        tabuleiro->GeraListaBitboardsPossiveisBispo();
        tabuleiro->GeraListaBitboardsPossiveisTorre();
        //return tabuleiro-filhos;


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
void Minimax::ExpandeMeuSegundoNivelPreto(Tabuleiro tabuleiro)
{
            Tabuleiro *ptAux;
            Tabuleiro *ptAux2; // segundo nivel
            for(ptAux = tabuleiro.filhos; ptAux!=NULL;ptAux = ptAux->irmao)
            {       for(ptAux2 = ptAux->filhos; ptAux2!=NULL;ptAux2 = ptAux2->irmao)
                    {
                         InverteTabuleiro(ptAux2);

                    }
          }
           cout<< "Gerei Meus Movimentos 2-Nivel" <<endl;

}
void Minimax::ExpandeSegundoNivelInimigoPreto(Tabuleiro tabuleiro)
{
    Tabuleiro *ptAux;
    Tabuleiro *ptAux2;
    Tabuleiro *ptAux3;

         for(ptAux = tabuleiro.filhos;ptAux!=NULL; ptAux = ptAux->irmao)
            {
                    for(ptAux2 = ptAux->filhos; ptAux2!=NULL;ptAux2 = ptAux2->irmao)
                    {
                        for(ptAux3 = ptAux2->filhos;ptAux3!=NULL;ptAux3 = ptAux3->irmao)
                        {
                          InverteTabuleiro(ptAux3);
                        }
                    }
            }
            cout<< "Gerei Movimentos Inimigos 2-Nivel" <<endl;

}
void Minimax::ExpandeMeuSegundoNivel(Tabuleiro tabuleiro)
{
    Tabuleiro *ptAux; //primeiro nível
    Tabuleiro *ptAux2; // segundo nivel
    for(ptAux = tabuleiro.filhos; ptAux!=NULL;ptAux = ptAux->irmao)
    {       for(ptAux2 = ptAux->filhos; ptAux2!=NULL;ptAux2 = ptAux2->irmao)
            {
                InverteTabuleiro(ptAux2);
            }
    }


    cout<< "Gerei Meus Movimentos 2-Nivel" <<endl;

}
void Minimax::ExpandeSegundoNivelInimigo(Tabuleiro tabuleiro)
{

    Tabuleiro *ptAux  = tabuleiro.filhos;
    Tabuleiro *ptAux2;
    Tabuleiro *ptAux3;

    for(ptAux = tabuleiro.filhos;ptAux!=NULL; ptAux = ptAux->irmao)
    {
            for(ptAux2 = ptAux->filhos; ptAux2!=NULL;ptAux2 = ptAux2->irmao)
            {
                for(ptAux3 = ptAux2->filhos;ptAux3!=NULL;ptAux3 = ptAux3->irmao)
                {
                     InverteTabuleiro(ptAux3);

                }
            }
    }
    cout<< "Gerei Movimentos Inimigos 2-Nivel" <<endl;

}
void Minimax::IdentificaCOORD(Tabuleiro *tabJogada)
{

     this->To.X = tabJogada->posTo/8;
     this->To.Y = tabJogada->posTo%8;
     this->From.X = tabJogada->posFrom/8;
     this->From.Y = tabJogada->posFrom%8;


}

void Minimax:: Printar1Nivel(Tabuleiro tabuleiro)
{
    Tabuleiro *ptAux;
    int counte=0;

    cout << "Nodos Primeiro Nivel" <<endl;
     for(ptAux = tabuleiro.filhos;ptAux!=NULL; ptAux = ptAux->irmao)
     {
          counte++;
          cout << ptAux->allPieces <<endl;

     }
     cout << counte <<endl;
     cout << "Primeiro Nível OK!"<<endl;

}
void Minimax:: Printar2Nivel(Tabuleiro tabuleiro)
{
     Tabuleiro *ptAux;
     Tabuleiro *ptAux2;
     int counte = 0;
     cout << "Nodos Segundo Nivel" <<endl;
     for(ptAux = tabuleiro.filhos;ptAux!=NULL; ptAux = ptAux->irmao)
     {
         for(ptAux2 = ptAux->filhos;ptAux2!=NULL; ptAux2 = ptAux2->irmao)
         {
          counte++;
          cout << ptAux2->allPieces <<endl;
         }
     }
     cout << counte << endl;
     cout << "Segundo Nível OK!"<<endl;

}
void Minimax:: Printar3Nivel(Tabuleiro tabuleiro)
{
     Tabuleiro *ptAux;
     Tabuleiro *ptAux2;
     Tabuleiro *ptAux3;
     int counte = 0;
     cout << "Nodos Terceiro Nivel" <<endl;
     for(ptAux = tabuleiro.filhos;ptAux!=NULL; ptAux = ptAux->irmao)
     {
         for(ptAux2 = ptAux->filhos;ptAux2!=NULL; ptAux2 = ptAux2->irmao)
             for(ptAux3 = ptAux2->filhos;ptAux3!=NULL; ptAux3 = ptAux3->irmao)
            {
                counte++;
                cout << ptAux3->allPieces <<endl;
         }
     }

     cout << counte << endl;
     cout << "Terceiro Nível OK!"<<endl;

}
void Minimax:: Printar4Nivel(Tabuleiro tabuleiro)
{
     Tabuleiro *ptAux;
     Tabuleiro *ptAux2;
     Tabuleiro *ptAux3;
     Tabuleiro *ptAux4;
     int counte = 0;
     cout << "Nodos Terceiro Nivel" <<endl;
     for(ptAux = tabuleiro.filhos;ptAux!=NULL; ptAux = ptAux->irmao)
     {
         for(ptAux2 = ptAux->filhos;ptAux2!=NULL; ptAux2 = ptAux2->irmao)
             {for(ptAux3 = ptAux2->filhos;ptAux3!=NULL; ptAux3 = ptAux3->irmao)
            {
                for(ptAux4 = ptAux3->filhos;ptAux4!=NULL; ptAux4 = ptAux4->irmao)
                {
                counte++;
                //cout << ptAux3->allPieces <<endl;
                }

            }

            }
     }

     cout << counte << endl;
     cout << "Quarto Nível OK!"<<endl;

}
