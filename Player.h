#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef); // Constructor
        ~Player(); // Destructor

        objPosArrayList* getPlayerPosList() const; // Retrieves the list of positions representing the player's current state // Upgrade this in iteration 3.       
        void updatePlayerDir();
        void movePlayer();
        void checkfoodcoll(const objPos& headNew); // Checks if the player collides with food and handles consumption
        void checkselfcoll(const objPos& headNew); // Checks if the player collides with itself
        void handleMovement(const objPos& headNew); // Handles movement logic for the player, including updating position
        void checkSpecialfoodcoll(const objPos& headNew); // Checks if the player collides with special food and handles the event

        //Bonus
        void setSpecialFoodActive(bool isActive);

        // More methods to be added here

    private:
        objPosArrayList* playerPosList; // List representing the player's body positions // Upgrade this in iteration 3.       
        enum Dir myDir; // Current direction of the player
        int quit = 0;  // Flag to indicate if the player has quit the game


        // Reference to the main game mechanics object for interaction
        GameMechs* mainGameMechsRef;

        
};

#endif