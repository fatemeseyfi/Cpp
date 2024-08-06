#pragma once
#include <string>
#include <vector>
using namespace std;
class Account
{
public:
	Account();
	Account(string name,string aNum, double amount, double profit, string type);

	void getInfo();
	void pay(double payment);
	double t_profit();
	void withdraw(double withdraw);

	void setName(string name);
	void setANum(string aNum);
	void setAmount(double amount);
	void setProfit(double profit);
	void setType(string type);

	string getName();
	string getANum();
	double getAmount();
	double getProfit();
	string getType();


private:
	string m_name;
	string m_aNum;
	double m_amount;
	double m_profit;
	string m_type;
};

