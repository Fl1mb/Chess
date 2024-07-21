#ifndef PAWN_H
#define PAWN_H
#include "figure.h"

class Pawn: public Figure
{
public:
    Pawn(COLOR clr, QGraphicsItem* parent = 0);


private:
    int NumOfMove;

};

#endif // PAWN_H
