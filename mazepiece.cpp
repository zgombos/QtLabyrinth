#include "mazepiece.h"

MazePiece::MazePiece(QVector<QVector<int>> &shape, Treasure treasure, QString player)
{
    my_shape = shape;
    my_treasure = treasure;
    my_player = player;

    // Setup the coordinates
    int tx = 0; int ty = 0;
    int  bx = 30; int by = 30;
    for (int i{0}; i<3; ++i)
    {
        QVector<QRect> tmp;
        for (int j{0}; j<3; ++j)
        {
            QRect pos(tx, ty, bx, by);
            tmp.append(pos);
            tx += 30;
        }
        // Build a list of list
        coordinateList.append(tmp);
        ty += 30;
        tx -= 90;
    }
}

QRectF MazePiece::boundingRect() const
{
    return QRectF(0-penWidth/2, 0-penWidth/2, 90+penWidth, 90+penWidth);
}

void MazePiece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Draw an outer frame
    QPen pen;
    pen.setWidth(penWidth);
    pen.setColor(Qt::black);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);
    painter->drawRect(boundingRect());

    // Draw the individual pieces based on the shape
    for (int i{0}; i<3; ++i)
    {
        for (int j{0}; j<3; ++j)
        {
            //QRect rect = coordinateList[i][j];
            if (my_shape[i][j] == 0)
            {
                painter->setBrush(QColor(Qt::white));
                painter->setPen(QColor(Qt::white));
            }
            else
            {
                painter->setBrush(QColor(Qt::darkGreen));
                painter->setPen(QColor(Qt::darkGreen));
            }
            painter->drawRect(coordinateList[i][j]);
        }
    }

    // Draw treasure if exist
    switch (my_treasure) {
    case Treasure::Bag_of_Gold_Coins:
        numToDraw = 1;
        break;
    case Treasure::Bat:
        numToDraw = 2;
        break;
    case Treasure::Book:
        numToDraw = 3;
        break;
    case Treasure::Dragon:
        numToDraw = 4;
        break;
    case Treasure::Ghost_in_bottle:
        numToDraw = 5;
        break;
    case Treasure::Ghost_waving:
        numToDraw = 6;
        break;
    case Treasure::Gold_Crown:
        numToDraw = 7;
        break;
    case Treasure::Gold_Menorah:
        numToDraw = 8;
        break;
    case Treasure::Gold_Ring:
        numToDraw = 9;
        break;
    case Treasure::Helmet:
        numToDraw = 10;
        break;
    case Treasure::Jewel:
        numToDraw = 11;
        break;
    case Treasure::Lady_Pig:
        numToDraw = 12;
        break;
    case Treasure::Lizard:
        numToDraw = 13;
        break;
    case Treasure::Moth:
        numToDraw = 14;
        break;
    case Treasure::Owl:
        numToDraw = 15;
        break;
    case Treasure::Rat:
        numToDraw = 16;
        break;
    case Treasure::Scarab:
        numToDraw = 17;
        break;
    case Treasure::Keys:
        numToDraw = 18;
        break;
    case Treasure::Skull:
        numToDraw = 19;
        break;
    case Treasure::Sorceress:
        numToDraw = 20;
        break;
    case Treasure::Spider:
        numToDraw = 21;
        break;
    case Treasure::Sword:
        numToDraw = 22;
        break;
    case Treasure::Treasure_Chest:
        numToDraw = 23;
        break;
    case Treasure::Treasure_Map:
        numToDraw = 24;
        break;
    default:
        break;
    };

    if (numToDraw !=0)
    {
        QString s = QString::number(numToDraw);
        painter->setPen(QColor(Qt::black));
        painter->drawText(45,45, s);
    }

    // Draw player pos if exist
    if (my_player!="None")
    {
        if (my_player=="RED")
        {
            painter->setBrush(QColor(Qt::red));
            painter->setPen(QColor(Qt::red));
        }
        else if (my_player=="GREEN")
        {
            painter->setBrush(QColor(Qt::green));
            painter->setPen(QColor(Qt::green));
        }
        else if (my_player=="BLUE")
        {
                painter->setBrush(QColor(Qt::blue));
                painter->setPen(QColor(Qt::blue));
        }
        else if (my_player=="YELLOW")
        {
                painter->setBrush(QColor(Qt::yellow));
                painter->setPen(QColor(Qt::yellow));
        }
        painter->drawEllipse(boundingRect().center(), 20, 20);
    }
}

void MazePiece::turnLeft()
{
    /*
     * Rotate the my_shape matrix left by 90 degrees.
    */
    QVector<QVector<int>> tmp = {{0,0,0}, {0,0,0}, {0,0,0}};

    for(int i = 0; i < my_shape.size(); i++)
    {
        for(int j = 0; j < my_shape.size(); j++)
            tmp[my_shape.size()-1-j][i] = my_shape[i][j];
    }
    for(int i = 0; i < my_shape.size(); i++)
    {
        for(int j = 0; j < my_shape.size(); j++)
            my_shape[i][j] = tmp[i][j];
    }
}

void MazePiece::turnRight()
{
    /*
     * Rotate the my_shape matrix right by 90 degrees.
    */
    QVector<QVector<int>> tmp = {{0,0,0}, {0,0,0}, {0,0,0}};

    for(int i = 0; i < my_shape.size(); i++)
    {
        for(int j = 0; j < my_shape.size(); j++)
            tmp[j][my_shape.size()-1-i] = my_shape[i][j];
    }
    for(int i = 0; i < my_shape.size(); i++)
    {
        for(int j = 0; j < my_shape.size(); j++)
            my_shape[i][j] = tmp[i][j];
    }
}

QVector<int> MazePiece::path()
{
    QVector<int> path;
    path.append(my_shape[0][1]);
    path.append(my_shape[1][2]);
    path.append(my_shape[2][1]);
    path.append(my_shape[1][0]);

    return path;
}
