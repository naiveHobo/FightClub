#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <limits>
#include "Player.h"
#include "Opponent.h"

using namespace std;

fstream fin,fout;
player p1,p2;
opponent o1;
char use[20],ch2,n1[20],n2[20];
int mch,fch,ch1,flag,found,flag1,flag2,pos,ch3,i,score1,score2;

char* getString(){
    cin.ignore();
    cin.getline(n1,20);
    return n1;
}

int getInt(){
	int x = 0;
	while(!(cin >> x)){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout<<"\n\aERROR: Invalid Input. Try again: ";
	}
	return x;
}

void usep(char n[20])
{
	found=0;
	fin.open("fightclub.dat",ios::in|ios::binary);
	while(fin.read((char*)&p1,sizeof(p1)))
	{
		if(strcmp(n,p1.retname())==0)
		{
			cout<<"\nWelcome back "<<n<<". Are you ready to fight? (y/n): ";
			cin>>ch2;
			if(ch2=='y'||ch2=='Y')
			{
				p2=p1;
				flag=1;
				pos=fin.tellg();
			}
			else
			flag=0;
			found=1;
		}
	}
	fin.close();
	if(found==0)
	{
		cout<<"\nPlayer not found!";
		flag=0;
	}
}

void editp(char n[20])
{
	found=0;
	fin.open("fightclub.dat",ios::in|ios::binary);
	fout.open("temp.dat",ios::out|ios::binary);
	while(fin.read((char*)&p1,sizeof(p1)))
	{
		if(strcmp(n,p1.retname())==0)
		{
			cout<<"\nPlayer found!\n\nEditing will reset the attributes of the fighter.\n\nDo you want to continue? (y/n): ";
			cin>>ch2;
			if(ch2=='y'||ch2=='Y')
			{
				cout<<"\nEnter the details:\n";
				p1.createp();
				found=1;
			}
			else
			found=2;
		}
		fout.write((char*)&p1,sizeof(p1));
	}
	if(found==0)
	cout<<"\n\nPlayer not found!";
	if(found==1)
	cout<<"\n\nEDIT SUCCESSFUL!";
	fin.close();
	fout.close();
	remove("fightclub.dat");
	rename("temp.dat","fightclub.dat");
	flag=0;
}

void delp(char n[20])
{
	found=0;
	fin.open("fightclub.dat",ios::in|ios::binary);
	fout.open("temp.dat",ios::out|ios::binary);
	while(fin.read((char*)&p1,sizeof(p1)))
	{
		if(strcmp(n,p1.retname())!=0)
		fout.write((char*)&p1,sizeof(p1));
		else
		{
			found=1;
			cout<<"\nPLAYER SUCCESSFULLY DELETED!";
		}
	}
	if(found==0)
	cout<<"\nPlayer not found!";
	fin.close();
	fout.close();
	remove("fightclub.dat");
	rename("temp.dat","fightclub.dat");
	flag=0;
}

void leaderboard()
{
	int cnt=0,pos;
	player t,sp;
	fin.open("fightclub.dat",ios::in|ios::binary);
	while(fin.read((char*)&p1,sizeof(p1)))
	cnt++;
	fin.close();
	player *sarr = new player[cnt];
	fin.open("fightclub.dat",ios::in|ios::binary);
	for(i=0;i<cnt;i++)
	{
		fin.read((char*)&p1,sizeof(p1));
		sarr[i]=p1;
	}
	fin.close();
	for(i=0;i<cnt-1;i++)
	{
		sp=sarr[i]; pos=i;
		for(int j=i+1;j<cnt;j++)
		{
			if(sp.retexp()<sarr[j].retexp())
			{
				sp=sarr[j]; pos=j;
			}
		}
		t=sarr[i];
		sarr[i]=sarr[pos];
		sarr[pos]=t;
	}
	system("cls");
	cout<<"LEADERBOARD:\n\n";
	for(i=0;i<cnt;i++)
	cout<<"POSITION: "<<i+1<<"\nFighter: "<<sarr[i].retname()<<"\t\tExperience: "<<sarr[i].retexp()<<"\t\tLevel: "<<sarr[i].retlvl()<<"\n\n";
	flag=0;
}

void updatep(player &p)
{
	fin.open("fightclub.dat",ios::in|ios::binary);
	fout.open("temp.dat",ios::out|ios::binary);
	while(fin.read((char*)&p1,sizeof(p1)))
	{
		if(strcmp(p.retname(),p1.retname())==0)
		fout.write((char*)&p,sizeof(p));
		else
		fout.write((char*)&p1,sizeof(p1));
	}
	fin.close();
	fout.close();
	remove("fightclub.dat");
	rename("temp.dat","fightclub.dat");
	for(i=0;i<3;i++)
	{
		system("cls");
		cout<<"AUTOSAVING PROGRESS";
		for(int j=0;j<4;j++)
		{
            Sleep(250);
			cout<<'.';
		}
	}
	system("cls");
	cout<<"AUTOSAVE SUCCESSFUL!";
	getch();
}

void fight(player &p, opponent o)
{
	int php,ohp,ch,patt,oatt,pdef,odef,olvl;
	php=p.rethp();
	ohp=o.rethp();
	olvl=o.retlvl();
	while(php>0 && ohp>0)
	{
		system("cls");
		o.showo();
		cout<<ohp;
		cout<<"\n\nFIGHTER: "<<p.retname()<<"\t\tLevel: "<<p.retlvl()<<"\nAttack: "<<p.retatt()<<"\tDefence: "<<p.retdef()<<"\t\tHP: "<<php;
		cout<<"\n\n 1. Attack\n 2. Use HP Shot\n 3. Special Ability (Success rate: "<<10+(3*p.retlvl())<<"%)\n\nEnter your choice: ";
		ch = getInt();
		srand(time(NULL));
		patt=rand()%p.retatt();
		oatt=rand()%o.retatt();
		pdef=rand()%p.retdef();
		odef=rand()%o.retdef();
		Sleep(500);
		switch(ch)
		{
			case 1:
			if(odef<6+(2*olvl))
			{
				cout<<"\nDamage caused: "<<patt;
				ohp=ohp-patt;
			}
			else
			cout<<"\nOpponent defended your attack!";
			break;
			case 2:
			cout<<"\nHP Shot:\n 1. Normal HP Shot (25HP) \t Available: "<<p.rethps()<<"\n 2. Super HP Shot (50HP) \t Available: "<<p.retshps()<<"\n 3. Mega HP Shot (Full) \t Available: "<<p.retmhps()<<"\nEnter your choice: ";
			ch3 = getInt();
			switch(ch3)
			{
				case 1:
				php=p.dechps(php);
				break;
				case 2:
				php=p.decshps(php);
				break;
				case 3:
				php=p.decmhps(php);
				break;
				default: cout<<"\nWRONG CHOICE!\n\nAttack missed!";
			}
			break;
			case 3:
			srand(time(NULL));
			if(rand()%(20+p.retlvl())<3+p.retlvl())
			{
				cout<<"\nCRITICAL HIT\n\n Damage caused: "<<30+(5*p.retlvl());
				ohp=ohp-(30+(5*p.retlvl()));
			}
			else
			cout<<"\nSpecial ability failed!";
			break;
			default: cout<<"\nWRONG CHOICE!\n\nOpponent defended your attack!";
		}
		Sleep(500);
		if((rand()%10)>0)
		{
			cout<<"\n\nOpponent attacked you!";
			cout<<"\n\n 1. Defend\n 2. Counter (Success rate= "<<10+(3*p.retlvl())<<"%)\n\nEnter choice: ";
			ch = getInt();
			switch(ch)
			{
				case 1:
				if(pdef<5+(2*p.retlvl()))
				{
					cout<<"\nDefence failed!\n\nDamage caused: "<<oatt;
					php=php-oatt;
				}
				else
				cout<<"\nYou defended your opponent's attack!";
				break;
				case 2:
				srand(time(NULL));
				if((rand()%20+p.retlvl())<3+p.retlvl())
				{
					cout<<"\nCOUNTER SUCCESSFUL\n\n Damage caused: "<<10+(5*p.retlvl());
					ohp=ohp-(10+(5*p.retlvl()));
				}
				else
				{
					cout<<"\nCounter failed!\n\nDamage caused: "<<oatt;
					php=php-oatt;
				}
				break;
				default: { cout<<"\nWRONG CHOICE!\n\nDamage caused: "<<oatt; php=php-oatt; }
			}
		}
		else
		{
			if(ohp<o.rethp()-(p.retlvl()*5)-4)
			ohp=ohp+5+(p.retlvl()*5);
			else
			ohp=o.rethp();
			cout<<"\n\nOpponent replenished "<<5+p.retlvl()*5<<"HP";
		}
		getch();
	}
	system("cls");
	if(ohp<=0)
	{
		p.win(olvl,php);
	}
	else if(php<=0)
	{
		cout<<"\nYOU LOSE!";
		p.lose(olvl);
	}
	getch();
	if(p.retloan()>0)
	p.loanexp();
}

void twop(char name1[20], char name2[20])
{

	int ch1,ch2,ch3,hp1=100,hp2=100,nhps1=1,nhps2=1,shps1=1,shps2=1,mhps1=1,mhps2=1,p1att,p2att,p1def,p2def;
	while(hp1>0 && hp2>0)
	{
		system("cls");
		cout<<"FIGHTER 1: "<<name1<<"\nATTACK: 25\t\tHP: "<<hp1;
		cout<<"\n\n 1. Attack\n 2. Use HP Shot\n 3. Special Ability (Success rate: 10%)\n\nEnter your choice: ";
		ch1 = getInt();
		srand(time(NULL));
		p1att=rand()%25;
		p2att=rand()%25;
		p1def=rand()%15;
		p2def=rand()%15;
		switch(ch1)
		{
			case 1:
			cout<<"\n\nFIGHTER 2: "<<name2<<"\nDEFENCE: 15\t\tHP: "<<hp2<<"\n\n 1. Defend\n 2. Counter (Success rate= 10%)\n\nEnter choice: ";
			ch2 = getInt();
			switch(ch2)
			{
				case 1:
				if(p2def%2==0)
				{
					cout<<'\n'<<name2<<"'s defence failed!\n\nDamage caused: "<<p1att;
					hp2=hp2-p1att;
				}
				else
				cout<<'\n'<<name2<<" defended "<<name1<<"'s attack!";
				break;
				case 2:
				srand(time(NULL));
				if((rand()%20)/4==0)
				{
					cout<<"\nCOUNTER SUCCESSFUL\n\n Damage caused: "<<10;
					hp1=hp1-10;
				}
				else
				{
					cout<<"\nCounter failed!\n\nDamage caused: "<<p1att;
					hp2=hp2-p1att;
				}
				break;
				default: { cout<<"\nWRONG CHOICE!\n\nDamage caused: "<<p1att; hp2=hp2-p1att; }
			}
			break;
			case 2:
			cout<<"\nHP Shot:\n 1. Normal HP Shot (20HP) \t Available: "<<nhps1<<"\n 2. Super HP Shot (40HP) \t Available: "<<shps1<<"\n 3. Mega HP Shot (Full) \t Available: "<<mhps1<<"\nEnter your choice: ";
			ch3 = getInt();
			switch(ch3)
			{
				case 1:
				if(nhps1==1)
				{
					nhps1=0;
					hp1=hp1+20;
					if(hp1>100)
					hp1=100;
					cout<<"\n\n"<<name1<<" replenished 20HP";
				}
				else
				cout<<"\n\nNot available!";
				break;
				case 2:
				if(shps1==1)
				{
					shps1=0;
					hp1=hp1+40;
					if(hp1>100)
					hp1=100;
					cout<<"\n\n"<<name1<<" replenished 40HP";
				}
				else
				cout<<"\n\nNot available!";
				break;
				case 3:
				if(mhps1==1)
				{
					cout<<"\n\n"<<name1<<" replenished "<<100-hp1<<"HP";
					mhps1=0;
					hp1=100;
				}
				else
				cout<<"\n\nNot available!";
				break;
				default: cout<<"\nWRONG CHOICE!\n\nAttack missed!";
			}
			break;
			case 3:
			srand(time(NULL));
			if((rand()%20)/4==0)
			{
				cout<<"\n\nFIGHTER 2: "<<name2<<"\nDEFENCE: 15\t\tHP: "<<hp2<<"\n\n 1. Defend\n 2. Counter (Success rate= 10%)\n\nEnter choice: ";
				ch2 = getInt();
				switch(ch2)
				{
					case 1:
					if(p2def%2==0)
					{
						cout<<'\n'<<name2<<"'s defence failed!\n\nCRITICAL HIT!\nDamage caused: 40";
						hp2=hp2-40;
					}
					else
					cout<<'\n'<<name2<<" defended "<<name1<<"'s attack!";
					break;
					case 2:
					if((rand()%20)/4==0)
					{
						cout<<"\nCOUNTER SUCCESSFUL\n\nCRITICAL HIT\nDamage caused: 15";
						hp1=hp1-15;
					}
					else
					{
						cout<<"\nCounter failed!\n\nCRITICAL HIT\nDamage caused: 40";
						hp2=hp2-40;
					}
					break;
					default: { cout<<"\nWRONG CHOICE!\n\nCRITICAL HIT\nDamage caused: 40"; hp2=hp2-40; }
				}
			}
			else
			cout<<"\nSpecial ability failed!";
			break;
			default: cout<<"\nWRONG CHOICE!\n\nAttack missed!";
		}
		getch();
		system("cls");
		if(hp2<=0)
		{
			cout<<name1<<" wins!";
			score1++;
			getch();
			break;
		}
		cout<<"FIGHTER 2: "<<name2<<"\nATTACK: 25\t\tHP: "<<hp2;
		cout<<"\n\n 1. Attack\n 2. Use HP Shot\n 3. Special Ability (Success rate: 10%)\n\nEnter your choice: ";
		ch1 = getInt();
		switch(ch1)
		{
			case 1:
            cout<<"\n\nFIGHTER 1: "<<name1<<"\nDEFENCE: 15\t\tHP: "<<hp1<<"\n\n 1. Defend\n 2. Counter (Success rate= 10%)\n\nEnter choice: ";
			ch2 = getInt();
			switch(ch2)
			{
				case 1:
				if(p1def%2==0)
				{
					cout<<'\n'<<name1<<"'s defence failed!\n\nDamage caused: "<<p2att;
					hp1=hp1-p2att;
				}
				else
				cout<<'\n'<<name1<<" defended "<<name2<<"'s attack!";
				break;
				case 2:
				srand(time(NULL));
				if((rand()%20)/4==0)
				{
					cout<<"\nCOUNTER SUCCESSFUL\n\n Damage caused: "<<10;
					hp2=hp2-10;
				}
				else
				{
					cout<<"\nCounter failed!\n\nDamage caused: "<<p2att;
					hp1=hp1-p2att;
				}
				break;
				default: { cout<<"\nWRONG CHOICE!\n\nDamage caused: "<<p2att; hp1=hp1-p2att; }
			}
			break;
			case 2:
			cout<<"\nHP Shot:\n 1. Normal HP Shot (20HP) \t Available: "<<nhps2<<"\n 2. Super HP Shot (40HP) \t Available: "<<shps2<<"\n 3. Mega HP Shot (Full) \t Available: "<<mhps2<<"\nEnter your choice: ";
			ch3 = getInt();
			switch(ch3)
			{
				case 1:
				if(nhps2==1)
				{
					nhps2=0;
					hp2=hp2+20;
					if(hp2>100)
					hp2=100;
					cout<<"\n\n"<<name2<<" replenished 20HP";
				}
				else
				cout<<"\n\nNot available!";
				break;
				case 2:
				if(shps2==1)
				{
					shps2=0;
					hp2=hp2+40;
					if(hp2>100)
					hp2=100;
					cout<<"\n\n"<<name2<<" replenished 40HP";
				}
				else
				cout<<"\n\nNot available!";
				break;
				case 3:
				if(mhps2==1)
				{
					cout<<"\n\n"<<name2<<" replenished "<<100-hp2<<"HP";
					mhps2=0;
					hp2=100;
				}
				else
				cout<<"\n\nNot available!";
				break;
				default: cout<<"\nWRONG CHOICE!\n\nAttack missed!";
			}
			break;
			case 3:
			srand(time(NULL));
			if((rand()%20)/4==0)
			{
				cout<<"\n\nFIGHTER 1: "<<name1<<"\nDEFENCE: 15\t\tHP: "<<hp1<<"\n\n 1. Defend\n 2. Counter (Success rate= 10%)\n\nEnter choice: ";
				ch2 = getInt();
				switch(ch2)
				{
					case 1:
					if(p1def%2==1)
					{
						cout<<'\n'<<name1<<"'s defence failed!\n\nCRITICAL HIT!\nDamage caused: 40";
						hp1=hp1-40;
					}
					else
					cout<<'\n'<<name1<<" defended "<<name2<<"'s attack!";
					break;
					case 2:
					if((rand()%20)/4==0)
					{
						cout<<"\nCOUNTER SUCCESSFUL\n\nCRITICAL HIT\nDamage caused: 15";
						hp2=hp2-15;
					}
					else
					{
						cout<<"\nCounter failed!\n\nCRITICAL HIT\nDamage caused: 40";
						hp1=hp1-40;
					}
					break;
					default: { cout<<"\nWRONG CHOICE!\n\nCRITICAL HIT\nDamage caused: 40"; hp1=hp1-40; }
				}
			}
			else
			cout<<"\nSpecial ability failed!";
			break;
			default: cout<<"\nWRONG CHOICE!\n\nAttack missed!";
		}
		getch();
		system("cls");
		if(hp1<=0)
		{
			cout<<name2<<" wins!";
			score2++;
			getch();
			break;
		}
	}
	system("cls");
	cout<<"SCORE:\n\n"<<name1<<": "<<score1<<'\n'<<name2<<": "<<score2;
}

void tournament(player &p, int num)
{
	int nf,cnt=0,win;
	switch(num)
	{
		case 1:
		if(p.retmoney()<200)
		{
			cout<<"\n\nYOU DON'T HAVE ENOUGH MONEY!";
			return;
		}
		else
		p.tourmoney(num);
		nf=3;
		break;
		case 2:
		if(p.retmoney()<500)
		{
			cout<<"\n\nYOU DON'T HAVE ENOUGH MONEY!";
			return;
		}
		else
		p.tourmoney(num);
		nf=4;
		break;
		case 3:
		if(p.retmoney()<1000)
		{
			cout<<"\n\nYOU DON'T HAVE ENOUGH MONEY!";
			return;
		}
		else
		p.tourmoney(num);
		nf=5;
		break;
		case 4:
		if(p.retmoney()<10000)
		{
			cout<<"\n\nYOU DON'T HAVE ENOUGH MONEY!";
			return;
		}
		else
		p.tourmoney(num);
		break;
		case 5:
		break;
		default:
		{
			cout<<"\n\nWRONG CHOICE!";
			return;
		}
	}
	opponent opp;
	fstream fin;
	fin.open("opponents.dat",ios::binary|ios::in);
	opponent *arr= new opponent[nf];
	for(i=0;i<nf;i++)
	{
		srand(time(NULL));
		pos=rand()%32;
		fin.seekg(pos*sizeof(opp));
		fin.read((char*)&opp,sizeof(opp));
		arr[i]=opp;
	}
	fin.close();
	do
	{
		int php,ohp,ch,patt,oatt,pdef,odef,olvl;
		php=p.rethp();
		ohp=arr[cnt].rethp();
		olvl=arr[cnt].retlvl();
		system("cls");
		if(cnt!=nf-1)
		cout<<"\nROUND "<<cnt+1<<"!\n\nOpponent: "<<arr[cnt].retname();
		else
		cout<<"\nFINAL ROUND!\n\n"<<arr[cnt].retname();
		while(php>0 && ohp>0)
		{
			system("cls");
			arr[cnt].showt();
			cout<<ohp;
			cout<<"\n\nFIGHTER: "<<p.retname()<<"\t\tLevel: "<<p.retlvl()<<"\nAttack: "<<p.retatt()<<"\tDefence: "<<p.retdef()<<"\t\tHP: "<<php;
			cout<<"\n\n 1. Attack\n 2. Use HP Shot\n 3. Special Ability (Success rate: "<<10+(3*p.retlvl())<<"%)\n\nEnter your choice: ";
			ch = getInt();
			srand(time(NULL));
			patt=rand()%p.retatt();
			oatt=rand()%arr[cnt].retatt();
			pdef=rand()%p.retdef();
			odef=rand()%arr[cnt].retdef();
			Sleep(500);
			switch(ch)
			{
				case 1:
				if(odef<6+(2*olvl))
				{
					cout<<"\nDamage caused: "<<patt;
					ohp=ohp-patt;
				}
				else
				cout<<'\n'<<arr[cnt].retname()<<" defended your attack!";
				break;
				case 2:
				cout<<"\nHP Shot:\n 1. Normal HP Shot (25HP) \t Available: "<<p.rethps()<<"\n 2. Super HP Shot (50HP) \t Available: "<<p.retshps()<<"\n 3. Mega HP Shot (Full) \t Available: "<<p.retmhps()<<"\nEnter your choice: ";
				ch3 = getInt();
				switch(ch3)
				{
					case 1:
					php=p.dechps(php);
					break;
					case 2:
					php=p.decshps(php);
					break;
					case 3:
					php=p.decmhps(php);
					break;
					default: cout<<"\nWRONG CHOICE!\n\nAttack missed!";
				}
				break;
				case 3:
				srand(time(NULL));
				if(rand()%(20+p.retlvl())<3+p.retlvl())
				{
					cout<<"\nCRITICAL HIT\n\n Damage caused: "<<30+(5*p.retlvl());
					ohp=ohp-(30+(5*p.retlvl()));
				}
				else
				cout<<"\nSpecial ability failed!";
				break;
				default: cout<<"\nWRONG CHOICE!\n\n"<<arr[cnt].retname()<<" defended your attack!";
			}
			Sleep(500);
			if((rand()%10)>0)
			{
				cout<<"\n\n"<<arr[cnt].retname()<<" attacked you!";
				cout<<"\n\n 1. Defend\n 2. Counter (Success rate= "<<10+(3*p.retlvl())<<"%)\n\nEnter choice: ";
				ch = getInt();
				switch(ch)
				{
					case 1:
					if(pdef<5+(2*p.retlvl()))
					{
						cout<<"\nDefence failed!\n\nDamage caused: "<<oatt;
						php=php-oatt;
					}
					else
					cout<<"\nYou defended "<<arr[cnt].retname()<<"'s attack!";
					break;
					case 2:
					srand(time(NULL));
					if(rand()%(20+p.retlvl())<3+p.retlvl())
					{
						cout<<"\nCOUNTER SUCCESSFUL\n\n Damage caused: "<<10+(5*p.retlvl());
						ohp=ohp-(10+(5*p.retlvl()));
					}
					else
					{
						cout<<"\nCounter failed!\n\nDamage caused: "<<oatt;
						php=php-oatt;
					}
					break;
					default: { cout<<"\nWRONG CHOICE!\n\nDamage caused: "<<oatt; php=php-oatt; }
				}
			}
			else
			{
				if(ohp<arr[cnt].rethp()-(p.retlvl()*5)-4)
				ohp=ohp+5+(p.retlvl()*5);
				else
				ohp=arr[cnt].rethp();
				cout<<"\n\n"<<arr[cnt].retname()<<" replenished "<<5+p.retlvl()*5<<"HP";
			}
			getch();
		}
		system("cls");
		if(ohp<=0)
		{
			cnt++;
			cout<<"\nYOU ADVANCE TO THE NEXT ROUND!";
			win=1;
		}
		else if(php<=0)
		{
			cout<<"\nYOU GOT KNOCKED OUT OFF THE TOURNAMENT!";
			win=0;
			break;
		}
		getch();
	}
	while(cnt<nf);
	if(win==1)
	p.tourney(num);
}

void bank(player &p)
{
	int num;
	do
	{
		system("cls");
		cout<<"Fighter: "<<p.retname()<<"\tMoney: "<<p.retmoney()<<"\tLoan: "<<p.retloan();
		cout<<"\n\nBANK:\tLimit: "<<1000+(p.retlvl()*1000)<<"\tInterest: 100%\n\n 1. Take Loan\n 2. Repay Loan\n 3. Exit Bank\n\nEnter choice: ";
		ch1 = getInt();
		flag2=1;
		switch(ch1)
		{
			case 1:
			cout<<"\n\nEnter amount: ";
			num = getInt();
			if(num+p.retloan()>1000+(p.retlvl()*1000))
			{
				cout<<"\n\nYOU HAVE EXCEEDED THE LOAN LIMIT!";
				getch();
			}
			else
			{
				cout<<"\nYou will have to repay $$$: "<<num*2<<" to the bank. Continue? (y/n): ";
				char bch;
				cin>>bch;
				if(bch=='y'||bch=='Y')
				p.takeloan(num,ch1);
			}
			break;
			case 2:
			cout<<"\n\nEnter amount: ";
			num = getInt();
			if(p.retloan()-num<0 || p.retmoney()<num)
			{
				cout<<"\n\nInvalid amount!";
				getch();
			}
			else
			p.takeloan(num,ch1);
			break;
			case 3:
			flag2=0;
			break;
			default: { cout<<"\nWRONG CHOICE!"; getch(); }
		}
	}
	while(flag2==1);
}

void market(player &p)
{
	do
	{
		system("cls");
		cout<<"Fighter: "<<p.retname()<<"\tMoney: "<<p.retmoney()<<"\nAttack: "<<p.retatt()<<"\t\tDefence: "<<p.retdef()<<"\t\tHP: "<<p.rethp()<<"\nNormal HP Shots: "<<p.rethps()<<"\tSuper HP Shots: "<<p.retshps()<<"\tMega HP Shots: "<<p.retmhps();
		cout<<"\n\nMARKET:\n\n 1. HP Shots\n 2. Attack +2 \t\t Price: "<<500+(p.retlvl()*250)<<"\n 3. Defence +1 \t\t Price: "<<500+(p.retlvl()*250)<<"\n 4. HP +2 \t\t Price: "<<500+(p.retlvl()*250)<<"\n 5. Exit Market\n\nEnter your choice: ";
		ch1 = getInt();
		flag2=1;
		switch(ch1)
		{
			case 2:
			p.incatt();
			break;
			case 3:
			p.incdef();
			break;
			case 4:
			p.inchp();
			break;
			case 1:
			cout<<"\n HP Shots:\n\n  1. Normal HP Shot (25HP) \t Price: "<<50+(p.retlvl()*100)<<"\n  2. Super HP Shot (50HP) \t Price: "<<100+(p.retlvl()*200)<<"\n  3. Mega HP Shot (Full HP) \t Price: "<<250+(p.retlvl()*250)<<"\n\n Enter your choice: ";
			ch3 = getInt();
			switch(ch3)
			{
				case 1:
				p.inchps();
				break;
				case 2:
				p.incshps();
				break;
				case 3:
				p.incmhps();
				break;
				default: cout<<"\nWRONG CHOICE!";
			}
			break;
			case 5:
			flag2=0;
			break;
			default: { cout<<"\nWrong choice!"; getch(); }
		}
	}
	while(flag2==1);
}

int main()
{
	system("cls");
	cout<<"THIS IS FIGHT CLUB!";
	cout<<"\n\nHere are the rules:\n1. You don't talk about Fight Club.\n2. YOU DON'T TALK ABOUT FIGHT CLUB.\n3. Win fights, earn money and experience.\n4. Use money to improve your fighter.\n5. Fight your way to the top of FIGHT CLUB.\n\n";
	do
	{
		cout<<"MAIN MENU:\n\n 1. Create new player\n 2. Use existing player\n 3. Two player fight\n 4. Edit player\n 5. Delete player\n 6. Leaderboard\n 7. Quit game\n\nEnter your choice: ";
		mch = getInt();
        cin.clear();
		switch(mch)
		{
			case 1:
			fout.open("fightclub.dat",ios::out|ios::app|ios::binary);
			p1.createp();
			fout.write((char*)&p1,sizeof(p1));
			cout<<"\n\nPLAYER SUCCESSFULLY CREATED";
			cout<<"\n\nAre you ready to fight? (y/n): ";
			cin>>ch2;
			if(ch2=='y'||ch2=='Y')
			{
				p2=p1;
				flag=1;
				pos=fout.tellp();
			}
			else
			flag=0;
			fout.close();
			break;
			case 2:
			fin.open("fightclub.dat",ios::in|ios::binary);
			while(fin.read((char*)&p1,sizeof(p1)))
			{
				p1.show();
				cout<<endl;
			}
			fin.close();
			cout<<"\nEnter name of player to be used: ";
			strcpy(use,getString());
			usep(use);
			break;
			case 3:
			system("cls");
			cout<<"FIGHTER 1\nEnter name: ";
			strcpy(n1,getString());
			cout<<"\n\nFIGHTER 2\nEnter name: ";
			strcpy(n2,getString());
			cout<<"\n\n\n\nDo you want to fight? (y/n): ";
			cin>>ch2;
			if(ch2=='y'||ch2=='Y')
			{
				score1=0; score2=0;
				while(ch2=='y'||ch2=='Y')
				{
					twop(n1,n2);
					cout<<"\n\n\nDo you want to fight again? (y/n): ";
					cin>>ch2;
				}
			}
			flag=0;
			break;
			case 4:
			fin.open("fightclub.dat",ios::in|ios::binary);
			while(fin.read((char*)&p1,sizeof(p1)))
			{
				p1.show();
				cout<<endl;
			}
			fin.close();
			cout<<"\nEnter name of player to be edited: ";
			strcpy(use,getString());
			editp(use);
			break;
			case 5:
			fin.open("fightclub.dat",ios::in|ios::binary);
			while(fin.read((char*)&p1,sizeof(p1)))
			{
				p1.show();
				cout<<endl;
			}
			fin.close();
			cout<<"\nEnter name of player to be deleted: ";
			strcpy(use,getString());
			delp(use);
			break;
			case 6:
			leaderboard();
			break;
			case 7:
			cout<<"\nAre you sure you want to quit? (y/n): ";
			cin>>ch2;
			if(ch2=='y'||ch2=='Y')
			flag=2;
			else
			flag=0;
			break;
			default: cout<<"\nWRONG CHOICE!";
		}
		if(flag==0)
		{
			getch();
			system("cls");
		}
		else if(flag==1)
		{
			do
			{
				flag1=1;
				system("cls");
				cout<<"FIGHT MENU:\n\n 1. Start fight ($$$: "<<p2.retlvl()*25<<")\n 2. Tournament\n 3. Market\n 4. Bank\n 5. Player stats\n 6. Main menu\n\nEnter your choice: ";
				fch = getInt();
				switch(fch)
				{
					case 1:
					system("cls");
					srand(time(NULL));
					o1.createo();
					o1.showo();
					p2.takemoney();
					cout<<o1.rethp()<<"\n\nFIGHTER: "<<p2.retname()<<"\t\tLevel: "<<p2.retlvl()<<"\nAttack: "<<p2.retatt()<<"\tDefence: "<<p2.retdef()<<"\t\tHP: "<<p2.rethp();
					cout<<"\n\nPRIZE MONEY: "<<o1.retmoney()<<"\t\tEXPERIENCE: "<<o1.retexp();
					cout<<"\n\nDo you want to fight? (y/n): ";
					cin>>ch2;
					if(ch2=='y')
					{
						fight(p2,o1);
						updatep(p2);
					}
					system("cls");
					flag1=1;
					break;
					case 2:
					system("cls");
					cout<<"TOURNAMENT MENU:\n\nCODE\tPLAYERS\t\t PRIZE\t\tSTATUS\t\tREQUIREMENTS\n\n";
					cout<<" 1\t   8\t\t";
					if(p2.retexp()<400)
					cout<<"  ???\t\tClosed\t\t  Exp: 400\n\n";
					else
					cout<<"$$$: 400\t Open\t\t  $$$: 200\t\t\t\t\tExp: 40\n\n";
					cout<<" 2\t  16\t\t";
					if(p2.retexp()<1000)
					cout<<"  ???\t\tClosed\t\t  Exp: 1000\n\n";
					else
					cout<<"$$$: 1000\t Open\t\t  $$$: 500\t\t\t\t\tExp: 100\n\n";
					cout<<" 3\t  32\t\t";
					if(p2.retexp()<2000)
					cout<<"  ???\t\tClosed\t\t  Exp: 2000\n\n";
					else
					cout<<"$$$: 2000\t Open\t\t  $$$: 1000\t\t\t\t\tExp: 200\n\n";
					cout<<" 4\t BOSS!\t\t";
					if(p2.retexp()<3000)
					cout<<"  ???\t\tClosed\t\t     ???\n\n";
					else
					cout<<"$$$: 20000\t Open\t\t  $$$: 10000\t\t\t\t\tExp: 2000\n\n 5\t Exit\n\n\n";
					cout<<"Enter tournament code: ";
					ch1 = getInt();
					if(p2.retexp()<400)
					cout<<"\n\nCLOSED! YOU NEED MORE EXPERIENCE!";
					else if(p2.retexp()<1000 && ch1>1)
					cout<<"\n\nCLOSED! YOU NEED MORE EXPERIENCE!";
					else if(p2.retexp()<2000 && ch1>2)
					cout<<"\n\nCLOSED! YOU NEED MORE EXPERIENCE!";
					else if(p2.retexp()<3000 && ch1>3)
					cout<<"\n\nCLOSED! YOU NEED MORE EXPERIENCE!";
					else
					tournament(p2,ch1);
					getch();
					updatep(p2);
					flag1=1;
					break;
					case 3:
					market(p2);
					updatep(p2);
					flag1=1;
					break;
					case 4:
					system("cls");
					bank(p2);
					updatep(p2);
					flag1=1;
					break;
					case 5:
					cout<<'\n';
					p2.show();
					cout<<"\nNormal HP Shots: "<<p2.rethps()<<"\tSuper HP Shots: "<<p2.retshps()<<"\tMega HP Shots: "<<p2.retmhps();
					getch();
					flag1=1;
					break;
					case 6:
					cout<<"\nAre you sure you want to continue? (y/n): ";
					cin>>ch2;
					if(ch2=='y'||ch2=='Y')
					{ flag1=0; flag=0; }
					else
					flag1=1;
					break;
					default: { cout<<"\nWrong choice!"; getch(); }
				}
			}
			while(flag1==1);
			flag=0;
		}
		system("cls");
	}
	while(flag==0);
	system("cls");
	cout<<"FIGHT CLUB\n\nThank you for playing! Goodbye.";
	getch();
	return 0;
}
