#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QPainter>

#include "card.h"
#include "ai.h"

class Player : public QGraphicsItem
{
public:
    enum {Type = UserType + 3}; // Need it for qgraphicsitem_cast() with a custom item

    Player(QString name);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void setCoordinate(QPoint coordinate);
    QPoint coordinate() const {return myCorrdinate;}
    int type() const override {return Type;}

    QString name() const {return myName;}

    void setLock(bool lock);
    bool isLocked() const {return locked;}

    void addCards(QVector<Card *> cards);
    Card *getCard();
    QVector<Card *> myCards() const {return my_cards;}

    void setAI();

private:
    QString myName;
    QPoint myCorrdinate; // Position in the gameboard
    bool locked {false};
    QVector<Card *> my_cards;
    AI myAI;
};

#endif // PLAYER_H
