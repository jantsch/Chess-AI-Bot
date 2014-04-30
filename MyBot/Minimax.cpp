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
     bitboard.tabuleiro.GeraListaBitboardsPossiveisBispo(); //ok
     bitboard.tabuleiro.GeraListaBitboardsPossiveisTorre(); // ok

     cout<< "Gerei Meus Movimentos 1-Nivel" <<endl;
     Printar1Nivel(bitboard.tabuleiro); // Até Aqui Ok!



     Tabuleiro *ptAux;
     for(ptAux = bitboard.tabuleiro.filhos;ptAux!=NULL; ptAux = ptAux->irmao)
     {
             Tabuleiro *MovInvGerados = InverteTabuleiro(ptAux);
             DesinverteTabuleiro(MovInvGerados,ptAux);
     }
      cout<< "Gerei Movimentos Inimigos 1-Nivel" <<endl;

      Printar2Nivel(bitboard.tabuleiro);
      //ExpandeMeuSegundoNivel(bitboard.tabuleiro); // Nao Conferido!
      //Printar3Nivel(bitboard.tabuleiro);

      //ExpandeSegundoNivelInimigo(bitboard.tabuleiro); // Nao Conferido!



     IdentificaCOORD(bitboard.tabuleiro.filhos,bitboard.tabuleiro); // Elaborar uma forma de avaliar Último Nível
    }                                                               // PseudoFuncao de Avaliacao pronta!
    else //Eu sou o Preto
    {

    }

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
        Buffer.GeraListaBitboardsPossiveisBispo();
        Buffer.GeraListaBitboardsPossiveisTorre();
        return Buffer.filhos;


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

        ptAux= ptAux->irmao;

        if(EncadearNele->ptUltimo==NULL)
        {

            EncadearNele->filhos = Buffer;
            EncadearNele->ptUltimo = Buffer;
        }
        else
        {

            EncadearNele->ptUltimo->irmao = Buffer;
            EncadearNele->ptUltimo = EncadearNele->ptUltimo->irmao;
        }
        }
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
void Minimax:: Printar1Nivel(Tabuleiro tabuleiro)
{
    Tabuleiro *ptAux;
    int counte = 0;
    cout << "Nodos Primeiro Nivel" <<endl;
     for(ptAux = tabuleiro.filhos;ptAux!=NULL; ptAux = ptAux->irmao)
     {
          counte++;
          cout << ptAux->allPieces <<endl;
     }

     cout << "Encadeamento" <<endl;
     cout << tabuleiro.ptUltimo->allPieces <<endl;
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
         {counte++;
          cout << ptAux2->allPieces <<endl;
         }
     }
     cout << "Encadeamento" <<endl;
     cout << tabuleiro.ptUltimo->ptUltimo->allPieces <<endl;
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
                //cout << ptAux3->allPieces <<endl;
         }
     }
     cout << "Encadeamento" <<endl;
     //cout << tabuleiro.ptUltimo->ptUltimo->allPieces <<endl;
     cout << counte << endl;
     //cout << "Segundo Nível OK!"<<endl;

}
void Minimax::ExpandeMeuSegundoNivel(Tabuleiro tabuleiro)
{
    Tabuleiro *ptAux; //primeiro nível
    Tabuleiro *ptAux2; // segundo nivel
    cout<< "Iniciando" <<endl;
    for(ptAux = tabuleiro.filhos; ptAux!=NULL;ptAux = ptAux->irmao)
    {       cout<< "Iniciando2" <<endl;
            cout<< ptAux->WhitePieces <<endl;
            for(ptAux2 = ptAux->filhos; ptAux2!=NULL;ptAux2 = ptAux2->irmao)
            {cout<< "Iniciando3" <<endl;
             cout<< ptAux2->WhitePieces <<endl;
            ptAux2->GeraListaBitboardsPossiveisPeao();
            ptAux2->GeraListaBitboardsPossiveisBispo();
            ptAux2->GeraListaBitboardsPossiveisTorre();
            cout<< ptAux2->ptUltimo->WhitePieces <<endl;
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
                    Tabuleiro *MovInvGerados = InverteTabuleiro(ptAux3);
                    DesinverteTabuleiro(MovInvGerados,ptAux3); // Pau!
                }
            }
    }
    cout<< "Gerei Movimentos Inimigos 2-Nivel" <<endl;

}
void Minimax::IdentificaCOORD(Tabuleiro *tabJogada,Tabuleiro tabuleiro)
{

     this->To.X = tabJogada->posTo/8;
     this->To.Y = tabJogada->posTo%8;
     this->From.X = tabJogada->posFrom/8;
     this->From.Y = tabJogada->posFrom%8;


}

