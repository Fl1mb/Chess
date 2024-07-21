#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QStackedLayout>
#include "board.h"
#include <QLabel>
#include "checker.h"

class Game: public QWidget
{
    Q_OBJECT
public:
    explicit Game(QWidget* parent = nullptr);
    ~Game();


public slots:
    void ChangeText();

protected:

private:
    Board* WhiteBoard;
    Board* BlackBoard;
    QVBoxLayout* layout;
    QStackedLayout* Stack;
    QWidget* wgt;
    QLabel* WhoGo;
    Logic* logic;


    bool IsWhiteMove{true};

};

#endif // GAME_H
