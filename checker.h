#ifndef CHECKER_H
#define CHECKER_H

#include <QObject>
#include "fieldelement.h"
#include <array>
#include <QPair>

struct SquareOfBoard{
    setUnderAttack(bool boolean = true){
        isUnderAttack = boolean;
    }

    FigureType type;
    COLOR color;
    bool isUnderAttack{false};
};

class Checker : public QObject
{
    Q_OBJECT
public:
    explicit Checker(QObject* parent = nullptr);

    bool IsElementUnderDefence(const QPair<int,int>& coordinates);
    bool isKingInCheck();
    bool IsCheckMate();
    bool canTakeAttacker(const QPair<int, int>& coordinates);
    bool canBlockAttacker(const QPair<int,int>& coordinates);
    bool canAttack(int pieceX, int pieceY, int kingX, int kingY, FigureType Type);


    QPair<int,int> getAttackerCoordinates();

protected:


    void CheckPawnPossibleMove(const QPair<int, int>& coordinates);
    void CheckKnightPossibleMove(const QPair<int, int>& coordinates);
    void CheckQueenPossibleMove(const QPair<int, int>& coordinates);
    void CheckRookPossibleMove(const QPair<int, int>& coordinates);
    void CheckBishopPossibleMove(const QPair<int, int>& coordinates);
    void CheckKingPossibleMove(const QPair<int, int>& coordinates);

    void DeleteAllAttacks();

    void CheckAllFigures();

    void CheckForCheck();
    void CheckForMate();

public slots:
    void MakeMoveOnBoard(const QString& Notation);

signals:
    void Check(COLOR clr);
    void Mate(COLOR clr);

private:
    std::array<std::array<SquareOfBoard, 8>, 8> ChessBoard;
    QPair<int,int> WhiteKingCoordinates;
    QPair<int,int> BlackKingCoordinates;
};

#endif // CHECKER_H
