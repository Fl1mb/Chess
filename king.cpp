#include "king.h"

King::King(COLOR clr, QGraphicsItem *parent): Figure(parent)
{
    switch(clr){
    case WHITE:
        this->setPixmap(QPixmap(":/ChessFigures/ChessFiguresImgs/WhiteKing.png"));
        break;
    case BLACK:
        this->setPixmap(QPixmap(":/ChessFigures/ChessFiguresImgs/BlackKing.png"));
    }
    setTransformationMode(Qt::SmoothTransformation);

}
