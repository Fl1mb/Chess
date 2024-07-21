#include "rook.h"

Rook::Rook(COLOR clr, QGraphicsItem* parent) : Figure(parent)
{
    switch(clr){
    case WHITE:
        this->setPixmap(QPixmap(":/ChessFigures/ChessFiguresImgs/WhiteRook.png"));
        break;
    case BLACK:
        this->setPixmap(QPixmap(":/ChessFigures/ChessFiguresImgs/BlackRook.png"));
    }
    setTransformationMode(Qt::SmoothTransformation);
}
