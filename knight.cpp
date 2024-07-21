#include "knight.h"


Knight::Knight(COLOR clr, QGraphicsItem *parent) : Figure(parent)
{
    switch(clr){
    case WHITE:
        this->setPixmap(QPixmap(":/ChessFigures/ChessFiguresImgs/WhiteKnight.png"));
        break;
    case BLACK:
        this->setPixmap(QPixmap(":/ChessFigures/ChessFiguresImgs/BlackKnight.png"));
    }
    setTransformationMode(Qt::SmoothTransformation);
}
