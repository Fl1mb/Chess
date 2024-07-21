#include "game.h"
#include <cassert>


Game::Game(QWidget *parent) : QWidget(parent)
{
    logic = new Logic();


    WhiteBoard = new Board(WhitePlayer, logic);
    BlackBoard = new Board(BlackPlayer, logic);

    QObject::connect(logic, SIGNAL(WhiteMove()), WhiteBoard, SLOT(SetFiguresEnable()));
    QObject::connect(logic, SIGNAL(BlackMove()), BlackBoard, SLOT(SetFiguresEnable()));
    QObject::connect(logic, SIGNAL(DeleteFigureBlackBoard(Figure*,COLOR)), BlackBoard, SLOT(DeleteElement(Figure*,COLOR)));
    QObject::connect(logic, SIGNAL(DeleteFigureWhiteBoard(Figure*,COLOR)), WhiteBoard, SLOT(DeleteElement(Figure*,COLOR)));
    QObject::connect(logic, SIGNAL(ChangeMove()), this, SLOT(ChangeText()));


    connect(WhiteBoard, &Board::Change, this, &Game::ChangeText);
    connect(BlackBoard, &Board::Change, this, &Game::ChangeText);

    WhoGo = new QLabel("<CENTER>ХОД БЕЛЫХ<CENTER>");
    QFont font("Times New Roman", 16);
    WhoGo->setFont(font);


    wgt = new QWidget();
    layout = new QVBoxLayout;
    Stack = new QStackedLayout;
    Stack->addWidget(WhiteBoard);
    Stack->addWidget(BlackBoard);
    wgt->setLayout(Stack);

    layout->addWidget(WhoGo);
    layout->addWidget(wgt);

    this->setLayout(layout);
    this->show();

}

Game::~Game()
{
    delete WhiteBoard;
    delete BlackBoard;
    delete layout;
    delete Stack;
    delete wgt;
    delete WhoGo;
    delete logic;
}

void Game::ChangeText()
{
    if(IsWhiteMove){
        WhoGo->setText("<CENTER>ХОД ЧЕРНЫХ<CENTER>");
        Stack->setCurrentIndex(1);
    }else{
        WhoGo->setText("<CENTER>ХОД БЕЛЫХ<CENTER>");
        Stack->setCurrentIndex(0);
    }
    IsWhiteMove = !IsWhiteMove;

}

