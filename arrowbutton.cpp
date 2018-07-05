#include "arrowbutton.h"

ArrowButton::ArrowButton(int type, int posToChange, QGraphicsItem *parent) : QGraphicsItem(parent)
{
    myType = type;
    pos = posToChange;

   // Enable the hover event
   setAcceptHoverEvents(true);
}

QRectF ArrowButton::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(0-penWidth/2, 0-penWidth/2, 30+penWidth, 15+penWidth);
}

void ArrowButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (!locked && !sessionLock && hover)
    {
        painter->setBrush(QColor(ORANGE));
        painter->setPen(QColor(ORANGE));
    }
    else if (locked)
    {
        painter->setBrush(QColor(Qt::gray));
        painter->setPen(QColor(Qt::gray));
    }
    else if (sessionLock)
    {
        painter->setBrush(QColor(Qt::blue));
        painter->setPen(QColor(Qt::blue));
    }
    else
    {
        painter->setBrush(QColor(Qt::red));
        painter->setPen(QColor(Qt::red));
    }
    QPainterPath path;
    path.moveTo(0, 0);
    path.lineTo(30, 0);
    path.lineTo(15, 15);
    path.closeSubpath();
    painter->drawPath(path);
}

void ArrowButton::setLock(bool lock)
{
    locked = lock;
}

void ArrowButton::setSessionLock(bool lock)
{
    sessionLock = lock;
}

void ArrowButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!locked && !sessionLock)
        emit onClick(myType, pos);
}

void ArrowButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    // Change the arrow color
    hover = true;
    update();
}

void ArrowButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // Change the arrow color
    hover = false;
    update();
}
