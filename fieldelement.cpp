#include "fieldelement.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPushButton>
#include <QPen>
#include <QBrush>
#include <cassert>

//constructor to inizial

bool FieldElement::AnySelect = false;
FieldElement* FieldElement::SelectedElement = nullptr;

FieldElement::FieldElement(int row, int col, COLOR _clr, PlayerColor PlayerClr_, QGraphicsRectItem *parent): QGraphicsRectItem(0,0,75,75,parent)
{
    QFont font("Anton", 10);
    QColor brush(_clr == WHITE? QColor(125, 148, 93) : QColor(238,238,213));
    figure = nullptr;
    choice = nullptr;
    PlayerClr = PlayerClr_;

    if(PlayerClr == WhitePlayer){
        if(col == 0){
            char chr = '8' - row;
            CoordinateNavigator = new QGraphicsTextItem(QString(chr), this);
            CoordinateNavigator->setPos(5,5);
            CoordinateNavigator->setFont(font);
            CoordinateNavigator->setDefaultTextColor(brush);
        }
        if(row == 7){
            char chr = 'a' + col;
            Letter = new QGraphicsTextItem(QString(chr), this);
            Letter->setPos(50,50);
            Letter->setFont(font);
            Letter->setDefaultTextColor(brush);
        }
        this->num = 'a' + col;
        this->ch = '8' - row;

    }else{
        if(col == 0){
            char chr = '1' + row;
            CoordinateNavigator = new QGraphicsTextItem(QString(chr), this);
            CoordinateNavigator->setPos(5,5);
            CoordinateNavigator->setFont(font);
            CoordinateNavigator->setDefaultTextColor(brush);
        }
        if(row == 7){
            char chr = 'h' - col;
            Letter = new QGraphicsTextItem(QString(chr), this);
            Letter->setPos(50,50);
            Letter->setFont(font);
            Letter->setDefaultTextColor(brush);
        }

        this->num = 'h' - col;
        this->ch = '1' + row;
    }



    clr = _clr;



}

void FieldElement::AddFigure(const FigureType type, const COLOR FigColor, QVector<Figure*>& array)
{
    figure_type = type;



    figure = new Figure();
    figure->SetType(type);
    figure->SetColor(FigColor);
    figure->SetupFigure();
    array.push_back(figure);

    connect(figure, SIGNAL(clicked()), this, SLOT(SelectedFigure()));

    QPointF centerPos = QPointF(this->x() + this->boundingRect().center().x() - 25,this->y() + this->boundingRect().center().y() - 28);

    figure->setPos(centerPos);
    scene()->addItem(figure);


}

void FieldElement::AddFigure(Figure *fig)
{
    figure = fig;
    figure_type = figure->getType();
    connect(figure, SIGNAL(clicked()), this, SLOT(SelectedFigure()));
    QPointF centerPos = QPointF(this->x() + this->boundingRect().center().x() - 25,this->y() + this->boundingRect().center().y() - 28);
    figure->setPos(centerPos);
    figure->update();
}

QRectF FieldElement::boundingRect() const
{
    return QRectF(0,0,75, 75);
}

void FieldElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *wgt)
{
    painter->setBrush(clr == WHITE? QColor(238,238,213) : QColor(125, 148, 93));
    painter->drawRect(boundingRect());

    if(IsSelect){
        QColor color(clr == WHITE? QColor(125, 148, 93) : QColor(238,238,213));
        color.setAlpha(64);

        QBrush highlightBrush(color);
        highlightBrush.setStyle(Qt::SolidPattern); // semi-transparent red brush
        painter->setBrush(highlightBrush);
        painter->drawRect(boundingRect());
    }


}

void FieldElement::SelectThisSquare()
{
    choice = new MoveChoice(QPointF(this->x() + 75 / 2 , this->y() + 75/2), this->figure != nullptr);
    scene()->addItem(choice);

    connect(choice, SIGNAL(clicked()), this, SLOT(MakeMove()));
    connect(choice, SIGNAL(killedFigure()), this, SLOT(KillHim()));
}

void FieldElement::UnselectThisSquare()
{
    scene()->removeItem(choice);
    delete choice;
}


void FieldElement::SelectedFigure()
{
    if(!AnySelect && !SelectedElement){
        this->IsSelect = !this->IsSelect;
        this->update();

        AnySelect = !AnySelect;
        SelectedElement = this;
        
        emit ShowPossibleMoves(this);
    }else if(SelectedElement == this){
        this->IsSelect = !this->IsSelect;
        this->update();

        AnySelect = !AnySelect;
        SelectedElement = nullptr;

        emit HidePossibleMoves();
    }else{

        SelectedElement->IsSelect = false;
        SelectedElement->update();
        emit HidePossibleMoves();

        this->IsSelect = !this->IsSelect;
        this->update();

        SelectedElement = this;
        emit ShowPossibleMoves(this);
    }

}

void FieldElement::MakeMove()
{
    emit MoveFigureTo();
}

void FieldElement::KillHim()
{
    emit KillThisFigure(this);
}
///Другой класс
/// Класс, pixmap , для того чтобы отображать ходы юзера

MoveChoice::MoveChoice(QPointF pos,bool isFig, QGraphicsItem *parent): QGraphicsItem(parent)
{
    setPos(pos);
    setFlag(QGraphicsItem::ItemIsSelectable);
    isFigure = isFig;
}

QRectF MoveChoice::boundingRect() const
{
    return QRectF(-10, - 10, 75, 75);
}

void MoveChoice::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor color(Qt::blue);
    color.setAlpha(64);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(color);
    painter->drawEllipse(QRectF(-10, -10, 20, 20));
}





void MoveChoice::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(isFigure){
        emit killedFigure();
    }else{
        emit clicked();
    }
    event->accept();


}
