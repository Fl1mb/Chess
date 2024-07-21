#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include "board.h"
#include <QPair>
#include <QVector>
#include <QSignalMapper>
#include "checker.h"


class Logic: public QObject
{
    Q_OBJECT
public:
    explicit Logic(QObject* parent = 0);
    ~Logic() = default;
    
    void setBoard(QVector<QVector<FieldElement*>>& board, PlayerColor clr);
    void TransformPawn(FieldElement* element);
    void SelectSquares();

    void MakeMoveByText(const QString& str);

    inline void CheckAllMoves(FieldElement* element, PlayerColor clr);
    inline bool CheckKnightMoves(int x, int y, COLOR clr);
    inline void CheckRookMoves(COLOR clr);
    inline void CheckBishopMoves(COLOR clr);
    inline void CheckKingMoves(COLOR clr);

    QString Notation(QPair<int, int> From, QPair<int,int> To);

    int GetNumberOfMoves();

public slots:
    void HidePossibleMoves();
    void MakeMoveTo(const QString& str);
    void ShowPossibleMoves(FieldElement* element);
    void KillFigure(FieldElement* element);

signals:
    void ChangeMove();
    void Moved();
    void WhiteMove();
    void BlackMove();
    void DeleteFigureBlackBoard(Figure* fig, COLOR clr);
    void DeleteFigureWhiteBoard(Figure* fig, COLOR clr);
    void CheckForCheck(const QString& Notation);

    
private:
    QPair<int,int> mapMove(int x, int y)const;
    Checker* checker;

    QVector<QPair<int, int>> possibleMoves;
    QVector<QSignalMapper*> mappers_;
    QVector<QVector<FieldElement*>> ChessBoard;

    QVector<QVector<FieldElement*>> WhitePlayerBoard;
    QVector<QVector<FieldElement*>> BlackPlayerBoard;

    QPair<int,int> MoveFrom;
    QPair<int, int> MoveTo;
    
    FieldElement* CurrentElement;
    int CurrentX;
    int CurrentY;

    int NumberOfMoves{0};

};

#endif // LOGIC_H
