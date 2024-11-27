#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

#include <stdexcept>
//#include <iostream>

//Contructor
objPosArrayList:: objPosArrayList()
{
    arrayCapacity = ARRAY_MAX_CAP;
    listSize = 0;
    aList = new objPos [arrayCapacity];

    for(int i = 0; i < arrayCapacity;++i)
    {
        aList[i] = objPos();
    }
}

//Destructor
objPosArrayList:: ~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList:: getSize() const
{
    return listSize;
}

void objPosArrayList:: insertHead(const objPos& thisPos)
{
    if(listSize >= arrayCapacity)
    {
        throw std::overflow_error("Array is full!");
    }

    //Shift elements to the right
    for (int i = listSize; i> 0; --i)
    {
        aList[i] = aList[i-1];
    }

    aList[0] = thisPos;
    listSize++;
}

void objPosArrayList:: insertTail (const objPos& thisPos)
{
    if (listSize >= arrayCapacity)
    {
        throw std::overflow_error("Array is full!");
    }

    aList[listSize] = thisPos;
    listSize++;
}

void objPosArrayList::removeHead()
{
    if(listSize == 0)
    {
        throw std::underflow_error ("Array is empty");
    }

    //Shifts elements to the left
    for (int i = 0; i < listSize - 1; ++i)
    {
        aList[i] = aList[ i + 1];
    }

    listSize--;
}

void objPosArrayList::removeTail() {
    if (listSize == 0) {
        // Prevent underflow error
        return;
    }

    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    if(listSize == 0)
    {
        throw std::underflow_error ("Array is empty");
    }

    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    if(listSize == 0)
    {
        throw std::underflow_error ("Array is empty");
    }

    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const
{
    if (index < 0 || index >= arrayCapacity)
    {
        throw std::out_of_range("Index out of bounds!");
    }

    if (index < listSize)
    {
      return aList[index];  
    }

    return objPos();
}


