#include "interpreter.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "quadris.h"
#include "graphicsdisplay.h"

using namespace std;

int main(int argc, char *argv[]) {
	cin.exceptions(ios::eofbit|ios::failbit);
	
	Interpreter commander;
	string cmd;
	bool graphFlag = 1;
	string str;
	string scrFile = "sequence.txt";
	int level = 0;

	//Command Line Interface
	for (int i = 1; i < argc; i++) {
		str = argv[i];
		if (str == "-text"){
			graphFlag = 0;
		} else if (str == "-seed") {
			if (argc <= (i+1) || atoi(argv[i+1]) < 0)	{
				cerr << "No seed number provided or negative seed" << endl;
				return 0;
			} else {
				srand(atoi(argv[i+1]));
			}
		} else if (str == "-scriptfile") {
			scrFile = argv[i+1];
		} else if (str == "-startlevel" && atoi(argv[i+1]) < 4 && atoi(argv[i+1]) >= 0) {
			level = atoi(argv[i+1]);
		}
	}

	Quadris q{graphFlag};

	if (level == 0) q.setSequence(scrFile); 

	try {
		q.init(graphFlag, level);
		cout << q;
 		while (true) {
			getline(cin, cmd);
			commander.processCommand(cmd, &q);
			cout << q;
      		}
	} catch (GameOver &) {
		cout << q;
		cout << "Game Over!" << endl; 
	} catch (ios::failure &) {
		cerr << "Input exhausted!" << endl;
	}  // Any I/O failure quits
}
