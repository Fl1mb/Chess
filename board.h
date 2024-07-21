#ifndef BOARD_H
#define BOARD_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector>
#include "fieldelement.h"
#include <QMouseEvent>
#include <QObject>
#include "logic.h"

class Logic;

class Board : public QGraphicsView
{
    Q_OBJECT
public:
    Board(PlayerColor color_, Logic* logic_);

    void SetArrangement();


signals:
    void Change();


public slots:
    void SetFiguresEnable();
    void DeleteElement(Figure* fig, COLOR clr);


private:
    QGraphicsScene* scene;
    PlayerColor color;
    static PlayerColor CurrentPlayer;
    Logic* logic;


    QVector<QVector<FieldElement*>> FieldSquares;
    QVector<Figure*> WhiteFigures;
    QVector<Figure*> BlackFigures;


};

#endif // BOARD_H
