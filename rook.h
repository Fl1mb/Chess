#ifndef ROOK_H
#define ROOK_H
#include "figure.h"

class Rook: public Figure
{
public:
    Rook(COLOR clr, QGraphicsItem* parent = 0);
};

#endif // ROOK_H
