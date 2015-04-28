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
int tuneEndsEarly(string tuneInput)
{
    int i = tuneInput.length()-1;
    cerr << i << "  ";
    int counter = 0;
    int counter2 = 0;
    do
    {
        counter++;
        i--;
    }
    while(tuneInput[i]=='/');
    cerr << counter << " ";
    if(counter != (tuneInput[i-1]-48))
    {
        for(int j = 0; j<tuneInput.length();j++)
        {
            if(tuneInput[j] == '/')
            {
                counter2++;
            }
        }
    }
    return(counter2+1);
}
string actualTranslation(string inputTune)
{
    string output;
    int slashCounter=0;
    for(int i = 0; i<inputTune.length(); i++)
    {
        if(((isalpha(inputTune[i])&&(islower(inputTune[i]))))||(isalpha(inputTune[i])&&(isupper(inputTune[i]))))
           {
               output += tolower(inputTune[i]);
               slashCounter = 0;
           }
        else if(isdigit(inputTune[i]))
        {
            for(int j = 0; j<(inputTune[i]-48); j++)
            {
                output +=toupper(inputTune[i+1]);
                cerr << j << endl;
            }
            i+=(inputTune[i]-47);
            slashCounter = 0;
        }
        else if(i==0)
        {
            output+= 'x';
            slashCounter++;
        }
        else if(inputTune[i]=='/')
        {
            slashCounter++;
            if(slashCounter>1)
            {
                output += 'x';
            }
            
        }
        cerr << i << endl;
    }
    return(output);
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
    else if (isTuneWellFormed(tune) && (tuneEndsEarly(tune)>1))
    {
        badBeat = tuneEndsEarly(tune);
        return(4);
    }
} */

int main() {
    //bool test;
    //test = isTuneWellFormed(" ");
    //cerr << test;
    string temp;
    temp = actualTranslation("r//y/3g///o/");
    cerr << temp;
    
}