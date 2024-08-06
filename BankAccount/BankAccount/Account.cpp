#include "Account.h"
#include <iostream>
using namespace std;

Account::Account()
{
}

Account::Account(string name, string aNum, double amount, double profit, string type)
{
	setName(name);
	setANum(aNum);
	setAmount(amount);
	setProfit(profit);
	setType(type);
}

void Account::getInfo()
{
	cout << "Owner: " << getName()<<endl;
	cout << "Account number: " << getANum()<<endl;
	cout << "Account type: " << getType()<<endl;
	cout << "Total: " << getAmount()<<endl;
	cout << "Profit : " << getProfit()<<endl;

}

void Account::pay(double payment)
{
	setAmount(getAmount() + payment);
}

double Account::t_profit()
{
	return (m_profit * getAmount())/100;
}

void Account::withdraw(double withdraw)
{
	if (withdraw > getAmount()) {
		cout << "Not enough balance!!!";
	}
	else
	{
		setAmount(getAmount() - withdraw);

	}
}

void Account::setName(string name)
{
	m_name = name;
}

void Account::setANum(string aNum)
{
	m_aNum = aNum;
}

void Account::setAmount(double amount)
{
	m_amount = amount;
}

void Account::setProfit(double profit)
{
	m_profit = profit;
}

void Account::setType(string type)
{
	m_type = type;
}

string Account::getName()
{
	return m_name;
}

string Account::getANum()
{
	return m_aNum;
}

double Account::getAmount()
{
	return m_amount;
}

double Account::getProfit()
{
	return m_profit;
}

string Account::getType()
{
	return m_type;
}
