#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <stdio.h>


class Minimax
{
    public:
        Minimax();
        virtual ~Minimax();
        COORD exe(BitBoard bitboard);
    protected:
    private:
};
