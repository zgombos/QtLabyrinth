#include "gameboard.h"

//#include <QDebug>

GameBoard::GameBoard()
{
    QVector<QVector<int>> TSHAPE = {{1, 1, 1},
                                    {0, 0, 0},
                                    {1, 0, 1}};

    QVector<QVector<int>> LSHAPE = {{1, 0, 1},
                                    {1, 0, 0},
                                    {1, 1, 1}};

    QVector<QVector<int>> ISHAPE = {{1, 0, 1},
                                    {1, 0, 1},
                                    {1, 0, 1}};

    // Setup the board coordinates
    int x{0}; int y{0};
    for (int i{0}; i<7; ++i)
    {
        QVector<QPoint> tmp;
        for (int j{0}; j<7; ++j)
        {
            QPoint pos(x, y);
            tmp.append(pos);
            x += 100;
        }
        // Build a list of list
        coordinateList.append(tmp);
        x -= 700;
        y += 100;
    }

    // Call the helper functions to construct the board
    fixMaze();
    movableMaze();
    shuffleMaze();
}

void GameBoard::fixMaze()
{
        MazePiece *maze00 = new MazePiece(LSHAPE, Treasure::NOTHING, "BLUE");
        maze00->turnRight();
        MazePiece *maze02 = new MazePiece(TSHAPE, Treasure::Helmet);
        MazePiece *maze04 = new MazePiece(TSHAPE, Treasure::Gold_Menorah);
        MazePiece *maze06 = new MazePiece(LSHAPE, Treasure::NOTHING, "GREEN");
        maze06->turnRight();
        maze06->turnRight();

        MazePiece *maze20 = new MazePiece(TSHAPE, Treasure::Sword);
        maze20->turnLeft();
        MazePiece *maze22 = new MazePiece(TSHAPE, Treasure::Jewel);
        maze22->turnLeft();
        MazePiece *maze24 = new MazePiece(TSHAPE, Treasure::Treasure_Chest);
        MazePiece *maze26 = new MazePiece(TSHAPE, Treasure::Gold_Ring);
        maze26->turnRight();

        MazePiece *maze40 = new MazePiece(TSHAPE, Treasure::Skull);
        maze40->turnLeft();
        MazePiece *maze42 = new MazePiece(TSHAPE, Treasure::Keys);
        maze42->turnLeft();
        maze42->turnLeft();
        MazePiece *maze44 = new MazePiece(TSHAPE, Treasure::Gold_Crown);
        maze44->turnRight();
        MazePiece *maze46 = new MazePiece(TSHAPE, Treasure::Treasure_Map);
        maze46->turnRight();

        MazePiece *maze60 = new MazePiece(LSHAPE, Treasure::NOTHING, "RED");
        MazePiece *maze62 = new MazePiece(TSHAPE, Treasure::Bag_of_Gold_Coins);
        maze62->turnLeft();
        maze62->turnLeft();
        MazePiece *maze64 = new MazePiece(TSHAPE, Treasure::Book);
        maze64->turnLeft();
        maze64->turnLeft();
        MazePiece *maze66 = new MazePiece(LSHAPE, Treasure::NOTHING, "YELLOW");
        maze66->turnLeft();

        fixMazePieces = {{maze00 , nullptr , maze02 , nullptr , maze04 , nullptr , maze06},
                         {nullptr , nullptr , nullptr , nullptr , nullptr , nullptr , nullptr},
                         {maze20 , nullptr , maze22 , nullptr , maze24 , nullptr , maze26},
                         {nullptr , nullptr , nullptr , nullptr , nullptr , nullptr , nullptr},
                         {maze40 , nullptr , maze42 , nullptr , maze44 , nullptr , maze46},
                         {nullptr , nullptr , nullptr , nullptr , nullptr , nullptr , nullptr},
                         {maze60 , nullptr , maze62 , nullptr , maze64 , nullptr , maze66}};

}

void GameBoard::movableMaze()
{
    // Construct the movable maze pieces
    MazePiece *lmaze1 = new MazePiece(LSHAPE, Treasure::Lizard);
    MazePiece *lmaze2 = new MazePiece(LSHAPE, Treasure::Moth);
    MazePiece *lmaze3 = new MazePiece(LSHAPE, Treasure::Owl);
    MazePiece *lmaze4 = new MazePiece(LSHAPE, Treasure::Scarab);
    MazePiece *lmaze5 = new MazePiece(LSHAPE, Treasure::Rat);
    MazePiece *lmaze6 = new MazePiece(LSHAPE, Treasure::Spider);

    MazePiece *lmaze7 = new MazePiece(LSHAPE, Treasure::NOTHING);
    MazePiece *lmaze8 = new MazePiece(LSHAPE, Treasure::NOTHING);
    MazePiece *lmaze9 = new MazePiece(LSHAPE, Treasure::NOTHING);
    MazePiece *lmaze10 = new MazePiece(LSHAPE, Treasure::NOTHING);
    MazePiece *lmaze11 = new MazePiece(LSHAPE, Treasure::NOTHING);
    MazePiece *lmaze12 = new MazePiece(LSHAPE, Treasure::NOTHING);
    MazePiece *lmaze13 = new MazePiece(LSHAPE, Treasure::NOTHING);
    MazePiece *lmaze14 = new MazePiece(LSHAPE, Treasure::NOTHING);
    MazePiece *lmaze15 = new MazePiece(LSHAPE, Treasure::NOTHING);

    MazePiece *tmaze1 = new MazePiece(TSHAPE, Treasure::Bat);
    MazePiece *tmaze2 = new MazePiece(TSHAPE, Treasure::Dragon);
    MazePiece *tmaze3 = new MazePiece(TSHAPE, Treasure::Ghost_in_bottle);
    MazePiece *tmaze4 = new MazePiece(TSHAPE, Treasure::Ghost_waving);
    MazePiece *tmaze5 = new MazePiece(TSHAPE, Treasure::Lady_Pig);
    MazePiece *tmaze6 = new MazePiece(TSHAPE, Treasure::Sorceress);

    MazePiece *imaze1 = new MazePiece(ISHAPE, Treasure::NOTHING);
    MazePiece *imaze2 = new MazePiece(ISHAPE, Treasure::NOTHING);
    MazePiece *imaze3 = new MazePiece(ISHAPE, Treasure::NOTHING);
    MazePiece *imaze4 = new MazePiece(ISHAPE, Treasure::NOTHING);
    MazePiece *imaze5 = new MazePiece(ISHAPE, Treasure::NOTHING);
    MazePiece *imaze6 = new MazePiece(ISHAPE, Treasure::NOTHING);
    MazePiece *imaze7 = new MazePiece(ISHAPE, Treasure::NOTHING);
    MazePiece *imaze8 = new MazePiece(ISHAPE, Treasure::NOTHING);
    MazePiece *imaze9 = new MazePiece(ISHAPE, Treasure::NOTHING);
    MazePiece *imaze10 = new MazePiece(ISHAPE, Treasure::NOTHING);
    MazePiece *imaze11 = new MazePiece(ISHAPE, Treasure::NOTHING);
    MazePiece *imaze12 = new MazePiece(ISHAPE, Treasure::NOTHING);
    MazePiece *imaze13 = new MazePiece(ISHAPE, Treasure::NOTHING);

    movableMazePieces = {lmaze1 , lmaze2 , lmaze3 , lmaze4 , lmaze5 , lmaze6 , lmaze7,
                         lmaze8 , lmaze9 , lmaze10 , lmaze11 , lmaze12 , lmaze13 , lmaze14 , lmaze15,
                         tmaze1 , tmaze2 , tmaze3 , tmaze4 , tmaze5 , tmaze6,
                         imaze1 , imaze2 , imaze3 , imaze4 , imaze5 , imaze6 , imaze7,
                         imaze8 , imaze9 , imaze10 , imaze11 , imaze12 , imaze13};

    // Randomize the movable maze order
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(movableMazePieces.begin(), movableMazePieces.end(), g);

    // Get the first from the list as a start maze
    newMaze = movableMazePieces.takeFirst();
}

void GameBoard::shuffleMaze()
{
    /*
     *  Add the movable pieces to the game board pieces
     */

    // Create an iterator from the movable pieces
    QVectorIterator<MazePiece*> it(movableMazePieces);

    // Go over the fix piece and if the item is nullptr add a movable piece
    for (auto &row : fixMazePieces)
    {
        for (auto &maze : row)
        {
            if (maze == nullptr)
                maze = it.next();
        }
    }
}

QVector<QPoint> GameBoard::findNonDiagonalNeighbours(int x, int y, int w, int h)
{
    /*
     * Find non-diagonal neighbours in a matrix[w, h] in clockwise direction.
     * x and y coordinates in the matrix[w, h].
     */

    QVector<QPoint> result;
    QVector<QVector<int>> pattern = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    for (const auto& item : pattern)
        if ( ((0 <= x + item[0]) && (x + item[0]< w)) && ((0 <= y + item[1]) && (y + item[1]< h)) )
        {
            QPoint p(x + item[0], y + item[1]);
            result.append(p);
        }
        else
        {
            QPoint p(-7, -7); // Use it for out of range coordinates
            result.append(p);
        }
    return result;
}

void GameBoard::createPath()
{
    /*
     *  Represent the side comparison. A (x,y) point has four non diagonal neighbours stored in clockwise direction
     *  E.g: Neighbours: (0:0) QVector(QPoint(-7,-7), QPoint(0,1), QPoint(1,0), QPoint(-7,-7))
     *  Only the 1 and 2 items are vaild. So look at them in the sideList {0-4}.
     *  1 - QPoint(1, 3): so look at the (1)item in the (0:0)path than compare it with (3)item in QPoint(0,1)path
     *                    If they have 0 in these positions put (0:0) - QPoint(0,1) into the graph
     *  2 - QPoint(2, 0): so look at the (2)item in the (0:0)path than compare it with (0)item in QPoint(1,0)path
     *                    If they have 0 in these positions put (0:0) - QPoint(1,0) into the grap
     */

    // Clear the QMultiMap content
    graph.clearAll();

    // Define the corret maze sides what we have to compare with
    QVector<QPoint> sideList = {QPoint(0, 2), QPoint(1, 3), QPoint(2, 0), QPoint(3, 1)};

    for (int i{0}; i<7; ++i)
    {
        for (int j{0}; j<7; ++j)
        {
            // Get all non diagonal neighbours
            QVector<QPoint> neighbourList = findNonDiagonalNeighbours(i, j);
            //qDebug() << "Neighbours:" << i << ":" << j << neighbourList;

            // Get the current maze and its path
            MazePiece *maze = fixMazePieces[i][j];
            QVector<int> mazePath = maze->path();
            //qDebug() << "\tMaze Path:" << i << ":" << j << mazePath;

            for (int k{0}; k < neighbourList.size(); ++k)
            {
                // Drop invalid neighbour (-7,-7)
                if ( (neighbourList[k].x()!=-7) || (neighbourList[k].y()!=-7) )
                {
                    // Get the k element from the sideList
                    QPoint side = sideList[k];

                    // Get the k element and its path from fixMazePieces
                    MazePiece *neighbour = fixMazePieces[neighbourList[k].x()][neighbourList[k].y()];
                    QVector<int> neighbourPath = neighbour->path();
                    //qDebug() << "\tNeighbour Path:" << neighbourList[k].x() << ":" << neighbourList[k].y() << neighbourPath;

                    // Compare the mazePath and neighbourPath based on the sideList content
                    if ((mazePath[side.x()] == 0) && (neighbourPath[side.y()] == 0))
                    {
                        graph.addNode(QPoint(i,j), neighbourList[k]);
                        //qDebug() << "\t\tNode added to the graph!" << neighbourList[k];
                    }
                }
            }
        }
    }
}

bool GameBoard::validPath(const QPoint &start, const QPoint &end)
{
    QVector<QPoint> path = graph.findPath(start, end);
    //qDebug() << "\nPath in the Graph:\n" << path << endl;
    if (path.isEmpty())
        return false;
    else
        return true;
}

void GameBoard::moveRowLeft(int rowNumber)
{
    /*
     * Move a row left and add the free maze to the end.
     * Movable rows {1, 3, 5} from {0-6}
     */

    // Get the requested row
    QVector<MazePiece*> tmp;
    for (const auto &item : fixMazePieces[rowNumber])
        tmp.append(item);

    // Take out the old item and add the new one
    oldMaze = tmp.takeFirst();
    tmp.append(newMaze);

    // Update the original vector
    fixMazePieces.replace(rowNumber, tmp);
    newMaze = oldMaze;
}

void GameBoard::moveRowRight(int rowNumber)
{
    /*
     * Move a row right and add the free maze to the end.
     * Movable rows {1, 3, 5} from {0-6}
     */

    // Get the requested row
    QVector<MazePiece*> tmp;
    for (const auto &item : fixMazePieces[rowNumber])
        tmp.append(item);

    // Take out the old item and add the new one
    oldMaze = tmp.takeLast();
    tmp.prepend(newMaze);

    // Update the original vector
    fixMazePieces.replace(rowNumber, tmp);
    newMaze = oldMaze;
}

void GameBoard::moveColUp(int colNumber)
{
    /*
     * Move a column up and add the free maze to the bottom.
     * Movable columns {1, 3, 5} from {0-6}
     */

    // Get the requested column
    QVector<MazePiece*> tmp;
    for (int i{0}; i < fixMazePieces.size(); ++i)
        tmp.append(fixMazePieces[i][colNumber]);

    // Take out the old item and add the new one
    oldMaze = tmp.takeFirst();
    tmp.append(newMaze);

    // Update the original vector
    for (int i{0}; i < fixMazePieces.size(); ++i)
        fixMazePieces[i][colNumber] = tmp[i];

    newMaze = oldMaze;
}

void GameBoard::moveColDown(int colNumber)
{
    /*
     * Move a column down and add the free maze to the top.
     * Movable columns {1, 3, 5} from {0-6}
     */

    // Get the requested column
    QVector<MazePiece*> tmp;
    for (int i{0}; i < fixMazePieces.size(); ++i)
        tmp.append(fixMazePieces[i][colNumber]);

    // Take out the old item and add the new one
    oldMaze = tmp.takeLast();
    tmp.prepend(newMaze);

    // Update the original vector
    for (int i{0}; i < fixMazePieces.size(); ++i)
        fixMazePieces[i][colNumber] = tmp[i];

    newMaze = oldMaze;
}
