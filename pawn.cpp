#include "pawn.h"

Pawn::Pawn(COLOR clr,QGraphicsItem* parent): Figure(parent)
{
    NumOfMove = 0;

    switch(clr){
    case WHITE:
        this->setPixmap(QPixmap(":/ChessFigures/ChessFiguresImgs/WhitePawn.png"));
        break;
    case BLACK:
        this->setPixmap(QPixmap(":/ChessFigures/ChessFiguresImgs/BlackPawn.png"));
    }
    setTransformationMode(Qt::SmoothTransformation);
}


