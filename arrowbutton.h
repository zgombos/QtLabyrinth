#ifndef ARROWBUTTON_H
#define ARROWBUTTON_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QColor>

class ArrowButton : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    enum {Type = UserType + 1};
    ArrowButton(int type, int posToChange, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    int type() const override {return Type;}

    void setLock(bool lock);
    bool isLocked() const {return locked;}

    void setSessionLock(bool lock);
    bool isSessionLocked() const {return sessionLock;}


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event) override;

private:
    int pos; // row or column to move
    int myType;
    bool hover {false};
    bool locked {false};
    bool sessionLock {false};
    QColor ORANGE {250, 200, 10};

signals:
    void onClick(int id, int posToChange);
};

#endif // ARROWBUTTON_H
