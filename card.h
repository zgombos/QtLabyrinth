#ifndef CARD_H
#define CARD_H

#include <QGraphicsItem>
#include <QPainter>

class Card : public QGraphicsItem
{
public:
    Card(int name);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    int name() const {return numToDraw;}

    void setColor(const QColor &color);

    void setVisible(bool state);
    bool isVisible() const {return visible;}

private:
    int numToDraw{0};
    bool visible {false};
    qreal PENWIDTH{2};
    QColor myColor;
};

#endif // CARD_H
