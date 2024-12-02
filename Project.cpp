#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "Player.h"
#include "GameMechs.h"

using namespace std; 

#define DELAY_CONST 100000

//Global variables and constants 
bool exitFlag;  //Flag to signal the game loop to exit 
const int board_width = 30;  //Width of the game board
const int board_height = 15; //Height of the game board 


GameMechs* gameMechanics; // Pointer to GameMechs object for handling game mechanics 
Player* player;           // Pointer to Player object

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void) 
{
    MacUILib_init();  
    MacUILib_clearScreen();

    // Create game mechanics and player objects 
    gameMechanics = new GameMechs(board_width, board_height);
    player = new Player(gameMechanics);

    // Generate food items for the game 
    gameMechanics->generateFoods(*player->getPlayerPosList());
}

void GetInput(void)
{
    
    // Check if a key was pressed
    if(MacUILib_hasChar())
    {
        char input = MacUILib_getChar(); // Get the pressed key
        gameMechanics->setInput(input);  // Pass input to game mechanics
    }

}

void RunLogic(void)
{
    // Update player direction and position
    player -> updatePlayerDir();
    player -> movePlayer();

    // Check if the exit flag is set by the game mechanic
    if(gameMechanics->getExitFlagStatus())
    {
        exitFlag = true;
    }



}

void DrawScreen(void) {
    MacUILib_clearScreen();

    // Render the game board
    for (int y = 0; y < board_height; ++y) {
        for (int x = 0; x < board_width; ++x) {
            if (x == 0 || x == board_width - 1 || y == 0 || y == board_height - 1) {
                std::cout << '#'; // Draw border
                continue;
            }

            bool printed = false;  // Track if a position is already drawn

            // Draw the snake
            objPosArrayList* snakeBody = player->getPlayerPosList();
            for (int i = 0; i < snakeBody->getSize(); ++i) {
                objPos segment = snakeBody->getElement(i);
                if (segment.pos->x == x && segment.pos->y == y) {
                    std::cout << segment.symbol;  // Draw snake segment
                    printed = true;
                    break;
                }
            }

            // Draw regular foods
            for (int i = 0; i < 2; ++i) {
                objPos food = gameMechanics->getRegularFood(i);
                if (!printed && food.pos->x == x && food.pos->y == y) {
                    std::cout << food.symbol; 
                    printed = true;
                }
            }

            // Draw special food
            if (!printed && gameMechanics->isSpecialFoodActive()) {
                objPos specialFood = gameMechanics->getSpecialFood();
                if (specialFood.pos->x == x && specialFood.pos->y == y) {
                    std::cout << specialFood.symbol; // Special food symbol (@)
                    printed = true;
                }
            }

            // Draw empty spaces
            if (!printed) {
                std::cout << ' ';
            }
        }
        std::cout << '\n'; // Move to the next line
    }

    // Display score and controls below the game board
    std::cout << "Score: " << gameMechanics->getScore() << "\n";
    std::cout << "Use 'W', 'A', 'S', 'D' to move. Press ESC to quit.\n";
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void) {
    MacUILib_clearScreen();

    // Display end-game message
    if (gameMechanics->getLoseFlagStatus()) {
        MacUILib_printf("You lost! Better luck next time!\n");
    } else {
        MacUILib_printf("Thanks for playing! Your final score: %d\n", gameMechanics->getScore());
    }

    // Delete dynamically allocated objects safely
    if (player) {
        delete player;
        player = nullptr; // Avoid dangling pointer
    }

    if (gameMechanics) {
        delete gameMechanics;
        gameMechanics = nullptr; // Avoid dangling pointer
    }

    MacUILib_uninit();
}