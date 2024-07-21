#ifndef FIGURE_H
#define FIGURE_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPointF>

enum FigureType{
    PAWN = 0x00, KING, QUEEN, KNIGHT, BISHOP, ROOK, NONE
};

enum COLOR{
    WHITE = 297, BLACK, None
};

enum PlayerColor{
    WhitePlayer = 300, BlackPlayer
};


class Figure : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Figure(QGraphicsItem* parent  =0);
    void SetType(FigureType type);
    void SetColor(COLOR clr);

    void SetupFigure();

    void IncrementNumOfMoves(){numOfMoves++;}
    int getNumOfMoves(){return numOfMoves;}
    COLOR getColor(){return clr_;}
    FigureType getType(){return type_;}


protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* wgt);

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    //Для обновы :D
    //void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;


signals:
    void clicked();


private:


    int numOfMoves{0};
    FigureType type_;
    COLOR clr_;
};


#endif // FIGURE_H
