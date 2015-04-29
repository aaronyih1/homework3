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

bool isTuneWellFormed(string tune);
int findLowest(string tuneInput);
int emptyBeats(string tuneInput);
int tuneEndsEarly(string tuneInput);
string actualTranslation(string inputTune);
int translateTune(string tune, string& instructions, int& badBeat);

int main() {
     int output;
     string userInput = "//";
     string instructions;
     int badBeat;
     output = translateTune(userInput, instructions, badBeat);
     cerr << output << endl;
}

bool isTuneWellFormed(string tune){
    for(int i=0; i<tune.length()-1; i++)
    {
        if(tune.length() == 0)
        {
            return(true);
        }
        else if(!isalnum(tune[i])&&(tune[i] != '/')) //checks tune to see if there are any invalid characters
        {
            return(false);
        }
        else if(isalpha(tune[i]) &&(!((tolower(tune[i])=='g')||(tolower(tune[i])=='r')||(tolower(tune[i])=='y')|| (tolower(tune[i])=='b')|| (tolower(tune[i])=='o')))) //checks if there are any invalid colors
        {
            return(false);
        }
        else if(isdigit(tune[i]) && (tune[i+1] == '/')) //checks if there are any numbers w/o a color specified
        {
            return(false);
        }
        else if(isalpha(tune[i]) && (tune[1+i]!='/') ) //checks if there are any colors w/o a beat
        {
            return(false);
        }
    }
    for(int j = 2; j < tune.length()-1; j++) //checks that there aren't any numbers larger than 3 digits in the tune
    {
        if(isdigit(tune[j-2])&&isdigit(tune[j-1])&&isdigit(tune[j]))
           {
               return(false);
           }
    }
    return(true);
}

int findLowest(string tuneInput) // this method finds whether there is a 1 or a 0 beat color in the tune
{
    for(int j = 0; j < tuneInput.length(); j++)
    {
        if(tuneInput[j]=='0')
            return(0);
        else if(tuneInput[j] == '1')
            return(1);
    }
    return(3);
}

int emptyBeats(string tuneInput) //this method checks that there are sufficient empty beats after a long beat
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
int tuneEndsEarly(string tuneInput) //this method checks if the tune ends early, and if it does, it returns 1+the total number of beats
{
    int i = tuneInput.length()-1;
    int counter = 0;
    int counter2 = 0;
    do
    {
        counter++;
        i--;
    }
    while(tuneInput[i]=='/');
    if(counter == tuneInput.length())
    {
        return(0);
    }
    else if(counter != (tuneInput[i-1]-48))
    {
        for(int j = 0; j<tuneInput.length();j++)
        {
            if(tuneInput[j] == '/')
            {
                counter2++;
            }
        }
    }
    cerr << counter2 <<endl;
    return(counter2+1);
}
string actualTranslation(string inputTune) //this function does the actualy translation to the right syntax
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
    }
    return(output);
}
int translateTune(string tune, string& instructions, int& badBeat){

    if(!isTuneWellFormed(tune))
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
    else
    {
        instructions = actualTranslation(tune);
        cerr<<instructions <<endl;
        return(0);
    }
}
