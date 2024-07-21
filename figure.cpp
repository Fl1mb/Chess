#include "figure.h"
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QCursor>
#include <QTransform>

Figure::Figure(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
}

void Figure::SetType(const FigureType type)
{
    this->type_ = type;
}

void Figure::SetColor(const COLOR clr)
{
    this->clr_ = clr;
}

void Figure::SetupFigure()
{
    QString tp;
    switch(type_){
    case PAWN:
        tp = "Pawn";
        break;
    case ROOK:
        tp = "Rook";
        break;
    case QUEEN:
        tp = "Queen";
        break;
    case KING:
        tp = "King";
        break;
    case BISHOP:
        tp = "Bishop";
        break;
    case KNIGHT:
        tp = "Knight";
        break;
    default:
        return;
    }


    QString ImageName = QString(":/ChessFigures/ChessFiguresImgs/%1%2.png").arg(clr_ == WHITE? "White" : "Black").arg(tp);
    this->setPixmap(QPixmap(ImageName));

    this->setTransformationMode(Qt::SmoothTransformation);

}


void Figure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *wgt)
{
    QGraphicsPixmapItem::paint(painter, option, wgt);

    if(isSelected()){
        QColor color(Qt::red);
        color.setAlpha(100);
        QBrush brush(color);
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setBrush(brush);
        painter->setPen(Qt::NoPen);
        painter->drawEllipse(QPointF(20,20), 40,40);
    }

}

void Figure::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "clicked";
    emit clicked();
    Q_UNUSED(event);
}




