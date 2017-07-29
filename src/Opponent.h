#ifndef OPPONENT_H_INCLUDED
#define OPPONENT_H_INCLUDED

class opponent
{
	private:
	int hp,attack,defence,lvl,money,exp;
	char name[20];

	public:
	void createo();
	void showo();
	void showt();
	int rethp();
	int retatt();
	int retdef();
	int retlvl();
	int retmoney();
	int retexp();
	char* retname();
};

#endif // OPPONENT_H_INCLUDED
