#ifndef OBJPOS_H
#define OBJPOS_H

// Define a simple struct to hold positional coordinates (x, y)
// Not typically a C++ feature, but used here for simplicity.
typedef struct 
{
    int x; // x-coordinate
    int y; // y-coordinate
} Pos;

// Define the objPos class, which represents an object with a position and a symbol
class objPos
{
    public:
        Pos* pos;        // Pointer to a Pos struct representing the position
        char symbol;     // Character symbol representing the object

        // Constructors
        objPos();                              // Default constructor (initializes position to (0, 0) and symbol to 0)
        objPos(int xPos, int yPos, char sym);  // Parameterized constructor (initializes position and symbol)

        // The "Rule of Four/Six" requires certain special member functions to be implemented
        // [TODO]: Implement move constructor and move assignment operator to follow Rule of Six

        // Destructor
        ~objPos();                             // Destructor to free dynamically allocated memory

        // Copy Constructor
        objPos(const objPos& other);          // Deep copy constructor to copy data from another objPos object

        // Copy Assignment Operator
        objPos& operator=(const objPos& other); // Deep copy assignment operator for safe copying

        // Setter methods
        void setObjPos(objPos o);             // Sets the position and symbol using another objPos object
        void setObjPos(int xPos, int yPos, char sym); // Sets the position and symbol using specific values

        // Getter methods
        objPos getObjPos() const;             // Returns a copy of the current objPos object
        char getSymbol() const;               // Returns the symbol of the current object
        char getSymbolIfPosEqual(const objPos* refPos) const; // Returns the symbol if the position matches a reference position

        // Utility methods
        bool isPosEqual(const objPos* refPos) const; // Checks if the position matches a reference position
};

#endif // OBJPOS_H
