#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "Player.h"

using namespace std;

void player::createp()
{
    cout<<"\nEnter name: ";
    cin.getline(name,20);
    fw=0; fl=0; exp=0; hp=50; money=0; lvl=0; attack=20; defence=10; hps=0; shps=0; mhps=0; tour=0; loan=0;
    cout<<"\nPlayer details:";
    show();
}

void player::show()
{
    cout<<"\nFighter: "<<name<<"\nExperience: "<<exp<<"\t\tLevel: "<<lvl<<"\t\tMoney: "<<money<<"\nAttack: "<<attack<<"\t\tDefence: "<<defence<<"\t\tHP: "<<hp<<"\nFights won: "<<fw<<"\t\tFights lost: "<<fl<<"\t\tTournaments won: "<<tour;
}

int player::retatt()
{
    return attack;
}

int player::retdef()
{
    return defence;
}

char* player::retname()
{
    return (name);
}

int player::rethp()
{
    return hp;
}

int player::retexp()
{
    return exp;
}

int player::retmoney()
{
    return money;
}

int player::retlvl()
{
    return lvl;
}

int player::rethps()
{
    return hps;
}

int player::retshps()
{
    return shps;
}

int player::retmhps()
{
    return mhps;
}

int player::retloan()
{
    return loan;
}

void player::loanexp()
{
    exp=exp-5;
}

void player::takeloan(int l,int n)
{
    if(n==1)
    {
        loan=loan+(l*2);
        money=money+l;
        cout<<"\nYou loaned $$$: "<<l<<" from the bank!";
        getch();
    }
    else if(n==2)
    {
        loan=loan-l;
        money=money-l;
        cout<<"\nYou repaid $$$: "<<l<<" to the bank!";
        getch();
    }
}

void player::takemoney()
{
    money=money-(lvl*25);
}

void player::win(int l, int ph)
{
    fw++;
    if(ph==hp)
    {
        cout<<"PERFECT!";
        Sleep(400);
        cout<<"\n\nYOU WIN!\n\nEXPERIENCE EARNED: "<<10+(l*10)<<" x 2\n\nMONEY EARNED: "<<100+(l*100)<<" x 2";
        exp=exp+20+(l*20);
        money=money+200+(l*200);
    }
    else
    {
        cout<<"YOU WIN!\n\nEXPERIENCE EARNED: "<<10+(l*10)<<"\n\nMONEY EARNED: "<<100+(l*100);
        exp=exp+10+(l*10);
        money=money+100+(l*100);
    }
    if(exp/(100+(lvl*50))>lvl)
    {
        cout<<"\n\n\n\nLEVEL UP!!";
        attack=attack+4; defence=defence+4; hp=hp+20; money=money+400+(lvl*200); lvl++;
        cout<<"\n\nNEW STATS:\nHP: "<<hp<<"\t\tAttack: "<<attack<<"\t\tDefence: "<<defence<<"\t\tMoney: "<<money<<"\n\nSpecial Ability Success Rate: "<<10+(3*lvl)<<"%\n\nCounter Success Rate: "<<10+(3*lvl)<<'%';
    }
    else
    cout<<"\n\nEperience needed for next level: "<<(lvl+1)*(100+(lvl*50))-exp;
}

void player::lose(int l)
{
    fl++;
    if(l>lvl+1)
    {
        if(exp!=0)
        exp=exp-20;
        money=money-200;
        cout<<"\n\nEXPERIENCE LOST: 20\n\nMONEY LOST: 200";
    }
    else if(l==lvl||l==lvl+1)
    {
        if(exp!=0)
        exp=exp-30;
        money=money-300;
        cout<<"\n\nEXPERIENCE LOST: 30\n\nMONEY LOST: 300";
    }
    else
    {
        l=lvl-l;
        if(exp!=0)
        exp=exp-(50*l);
        money=money-(500*l);
        cout<<"\n\nEXPERIENCE LOST: "<<50*l<<"\n\nMONEY LOST: "<<500*l;
    }
    if(exp<0)
    exp=0;
    cout<<"\n\nEperience needed for next level: "<<(lvl+1)*(100+(lvl*50))-exp;
}

void player::incatt()
{
    if(money>=500+(lvl*250))
    {
        attack=attack+2;
        money=money-(500+(lvl*250));
    }
    else
    {
        cout<<"\nInsufficient money!";
        getch();
    }
}

void player::incdef()
{
    if(money>=500+(lvl*250))
    {
        defence=defence+1;
        money=money-(500+(lvl*250));
    }
    else
    {
        cout<<"\nInsufficient money!";
        getch();
    }
}

void player::inchp()
{
    if(money>=500+(lvl*250))
    {
        hp=hp+2;
        money=money-(500+(lvl*250));
    }
    else
    {
        cout<<"\nInsufficient money!";
        getch();
    }
}

void player::inchps()
{
    if(money>=50+(lvl*100))
    {
        hps++;
        money=money-(50+(lvl*100));
    }
    else
    {
        cout<<"\nInsufficient money!";
        getch();
    }
}

int player::dechps(int ph)
{
    int temp;
    if(hps>0)
    {
        hps--;
        temp=ph+25;
        cout<<"\nYou replenished 25HP!";
        if(temp>hp)
        temp=hp;
        return temp;
    }
    else
    {
        cout<<"\nYou don't have enough Normal HP Shots!";
        return ph;
    }
}

void player::incshps()
{
    if(money>=100+(lvl*200))
    {
        shps++;
        money=money-(100+(lvl*200));
    }
    else
    {
        cout<<"\nInsufficient money!";
        getch();
    }
}

int player::decshps(int ph)
{
    int temp;
    if(shps>0)
    {
        shps--;
        temp=ph+50;
        cout<<"\nYou replenished 50HP!";
        if(temp>hp)
        temp=hp;
        return temp;
    }
    else
    {
        cout<<"\nYou don't have enough Super HP Shots!";
        return ph;
    }
}

void player::incmhps()
{
    if(money>=250+(lvl*250))
    {
        mhps++;
        money=money-(250+(lvl*250));
    }
    else
    {
        cout<<"\nInsufficient money!";
        getch();
    }
}

int player::decmhps(int ph)
{
    if(mhps>0)
    {
        mhps--;
        cout<<"\nYou replenished all your HP!";
        return hp;
    }
    else
    {
        cout<<"\nYou don't have enough Mega HP Shots!";
        return ph;
    }
}

void player::tourney(int num)
{
    system("cls");
    cout<<"YOU WON THE TOURNAMENT!";
    if(num==1)
    {
        cout<<"\n\nEXPERIENCE EARNED: 40\n\nMONEY EARNED: 400";
        money+=400;
        exp+=40;
    }
    else if(num==2)
    {
        cout<<"\n\nEXPERIENCE EARNED: 100\n\nMONEY EARNED: 1000";
        money+=1000;
        exp+=100;
    }
    else if(num==3)
    {
        cout<<"\n\nEXPERIENCE EARNED: 200\n\nMONEY EARNED: 2000";
        money+=2000;
        exp+=200;
    }
    else
    {
        system("cls");
        cout<<"\nYOU DEFEATED TYLER DURDEN!";
        cout<<"\n\nEXPERIENCE EARNED: 20000\n\nMONEY EARNED: 2000";
        money+=20000;
        exp+=2000;
    }
    if(exp/(100+(lvl*50))>lvl)
    {
        cout<<"\n\n\n\nLEVEL UP!!";
        attack=attack+4; defence=defence+4; hp=hp+20; money=money+400+(lvl*200); lvl++;
        cout<<"\n\nNEW STATS:\nHP: "<<hp<<"\t\tAttack: "<<attack<<"\t\tDefence: "<<defence<<"\t\tMoney: "<<money<<"\n\nSpecial Ability Success Rate: "<<10+(3*lvl)<<"%\n\nCounter Success Rate: "<<10+(3*lvl)<<'%';
    }
    else
    cout<<"\n\nEperience needed for next level: "<<(lvl+1)*(100+(lvl*50))-exp;
    tour++;
}

void player::tourmoney(int num)
{
    if(num==1)
    money=money-200;
    else if(num==2)
    money=money-500;
    else if(num==3)
    money=money-1000;
    else if(num==4)
    money=money-10000;
}
