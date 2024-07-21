#include "checker.h"
#include <algorithm>


Checker::Checker(QObject *parent) :QObject(parent)
{
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            ChessBoard[row][col] = SquareOfBoard{ FigureType::NONE, COLOR::None, false };
        }
    }

    // Set up the pawns
    for (int col = 0; col < 8; ++col) {
        ChessBoard[6][col] = SquareOfBoard{ FigureType::PAWN, COLOR::WHITE, false };
        ChessBoard[1][col] = SquareOfBoard{ FigureType::PAWN, COLOR::BLACK, false };
    }

    // Set up the rooks
    ChessBoard[7][0] = SquareOfBoard{ FigureType::ROOK, COLOR::WHITE, false };
    ChessBoard[7][7] = SquareOfBoard{ FigureType::ROOK, COLOR::WHITE, false };
    ChessBoard[0][0] = SquareOfBoard{ FigureType::ROOK, COLOR::BLACK, false };
    ChessBoard[0][7] = SquareOfBoard{ FigureType::ROOK, COLOR::BLACK, false };

    // Set up the knights
    ChessBoard[7][1] = SquareOfBoard{ FigureType::KNIGHT, COLOR::WHITE, false };
    ChessBoard[7][6] = SquareOfBoard{ FigureType::KNIGHT, COLOR::WHITE, false };
    ChessBoard[0][1] = SquareOfBoard{ FigureType::KNIGHT, COLOR::BLACK, false };
    ChessBoard[0][6] = SquareOfBoard{ FigureType::KNIGHT, COLOR::BLACK, false };

    // Set up the bishops
    ChessBoard[7][2] = SquareOfBoard{ FigureType::BISHOP, COLOR::WHITE, false };
    ChessBoard[7][5] = SquareOfBoard{ FigureType::BISHOP, COLOR::WHITE, false };
    ChessBoard[0][2] = SquareOfBoard{ FigureType::BISHOP, COLOR::BLACK, false };
    ChessBoard[0][5] = SquareOfBoard{ FigureType::BISHOP, COLOR::BLACK, false };

    // Set up the queens
    ChessBoard[7][4] = SquareOfBoard{ FigureType::QUEEN, COLOR::WHITE, false };
    ChessBoard[0][4] = SquareOfBoard{ FigureType::QUEEN, COLOR::BLACK, false };

    // Set up the kings
    ChessBoard[7][3] = SquareOfBoard{ FigureType::KING, COLOR::WHITE, false };
    ChessBoard[0][3] = SquareOfBoard{ FigureType::KING, COLOR::BLACK, false };

    WhiteKingCoordinates = QPair<int,int>(0,4);
    BlackKingCoordinates = QPair<int,int>(7, 4);
}

bool Checker::IsElementUnderDefence(const QPair<int, int> &coordinates)
{
    return ChessBoard[coordinates.first][coordinates.second].isUnderAttack;
}

bool Checker::isKingInCheck()
{
    return IsElementUnderDefence(WhiteKingCoordinates);
}

bool Checker::IsCheckMate()
{
    //1. Firstly, is check?
    if(!isKingInCheck()){
        return false;
    }

    //2. Secondly, Can King move to another square
    for(int dx = - 1;dx <= 1; dx++ ){
        for(int dy = -1; dy <=1; dy++){
            int newX = WhiteKingCoordinates.first + dx;
            int newY = WhiteKingCoordinates.second + dy;

            if(newX >= 0 && newX < 8 && newY >=0 && newY < 8){
                if(!IsElementUnderDefence(QPair<int, int>(newX, newY)));
                return false;
            }
        }
    }

    //3. Thirdly, Can another piece get into the way??

    return true;

}





void Checker::CheckPawnPossibleMove(const QPair<int, int> &coordinates)
{
    int x = coordinates.first;
    int y = coordinates.second;

    if(ChessBoard[x][y].color == WHITE){
        if(y == 0){
            ChessBoard[x + 1][y + 1].setUnderAttack();
        }else if(y == 7){
            ChessBoard[x+ 1][y - 1].setUnderAttack();
        }else{
            ChessBoard[x+ 1][y + 1].setUnderAttack();
            ChessBoard[x + 1][y - 1].setUnderAttack();
        }
    }else{
        if(y == 0){
            ChessBoard[x - 1][y + 1].setUnderAttack();
        }else if(y == 7){
            ChessBoard[x - 1][y - 1].setUnderAttack();
        }else{
            ChessBoard[x - 1][y + 1].setUnderAttack();
            ChessBoard[x - 1][y - 1].setUnderAttack();
        }
    }
}

void Checker::CheckKnightPossibleMove(const QPair<int, int> &coordinates)
{
    int x = coordinates.first;
    int y = coordinates.second;

    // Define the possible moves of a knight
    int dx[] = {-2, -1, 1, 2, -2, -1, 1, 2};
    int dy[] = {-1, -2, -2, -1, 1, 2, 2, 1};

    for (int i = 0; i < 8; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];

        // Check if the new coordinates are within the board
        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            // Mark the square as under attack
            ChessBoard[newX][newY].setUnderAttack();
        }
    }
}

void Checker::CheckQueenPossibleMove(const QPair<int, int> &coordinates)
{
    CheckBishopPossibleMove(coordinates);
    CheckRookPossibleMove(coordinates);
}

void Checker::CheckRookPossibleMove(const QPair<int, int> &coordinates)
{
    int x = coordinates.first;
    int y = coordinates.second;

    for(int i = 0; i < 8; i ++){
        if(i != x){
            ChessBoard[i][y].setUnderAttack();
        }
    }

    for(int i = 0; i < 8; i ++){
        if(i != y){
            ChessBoard[x][i].setUnderAttack();
        }
    }
}

void Checker::CheckBishopPossibleMove(const QPair<int, int> &coordinates)
{
    int x = coordinates.first;
    int y = coordinates.second;

    // Check diagonal moves (top-left to bottom-right)
    for (int i = 1; x - i >= 0 && y - i >= 0; i++) {
        ChessBoard[x - i][y - i].setUnderAttack(true);
    }
    for (int i = 1; x + i < 8 && y + i < 8; i++) {
        ChessBoard[x + i][y + i].setUnderAttack(true);
    }

    // Check diagonal moves (bottom-left to top-right)
    for (int i = 1; x - i >= 0 && y + i < 8; i++) {
        ChessBoard[x - i][y + i].setUnderAttack(true);
    }
    for (int i = 1; x + i < 8 && y - i >= 0; i++) {
        ChessBoard[x + i][y - i].setUnderAttack(true);
    }
}

void Checker::CheckKingPossibleMove(const QPair<int, int> &coordinates)
{
    int x = coordinates.first;
    int y = coordinates.second;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            int newX = x + dx;
            int newY = y + dy;

            if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
                ChessBoard[newX][newY].setUnderAttack(true);
            }
        }
    }
}

void Checker::DeleteAllAttacks()
{
    for(int i = 0; i < 8;i ++){
        for(int j = 0 ; j  < 8; j++){
            ChessBoard[i][j].setUnderAttack(false);
        }
    }
}

void Checker::CheckAllFigures()
{
    for(int i = 0; i < 8; i ++){
        for (int j = 0; j < 8; j ++){
            FigureType Type = ChessBoard[i][j].type;
            switch(Type){
            case PAWN:
                CheckPawnPossibleMove(QPair<int, int>(i, j));
                break;
            case QUEEN:
                CheckQueenPossibleMove(QPair<int, int>(i, j));
                break;
            case KNIGHT:
                CheckKnightPossibleMove(QPair<int, int>(i, j));
                break;
            case ROOK:
                CheckRookPossibleMove(QPair<int, int>(i, j));
                break;
            case BISHOP:
                CheckBishopPossibleMove(QPair<int,int>(i, j));
                break;
            case KING:
                CheckKingPossibleMove(QPair<int, int>(i, j));
                break;
            case NONE:
                break;
            default:
                break;
            }
        }
    }
}

void Checker::MakeMoveOnBoard(const QString &Notation)
{
    QString fromStr, toStr;
    int fromRow, fromCol, toRow, toCol;

    if(Notation.length() < 2 || Notation.length() > 5){
        qDebug() << "Notation err";
        return;
    }

    fromStr = Notation.mid(0, 2);
    toStr = Notation.mid(2, Notation.length() - 2);

    fromRow = fromStr[0].toLower().unicode() - 'a';
    fromCol = 8 - (fromStr[1].digitValue());
    toRow = toStr[0].toLower().unicode() - 'a';
    toCol = 8 - (toStr[1].digitValue());

    qDebug() << fromRow << " " << fromCol << " "<< toRow << " " << toCol;

    if(ChessBoard[fromRow][fromCol].type == KING){
        if(ChessBoard[fromRow][fromCol].color == WHITE){
            WhiteKingCoordinates = QPair<int,int>(toRow, toCol);
        }else{
            BlackKingCoordinates = QPair<int,int>(toRow, toCol);
        }

        qDebug() << "KING";
    }

    ChessBoard[toRow][toCol] = ChessBoard[fromRow][fromCol];
    ChessBoard[fromRow][fromCol] = SquareOfBoard{FigureType::NONE, COLOR::None, false};

    DeleteAllAttacks();
    CheckAllFigures();


}

