
#include <iostream>

class Tabuleiro
{

    public:
      enum  Squares {
            A1, B1, C1, D1, E1, F1, G1, H1,
            A2, B2, C2, D2, E2, F2, G2, H2,
            A3, B3, C3, D3, E3, F3, G3, H3,
            A4, B4, C4, D4, E4, F4, G4, H4,
            A5, B5, C5, D5, E5, F5, G5, H5,
            A6, B6, C6, D6, E6, F6, G6, H6,
            A7, B7, C7, D7, E7, F7, G7, H7,
            A8, B8, C8, D8, E8, F8, G8, H8,
            INVALID
    };

    public:


         uint64_t WhiteRooks;
         uint64_t WhiteBishops;
         uint64_t WhitePawns;
         uint64_t WhitePieces;

         uint64_t BlackRooks;
         uint64_t BlackBishops;
         uint64_t BlackPawns;
         uint64_t BlackPieces;

         uint64_t allPieces;
         uint64_t emptySpace;

         Tabuleiro* filhos;
         Tabuleiro* irmao;
         Tabuleiro* ptAux;

    public:
        Tabuleiro();
        virtual ~Tabuleiro();

        uint64_t Set(uint64_t bitboard, Squares square);
        uint64_t Set (uint64_t bitboard, int numSquare);
        uint64_t Clear (uint64_t bitboard, Squares square);
        uint64_t Clear (uint64_t bitboard, int numSquare);
        bool Is_set(uint64_t bitboard, Squares square);
        bool Is_set(uint64_t bitboard,int numSquare);
        uint64_t GeraListaBitboardsPossiveis(uint64_t maskMovPossiveisCome,uint64_t maskMovPossiveisCima,Squares square);




    protected:
    private:
        uint64_t SetMasksField(Squares square);
        uint64_t SetMasksField(int numSquare);
        uint64_t ClearMasksField(Squares square);
        uint64_t ClearMasksField(int numSquare);
        uint64_t GetPawnMovMaskCima(Squares square);
        uint64_t GetPawnMovMaskCome(Squares square);
        uint64_t GeraMovValidoPeaoCima(uint64_t maskMovCima,Squares square);
        uint64_t GeraMovValidoPeaoCome(uint64_t maskMovCome);
        void VeQualPecaFoiComida(int i);
};


