#include <iostream>

class Tabuleiro
{    public:

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

         int valAvalia;
         Tabuleiro* filhos;
         Tabuleiro* irmao;
         Tabuleiro* ptAux;

    public:
        Tabuleiro();
        virtual ~Tabuleiro();

        uint64_t Set (uint64_t bitboard, int numSquare);
        uint64_t Clear (uint64_t bitboard, int numSquare);
        bool Is_set(uint64_t bitboard,int numSquare);
        void GeraListaBitboardsPossiveisPeao();


    protected:
    private:
        uint64_t SetMasksField(int numSquare);
        uint64_t ClearMasksField(int numSquare);
        uint64_t GetPawnMovMaskCima(int square);
        uint64_t GetPawnMovMaskCome(int square);
        uint64_t GeraMovValidoPeaoCima(uint64_t maskMovCima,int square);
        uint64_t GeraMovValidoPeaoCome(uint64_t maskMovCome);
        void VeQualPecaFoiComida(int i);
};


