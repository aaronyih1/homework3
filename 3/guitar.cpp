//
//  guitar.cpp
//  3
//
//  Created by Aaron Yih on 4/24/15.
//  Copyright (c) 2015 aaronyih. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool isTuneWellFormed(string tune){
    for(int i=0; i<tune.length()-1; i++)
    {
        if(tune.length() == 0)
        {
            return(true);
        }
        else if(isdigit(tune[i]) && (tune[i+1] == '/'))
        {
            return(false);
        }
        else if(isalpha(tune[i]) && (tune[1+i]!='/') )
        {
            return(false);
        }
    }
    return(true);
}

int findLowest(string tuneInput)
{
    for(int j = 0; j < tuneInput.length(); j++)
    {
        cerr << "in the for loop";
        cerr << tuneInput[j]<< endl;
        if(tuneInput[j]=='0')
            return(0);
        else if(tuneInput[j] == '1')
            return(1);
    }
    return(3);
}

int emptyBeats(string tuneInput)
{
    int counter=0;
    for(int j = 0; j < tuneInput.length(); j++)
    {
        if(isdigit(tuneInput[j]))
        {
            for(int i = j+2; tuneInput[i] =='/'; i++)
            {
                counter++;
            }
            if(counter != (tuneInput[j]-48))
            {
                return(counter);
            }
        }
        counter = 0;
    }
    return(0);
}
/*int translateTune(string tune, string& instructions, int& badBeat){
    if(isTuneWellFormed(tune))
    {
        instructions = tune;
        return(0);
    }
    else if(!isTuneWellFormed(tune))
    {
        return(1);
    }
    else if(isTuneWellFormed(tune)&& (findLowest(tune)<2))
    {
        badBeat = findLowest(tune);
        return(2);
    }
 else if(isTuneWellFormed(tune)&& (emptyBeats(tune)>0))
    {
        badBeat = emptyBeats(tune);
        return(3);
    }
} */

int main() {
    //bool test;
    //test = isTuneWellFormed(" ");
    //cerr << test;
    int temp;
    temp = emptyBeats("r//y/3g///o/");
    cerr << temp;
    
}