#ifndef AI_H
#define AI_H

/*
 * Step 1: Save the gameboard state
 * Step 2: Get the current player pos and the card name + pos what the player has to find
 * Step 3: Iterate over the current Maze (which is not inside the gameboard) clockwise
 * Step 4: Insert this current Maze into the gameboard clockwise and see if the player can find it
 * Step 5: If so, this is the next step what the player has to take
 * Step 6: If not, go thrugh all the gamebored move possibilites (12)
 * Setp 7: If the crads is not found, do a random move
 *
 * After every move restore the gameboard state
 */

class AI
{
public:
    AI();

    void saveCurrentState();

private:
};

#endif // AI_H
