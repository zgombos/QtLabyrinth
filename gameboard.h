#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QGraphicsRectItem>
#include "mazepiece.h"
#include "graph.h"

// Need it for random_shuffle
#include <algorithm>



class GameBoard : public QGraphicsRectItem
{
public:
    enum {Type = UserType + 2};

    GameBoard();

    QVector<QVector<MazePiece*>> mazePieces() {return fixMazePieces;}
    QVector<QVector<QPoint>> coordinates() const {return coordinateList;}
    MazePiece* currentMaze(){return newMaze;}

    void moveRowLeft(int rowNumber);
    void moveRowRight(int rowNumber);
    void moveColUp(int colNumber);
    void moveColDown(int colNumber);
    void createPath();
    bool validPath(const QPoint &start, const QPoint &end);
    int type() const override {return Type;}

private:
    QVector<QVector<QPoint>> coordinateList;
    QVector<QVector<MazePiece*>> fixMazePieces;
    QVector<MazePiece*> movableMazePieces;
    MazePiece* newMaze;
    MazePiece* oldMaze;
    Graph graph;

    QVector<QVector<int>> TSHAPE = {{1, 1, 1},
                                    {0, 0, 0},
                                    {1, 0, 1}};

    QVector<QVector<int>> LSHAPE = {{1, 0, 1},
                                    {1, 0, 0},
                                    {1, 1, 1}};

    QVector<QVector<int>> ISHAPE = {{1, 0, 1},
                                    {1, 0, 1},
                                    {1, 0, 1}};

    void fixMaze();
    void movableMaze();
    void shuffleMaze();
    QVector<QPoint> findNonDiagonalNeighbours(int x, int y, int w = 7, int h = 7);
};

#endif // GAMEBOARD_H
