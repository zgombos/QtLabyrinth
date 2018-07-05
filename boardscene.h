#ifndef BOARDSCENE_H
#define BOARDSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QSignalMapper>
#include <QMessageBox>
#include <QDebug>

#include "arrowbutton.h"
#include "mybutton.h"
#include "gameboard.h"
#include "player.h"
#include "card.h"


class BoardScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit BoardScene();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    GameBoard *gameBoard;

    ArrowButton *top1_arrow;
    ArrowButton *top2_arrow;
    ArrowButton *top3_arrow;
    ArrowButton *bottom1_arrow;
    ArrowButton *bottom2_arrow;
    ArrowButton *bottom3_arrow;
    ArrowButton *left1_arrow;
    ArrowButton *left2_arrow;
    ArrowButton *left3_arrow;
    ArrowButton *right1_arrow;
    ArrowButton *right2_arrow;
    ArrowButton *right3_arrow;
    QVector<ArrowButton *> lockList;
    QVector<ArrowButton *> sessionLockList;

    Player *RedPlayer;
    Player *GreenPlayer;
    Player *YellowPlayer;
    Player *BluePlayer;
    QVector<Player *> playerList;
    QVector<Player *> playerCheckList;
    Player *currentPlayer {nullptr};
    QGraphicsTextItem *playerTrackerText;

    QVector <Card *> cardList;

    void newGame();
    void setupGUI();
    void setupGameBoard();
    void setupArrowButtons();
    void setupPlayers();
    void setupCards();
    void shuffleCards();
    void updateCardDeck(Player *player);
    void updateGameBoard();
    void lockArrowButton(ArrowButton *button1, ArrowButton *button2);
    void setSessionArrowLockState(bool lock);
    void movePlayer(Player *player, QPoint newPos);
    void stickPlayer(QString direction, int boardPos);
    void setPlayerLockState(bool lock);
    void changePlayer(Player *player);

public slots:
    void turnMazeLeft();
    void turnMazeRight();
    void moveRowLeft(int id, int pos);
    void moveRowRight(int id, int pos);
    void moveColUp(int id, int pos);
    void moveColDown(int id, int pos);
};

#endif // BOARDSCENE_H
