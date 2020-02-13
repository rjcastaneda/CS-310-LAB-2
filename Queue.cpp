/*
 * CS 310
 * Project 2: Software Decode
 * queue.cpp
 *
 * Programmer Notes:
 *
 * Definition of Queue Class member functions.
 *
 */

#include "queue.h"
#include <iostream>

using namespace std;

queue::queue()
{
    front = back = -1;
    qSize = 0;
}

bool queue::isEmpty()
{
    return (front == back);
}

void queue::loadValue(int val)
{
    // % allows for wrap around of array.
   int newBack = (back + 1) % queueCapacity;
   if (newBack != front)
   {
       back = newBack;
       queueData[back] = val;
       qSize++;
   }
}

int queue::nextValue()
{
    if(!isEmpty())
    {
        front = (front + 1) % queueCapacity;
        qSize--;
        return queueData[front];
    }
    else
    {
        cout << "There is no other next value to grab" << endl;
        return -1;
    }
}

void queue::normalize()
{
    if( !isEmpty())
    {
        for (int x = 0; x < back; x++)
        {
            front = front - queueData[x];
        }
    }
}

int queue::size()
{
   return qSize;
}

int* queue::peak(int num)
{
    int temp[num];
    if((front+num % queueCapacity) < size())
    {
        for (int x = 0;x < num;x++)
        {
            temp[x] = queueData[front+7+x];
        }
    }
    return temp;
}
