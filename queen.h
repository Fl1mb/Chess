#ifndef QUEEN_H
#define QUEEN_H
#include "figure.h"

class Queen: public Figure
{
public:
    Queen(COLOR clr, QGraphicsItem* parent = 0);
};

#endif // QUEEN_H
