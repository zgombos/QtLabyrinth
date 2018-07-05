#include "mybutton.h"

MyButton::MyButton(QRectF size, QString name, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    // Draw the button
    setRect(size);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(DarkOrange);
    setBrush(brush);

    // Draw the text (Add self to QGraphicsTextItem to be draw on the scene)
    text = new QGraphicsTextItem(name, this);
    qreal x = rect().width()/2 - text->boundingRect().width()/2;
    qreal y = rect().height()/2 - text->boundingRect().height()/2;

    QFont font;
    font.setBold(true);
    text->setFont(font);
    text->setPos(x, y);

    // Enable the hover event
    setAcceptHoverEvents(true);

}

void MyButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit onClick();
}

void MyButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    // Change the color if the mouse hover
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(LightOrange);
    setBrush(brush);
}

void MyButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // Change the color back
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(DarkOrange);
    setBrush(brush);
}
