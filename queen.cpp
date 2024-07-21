#include "queen.h"

Queen::Queen(COLOR clr, QGraphicsItem* parent) : Figure(parent)
{
    switch(clr){
    case WHITE:
        this->setPixmap(QPixmap(":/ChessFigures/ChessFiguresImgs/WhiteQueen.png"));
        break;
    case BLACK:
        this->setPixmap(QPixmap(":/ChessFigures/ChessFiguresImgs/BlackQueen.png"));
    }
    setTransformationMode(Qt::SmoothTransformation);
}
