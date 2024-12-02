#include "objPosArrayList.h"
#include <stdexcept> // Include for exception handling


objPosArrayList::objPosArrayList() // Constructor: Initializes an empty array list
{
    arrayCapacity = ARRAY_MAX_CAP; // Set the capacity to the maximum
    listSize = 0; // Initialize the list size to 0
    aList = new objPos[arrayCapacity]; // Allocate memory for the array

    // Initialize all elements in the array with default objPos values
    for (int i = 0; i < arrayCapacity; ++i) 
    {
        aList[i] = objPos();
    }
}


objPosArrayList::~objPosArrayList() // Destructor: Cleans up the dynamic array
{
    delete[] aList; // Deallocate the array
}

// Returns the current size of the list
int objPosArrayList::getSize() const 
{
    return listSize;
}


void objPosArrayList::insertHead(const objPos& thisPos) // Inserts an element at the head of the list 
{
    if (listSize >= arrayCapacity) 
    {
        throw std::overflow_error("Array is full!"); // Prevent overflow
    }

    // Shift elements to the right to make space at the head
    for (int i = listSize; i > 0; --i) 
    {
        aList[i] = aList[i - 1];
    }

    aList[0] = thisPos; // Insert the new element at the head
    listSize++; // Increase the size of the list
}


void objPosArrayList::insertTail(const objPos& thisPos) // Inserts an element at the tail of the list 
{
    if (listSize >= arrayCapacity) 
    {
        throw std::overflow_error("Array is full!"); // Prevent overflow
    }

    aList[listSize] = thisPos; // Add the new element at the tail
    listSize++; // Increase the size of the list
}


void objPosArrayList::removeHead()  // Removes the head element from the list
{
    if (listSize == 0) 
    {
        throw std::underflow_error("Array is empty!"); // Prevent underflow
    }

    // Shift elements to the left to remove the head
    for (int i = 0; i < listSize - 1; ++i) 
    {
        aList[i] = aList[i + 1];
    }

    listSize--; // Decrease the size of the list
}


void objPosArrayList::removeTail()  // Removes the tail element from the list
{
    if (listSize == 0) 
    {
        return; // Prevent underflow
    }

    listSize--; // Decrease the size of the list
}


objPos objPosArrayList::getHeadElement() const  // Returns the head element of the list 
{
    if (listSize == 0) 
    {
        throw std::underflow_error("Array is empty!"); // Prevent underflow
    }

    return aList[0]; // Return the first element
}


objPos objPosArrayList::getTailElement() const // Returns the tail element of the list
{
    if (listSize == 0) 
    {
        throw std::underflow_error("Array is empty!"); // Prevent underflow
    }

    return aList[listSize - 1]; // Return the last element
}


objPos objPosArrayList::getElement(int index) const  // Returns the element at a specific index 
{
    if (index < 0 || index >= arrayCapacity) 
    {
        throw std::out_of_range("Index out of bounds!"); // Prevent out-of-range access
    }

    if (index < listSize) 
    {
        return aList[index]; // Return the element if within bounds
    }

    return objPos(); // Return a default objPos if index is beyond the current size
}