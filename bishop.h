#ifndef BISHOP_H
#define BISHOP_H
#include "figure.h"

class Bishop : public Figure
{
public:
    Bishop(COLOR clr,QGraphicsItem* parent = 0);
};

#endif // BISHOP_H
