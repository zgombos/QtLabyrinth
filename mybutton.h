#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QFont>

class MyButton : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    MyButton(QRectF size, QString name, QGraphicsItem *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event) override;

private:
    QGraphicsTextItem *text;
    QColor DarkOrange {250, 110, 0};
    QColor LightOrange {250, 200, 10};

signals:
    void onClick();
};

#endif // MYBUTTON_H
