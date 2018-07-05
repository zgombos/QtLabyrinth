#include "player.h"

Player::Player(QString name) : myName{name}
{
    setFlag(GraphicsItemFlag::ItemSendsGeometryChanges, true);
}

QRectF Player::boundingRect() const
{
    return QRectF(0, 0, 70, 70);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     QRectF source(0, 0, 96, 96);
     QRectF target(0, 0, 70, 70);
     QPixmap image;
     if (myName == "RED")
        image.load(":/images/player_red.png");
     else if (myName == "BLUE")
        image.load(":/images/player_blue.png");
     else if (myName == "YELLOW")
        image.load(":/images/player_yellow.png");
     else if (myName == "GREEN")
        image.load(":/images/player_green.png");

     painter->drawPixmap(target, image, source);
}

void Player::setCoordinate(QPoint coordinate)
{
    myCorrdinate = coordinate;
}

void Player::setLock(bool lock)
{
    locked = lock;
}

void Player::addCards(QVector<Card *> cards)
{
    my_cards = cards;
}

Card* Player::getCard()
{
    if (!my_cards.isEmpty())
    {
        my_cards.takeFirst();
    }
}

void Player::setAI()
{
    AI *myAI = new AI();
}

