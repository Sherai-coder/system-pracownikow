#include <iostream>
#include "input.h"

using namespace std;
int getInt(const string& message, const int& minRange, const int& maxRange)
{
    while(true)
    {
        int value;
        cout<<message<<endl;
        cin>>value;
        if(!cin.fail())
        {
            if(value>=minRange && value<=maxRange)
            {
                return value;
            }
        }
        cerr<<"Invalid output. Try again. "<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
}

void pause()
{
    cerr<<"Press button to continue."<<endl;
    getch();
    system("cls");
}

string getWord(const string& message)
{
    while(true)
    {
        string word;
        cout<<message<<endl;
        cin>>word;
        bool isValid=true;
        for (char c : word)
        {
            if(!isalpha(c))
            {
                isValid=false;
                break;
            }
        }
        if(!isValid)
        {
            cerr<<"Invalid output. Try again."<<endl;
        }
        else return word;
    }
}

double getDouble(const string& message,const double& minRange, const double& maxRange)
{
    while(true)
    {
        double value=0.0;
        cout<<message<<endl;
        cin>>value;
        if(!cin.fail())
        {
            if(value>=minRange && value<=maxRange)
            {
                return value;
            }
        }
            cerr<<"Invalid output. Try again."<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
}
TypPracownika getWorkerType(const string& message)
{
    while(true)
    {
        string workerType = getWord(message);
        if(stringNaTyp(workerType)!=TypPracownika::Nieznany)
        {
            return stringNaTyp(workerType);
            break;
        }
        else cout<<"Invalid output. Try again."<<endl;
    }
}
