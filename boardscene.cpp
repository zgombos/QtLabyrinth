#include "boardscene.h"

BoardScene::BoardScene()
{
    newGame();
}

void BoardScene::newGame()
{
    setupGameBoard();
    setupArrowButtons();
    setupPlayers();
    setupCards();
    shuffleCards();

    setPlayerLockState(true);
    currentPlayer = BluePlayer;
    currentPlayer->setLock(true);

    setupGUI();
}

void BoardScene::setupGUI()
{
    // Add left and right buttons for turn
    MyButton *TurnRightButton = new MyButton(QRectF(0, 0, 100, 30), "Turn Right");
    TurnRightButton->setPos(780, 180);
    addItem(TurnRightButton);

    MyButton *TurnLeftButton = new MyButton(QRectF(0, 0, 100, 30), "Turn Left");
    TurnLeftButton->setPos(930, 180);
    addItem(TurnLeftButton);

    connect(TurnLeftButton, SIGNAL(onClick()), this, SLOT(turnMazeLeft()));
    connect(TurnRightButton, SIGNAL(onClick()), this, SLOT(turnMazeRight()));

    // Draw a horizontal separator
    QGraphicsRectItem *hsep = new QGraphicsRectItem();
    hsep->setRect(0, 0, 10, 768);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    hsep->setBrush(brush);
    hsep->setPos(750, 0);
    addItem(hsep);

    // Draw a vertical separator
    QGraphicsRectItem *vsep = new QGraphicsRectItem();
    vsep->setRect(0, 0, 264, 10);
    vsep->setBrush(brush);
    vsep->setPos(760, 250);
    addItem(vsep);

    // Display a text who is the current player
    playerTrackerText = new QGraphicsTextItem();
    playerTrackerText->setPlainText("Current Player: " + currentPlayer->name());
    playerTrackerText->setFont(QFont("Ariel", 16, QFont::Bold));
    playerTrackerText->setPos(780, 280);
    addItem(playerTrackerText);
}

void BoardScene::setupGameBoard()
{
    gameBoard = new GameBoard;
    for (int i{0}; i<7; ++i)
    {
        for (int j{0}; j<7; ++j)
        {
            QPoint pos = gameBoard->coordinates()[i][j];
            MazePiece *maze = gameBoard->mazePieces()[i][j];
            maze->setPos(pos);
            addItem(maze);
        }
    }

    // Add the current maze to the left scene
    gameBoard->currentMaze()->setPos(860,40);
    addItem(gameBoard->currentMaze());

    // Create a graph for path finding
    gameBoard->createPath();
}

void BoardScene::setupArrowButtons()
{
    top1_arrow = new ArrowButton(1 ,1);
    top1_arrow->setPos(130, -20);
    addItem(top1_arrow);
    top2_arrow = new ArrowButton(2, 3);
    top2_arrow->setPos(330, -20);
    addItem(top2_arrow);
    top3_arrow = new ArrowButton(3, 5);
    top3_arrow->setPos(530, -20);
    addItem(top3_arrow);

    bottom1_arrow = new ArrowButton(4, 1);
    bottom1_arrow->setRotation(180);
    bottom1_arrow->setPos(160, 710);
    addItem(bottom1_arrow);
    bottom2_arrow = new ArrowButton(5, 3);
    bottom2_arrow->setRotation(180);
    bottom2_arrow->setPos(360, 710);
    addItem(bottom2_arrow);
    bottom3_arrow = new ArrowButton(6, 5);
    bottom3_arrow->setRotation(180);
    bottom3_arrow->setPos(560, 710);
    addItem(bottom3_arrow);

    left1_arrow = new ArrowButton(7, 1);
    left1_arrow->setRotation(-90);
    left1_arrow->setPos(-20, 160);
    addItem(left1_arrow);
    left2_arrow = new ArrowButton(8, 3);
    left2_arrow->setRotation(-90);
    left2_arrow->setPos(-20, 360);
    addItem(left2_arrow);
    left3_arrow = new ArrowButton(9, 5);
    left3_arrow->setRotation(-90);
    left3_arrow->setPos(-20, 560);
    addItem(left3_arrow);

    right1_arrow = new ArrowButton(10, 1);
    right1_arrow->setRotation(90);
    right1_arrow->setPos(710, 130);
    addItem(right1_arrow);
    right2_arrow = new ArrowButton(11, 3);
    right2_arrow->setRotation(90);
    right2_arrow->setPos(710, 330);
    addItem(right2_arrow);
    right3_arrow = new ArrowButton(12, 5);
    right3_arrow->setRotation(90);
    right3_arrow->setPos(710, 530);
    addItem(right3_arrow);

    connect (top1_arrow, SIGNAL(onClick(int,int)), this,SLOT(moveColDown(int,int)));
    connect (top2_arrow, SIGNAL(onClick(int,int)), this,SLOT(moveColDown(int,int)));
    connect (top3_arrow, SIGNAL(onClick(int,int)), this,SLOT(moveColDown(int,int)));

    connect (bottom1_arrow, SIGNAL(onClick(int,int)), this,SLOT(moveColUp(int,int)));
    connect (bottom2_arrow, SIGNAL(onClick(int,int)), this,SLOT(moveColUp(int,int)));
    connect (bottom3_arrow, SIGNAL(onClick(int,int)), this,SLOT(moveColUp(int,int)));

    connect (left1_arrow, SIGNAL(onClick(int,int)), this,SLOT(moveRowRight(int,int)));
    connect (left2_arrow, SIGNAL(onClick(int,int)), this,SLOT(moveRowRight(int,int)));
    connect (left3_arrow, SIGNAL(onClick(int,int)), this,SLOT(moveRowRight(int,int)));

    connect (right1_arrow, SIGNAL(onClick(int,int)), this,SLOT(moveRowLeft(int,int)));
    connect (right2_arrow, SIGNAL(onClick(int,int)), this,SLOT(moveRowLeft(int,int)));
    connect (right3_arrow, SIGNAL(onClick(int,int)), this,SLOT(moveRowLeft(int,int)));

    sessionLockList = { top1_arrow, top2_arrow, top3_arrow,
                        bottom1_arrow, bottom2_arrow, bottom3_arrow,
                        left1_arrow, left2_arrow, left3_arrow,
                        right1_arrow, right2_arrow, right3_arrow};
}

void BoardScene::setupPlayers()
{
    // Setup the players and add them to the scene
    BluePlayer = new Player("BLUE");
    QPoint blue(gameBoard->coordinates()[0][0]);
    BluePlayer->setPos(blue.x()+30, blue.y()+10);
    BluePlayer->setZValue(1);
    BluePlayer->setCoordinate(QPoint(0, 0));
    addItem(BluePlayer);

    GreenPlayer = new Player("GREEN");
    QPoint green(gameBoard->coordinates()[0][6]);
    GreenPlayer->setPos(green.x()+30, green.y()+10);
    GreenPlayer->setZValue(1);
    GreenPlayer->setCoordinate(QPoint(0, 6));
    addItem(GreenPlayer);

    YellowPlayer = new Player("YELLOW");
    QPoint yellow(gameBoard->coordinates()[6][6]);
    YellowPlayer->setPos(yellow.x()+30, yellow.y()+10);
    YellowPlayer->setZValue(1);
    YellowPlayer->setCoordinate(QPoint(6, 6));
    addItem(YellowPlayer);

    RedPlayer = new Player("RED");
    QPoint red(gameBoard->coordinates()[6][0]);
    RedPlayer->setPos(red.x()+30, red.y()+10);
    RedPlayer->setZValue(1);
    RedPlayer->setCoordinate(QPoint(6, 0));
    addItem(RedPlayer);

    // BluePlayer is the fisrt, therefore it is not part of the initial list
    playerList = {GreenPlayer, YellowPlayer, RedPlayer};

    // Need another list for sticky checking
    playerCheckList = {BluePlayer, GreenPlayer, YellowPlayer, RedPlayer};
}

void BoardScene::setupCards()
{
    for (int i{0}; i<24; ++i)
    {
        Card *card = new Card(i+1);
        cardList.append(card);
    }
}

void BoardScene::shuffleCards()
{
    // Randomize the card order in the list
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cardList.begin(), cardList.end(), g);

    int x{0}, y{0};
    // Iterate over the four players
    for (int i{0}; i<4; ++i)
    {
        // Add 6 cards for each user
        QVector<Card *> cards;
        for (int j{0}; j<6; ++j)
        {
            cards.append(cardList.takeFirst());

            if (playerCheckList[i]->name() == "BLUE")
            {
                cards[j]->setColor(QColor(Qt::blue));
            }
            else if (playerCheckList[i]->name() == "GREEN")
            {
                cards[j]->setColor(QColor(Qt::green));
            }
            else if (playerCheckList[i]->name() == "YELLOW")
            {
                cards[j]->setColor(QColor(Qt::yellow));
            }
            else if (playerCheckList[i]->name() == "RED")
            {
                cards[j]->setColor(QColor(Qt::red));
            }
        }
        playerCheckList[i]->addCards(cards);

        // Draw the cards on the scene
        QVector<Card *> myCards = playerCheckList[i]->myCards();
        int z{5};
        for (auto &item : myCards)
        {
            item->setPos(800 - x, 330 + y);
            item->setZValue(z);
            addItem(item);

            x -= 30;
            --z;
        }
        x += 180;
        y += 130;

        // Set the fisrt card visible
        myCards[0]->setVisible(true);
    }
}

void BoardScene::updateCardDeck(Player *player)
{
    Card *card = player->getCard();
    if (card)
    {
        if (player->myCards().isEmpty())
        {
            // Remove the card from the secen
            removeItem(card);

            QMessageBox msgBox;
            msgBox.setText(currentPlayer->name() + " player is the winner!");
            msgBox.setInformativeText("Do you want a new game or exit?");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Close);
            int ret = msgBox.exec();

            switch (ret)
            {
            case QMessageBox::Ok:
                // Call the new game
                break;
            case QMessageBox::Close:
                // Close the window
                break;
            }
        }
        else
        {
            // Remove the card from the secen
            removeItem(card);

            if (player->myCards().size() >= 1)
            {
                // Make the next card visible
                player->myCards()[0]->setVisible(true);
            }

            // Update the scene
            update();
        }
    }
}

void BoardScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QList<QGraphicsItem *> itemList = items(event->scenePos());
        for (const auto &item : itemList)
        {
            // If it is a Maze get the gameboard coordiante and use it for player movement
            if (item->type() == 65536 + 4)
            {
                QPointF itemPos = item->pos();
                int x = itemPos.y() / 100;
                int y = itemPos.x() / 100;
                QPoint newPos(x, y);

                // If path is available and the current player is not locked
                if (gameBoard->validPath(currentPlayer->coordinate(), newPos) && !currentPlayer->isLocked())
                {
                    // Move the player
                    movePlayer(currentPlayer, newPos);

                    // Lock the player
                    setPlayerLockState(true);

                    // Check treasure
                    MazePiece *maze = qgraphicsitem_cast<MazePiece *>(item);
                    Card *currentPlayerCard = currentPlayer->myCards().first();
                    if (currentPlayerCard->name() == maze->treasure())
                    {
                        updateCardDeck(currentPlayer);
                    }

                    // Change the player
                    changePlayer(currentPlayer);
                    playerTrackerText->setPlainText("Current Player: " + currentPlayer->name());

                    // Remove the session lock from the arrows
                    setSessionArrowLockState(false);
                }
                else if (currentPlayer->isLocked())
                    qDebug() << currentPlayer->name() << "is Locked";
                else
                {
                    QMessageBox msgBox;
                    msgBox.setText("No valid path for " + currentPlayer->name() + " player.");
                    msgBox.setIcon(QMessageBox::Information);
                    msgBox.exec();
                }
            }
        }

    }
    QGraphicsScene::mousePressEvent(event);
}

void BoardScene::updateGameBoard()
{
    // Update the maze piece position
    QList<QGraphicsItem *> mazeList = items();
    for (int i{0}; i<7; ++i)
    {
        for (int j{0}; j<7; ++j)
        {
            QPoint pos = gameBoard->coordinates()[i][j];
            MazePiece *maze = gameBoard->mazePieces()[i][j];
            maze->setPos(pos);
            maze->update();
        }
    }

    // Create new graph for path finding
    gameBoard->createPath();

    // Update the current maze
    gameBoard->currentMaze()->setPos(860, 40);
    gameBoard->currentMaze()->update();
}

void BoardScene::lockArrowButton(ArrowButton *button1, ArrowButton *button2)
{
    if (!lockList.isEmpty())
    {
        for(auto &item : lockList)
        {
            item->setLock(false);
            item->update();
        }
    }
    lockList.clear();
    if (!lockList.contains(button1) || !lockList.contains(button2))
    {
        lockList.append(button1);
        lockList.append(button2);
    }
    for(auto &item : lockList)
    {
        item->setLock(true);
        item->update();
    }
}

void BoardScene::setSessionArrowLockState(bool lock)
{
    for (auto & item : sessionLockList)
    {
        item->setSessionLock(lock);
        item->update();
    }
}

void BoardScene::movePlayer(Player *player, QPoint newPos)
{
        // Get the screen coordinated from the GameBoard coordinate
        QPoint pos = gameBoard->coordinates()[newPos.x()][newPos.y()];

        // Count how many players are already there
        int playerCount{0};
        QVector<Player *> tempList;
        for (const auto &item : playerCheckList)
        {
            if (item->coordinate() == newPos)
            {
                tempList.append(item);
                ++playerCount;
            }
        }
        // Change the players position on the scene to fit into a maze
        if (playerCount == 1)
        {
            tempList[0]->setPos(pos.x()+10, pos.y()+10);
            tempList[0]->update();

            player->setPos(pos.x()+50, pos.y()+10);
            player->setCoordinate(newPos);
            player->update();
        }
        else if (playerCount == 2)
        {
            tempList[0]->setPos(pos.x()+10, pos.y());
            tempList[0]->update();

            tempList[1]->setPos(pos.x()+50, pos.y());
            tempList[1]->update();

            player->setPos(pos.x()+10, pos.y()+30);
            player->setCoordinate(newPos);
            player->update();
        }
        else if (playerCount == 3)
        {
            tempList[0]->setPos(pos.x()+10, pos.y());
            tempList[0]->update();

            tempList[1]->setPos(pos.x()+50, pos.y());
            tempList[1]->update();

            tempList[2]->setPos(pos.x()+10, pos.y()+30);
            tempList[2]->update();

            player->setPos(pos.x()+50, pos.y()+30);
            player->setCoordinate(newPos);
            player->update();
        }
        else
        {
            // If no one is there move the player
            player->setPos(pos.x()+30, pos.y()+10);
            player->setCoordinate(newPos);
            player->update();
        }
}

void BoardScene::stickPlayer(QString direction, int boardPos)
{
    if (direction == "UP")
    {
        for (const auto &player : playerCheckList)
        {
            //qDebug() << "\t Player name inside the loop:" << player->name();

            // Get the players current position
            QPoint playerPos = player->coordinate();
            int row = playerPos.x();
            int col = playerPos.y();

            // If there is any player in the given column
            if (col == boardPos)
            {
                // If it is on the top row, move it to the buttom
                if (row == 0)
                {
                    QPoint newPos(6, col);
                    movePlayer(player, newPos);
                }
                else
                {
                    // Move it by one pos
                    QPoint newPos(row - 1, col);
                    movePlayer(player, newPos);
                }
            }
        }
    }
    else if (direction == "DOWN")
    {
        for (const auto &player : playerCheckList)
        {
            //qDebug() << "\t Player name inside the loop:" << player->name();

            // Get the players current position
            QPoint playerPos = player->coordinate();
            int row = playerPos.x();
            int col = playerPos.y();

            // If there is any player in the given column
            if (col == boardPos)
            {
                // If it is on the bottom row, move it to top
                if (row == 6)
                {
                    QPoint newPos(0, col);
                    movePlayer(player, newPos);
                }
                else
                {
                    // Move it by one pos
                    QPoint newPos(row + 1, col);
                    movePlayer(player, newPos);
                }
            }
        }
    }
    else if (direction == "RIGHT")
    {
        for (const auto &player : playerCheckList)
        {
            //qDebug() << "\t Player name inside the loop:" << player->name();

            // Get the players current position
            QPoint playerPos = player->coordinate();
            int row = playerPos.x();
            int col = playerPos.y();

            // If there is any player in the given row
            if (row == boardPos)
            {
                // If it is on the right side, move it to left
                if (col == 6)
                {
                    QPoint newPos(row, 0);
                    movePlayer(player, newPos);
                }
                else
                {
                    // Move it by one pos
                    QPoint newPos(row, col + 1);
                    movePlayer(player, newPos);
                }
            }
        }
    }
    else if (direction == "LEFT")
    {
        for (const auto &player : playerCheckList)
        {
            //qDebug() << "\t Player name inside the loop:" << player->name();

            // Get the players current position
            QPoint playerPos = player->coordinate();
            int row = playerPos.x();
            int col = playerPos.y();

            // If there is any player in the given row
            if (row == boardPos)
            {
                // if it is on the left side, move it to right
                if (col == 0)
                {
                    QPoint newPos(row, 6);
                    movePlayer(player, newPos);
                }
                else
                {
                    // Move it by one pos
                    QPoint newPos(row, col - 1);
                    movePlayer(player, newPos);
                }
            }
        }
    }
}

void BoardScene::setPlayerLockState(bool lock)
{
    for (auto & item : playerList)
        item->setLock(lock);
}

void BoardScene::changePlayer(Player *player)
{
    currentPlayer = playerList.takeFirst();

    // Add the old player back to the list
    playerList.append(player);
}

void BoardScene::turnMazeLeft()
{
    gameBoard->currentMaze()->turnLeft();
    update();
}

void BoardScene::turnMazeRight()
{
    gameBoard->currentMaze()->turnRight();
    update();
}

void BoardScene::moveRowLeft(int id, int pos)
{
    gameBoard->moveRowLeft(pos);
    updateGameBoard();

    // If right arrow button pressed lock it with its left pair
    // Remove all other the locks
    if (id == 10)
    {
        lockArrowButton(left1_arrow, right1_arrow);
    }
    else if (id == 11)
    {
        lockArrowButton(left2_arrow, right2_arrow);
    }
    else if (id == 12)
    {
        lockArrowButton(left3_arrow, right3_arrow);
    }

    // Put the session lock on the arrows
    setSessionArrowLockState(true);

    // Move players if was any in the row
    stickPlayer("LEFT", pos);

    // Unlock the player
    currentPlayer->setLock(false);
}

void BoardScene::moveRowRight(int id, int pos)
{
    gameBoard->moveRowRight(pos);
    updateGameBoard();

    // If left arrow button pressed lock it with its right pair
    // Remove all other the locks
    if (id == 7)
    {
        lockArrowButton(left1_arrow, right1_arrow);
    }
    else if (id == 8)
    {
        lockArrowButton(left2_arrow, right2_arrow);
    }
    else if (id == 9)
    {
        lockArrowButton(left3_arrow, right3_arrow);
    }

    // Put the session lock on the arrows
    setSessionArrowLockState(true);

    // Move players if was any in the row
    stickPlayer("RIGHT", pos);

    // Unlock the player
    currentPlayer->setLock(false);
}

void BoardScene::moveColUp(int id, int pos)
{
    gameBoard->moveColUp(pos);
    updateGameBoard();

    // If bottom arrow button pressed lock it with its top pair
    // Remove all other the locks
    if (id == 4)
    {
        lockArrowButton(top1_arrow, bottom1_arrow);
    }
    else if (id == 5)
    {
        lockArrowButton(top2_arrow, bottom2_arrow);
    }
    else if (id == 6)
    {
        lockArrowButton(top3_arrow, bottom3_arrow);
    }

    // Put the session lock on the arrows
    setSessionArrowLockState(true);

    // Move players if was any in the column
    stickPlayer("UP", pos);

    // Unlock the player
    currentPlayer->setLock(false);
}

void BoardScene::moveColDown(int id, int pos)
{
    gameBoard->moveColDown(pos);
    updateGameBoard();

    // If top arrow button pressed lock it with its bottom pair
    // Remove all other the locks
    if (id == 1)
    {
        lockArrowButton(top1_arrow, bottom1_arrow);
    }
    else if (id == 2)
    {
        lockArrowButton(top2_arrow, bottom2_arrow);
    }
    else if (id == 3)
    {
        lockArrowButton(top3_arrow, bottom3_arrow);
    }

    // Put the session lock on the arrows
    setSessionArrowLockState(true);

    // Move players if was any in the column
    stickPlayer("DOWN", pos);

    // Unlock the player
    currentPlayer->setLock(false);
}
