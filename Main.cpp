#include <iostream>
#include <string>
#include <map>
#include "Global.h"
using namespace std;

bool console = false;
map<string, string> vars;

// Returns 1 if not implemented yet, 0 otherwise for now
int main(int argc, char *argv) {
	//When given no arguements, the quick command script opens like a console/terminal
	if (argc == 1) {
		Global::PrintOut("== QuickCommandScript | Version 0.1 ==");
		console = true;
	}
	else {
		return 1;
	}

	while (true) {
		string line;
		if (console) {
			cout << "> ";
			getline(cin, line);
		}
		else {
			return 1;
		}

		string token = line.substr(0, line.find(" "));

		if (Global::toLower(token) == "exit" || Global::toLower(line) == "exit") {
			return 0;
		}

		if (Global::toLower(token) == "echo") {
			string toPrint = line.substr(line.find(" ")+1, line.length()-1);
			if (toPrint.find("%") != string::npos) {
				string VarName = "";
				bool foundFirst = false;
				int first = 0;
				int second = 0;
				for (int i = 0; i < toPrint.length(); i++) {
					if (toPrint[i] == '%') {
						if (foundFirst == false) {
							first = i;
							foundFirst = true;
							continue;
						}
						second = i;
						VarName = toPrint.substr(first + 1, i - 1);
						string FirstHalf = toPrint.substr(0, first);
						string SecondHalf = toPrint.substr(second + 1, toPrint.length() - 1 - second);
						if (vars.count(VarName)) {
							toPrint = FirstHalf + vars[VarName] + SecondHalf;
							first = 0; second = 0; VarName = ""; continue;
						}
						else {
							first = -1;
							break;
						}
					}
				}
				if (first== -1) {
					Global::PrintOut("Invalid Variable, " + VarName + " does not exist");
					continue;
				}
			}
			Global::PrintOut(toPrint);
			continue;
		}

		if (Global::toLower(token) == "set") {
			string VarName = line.substr(line.find(" ") + 1, line.find("=")-1-line.find(" "));
			string VarValue = line.substr(line.find("=") + 1, line.length() - 1);

			if (vars.count(VarName))
				vars[VarName] = VarValue;
			else 
				vars.insert(make_pair(VarName, VarValue));

			continue;
		}

		

		Global::PrintOut("Invalid Command");
	}

	return 0;
}