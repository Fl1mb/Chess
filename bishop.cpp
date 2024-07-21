nclude "bishop.h"

Bishop::Bishop(COLOR clr, QGraphicsItem* parent) : Figure(parent)
{
    switch(clr){
    case WHITE:
        this->setPixmap(QPixmap(":/ChessFigures/ChessFiguresImgs/WhiteBishop.png"));
        break;
    case BLACK:
        this->setPixmap(QPixmap(":/ChessFigures/ChessFiguresImgs/BlackBishop.png"));
        break;
    }
    setTransformationMode(Qt::SmoothTransformation);
}
