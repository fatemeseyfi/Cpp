#include <iostream>
#include <string>

bool checkInput(std::string s) {
	for (int i = 0; i < s.length(); i++) {
		for (int j = 0; j < s.length(); j++) {
			if (s[i] == s[j] && i != j) {
				return false;
			}
		}
	}
	return true;
}

bool checkDuplicate(std::string s1, std::string s2) {
	for (int i = 0; i < s1.length(); i++) {
		for (int j = 0; j < s2.length(); j++) {
			if (s1[i] == s2[j])
				return false;
		}
		
	}
	return true;
}

std::string getInput(int i) {
	std::cout << "enter string" << i << ": ";
	std::string s;
	std::cin >> s;
	while (!checkInput(s)) {
		std::cout << "string can't have duplicated character: ";
		std::cin >> s;
	}

	return s;
	
}

std::string encrypt(std::string s1, std::string s2, std::string org) {
	int idx;
	std::string encrypted = "";
	for (int i = 0; i < org.length(); i++) {

		idx = s1.find(org[i]);

		if (idx != -1) {
			encrypted = encrypted + s2[idx];

		}
		else {

			idx = s2.find(org[i]);

			if (idx != -1) {
				encrypted = encrypted + s1[idx];

			}
			else
			{
				encrypted = encrypted + org[i];

			}
		

		}

	}

	return encrypted;
}

void to_upper(std::string str) {
	for (char& c : str) {
		c = std::toupper(c);
	}
}

int main() {
	
	bool b = false;
	std::string s1 = "TCABGJPNEYDQU";
	std::string s2 = "HMFZIVWSOLRKX";
	std::string org;

	while (!b) {
		std::cout << "s1 and s2 can not have duplicate characters: " << std::endl;

		s1 = getInput(1);
		s2 = getInput(2);
		
		b = checkDuplicate(s1, s2);
	}
	

	std::cout << "enter original string: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

	std::getline(std::cin, org); 


	to_upper(s1);
	to_upper(s2);
	to_upper(org);

	std::string encrypted = encrypt(s1, s2, org);
	
	

	std::cout << encrypted;
	return 0;
}