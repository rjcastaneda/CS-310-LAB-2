/*
 * Roswell James Castaneda
 * 820249749
 * CS 310
 * Project 2: Software Decode
 * main.cpp
 *
 * Programmer Notes:
 *
 * The Weapon Codes (Patterns) are in codes.pat
 * The Inputs are in inputs.val
 * All inputs must be in-order and that is assumed.
 * If noise detected, the codes will not be printed out either way.
 *
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "softwareDecode.h"
#include "queue.h"

using namespace std;

//Global variables
//Object array with arrays. 7 Because we are only working with 7 total possible codes.
codes wepCodes[7];
queue* inputCodes = new queue;

bool weaponCodes()
{
    vector<int> data;
    vector<string> sdata;
    string word, wordTwo, line;
    int singleData;
    fstream thefile;
    thefile.open ("codes.pat", ios::in);

    if (thefile.fail())
    {
        cout << "File failed to Open, make sure codes.pat is correct name, restart program." << endl;
        thefile.close();
        return 0;
    }

    if (thefile.is_open()) {
        //grabs all CSV data as a string.
        while(getline(thefile, line))
        {
            stringstream s(line);
            while (getline(s, word, ','))
            {
                sdata.push_back(word);
            }
        }

        //converts the string into integer data.
        for (int x = 0; x < sdata.size(); x++) {
            singleData = stoi(sdata[x]);
            data.push_back(singleData);
        }


        //b is the index of inputCodes, z is the number of weapon codes from input.
        int b = 0, z = data.size() / 7;
        wepCodes[1].numPatterns = z; //Store the number  of patterns found in the 2nd object.
        while (b < z)
        {
            //load the patterns into seperate arrays
            for (int x = 0; x < 7; x++)
            {
                wepCodes[b].weaponCodes[x] = data[x];
            }
            //erase the data stored already.
            for (int x = 0; x < 7; x++)
            {
                data.erase(data.begin());
            }
            b++;
        }
    }

    thefile.close();
    return 1;
}

bool inputs() {
    vector<int> data;
    vector<string> sdata;
    string word, line;
    int singleData;
    fstream thefile;
    thefile.open("inputs.val", ios::in);

    if (thefile.fail())
    {
        cout << "File failed to Open, make sure inputs.val is correct name, restart program." << endl;
        thefile.close();
        return 0;
    }

    if (thefile.is_open())
    {
        //grabs all CSV data as a string.
        while(getline(thefile,line))
        {
            stringstream s(line);
            while (getline(s, word, ',')) {
                sdata.push_back(word);
            }
        }

        //converts the string into integer data.
        for (int x = 0; x < sdata.size(); x++)
        {
            singleData = stoi(sdata[x]);
            data.push_back(singleData);
        }

        //Loads pattern values into queue
        for (int z = 0; z < data.size(); z++)
        {
            inputCodes->loadValue(data[z]);
        }
    }

    thefile.close();
    return 1;
}

void outputFile(queue output)
{
    std::ofstream myfile;
    //Logs the output into an output.txt file.
    myfile.open ("output.txt", std::ios_base::app | ofstream::out);
    while(!output.isEmpty())
    {
        int patNum = output.nextValue();
        int codeOut = wepCodes[patNum].weaponCodes[6];
        for (int x = 0; x < 7; x++)
        {
            if(x == 6)
            {
                myfile << output.nextValue();
            }
            else
            {
            myfile << output.nextValue() << ",";
            }
        }
        myfile <<endl;
        myfile << "Code: "<< codeOut << " Detected." << endl << endl;
    }
    myfile.close();
    return;
}


int main()
{
    bool in = inputs();
    bool pat = weaponCodes();
    if(in == 0 && pat == 0)
    {
        cout<<"Error: Files failed to open, make sure files are named correctly and restart program."<<endl;
    }
    else
    {
        outputFile(softwareDecode(wepCodes, inputCodes));
    }
    return 0;
}