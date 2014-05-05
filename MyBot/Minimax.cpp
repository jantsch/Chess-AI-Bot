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
if(bitboard.winner==0)
 {
    if(bitboard.who_moves == 1 ) //Eu SOu o BRanco
    {
        if(bitboard.white_infractions<=3)
         {
             bitboard.tabuleiro.GeraListaBitboardsPossiveisPeao(); //ok
             bitboard.tabuleiro.GeraListaBitboardsPossiveisBispo(); //ok
             bitboard.tabuleiro.GeraListaBitboardsPossiveisTorre(); // ok

             cout<< "Gerei Meus Movimentos 1-Nivel" <<endl;


             Tabuleiro *ptAux;
             for(ptAux = bitboard.tabuleiro.filhos;ptAux!=NULL; ptAux = ptAux->irmao)
             {
              InverteTabuleiro(ptAux);
             }
             cout<< "Gerei Movimentos Inimigos 1-Nivel" <<endl;

              //Printar2Nivel(bitboard.tabuleiro);// Testando OKEI s� para debugar
              ExpandeMeuSegundoNivel(bitboard.tabuleiro);
              //Printar3Nivel(bitboard.tabuleiro);// Testando OKEI s� para debugar
              ExpandeSegundoNivelInimigo(bitboard.tabuleiro);
              //Printar4Nivel(bitboard.tabuleiro);

              Tabuleiro *Jogada = bitboard.AvaliaArvorePreta(bitboard.tabuleiro);
              //Printar1Nivel(bitboard.tabuleiro); // Testando OKEI s� para debugar
              IdentificaCOORD(Jogada);
         }
         else
         {
             bitboard.tabuleiro.GeraListaBitboardsPossiveisPeao(); //ok
             bitboard.tabuleiro.GeraListaBitboardsPossiveisBispo(); //ok
             bitboard.tabuleiro.GeraListaBitboardsPossiveisTorre(); // ok

             cout<< "Gerei Meus Movimentos 1-Nivel" <<endl;


             Tabuleiro *ptAux;
             for(ptAux = bitboard.tabuleiro.filhos;ptAux!=NULL; ptAux = ptAux->irmao)
             {
              InverteTabuleiro(ptAux);
             }
             cout<< "Gerei Movimentos Inimigos 1-Nivel" <<endl;

             Tabuleiro *Jogada = bitboard.AvaliaArvorePretaSegNivel(bitboard.tabuleiro);
              //Printar1Nivel(bitboard.tabuleiro); // Testando OKEI s� para debugar
             IdentificaCOORD(Jogada);

         }
    }
    else //Eu sou o Preto
    {
          if(bitboard.black_infractions<=3)
          {
              InverteTabuleiro(&bitboard.tabuleiro);

          cout<< "Gerei Meus Movimentos 1-Nivel" <<endl;

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


          Tabuleiro *Jogada = bitboard.AvaliaArvorePreta(bitboard.tabuleiro);
          Jogada->InverteMovimento();
          //Printar2Nivel(bitboard.tabuleiro);


          IdentificaCOORD(Jogada);
          }
          else
          {
            InverteTabuleiro(&bitboard.tabuleiro);

            cout<< "Gerei Meus Movimentos 1-Nivel" <<endl;

            Tabuleiro *ptAux;
            for(ptAux = bitboard.tabuleiro.filhos;ptAux!=NULL; ptAux = ptAux->irmao)
            {
                 InverteTabuleiro(ptAux);
            }
            cout<< "Gerei Movimentos Inimigos 1-Nivel" <<endl;
            //Printar2Nivel(bitboard.tabuleiro);

          Tabuleiro *Jogada = bitboard.AvaliaArvorePretaSegNivel(bitboard.tabuleiro);
          Jogada->InverteMovimento();


          IdentificaCOORD(Jogada);


          }

    }
 }
}

void Minimax::InverteTabuleiro(Tabuleiro *tabuleiro) //OK
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

                Buffer.GeraListaBitboardsPossiveisBispo();
                Buffer.GeraListaBitboardsPossiveisPeao();
                Buffer.GeraListaBitboardsPossiveisTorre();

                tabuleiro->filhos = Buffer.filhos;
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
    Tabuleiro *ptAux; //primeiro n�vel
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
     }
     cout << counte <<endl;
     cout << "Primeiro N�vel OK!"<<endl;

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

         }
     }
     cout << counte << endl;
     cout << "Segundo N�vel OK!"<<endl;

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
         {
             for(ptAux3 = ptAux2->filhos;ptAux3!=NULL; ptAux3 = ptAux3->irmao)
            {
                counte++;

            }
         }
     }

     cout << counte << endl;
     cout << "Terceiro N�vel OK!"<<endl;

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
     cout << "Quarto N�vel OK!"<<endl;

}
