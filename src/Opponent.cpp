#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "Opponent.h"

using namespace std;

void opponent::createo()
{
    srand(time(NULL));
    lvl=rand()%10;
    if(lvl==0)
    {
        defence=10;
        attack=16;
    }
    else
    {
        defence=8+(lvl*4);
        attack=18+(lvl*4);
    }
    money=100+(lvl*100);
    exp=10+(lvl*10);
    hp=50+(lvl*30);
}

void opponent::showo()
{
    cout<<"OPPONENT Level: "<<lvl<<"\nAttack: "<<attack<<"\tDefence: "<<defence<<"\t\tHP: ";
}

void opponent::showt()
{
    cout<<"OPPONENT: "<<name<<"\tLevel: "<<lvl<<"\nAttack: "<<attack<<"\tDefence: "<<defence<<"\t\tHP: ";
}

int opponent::rethp()
{
    return hp;
}

int opponent::retatt()
{
    return attack;
}

int opponent::retdef()
{
    return defence;
}

int opponent::retlvl()
{
    return lvl;
}

int opponent::retmoney()
{
    return money;
}

int opponent::retexp()
{
    return exp;
}

char* opponent::retname()
{
    return name;
}
