/*
 * Roswell James Castaneda
 * 820249749
 * CS 310
 * Project 2: Software Decode
 * softwareDecode.cpp
 *
 * Programmer Notes:
 *
 *  7 values will be decoded at a time.
 *  This is because only one noise value can be present for a code to be outputted.
 *  Some improvements that could be made are to make the pattern
 *  and noise checker its own function.
 *
 */

#include <iostream>
#include <fstream>
#include<math.h>
#include "softwareDecode.h"
#include "Queue.h"

using namespace std;

queue softwareDecode(codes wCodes[], queue* inputs)
{
    queue queueReturn;
    int noise = 0, matches = 0;
    int difference = 0, differenceTwo = 0;
    int numOne = 0, numTwo = 0, numThree = 0, endVal = 0;
    int tempInputs[7];
    bool noiseEnd = false, notNoise, noiseStart, start, patternFound;

    //Decode the inputs as long as inputs is not empty and there is enough elements for a MilesWord
    while (!inputs->isEmpty() && inputs->size() >= 5)
    {
        //reset variables for next set of inputs
        start = false;
        patternFound = false;
        noiseStart = false;
        notNoise = false;


        //A loop that will keep on searching for start code.
        //Search will stop until a MilesWord is not available.
        while(start == false && inputs->size() >= 5)
        {
            /*
             * If noise value was at the end of previous inputs,
             * make it the first value in 110 code search.
             */
            if(noiseEnd == true)
            {
                numOne = endVal;
                numTwo = inputs->nextValue();
                noiseEnd = false;
            }
            else if(notNoise == true)
            {
                numOne = numTwo;
                numTwo = numThree;
                //reset notNoise if after checking 3rd element in queue is just a stray signal.
                notNoise = false;
            }
            else
            {
                numOne = inputs->nextValue();
                numTwo = inputs->nextValue();
            }

            difference = numTwo - numOne;

            if(difference == 20)
            {
                start = true;
            }
            else if (difference != 20)
            {
                numThree = inputs -> nextValue();
                difference = numThree - numOne;
                if(difference == 20)
                {
                    noiseStart = true;
                    start = true;
                }
                else if(difference != 20)
                {
                    notNoise = true;
                    continue;
                }
            }
        }

        //If a start code sequence is found, begin actual decoding.
        if(start == true)
        {
            if (noiseStart == false)
            {
                tempInputs[0] = numOne;
                tempInputs[1] = numTwo;

                //Load rest of values into a temporary array.
                //7 Values will be decoded at a time.
                for (int x = 2; x < 7; x++)
                {
                    tempInputs[x] = inputs->nextValue();
                }
            }
            if (noiseStart == true)
            {
                tempInputs[0] = numOne;
                tempInputs[1] = numTwo;
                tempInputs[2] = numThree;

                //x = 3 to compensate for noise.
                for (int x = 3; x < 7; x++)
                {
                    tempInputs[x] = inputs->nextValue();
                }
            }



            //Pattern Finder
            //Finds the pattern of the closest match.
            int z = wCodes[1].numPatterns;
            int patNum = 0;
            int a = 0, base = tempInputs[0];
            while (a < z)
            {
                matches = 0;

                for (int x = 0; x < 7; x++)
                {
                    differenceTwo = tempInputs[x] - base;
                    if (differenceTwo == wCodes[a].weaponCodes[x])
                    {
                        matches++;
                    }

                    //to compensate for noise value, checks value after it.
                    //if there is 2 noise values in sequence, pattern won't be found anyway.
                    if (differenceTwo != wCodes[a].weaponCodes[x])
                    {
                        differenceTwo = tempInputs[x + 1] - base;
                        if (differenceTwo == wCodes[a].weaponCodes[x])
                        {
                            matches++;
                        }

                    }

                    if (matches >= 6 && matches < 8)
                    {
                        patternFound = true;
                        patNum = a;
                    }
                }

                if (patternFound == true) {
                    break;
                }

                a++;
            }

            //Noise Checker
            //Checks if pattern is valid enough for output.
            if (patternFound == true)
            {
                for (int x = 0; x < 7; x++)
                {
                    differenceTwo = tempInputs[x] - base;

                    if (differenceTwo != wCodes[patNum].weaponCodes[x])
                    {
                        noise++;
                    }

                    if (differenceTwo != wCodes[patNum].weaponCodes[x] && x == 6)
                    {
                        endVal = tempInputs[x];
                        noiseEnd = true;
                    }

                    if (noise >= 2)
                    {
                        //If there is more than one noise, end loop.
                        break;
                    }

                    if (differenceTwo == wCodes[patNum].weaponCodes[x])
                    {
                        continue;
                    }
                }
            }

            //If noise not found, and there is a pattern, output code.
            if (noise <= 2 && patternFound == true)
            {
                //Load the inputs into a queue to return.
                queueReturn.loadValue(patNum);
                for(int x = 0; x < 7; x++)
                {
                    queueReturn.loadValue(tempInputs[x]);
                }
            }
        }
    }

    //return a queue of valid inputs.
    return queueReturn;
}
