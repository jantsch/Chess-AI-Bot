#ifndef BITMAP_H
#define BITMAP_H


class Bitmap
{
    bool draw;
    COORD enpassant;
    int who_moves; //  -1 pretas ou 1 brancas
    bool bad_move;
    int white_infractions;
    int black_infractions;
    int winner; // 1 ,0 ou -1
    bool fiftyMoves;

    //Definir tipo da Matriz ou bitboard


    public:
        Bitmap(String msgServidor);
        virtual ~Bitmap();

        void GeraPossiveisJogadas();

    private:
        void ConverteFormatoServBit();

};

#endif // BITMAP_H
