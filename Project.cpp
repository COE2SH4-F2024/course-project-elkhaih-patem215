#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;
const int board_width = 30;
const int board_height = 15; 
const int num_obj = 3; // test with 3 objs first




objPos objects[num_obj]; //array to hold objPos objects

GameMechs* gameMechanics; // Pointer to GameMechs object
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

    gameMechanics = new GameMechs(board_width, board_height);
    player = new Player(gameMechanics);

    // Generate all foods
    gameMechanics->generateFoods(*player->getPlayerPosList());
}

void GetInput(void)
{
    
    if(MacUILib_hasChar())
    {
        char input = MacUILib_getChar();
        gameMechanics->setInput(input);
    }

}

void RunLogic(void)
{
    player -> updatePlayerDir();
    player -> movePlayer();

    if(gameMechanics->getExitFlagStatus())
    {
        exitFlag = true;
    }



}

void DrawScreen(void) {
    MacUILib_clearScreen();

    for (int y = 0; y < board_height; ++y) {
        for (int x = 0; x < board_width; ++x) {
            if (x == 0 || x == board_width - 1 || y == 0 || y == board_height - 1) {
                std::cout << '#'; // Border
                continue;
            }

            bool printed = false;

            // Draw the snake
            objPosArrayList* snakeBody = player->getPlayerPosList();
            for (int i = 0; i < snakeBody->getSize(); ++i) {
                objPos segment = snakeBody->getElement(i);
                if (segment.pos->x == x && segment.pos->y == y) {
                    std::cout << segment.symbol;
                    printed = true;
                    break;
                }
            }

            // Draw regular foods
            for (int i = 0; i < 2; ++i) {
                objPos food = gameMechanics->getRegularFood(i);
                if (!printed && food.pos->x == x && food.pos->y == y) {
                    std::cout << food.symbol; // Regular food symbol (*)
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

    // Display score below the game board
    std::cout << "Score: " << gameMechanics->getScore() << "\n";
    std::cout << "Use 'W', 'A', 'S', 'D' to move. Press ESC to quit.\n";
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void) {
    MacUILib_clearScreen();

    // Display appropriate end-game message
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