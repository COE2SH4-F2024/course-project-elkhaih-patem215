#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200

#include "objPos.h"

class objPosArrayList
{
    private:
        objPos* aList; // Pointer to the dynamic array of objPos objects
        int listSize;  // Current number of elements in the list
        int arrayCapacity;  // Current capacity of the array


    public:
        objPosArrayList(); // Constructor
        ~objPosArrayList(); // Destructor

        int getSize() const; // Returns the current size of the list
        void insertHead(const objPos& thisPos); // Inserts an objPos element at the head of the list
        void insertTail(const objPos& thisPos); // Inserts an objPos element at the tail of the list
        void removeHead(); // Removes the head element from the list
        void removeTail(); // Removes the tail element from the list
        
        objPos getHeadElement() const;  // Returns the head element of the list
        objPos getTailElement() const;  // Returns the tail element of the list
        objPos getElement(int index) const;  // Returns the element at a specific index
};

#endif