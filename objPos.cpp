#include "objPos.h"

// Default constructor
objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}
// Parameterized constructor
objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;  // Dynamically allocate memory for Pos object
    pos->x = xPos;  // Initialize x-coordinate to 0
    pos->y = yPos;  // Initialize y-coordinate to 0
    symbol = sym;    // Initialize symbol to null (or 0)
}



// Destructor-frees the dynamically allocated memory
objPos::~objPos()
{
    delete pos;
    pos = nullptr;
}

// Copy constructor-creates a deep copy of another objPos object
objPos::objPos(const objPos& other)
{
    pos = new Pos;//ALlocate new memory
    pos->x = other.pos->x;  // Copy the x-coordinate from the other object
    pos->y = other.pos->y; // Copy the y-coordinate from the other object
    symbol = other.symbol; // Copy the symbol from the other object
}

// Copy assignment operator - handles deep copying during assignment
objPos& objPos:: operator=(const objPos& other)
{
    if (this != &other) // Self-assignment check
    {
        delete pos; //Free existing memory
        pos = new Pos; //Allocate new memory
        pos->x = other.pos->x; // Copy the x-coordinate
        pos->y = other.pos->y;  // Copy the y-coordinate
        symbol = other.symbol;  // Copy the symbol
    }

    return *this;  // return *this, allow chained assignments
}

// Sets position and symbol using another objPos object
void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;  // Copy x-coordinate
    pos->y = o.pos->y;  // Copy y-coordinate
    symbol = o.symbol;  // Copy symbol
}
// Sets position and symbol using specific values
void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;  // Set x-coordinate
    pos->y = yPos;  // Set y-coordinate
    symbol = sym;   // Set symbol
}
// Returns a copy of the current objPos object
objPos objPos::getObjPos() const
{
    objPos returnPos;  // Create a new objPos object
    returnPos.pos->x = pos->x; // Copy x-coordinate
    returnPos.pos->y = pos->y; // Copy x-coordinate
    returnPos.symbol = symbol; // Copy symbol
    
    return returnPos; // Return the new objPos object
}
// Returns the symbol associated with the current objPos
char objPos::getSymbol() const
{
    return symbol;
}

// Compares the position of the current objPos with a reference objPos
bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y); // Return true if positions match
}

// Returns the symbol if the positions match; otherwise, returns 0
char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos)) // Check if positions match
        return symbol;    // Return the symbol if they match
    else
        return 0;  // Return 0 if they don't match
}
