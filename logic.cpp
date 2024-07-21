#include "logic.h"
#include <cassert>
#include "figure.h"
#include <QString>

//Конструктор
Logic::Logic(QObject *parent) : QObject(parent)
{
    CurrentElement = nullptr;
    checker = new Checker();

    QObject::connect(this, &Logic::CheckForCheck, checker, &Checker::MakeMoveOnBoard);
}


//Определяем доску, чтобы можно было отслеживать ходы
void Logic::setBoard(QVector<QVector<FieldElement *> > &board, PlayerColor clr)
{
    if(clr == WhitePlayer){
        WhitePlayerBoard = board;
    }else{
        BlackPlayerBoard = board;
    }
}


///Определяем тип фигуры, цвет и координаты
/// Просчитываем все возможные ходы для фигур
void Logic::ShowPossibleMoves(FieldElement* element)
{
    if(element->PlayerClr == WhitePlayer){
        ChessBoard = WhitePlayerBoard;
    }else{
        ChessBoard = BlackPlayerBoard;
    }
    if(!element->IsSelect){return;}
    //Тут за X выступает вертикальная координата, а за Y -  горизонтальная
    //Да странно, Но мне лень переделать
    CurrentX = element->GetVerticalCoordinate();
    CurrentY = element->GetHorizontalCoordinate();
    CurrentElement = element;
    
    //assert(CurrentX == -1 || CurrentY == 1);

    qDebug() << CurrentX  << " " << CurrentY;
    assert(element->figure != nullptr );

    CheckAllMoves(element, element->PlayerClr);

    
}

//Функция которая убивает фигуру
void Logic::KillFigure(FieldElement *element)
{
    int x = element->GetVerticalCoordinate();
    int y  = element->GetHorizontalCoordinate();

    QPair<int,int> OtherBoardCoordinates = this->mapMove(CurrentX, CurrentY);
    QPair<int,int> MoveToOtherBoard = this->mapMove(x, y);

    if(CurrentElement->PlayerClr  == WhitePlayer){
        FieldElement* from = BlackPlayerBoard[OtherBoardCoordinates.first][OtherBoardCoordinates.second];
        FieldElement* MoveTo = BlackPlayerBoard[MoveToOtherBoard.first][MoveToOtherBoard.second];

        QObject::disconnect(from->figure, SIGNAL(clicked()), from, SLOT(SelectedFigure()));
        QObject::disconnect(MoveTo->figure, SIGNAL(clicked()), MoveTo, SLOT(SelectedFigure()));

        MoveTo->scene()->removeItem(MoveTo->figure);
        emit DeleteFigureBlackBoard(MoveTo->figure, MoveTo->figure->getColor());
        delete MoveTo->figure;
        MoveTo->AddFigure(from->figure);
        MoveTo->figure->IncrementNumOfMoves();
        from->figure = nullptr;

    }else{
        FieldElement* from = WhitePlayerBoard[OtherBoardCoordinates.first][OtherBoardCoordinates.second];
        FieldElement* MoveTo = WhitePlayerBoard[MoveToOtherBoard.first][MoveToOtherBoard.second];

        QObject::disconnect(from->figure, SIGNAL(clicked()), from, SLOT(SelectedFigure()));
        QObject::disconnect(MoveTo->figure, SIGNAL(clicked()), MoveTo, SLOT(SelectedFigure()));

        MoveTo->scene()->removeItem(MoveTo->figure);
        emit DeleteFigureWhiteBoard(MoveTo->figure, MoveTo->figure->getColor());
        delete MoveTo->figure;
        MoveTo->AddFigure(from->figure);
        MoveTo->figure->IncrementNumOfMoves();
        from->figure = nullptr;
    }

    //Убираем элемент с графической сцены
    QObject::disconnect(element->figure, SIGNAL(clicked()), element, SLOT(SelectedFigure()));
    element->scene()->removeItem(element->figure);
    if(CurrentElement->PlayerClr == WhitePlayer){
        emit DeleteFigureWhiteBoard(element->figure, element->figure->getColor());
    }else{
        emit DeleteFigureBlackBoard(element->figure, element->figure->getColor());
    }
    delete element->figure;

    QObject::disconnect(CurrentElement->figure, SIGNAL(clicked()), CurrentElement, SLOT(SelectedFigure()) );
    //перемещаем фигуру с одного поля, в другое
    element->AddFigure(CurrentElement->figure);
    //Инкрементируем количество ходов PS нужно для пешки
    CurrentElement->figure->IncrementNumOfMoves();
    emit ChangeMove();

    if(CurrentElement->PlayerClr == WhitePlayer){
        emit WhiteMove();
        emit BlackMove();
        QPair<int, int> From(mapMove(CurrentX, CurrentY));
        QPair<int,int> To(mapMove(element->GetVerticalCoordinate(), element->GetHorizontalCoordinate()));
        emit CheckForCheck(Notation(From, To));
    }else{
        emit BlackMove();
        emit WhiteMove();
        QPair<int, int> From(CurrentX, CurrentY);
        QPair<int,int> To(element->GetVerticalCoordinate(), element->GetHorizontalCoordinate());
        emit CheckForCheck(Notation(From, To));
    }

    //Зануляем все то, чем пользовались
    CurrentElement->figure = nullptr;
    CurrentElement->IsSelect = false;
    CurrentElement = nullptr;
    HidePossibleMoves();

}

QPair<int, int> Logic::mapMove(int x, int y) const
{
    return QPair<int, int>(7 - x, 7 - y);
}


//Очищаем всевозможные ходы
void Logic::HidePossibleMoves()
{
    for(const auto& iter : possibleMoves){
        ChessBoard[iter.first][iter.second]->UnselectThisSquare();
    }
    possibleMoves.clear();
    CurrentX = -1;
    CurrentY = -1;
}

void Logic::MakeMoveTo(const QString &str)
{
    //Считываем x и y для перемещения фигуры
    int x = str[0].digitValue();
    int y = str[1] .digitValue();

    QPair<int,int> OtherBoardCoordinates = this->mapMove(CurrentX, CurrentY);
    QPair<int,int> MoveToOtherBoard = this->mapMove(x, y);

    if(CurrentElement->PlayerClr  == WhitePlayer){
        FieldElement* from = BlackPlayerBoard[OtherBoardCoordinates.first][OtherBoardCoordinates.second];
        FieldElement* MoveTo = BlackPlayerBoard[MoveToOtherBoard.first][MoveToOtherBoard.second];

        if(from->figure)
            QObject::disconnect(from->figure, SIGNAL(clicked()), from, SLOT(SelectedFigure()));
        if(MoveTo->figure)
            QObject::disconnect(MoveTo->figure, SIGNAL(clicked()), MoveTo, SLOT(SelectedFigure()));

        MoveTo->AddFigure(from->figure);
        from->figure = nullptr;
        MoveTo->figure->IncrementNumOfMoves();
    }else{
        FieldElement* from = WhitePlayerBoard[OtherBoardCoordinates.first][OtherBoardCoordinates.second];
        FieldElement* MoveTo = WhitePlayerBoard[MoveToOtherBoard.first][MoveToOtherBoard.second];

        if(from->figure)
            QObject::disconnect(from->figure, SIGNAL(clicked()), from, SLOT(SelectedFigure()));
        if(MoveTo->figure)
            QObject::disconnect(MoveTo->figure, SIGNAL(clicked()), MoveTo, SLOT(SelectedFigure()));


        MoveTo->AddFigure(from->figure);
        from->figure = nullptr;
        MoveTo->figure->IncrementNumOfMoves();
    }

    //Дисконнектим от FieldElement, чтобы он потом не вызывался
    QObject::disconnect(CurrentElement->figure, SIGNAL(clicked()), CurrentElement, SLOT(SelectedFigure()) );

    //перемещаем CurrentElement->figure на позицию x;y
    FieldElement* element = ChessBoard[x][y];
    element->AddFigure(CurrentElement->figure);
    CurrentElement->figure->IncrementNumOfMoves();
    emit ChangeMove();

    if(CurrentElement->PlayerClr == WhitePlayer){
        emit WhiteMove();
        emit BlackMove();
        QPair<int, int>From = mapMove(CurrentX, CurrentY);
        QPair<int, int>To = mapMove(element->GetVerticalCoordinate(), element->GetHorizontalCoordinate());
        emit CheckForCheck(Notation(From, To));
    }else{
        emit BlackMove();
        emit WhiteMove();
        QPair<int, int>From = QPair<int, int>(CurrentX, CurrentY);
        QPair<int, int>To = QPair<int, int>(element->GetVerticalCoordinate(), element->GetHorizontalCoordinate());
        emit CheckForCheck(Notation(From, To));
    }

    CurrentElement->figure = nullptr;
    CurrentElement->IsSelect = false;
    CurrentElement = nullptr;
    HidePossibleMoves();



}

//В случае когда пешка доходит до края доски, функция превращения пешки в другую фигуру
void Logic::TransformPawn(FieldElement *element)
{

}

//Функция Выделения квадратиков доски
void Logic::SelectSquares()
{
    foreach (QSignalMapper* mapper, mappers_) {
        delete mapper;
    }
    mappers_.clear();
    for(const auto& iter : possibleMoves){
        ChessBoard[iter.first][iter.second]->SelectThisSquare();
        QSignalMapper* mapper = new QSignalMapper(this);
        connect(ChessBoard[iter.first][iter.second], SIGNAL(MoveFigureTo()), mapper, SLOT(map()));
        mapper->setMapping(ChessBoard[iter.first][iter.second], QString("%1%2").arg(iter.first).arg(iter.second));
        connect(mapper, SIGNAL(mappedString(QString)), this, SLOT(MakeMoveTo(QString)));
        mappers_.push_back(mapper);
    }
}


//Делать ход, по надписи по типу e4, Ke5 и тд
void Logic::MakeMoveByText(const QString &str)
{

}

void Logic::CheckAllMoves(FieldElement *element, PlayerColor clr)
{
    FigureType Type = element->figure->getType();
    if(clr == WhitePlayer){
        switch (Type) {
        case PAWN:
                if(CurrentX == 0 || CurrentX == 7){
                    TransformPawn(element);
                }
                switch(element->figure->getColor()){
                case BLACK:
                    //Проверка есть ли впереди какая-либо фигура + если нет, то ++возможный ход
                    if(element->figure->getNumOfMoves() == 0){
                        if(ChessBoard[CurrentX + 1][CurrentY]->figure == nullptr){
                            possibleMoves.push_back(QPair<int, int>(CurrentX + 1, CurrentY));
                            if(ChessBoard[CurrentX + 2][CurrentY]->figure == nullptr)
                                possibleMoves.push_back(QPair<int, int>(CurrentX + 2, CurrentY));
                        }
                    }else{
                        if(ChessBoard[CurrentX + 1][CurrentY]->figure == nullptr)
                            possibleMoves.push_back(QPair<int, int>(CurrentX + 1, CurrentY));
                    }

                    //Проверка, есть ли по диагонали фигура оппонента
                    if(CurrentY == 0){
                        if(ChessBoard[CurrentX + 1][CurrentY + 1]->figure != nullptr){
                            if(ChessBoard[CurrentX + 1][CurrentY + 1]->figure->getColor() == WHITE){
                                possibleMoves.push_back(QPair<int,int>(CurrentX + 1, CurrentY + 1));
                            }
                        }
                    }else if(CurrentY == 7){
                        if(ChessBoard[CurrentX + 1][CurrentY -  1]->figure != nullptr){
                            if(ChessBoard[CurrentX + 1][CurrentY - 1]->figure->getColor() == WHITE){
                                possibleMoves.push_back(QPair<int,int>(CurrentX + 1, CurrentY - 1));
                            }
                        }
                    }else{
                        if(ChessBoard[CurrentX + 1][CurrentY -  1]->figure != nullptr){
                            if(ChessBoard[CurrentX + 1][CurrentY - 1]->figure->getColor() == WHITE){
                                possibleMoves.push_back(QPair<int,int>(CurrentX + 1, CurrentY - 1));
                            }
                        }
                        if(ChessBoard[CurrentX + 1][CurrentY + 1]->figure != nullptr){
                            if(ChessBoard[CurrentX + 1][CurrentY + 1]->figure->getColor() == WHITE){
                                possibleMoves.push_back(QPair<int,int>(CurrentX + 1, CurrentY + 1));
                            }
                        }
                    }
                    break;
                case WHITE:

                    //Проверка есть ли впереди какая-либо фигура + если нет, то ++возможный ход
                    if(element->figure->getNumOfMoves() == 0){
                        if(ChessBoard[CurrentX - 1][CurrentY]->figure == nullptr){
                            possibleMoves.push_back(QPair<int, int>(CurrentX - 1, CurrentY));
                            if(ChessBoard[CurrentX - 2][CurrentY]->figure == nullptr)
                                possibleMoves.push_back(QPair<int, int>(CurrentX - 2, CurrentY));
                        }
                    }else{
                        if(ChessBoard[CurrentX - 1][CurrentY]->figure == nullptr)
                            possibleMoves.push_back(QPair<int, int>(CurrentX - 1, CurrentY));
                    }


                    //Проверка, можем ли срубить
                    if(CurrentY == 0){
                        if(ChessBoard[CurrentX - 1][CurrentY + 1]->figure != nullptr){
                            if(ChessBoard[CurrentX - 1][CurrentY + 1]->figure->getColor() == BLACK){
                                possibleMoves.push_back(QPair<int,int>(CurrentX - 1, CurrentY + 1));
                            }
                        }
                    }else if(CurrentY == 7){
                        if(ChessBoard[CurrentX  - 1][CurrentY -  1]->figure != nullptr){
                            if(ChessBoard[CurrentX - 1][CurrentY - 1]->figure->getColor() == BLACK){
                                possibleMoves.push_back(QPair<int,int>(CurrentX - 1, CurrentY - 1));
                            }
                        }
                    }else{
                        if(ChessBoard[CurrentX - 1][CurrentY -  1]->figure != nullptr){
                            if(ChessBoard[CurrentX - 1][CurrentY - 1]->figure->getColor() == BLACK){
                                possibleMoves.push_back(QPair<int,int>(CurrentX - 1, CurrentY - 1));
                            }
                        }
                        if(ChessBoard[CurrentX - 1][CurrentY + 1]->figure != nullptr){
                            if(ChessBoard[CurrentX - 1][CurrentY + 1]->figure->getColor() == BLACK){
                                possibleMoves.push_back(QPair<int,int>(CurrentX - 1, CurrentY + 1));
                            }
                        }
                    }
                    break;
                }
                break;
        case KNIGHT:

            //Проверяем всевозможные восемь ходов для коня
            if(CheckKnightMoves(CurrentX + 2, CurrentY + 1, CurrentElement->figure->getColor())){
                possibleMoves.push_back(QPair<int,int>(CurrentX + 2, CurrentY + 1)) ;
            }
            if(CheckKnightMoves(CurrentX + 2, CurrentY - 1, CurrentElement->figure->getColor())){
                possibleMoves.push_back(QPair<int,int>(CurrentX + 2, CurrentY - 1)) ;
            }
            if(CheckKnightMoves(CurrentX - 2, CurrentY + 1, CurrentElement->figure->getColor())){
                possibleMoves.push_back(QPair<int,int>(CurrentX - 2, CurrentY + 1)) ;
            }
            if(CheckKnightMoves(CurrentX - 2, CurrentY - 1, CurrentElement->figure->getColor())){
                possibleMoves.push_back(QPair<int,int>(CurrentX - 2, CurrentY -1)) ;
            }
            if(CheckKnightMoves(CurrentX + 1, CurrentY + 2, CurrentElement->figure->getColor())){
                possibleMoves.push_back(QPair<int,int>(CurrentX + 1, CurrentY + 2)) ;
            }
            if(CheckKnightMoves(CurrentX - 1, CurrentY + 2, CurrentElement->figure->getColor())){
                possibleMoves.push_back(QPair<int,int>(CurrentX - 1, CurrentY + 2)) ;
            }
            if(CheckKnightMoves(CurrentX + 1, CurrentY - 2,CurrentElement->figure->getColor())){
                possibleMoves.push_back(QPair<int,int>(CurrentX + 1, CurrentY - 2)) ;
            }
            if(CheckKnightMoves(CurrentX - 1, CurrentY - 2, CurrentElement->figure->getColor())){
                possibleMoves.push_back(QPair<int,int>(CurrentX - 1, CurrentY - 2)) ;
            }
            break;
        case KING:
            CheckKingMoves(CurrentElement->figure->getColor());
            break;
        case QUEEN:
            CheckBishopMoves(CurrentElement->figure->getColor());
            CheckRookMoves(CurrentElement->figure->getColor());
            break;
        case BISHOP:
            CheckBishopMoves(CurrentElement->figure->getColor());
            break;
        case ROOK:
            CheckRookMoves(CurrentElement->figure->getColor());
            break;
        default:
            break;
        }
        SelectSquares();
    }
    else{
            switch (Type) {
            case PAWN:
                    if(CurrentX == 0 || CurrentX == 7){
                        TransformPawn(element);
                    }
                    switch(element->figure->getColor()){
                    case WHITE:
                        //Проверка есть ли впереди какая-либо фигура + если нет, то ++возможный ход
                        if(element->figure->getNumOfMoves() == 0){
                            if(ChessBoard[CurrentX + 1][CurrentY]->figure == nullptr){
                                possibleMoves.push_back(QPair<int, int>(CurrentX + 1, CurrentY));
                                if(ChessBoard[CurrentX + 2][CurrentY]->figure == nullptr)
                                    possibleMoves.push_back(QPair<int, int>(CurrentX + 2, CurrentY));
                            }
                        }else{
                            if(ChessBoard[CurrentX + 1][CurrentY]->figure == nullptr)
                                possibleMoves.push_back(QPair<int, int>(CurrentX + 1, CurrentY));
                        }

                        //Проверка, есть ли по диагонали фигура оппонента
                        if(CurrentY == 0){
                            if(ChessBoard[CurrentX + 1][CurrentY + 1]->figure != nullptr){
                                if(ChessBoard[CurrentX + 1][CurrentY + 1]->figure->getColor() == WHITE){
                                    possibleMoves.push_back(QPair<int,int>(CurrentX + 1, CurrentY + 1));
                                }
                            }
                        }else if(CurrentY == 7){
                            if(ChessBoard[CurrentX + 1][CurrentY -  1]->figure != nullptr){
                                if(ChessBoard[CurrentX + 1][CurrentY - 1]->figure->getColor() == WHITE){
                                    possibleMoves.push_back(QPair<int,int>(CurrentX + 1, CurrentY - 1));
                                }
                            }
                        }else{
                            if(ChessBoard[CurrentX + 1][CurrentY -  1]->figure != nullptr){
                                if(ChessBoard[CurrentX + 1][CurrentY - 1]->figure->getColor() == WHITE){
                                    possibleMoves.push_back(QPair<int,int>(CurrentX + 1, CurrentY - 1));
                                }
                            }
                            if(ChessBoard[CurrentX + 1][CurrentY + 1]->figure != nullptr){
                                if(ChessBoard[CurrentX + 1][CurrentY + 1]->figure->getColor() == WHITE){
                                    possibleMoves.push_back(QPair<int,int>(CurrentX + 1, CurrentY + 1));
                                }
                            }
                        }
                        break;
                    case BLACK:

                        //Проверка есть ли впереди какая-либо фигура + если нет, то ++возможный ход
                        if(element->figure->getNumOfMoves() == 0){
                            if(ChessBoard[CurrentX - 1][CurrentY]->figure == nullptr){
                                possibleMoves.push_back(QPair<int, int>(CurrentX - 1, CurrentY));
                                if(ChessBoard[CurrentX - 2][CurrentY]->figure == nullptr)
                                    possibleMoves.push_back(QPair<int, int>(CurrentX - 2, CurrentY));
                            }
                        }else{
                            if(ChessBoard[CurrentX - 1][CurrentY]->figure == nullptr)
                                possibleMoves.push_back(QPair<int, int>(CurrentX - 1, CurrentY));
                        }


                        //Проверка, можем ли срубить
                        if(CurrentY == 0){
                            if(ChessBoard[CurrentX - 1][CurrentY + 1]->figure != nullptr){
                                if(ChessBoard[CurrentX - 1][CurrentY + 1]->figure->getColor() == WHITE){
                                    possibleMoves.push_back(QPair<int,int>(CurrentX - 1, CurrentY + 1));
                                }
                            }
                        }else if(CurrentY == 7){
                            if(ChessBoard[CurrentX  - 1][CurrentY -  1]->figure != nullptr){
                                if(ChessBoard[CurrentX - 1][CurrentY - 1]->figure->getColor() == WHITE){
                                    possibleMoves.push_back(QPair<int,int>(CurrentX - 1, CurrentY - 1));
                                }
                            }
                        }else{
                            if(ChessBoard[CurrentX - 1][CurrentY -  1]->figure != nullptr){
                                if(ChessBoard[CurrentX - 1][CurrentY - 1]->figure->getColor() == WHITE){
                                    possibleMoves.push_back(QPair<int,int>(CurrentX - 1, CurrentY - 1));
                                }
                            }
                            if(ChessBoard[CurrentX - 1][CurrentY + 1]->figure != nullptr){
                                if(ChessBoard[CurrentX - 1][CurrentY + 1]->figure->getColor() == WHITE){
                                    possibleMoves.push_back(QPair<int,int>(CurrentX - 1, CurrentY + 1));
                                }
                            }
                        }
                        break;
                    }
                    break;
            case KNIGHT:

                //Проверяем всевозможные восемь ходов для коня
                if(CheckKnightMoves(CurrentX + 2, CurrentY + 1, CurrentElement->figure->getColor())){
                    possibleMoves.push_back(QPair<int,int>(CurrentX + 2, CurrentY + 1)) ;
                }
                if(CheckKnightMoves(CurrentX + 2, CurrentY - 1, CurrentElement->figure->getColor())){
                    possibleMoves.push_back(QPair<int,int>(CurrentX + 2, CurrentY - 1)) ;
                }
                if(CheckKnightMoves(CurrentX - 2, CurrentY + 1, CurrentElement->figure->getColor())){
                    possibleMoves.push_back(QPair<int,int>(CurrentX - 2, CurrentY + 1)) ;
                }
                if(CheckKnightMoves(CurrentX - 2, CurrentY - 1, CurrentElement->figure->getColor())){
                    possibleMoves.push_back(QPair<int,int>(CurrentX - 2, CurrentY -1)) ;
                }
                if(CheckKnightMoves(CurrentX + 1, CurrentY + 2, CurrentElement->figure->getColor())){
                    possibleMoves.push_back(QPair<int,int>(CurrentX + 1, CurrentY + 2)) ;
                }
                if(CheckKnightMoves(CurrentX - 1, CurrentY + 2, CurrentElement->figure->getColor())){
                    possibleMoves.push_back(QPair<int,int>(CurrentX - 1, CurrentY + 2)) ;
                }
                if(CheckKnightMoves(CurrentX + 1, CurrentY - 2,CurrentElement->figure->getColor())){
                    possibleMoves.push_back(QPair<int,int>(CurrentX + 1, CurrentY - 2)) ;
                }
                if(CheckKnightMoves(CurrentX - 1, CurrentY - 2, CurrentElement->figure->getColor())){
                    possibleMoves.push_back(QPair<int,int>(CurrentX - 1, CurrentY - 2)) ;
                }
                break;
            case KING:
                CheckKingMoves(CurrentElement->figure->getColor());
                break;
            case QUEEN:
                CheckBishopMoves(CurrentElement->figure->getColor());
                CheckRookMoves(CurrentElement->figure->getColor());
                break;
            case BISHOP:
                CheckBishopMoves(CurrentElement->figure->getColor());
                break;
            case ROOK:
                CheckRookMoves(CurrentElement->figure->getColor());
                break;
            default:
                break;
        }
        SelectSquares();
     }
 }

//Возращает true, если ход приемлимый
bool Logic::CheckKnightMoves(int x, int y, COLOR clr)
{
      if(x < 0 || y < 0 || x > 7 || y > 7){
          return false;
      }
      if(ChessBoard[x][y]->figure != nullptr){
          if(ChessBoard[x][y]->figure->getColor() == clr){
              return false;
          }
      }

      return true;
}

//Наполняет массив possibleMoves всеми ходами для Ладьи
void Logic::CheckRookMoves(COLOR clr)
{
    {
        int x = CurrentX - 1;
        int y = CurrentY;

        while(x >= 0){
            if(ChessBoard[x][y]->figure != nullptr){
                if(ChessBoard[x][y]->figure->getColor() == clr){
                    break;
                }
                possibleMoves.push_back(QPair<int,int>(x, y));
                break;
            }
            possibleMoves.push_back(QPair<int,int>(x, y));
            x--;
        }
    }

    {
        int x = CurrentX + 1;
        int y = CurrentY;

        while(x < 8){
            if(ChessBoard[x][y]->figure != nullptr){
                if(ChessBoard[x][y]->figure->getColor() == clr){
                    break;
                }
                possibleMoves.push_back(QPair<int,int>(x, y));
                break;
            }
            possibleMoves.push_back(QPair<int,int>(x, y));
            x++;
        }
    }

    {
        int x = CurrentX;
        int y = CurrentY - 1;

        while(y >= 0){
            if(ChessBoard[x][y]->figure != nullptr){
                if(ChessBoard[x][y]->figure->getColor() == clr){
                    break;
                }
                possibleMoves.push_back(QPair<int,int>(x, y));
                break;
            }
            possibleMoves.push_back(QPair<int,int>(x, y));
            y--;
        }
    }

    {
        int x = CurrentX;
        int y = CurrentY + 1;

        while(y < 8){
            if(ChessBoard[x][y]->figure != nullptr){
                if(ChessBoard[x][y]->figure->getColor() == clr){
                    break;
                }
                possibleMoves.push_back(QPair<int,int>(x, y));
                break;
            }
            possibleMoves.push_back(QPair<int,int>(x, y));
            y++;
        }
    }


}

void Logic::CheckBishopMoves(COLOR clr) {
    const int BOARD_SIZE = 8;

    // Top-left to bottom-right
    int x = CurrentX + 1;
    int y = CurrentY + 1;
    while (x < BOARD_SIZE && y < BOARD_SIZE) {
        if (ChessBoard[x][y]->figure != nullptr) {
            if (ChessBoard[x][y]->figure->getColor() != clr) {
                possibleMoves.push_back(QPair<int, int>(x, y));
            }
            break;
        }
        possibleMoves.push_back(QPair<int, int>(x, y));
        x++;
        y++;
    }

    // Top-right to bottom-left
    x = CurrentX + 1;
    y = CurrentY - 1;
    while (x < BOARD_SIZE && y >= 0) {
        if (ChessBoard[x][y]->figure != nullptr) {
            if (ChessBoard[x][y]->figure->getColor() != clr) {
                possibleMoves.push_back(QPair<int, int>(x, y));
            }
            break;
        }
        possibleMoves.push_back(QPair<int, int>(x, y));
        x++;
        y--;
    }

    // Bottom-left to top-right
    x = CurrentX - 1;
    y = CurrentY + 1;
    while (x >= 0 && y < BOARD_SIZE) {
        if (ChessBoard[x][y]->figure != nullptr) {
            if (ChessBoard[x][y]->figure->getColor() != clr) {
                possibleMoves.push_back(QPair<int, int>(x, y));
            }
            break;
        }
        possibleMoves.push_back(QPair<int, int>(x, y));
        x--;
        y++;
    }

    // Bottom-right to top-left
    x = CurrentX - 1;
    y = CurrentY - 1;
    while (x >= 0 && y >= 0) {
        if (ChessBoard[x][y]->figure != nullptr) {
            if (ChessBoard[x][y]->figure->getColor() != clr) {
                possibleMoves.push_back(QPair<int, int>(x, y));
            }
            break;
        }
        possibleMoves.push_back(QPair<int, int>(x, y));
        x--;
        y--;
    }
}

void Logic::CheckKingMoves(COLOR clr)
{
    int x = CurrentX;
    int y = CurrentY;

    if(x + 1 <= 7){
        if (ChessBoard[x + 1][y]->figure != nullptr) {
            if (ChessBoard[x + 1][y]->figure->getColor() != clr) {
                possibleMoves.push_back(QPair<int, int>(x + 1, y));
            }
        }else
            possibleMoves.push_back(QPair<int, int>(x + 1, y));
    }
    if(x - 1 >= 0){
        if (ChessBoard[x - 1][y]->figure != nullptr) {
            if (ChessBoard[x - 1][y]->figure->getColor() != clr) {
                possibleMoves.push_back(QPair<int, int>(x - 1, y));
            }
        }else
            possibleMoves.push_back(QPair<int, int>(x - 1, y));
    }
    if(y + 1 <= 7){
        if (ChessBoard[x][y + 1]->figure != nullptr) {
            if (ChessBoard[x][y + 1]->figure->getColor() != clr) {
                possibleMoves.push_back(QPair<int, int>(x, y + 1));
            }
        }else
            possibleMoves.push_back(QPair<int, int>(x, y + 1));
    }
    if (y - 1 >= 0){
        if (ChessBoard[x][y - 1]->figure != nullptr) {
            if (ChessBoard[x][y - 1]->figure->getColor() != clr) {
                possibleMoves.push_back(QPair<int, int>(x, y - 1));
            }
        }else
            possibleMoves.push_back(QPair<int, int>(x, y - 1));
    }
    if(x + 1 <=7 && y + 1 <=7){
        if (ChessBoard[x + 1][y + 1]->figure != nullptr) {
            if (ChessBoard[x + 1][y + 1]->figure->getColor() != clr) {
                possibleMoves.push_back(QPair<int, int>(x + 1, y + 1));
            }
        }else
            possibleMoves.push_back(QPair<int, int>(x + 1, y + 1));
    }
    if(x - 1 >= 0 && y + 1 <=7){
        if (ChessBoard[x - 1][y + 1]->figure != nullptr) {
            if (ChessBoard[x - 1][y + 1]->figure->getColor() != clr) {
                possibleMoves.push_back(QPair<int, int>(x - 1, y + 1));
            }
        }else
            possibleMoves.push_back(QPair<int, int>(x - 1, y + 1));
    }
    if(x + 1 <=7 && y - 1 >= 0){
        if (ChessBoard[x + 1][y - 1]->figure != nullptr) {
            if (ChessBoard[x + 1][y - 1]->figure->getColor() != clr) {
                possibleMoves.push_back(QPair<int, int>(x + 1, y - 1));
            }
        }else
            possibleMoves.push_back(QPair<int, int>(x + 1, y - 1));
    }
    if(x - 1 >= 0 && y - 1 >= 0){
        if (ChessBoard[x - 1][y - 1]->figure != nullptr) {
            if (ChessBoard[x - 1][y - 1]->figure->getColor() != clr) {
                possibleMoves.push_back(QPair<int, int>(x- 1, y - 1));
            }
        }else
            possibleMoves.push_back(QPair<int, int>(x - 1, y - 1));
    }
}

QString Logic::Notation(QPair<int, int> From, QPair<int, int> To)
{
    QString notation;

    // Convert the from square to algebraic notation
    notation += QChar('a' + From.first);
    notation += QString::number(8 - From.second);

    // Convert the to square to algebraic notation
    notation += QChar('a' + To.first);
    notation += QString::number(8 - To.second);

    return notation;
}

int Logic::GetNumberOfMoves(){return NumberOfMoves;}
