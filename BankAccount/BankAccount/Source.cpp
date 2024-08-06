#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Account.h"

Account* createAccount() {
	string name;
	string aNum;
	double amount;
	double profit;
	string type;

	cout << "Enter account information: " << endl;
	cout << "Example: \nfateme\n25\n4323234\n14\nbusiness" << endl;
	cout << "name: " << endl;
	cin >> name;
	cout << "account number: " << endl;
	cin >> aNum;
	cout << "balance: " << endl;
	cin >> amount;
	cout << "profit: " << endl;
	cin >> profit;
	cout << "type: " << endl;
	cin >> type;

	Account* a = new Account(name, aNum, amount, profit, type);

	return a;

}

Account* search(vector<Account*> accountList, string aNum) {
	for (int i = 0; i < accountList.size(); i++) {
		if (accountList[i]->getANum() == aNum) {
			return accountList[i];
		}
	}
	return nullptr;
}

void displayAccountList(vector<Account*> accountList) {
	for (int i = 0; i < accountList.size(); i++) {
		accountList[i]->getInfo();
	}
	cout << "*****************************************************"<<endl;
}

int main() {


	vector<Account*> accountList;
	Account* b = new Account("fateme", "23", 800, 12, "business");
	accountList.push_back(b);
	displayAccountList(accountList);

	
	Account* a = createAccount();
	



	int action = -1;
	double p;
	string aNum;

	while (action != 0) {
		cout <<endl<< "_______________________________________________________________________________________________"<<endl;
		cout << "What do you want to do? (Enter the number of action)" << endl;
		cout << "0.end actions\n1.pay\n2.deposit\n3.display total profit\n4.display account information\n5.deposit to another account" << endl;

		cin >> action;

		switch (action)
		{
		case 1:
			cout << "Enter payment: ";
			cin >> p;
			a->pay(p);
			a->getInfo();
			break;
		case 2:
			cout << "Enter withdraw: ";
			cin >> p;
			a->withdraw(p);
			a->getInfo();
			break;
		case 3:
			a->getProfit();
			break;
		case 4:
			a->getInfo();
			break;
		case 5:
			cout << "enter account number: ";
			cin >> aNum;
			while (search(accountList, aNum) == nullptr) {
				cout << "account number is invalid. Enter account number correctly: ";
				cin >> aNum;
			}
			Account* b = search(accountList, aNum);
			cout << "enter deposit amount: ";
			cin >> p;
			a->withdraw(p);
			b->pay(p);



		}
	}



}