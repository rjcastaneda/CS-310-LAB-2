/*
 * CS 310
 * Project 2: Software Decode
 * Queue.h
 *
 * Programmer Notes:
 *
 * Header for the implementation of Queue Data Structure.
 * Class and its member functions are prototyped here.
 * Definition of functions in Queue.cpp
 *
 */

#ifndef CS_310_PROJECT__2_QUEUE_H
#define CS_310_PROJECT__2_QUEUE_H

const int queueCapacity = 500;

class queue
{

    public:
        queue();
        bool isEmpty();
        void loadValue(int val);
        int nextValue();
        void normalize();
        int* peak(int num);
        int size();

    private:
        short queueData[queueCapacity];
        int front;
        int back;
        int qSize;

};

#endif //CS_310_PROJECT__2_QUEUE_H
