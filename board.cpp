#include "board.h"
#include <QLabel>
#include <QGraphicsProxyWidget>
#include "figure.h"

PlayerColor Board::CurrentPlayer = WhitePlayer;

Board::Board(PlayerColor color_, Logic* logic_): color(color_), logic(logic_)
{
    //Inizialize scene
    scene = new QGraphicsScene();

    //inizialize Figures + packing them into scene
    for (int row = 0; row < 8; row ++){
        QVector<FieldElement*> temp;

        for(int col = 0; col < 8;  col ++){
            //inizialize
            FieldElement* element = new FieldElement(row, col,(row+col)%2 == 0? WHITE : BLACK,  color);
            element->setRect(col * 75, row * 75, 75, 75);
            element->setPos(col * 75, row * 75);
            element->SetVerticalCoordinate(row);
            element->SetHorizontalCoordinate(col);
            
            connect(element, &FieldElement::ShowPossibleMoves, logic, &Logic::ShowPossibleMoves);
            connect(element, SIGNAL(HidePossibleMoves()) , logic, SLOT(HidePossibleMoves()));
            connect(element, &FieldElement::KillThisFigure , logic, &Logic::KillFigure);

            //Добавляем на сцену объект поля
            scene->addItem(element);


            //push_back into vector
            temp.push_back(element);

        }
        FieldSquares.push_back(temp);
    }



    scene->setSceneRect(0, 0, 600, 600);

    setScene(scene);

    //Отключаем Скролл бар
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //Устанавливаем размер и режим рисования
    setFixedSize(600, 600);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setTransform(QTransform());
    setRenderHint(QPainter::SmoothPixmapTransform);
    setRenderHint(QPainter::Antialiasing);

    SetArrangement();

}

void Board::SetArrangement()
{

    if(color == WhitePlayer){
        for(int i = 0; i < 8; i++){
            FieldSquares[1][i]->AddFigure(PAWN, BLACK, BlackFigures);
            FieldSquares[6][i]->AddFigure(PAWN,WHITE, WhiteFigures);
        }

        for (int i = 0; i < 4; i ++ ){
            switch(i){
            case 0:
                FieldSquares[0][i]->AddFigure(ROOK, BLACK,BlackFigures);
                FieldSquares[0][7 - i]->AddFigure(ROOK, BLACK, BlackFigures);
                FieldSquares[7][i]->AddFigure(ROOK, WHITE, WhiteFigures);
                FieldSquares[7][7 - i]->AddFigure(ROOK, WHITE, WhiteFigures);
                break;
            case 1:
                FieldSquares[0][i]->AddFigure(KNIGHT, BLACK, BlackFigures);
                FieldSquares[0][7 - i]->AddFigure(KNIGHT, BLACK, BlackFigures);
                FieldSquares[7][i]->AddFigure(KNIGHT, WHITE, WhiteFigures);
                FieldSquares[7][7 - i]->AddFigure(KNIGHT, WHITE, WhiteFigures);
                break;
            case 2:
                FieldSquares[0][i]->AddFigure(BISHOP, BLACK, BlackFigures);
                FieldSquares[0][7 - i]->AddFigure(BISHOP, BLACK, BlackFigures);
                FieldSquares[7][i]->AddFigure(BISHOP, WHITE, WhiteFigures);
                FieldSquares[7][7 - i]->AddFigure(BISHOP, WHITE, WhiteFigures);
                break;
            case 3:
                FieldSquares[0][i]->AddFigure(QUEEN, BLACK, BlackFigures);
                FieldSquares[0][7 - i]->AddFigure(KING, BLACK, BlackFigures);
                FieldSquares[7][i]->AddFigure(QUEEN, WHITE, WhiteFigures);
                FieldSquares[7][7 - i]->AddFigure(KING, WHITE, WhiteFigures);
                break;
            }
        }
    }else{

        for(int i = 0; i < 8; i++){
            FieldSquares[1][i]->AddFigure(PAWN, WHITE, WhiteFigures);
            FieldSquares[6][i]->AddFigure(PAWN,BLACK, BlackFigures);
        }
        for (int i = 0; i < 4; i ++ ){
            switch(i){
            case 0:
                FieldSquares[0][i]->AddFigure(ROOK, WHITE,WhiteFigures);
                FieldSquares[0][7 - i]->AddFigure(ROOK, WHITE, WhiteFigures);
                FieldSquares[7][i]->AddFigure(ROOK, BLACK, BlackFigures);
                FieldSquares[7][7 - i]->AddFigure(ROOK, BLACK, BlackFigures);
                break;
            case 1:
                FieldSquares[0][i]->AddFigure(KNIGHT, WHITE, WhiteFigures);
                FieldSquares[0][7 - i]->AddFigure(KNIGHT, WHITE, WhiteFigures);
                FieldSquares[7][i]->AddFigure(KNIGHT, BLACK, BlackFigures);
                FieldSquares[7][7 - i]->AddFigure(KNIGHT, BLACK, BlackFigures);
                break;
            case 2:
                FieldSquares[0][i]->AddFigure(BISHOP, WHITE, WhiteFigures);
                FieldSquares[0][7 - i]->AddFigure(BISHOP, WHITE, WhiteFigures);
                FieldSquares[7][i]->AddFigure(BISHOP, BLACK, BlackFigures);
                FieldSquares[7][7 - i]->AddFigure(BISHOP, BLACK, BlackFigures);
                break;
            case 3:
                FieldSquares[0][7 - i]->AddFigure(QUEEN, WHITE, WhiteFigures);
                FieldSquares[0][i]->AddFigure(KING, WHITE, WhiteFigures);
                FieldSquares[7][7 - i]->AddFigure(QUEEN, BLACK, BlackFigures);
                FieldSquares[7][i]->AddFigure(KING, BLACK, BlackFigures);
                break;
            }
        }
    }

    if(color == WhitePlayer){
        foreach (Figure* fig, BlackFigures ) {
            fig->setEnabled(false);
        }
        foreach (Figure* fig, WhiteFigures) {
            fig->setEnabled(false);
        }
    }
    else{
        foreach (Figure* fig, WhiteFigures ) {
            fig->setEnabled(false);
        }
    }
    logic->setBoard(FieldSquares, color);
    SetFiguresEnable();
}

void Board::SetFiguresEnable(){
    if(this->color == WhitePlayer){
        foreach (Figure* fig, WhiteFigures) {
            fig->setEnabled(!fig->isEnabled());
        }
    }else{
        foreach (Figure* fig, BlackFigures) {
            fig->setEnabled(!fig->isEnabled());
        }
    }
}

void Board::DeleteElement(Figure *fig, COLOR clr)
{
    if(clr == WHITE){
        for(int i = 0 ; i < WhiteFigures.size(); i++){
            if(WhiteFigures[i] == fig){
                WhiteFigures.remove(i);
            }
        }
    }else{
        for(int i = 0 ; i < BlackFigures.size(); i++){
            if(BlackFigures[i] == fig){
                BlackFigures.remove(i);
            }
        }
    }
}





