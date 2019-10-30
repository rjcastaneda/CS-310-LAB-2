/*
 * Roswell James Castaneda
 * 820249749
 * CS 310
 * Project 2: Software Decode
 * softwareDecode.h
 *
 * Programmer Notes:
 *
 * Header for the softwareDecode function.
 * The header prototypes everything.
 * softwareDecode.cpp defines the functions.
 *
 */


#ifndef CS_310_PROJECT__2_SOFTWAREDECODE_H
#define CS_310_PROJECT__2_SOFTWAREDECODE_H

#include "Queue.h"

struct codes
{
    int weaponCodes[7];
    int numPatterns;

};

queue softwareDecode(codes wCodes[], queue* in);

#endif //CS_310_PROJECT__2_SOFTWAREDECODE_H
