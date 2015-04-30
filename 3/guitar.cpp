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
     string userInput = "///";
     string instructions;
     int badBeat;
     output = translateTune(userInput, instructions, badBeat);
     cerr << output << endl;
}

bool isTuneWellFormed(string tune){
    int count=0;
    for(int i=0; i<tune.length();i++)
    {
        if(isspace(tune[i]))
        {
            count++;
        }
    }
    if(count == tune.length())
    {
        return(true);
    }
    for(int i=0; i<tune.length()-1; i++)
    {
        if(tune[tune.length()-1] != '/')
        {
            return(false);
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
    if(tuneInput.length()==0)
    {
        return(1);
    }
    for(int j = 0; j < tuneInput.length()-1; j++)
    {
        if((tuneInput[j]-48==1 || tuneInput[j]-48==0)&&isalpha(tuneInput[j+1])&& !(isalnum(tuneInput[j-1])))
        {
            return(0);
        }
            
    }
    return(1);
}

int emptyBeats(string tuneInput) //this method checks that there are sufficient empty beats after a long beat
{
    if(tuneInput.length()==0)
    {
        return(0);
    }
    int counter=0;
    for(int j = 0; j < tuneInput.length()-1; j++)
    {
        if((isdigit(tuneInput[j]))&&(isalpha(tuneInput[j+1])))
        {
            for(int i = j+2; tuneInput[i]=='/'; i++)
            {
                counter++;
            }
            if(counter < (tuneInput[j]-48))
            {
                return(counter);
            }
        }
        else if((isdigit(tuneInput[j]))&&(isdigit(tuneInput[j+1])))
        {
            for(int i = j+3; tuneInput[i]=='/'; i++)
            {
                counter++;
            }
            if(counter < ((tuneInput[j]-48)*10)+((tuneInput[j+1])-48))
            {
                return(counter);
            }
        }
    }
    return(0);
}
int tuneEndsEarly(string tuneInput) //this method checks if the tune ends early, and if it does, it returns 1+the total number of beats
{
    if(tuneInput.length()==0)
    {
        return(0);
    }
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
    else if(counter == 1)
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
    return(counter2+1);
}
string actualTranslation(string inputTune) //this function does the actual translation to the right syntax
{
    string output;
    int slashCounter=0;
    if(inputTune.length()==0)
    {
        output="";
        return(output);
    }
    for(int i = 0; i < inputTune.length()-1; i++)
    {
        if(isdigit(inputTune[i])&&isalpha(inputTune[i+1]))
        {
            for(int j = 0; j<(inputTune[i]-48); j++)
            {
                output +=toupper(inputTune[i+1]);
            }
            i+=(inputTune[i]-47);
            slashCounter = 0;
        }
        else if(isdigit(inputTune[i])&&isdigit(inputTune[i+1]))
        {
            for(int j = 0; j<(((inputTune[i]-48)*10)+(inputTune[i+1]-48)); j++)
            {
                output +=toupper(inputTune[i+2]);
            }
            cerr<<((((inputTune[i]-48)*10)+(inputTune[i+1]-48))+3)<< endl;
            i=i+((((inputTune[i]-48)*10)+(inputTune[i+1]-48))+3);
            slashCounter = 0;
        }
        else if(isalpha(inputTune[i]))
        {
            output += tolower(inputTune[i]);
            slashCounter = 0;
        }
        if(inputTune[i]=='/')
        {
            output+='x';
        }
    }
    /*for(int i = 0; i<inputTune.length(); i++)
    {
        if(isalpha(inputTune[i]))
           {
               cerr<<"you fail ma" << endl;
               cerr<<output<<endl;
               output += tolower(inputTune[i]);
               cerr<<"this is outpu2:"<<output<<endl;
               slashCounter = 0;
               i++;
           }
    } */
    int number=0;
    for(int i=0; i<inputTune.length(); i++)
    {
        if(inputTune[i]=='/')
        {
            number++;
        }
    }
    if(number==inputTune.length())
    {
        output+='x';
    }
    for(int i=1; i< inputTune.length();i++){
        if((inputTune[i+1]=='/')&& isdigit(inputTune[i-1]))
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
    else if(isTuneWellFormed(tune)&& (findLowest(tune)==0))
    {
        badBeat = findLowest(tune);
        return(2);
    }
    else if(isTuneWellFormed(tune)&& (emptyBeats(tune)>0))
    {
        badBeat = emptyBeats(tune);
        return(3);
    }
    else if (isTuneWellFormed(tune) && ((tuneEndsEarly(tune))>1))
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
