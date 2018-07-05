#include "card.h"

Card::Card(int name) : numToDraw{name}
{
}

QRectF Card::boundingRect() const
{
    // Always adjust the boundingRect with the pen width
    return QRectF(0-PENWIDTH/2, 0-PENWIDTH/2, 60+PENWIDTH, 100+PENWIDTH);
}

void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setWidth(PENWIDTH);
    pen.setColor(Qt::black);

    painter->setRenderHint(QPainter::Antialiasing);

    if (visible)
    {
        if (numToDraw != 0)
        {
            // Draw the card
            painter->setPen(pen);
            painter->setBrush(QColor(Qt::white));
            painter->drawRoundedRect(boundingRect(), 15, 15);

            // Draw the name
            QString s = QString::number(numToDraw);
            painter->setPen(QColor(Qt::black));
            painter->setFont(QFont("Verdana", 12));
            painter->drawText(boundingRect(), Qt::AlignCenter, s);
        }
    }
    else
    {
        // If not visible, draw the back side of the card
        QBrush brush;
        brush.setColor(myColor);
        brush.setStyle(Qt::SolidPattern);

        painter->setPen(pen);
        painter->setBrush(brush);
        painter->drawRoundedRect(boundingRect(), 15, 15);
    }
}

void Card::setColor(const QColor &color)
{
    myColor = color;
}

void Card::setVisible(bool state)
{
    visible = state;
}
