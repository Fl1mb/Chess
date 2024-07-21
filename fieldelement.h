#ifndef FIELDELEMENT_H
#define FIELDELEMENT_H
#include <QGraphicsItem>
#include "figure.h"
#include <QBrush>
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>

class MoveChoice : public QObject, public QGraphicsItem{
    Q_OBJECT
public:
    explicit MoveChoice(QPointF pos, bool isFig, QGraphicsItem* parent = nullptr);
    ~MoveChoice() = default;
    
    QRectF boundingRect()const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;    
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    bool isFigure;
    
signals:
    void clicked();
    void killedFigure();
    
};



class FieldElement :public QObject,  public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit FieldElement(int row, int col, COLOR _clr, PlayerColor PlayerClr_,  QGraphicsRectItem* parent = 0);

    void AddFigure(FigureType type, COLOR FigColor, QVector<Figure*>& array);
    void AddFigure(Figure* fig);

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* wgt) override;

    void SelectThisSquare();
    void UnselectThisSquare();

    void SetVerticalCoordinate(int X){VerticalCoord = X;}
    void SetHorizontalCoordinate(int Y){HorizontalCoord = Y;}

    int GetVerticalCoordinate(){return VerticalCoord;}
    int GetHorizontalCoordinate(){return HorizontalCoord;}


    bool IsSelect = false;
    FigureType figure_type;
    COLOR clr;
    Figure* figure;
    PlayerColor PlayerClr;

signals:
    void ShowPossibleMoves(FieldElement*);
    void HidePossibleMoves();
    void MoveFigureTo();
    void KillThisFigure(FieldElement*);

public slots:

    void SelectedFigure();
    void MakeMove();
    void KillHim();


protected:


private:
    static bool AnySelect;
    static FieldElement* SelectedElement;

    char ch;
    char num;

    int VerticalCoord;
    int HorizontalCoord;

    QGraphicsTextItem* CoordinateNavigator;
    QGraphicsTextItem* Letter;
    MoveChoice* choice;

};

#endif // FIELDELEMENT_H
