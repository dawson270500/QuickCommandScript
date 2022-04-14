#include <string>
#include <iostream>
using namespace std;
#pragma once

namespace Global {
	void PrintOut(string line) {
		cout << line << std::endl;
	}

	void Debug(std::string line) {
		cout << "::DEBUG:: " << line << std::endl;
	}

	string toLower(string lowerMe) {
		string ret = lowerMe;
		for (int i = 0; i < ret.length(); i++) {
			ret[i] = tolower(ret[i]);
		}
		return ret;
	}
}