#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class player
{
	private:
	char name[20];
	int fw,fl,exp,hp,attack,defence,money,lvl,hps,shps,mhps,tour,loan;
	void inclvl();

	public:
	void createp();
	void show();
	int retatt();
	int retdef();
	char* retname();
	int rethp();
	int retexp();
	int retmoney();
	int retlvl();
	int rethps();
	int retshps();
	int retmhps();
	int retloan();
	void loanexp();
	void takeloan(int l,int n);
	void takemoney();
	void win(int l, int ph);
	void lose(int l);
	void incatt();
	void incdef();
	void inchp();
	void inchps();
	int dechps(int ph);
	void incshps();
	int decshps(int ph);
	void incmhps();
	int decmhps(int ph);
	void tourney(int num);
	void tourmoney(int num);
};

#endif // PLAYER_H_INCLUDED
