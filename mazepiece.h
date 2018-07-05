#ifndef MAZEPIECE_H
#define MAZEPIECE_H

#include <QGraphicsItem>
#include <QPainter>

enum class Treasure {NOTHING,
                     Bag_of_Gold_Coins, Bat, Book, Dragon, Ghost_in_bottle, Ghost_waving,
                     Gold_Crown, Gold_Menorah, Gold_Ring, Helmet, Jewel, Lady_Pig,
                     Lizard, Moth, Owl, Rat, Scarab, Keys,
                     Skull, Sorceress, Spider, Sword, Treasure_Chest, Treasure_Map};

/*
 * 16 fix Maze cards:
 *  - [x15] L Shape (x6 with treasure)
 *  - [x6] T Shape with treasure
 *  - [x13] I Shape
 *
 * 34 movable Maze cards:
 *  - [x6] L Shape with treasure
 *  - [x6] T Shape with treasure
 *  - [x9] L Shape empty
 *  - [x13] I Shape empty
 */
class MazePiece : public QGraphicsItem
{
public:
    enum {Type = UserType + 4}; // Need it for qgraphicsitem_cast() with a custom item

    MazePiece(QVector<QVector<int>> &shape, Treasure treasure, QString player="None");

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void turnLeft();
    void turnRight();
    QVector<int> path();
    int treasure() const {return numToDraw;}
    int type() const override {return Type;}

private:
    QVector<QVector<int>> my_shape;
    Treasure my_treasure;
    QString my_player;
    QVector<QVector<QRect>> coordinateList;
    qreal penWidth = 2;
    int numToDraw{0};
};

#endif // MAZEPIECE_H
