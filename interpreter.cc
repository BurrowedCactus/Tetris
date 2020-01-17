#include "interpreter.h"
#include <fstream>
using namespace std;

Interpreter::Interpreter() {
	node = make_unique<TrieNode>();
	node->insert("w");
	node->insert("a");
	node->insert("s");
	node->insert("d");
	node->insert("left");
	node->insert("right");
	node->insert("down");
	node->insert("drop");
	node->insert("clockwise");
	node->insert("counterclockwise");
	node->insert("levelup");
	node->insert("leveldown");
	node->insert("restart");
	node->insert("random");
	node->insert("norandom");
	node->insert("sequence");
	node->insert("hint");
}

// The following method returns true if the command is any one of the acceptable commands.
bool Interpreter::isValid(const string& command) {
	return !(node->match(command).empty());
}

bool Interpreter::validMultiply(const string& command) {
	string s = node->match(command);
	if (s == "left" || s == "right" || s == "down" || s == "clockwise" ||
		s == "counterclockwise" || s == "levelup" || s == "leveldown" ||
		s == "w" || s == "a" || s == "s" || s == "d"){
		return true;
	} else {
		return false;
	}
}

void execute(const string& first, const string& second, Quadris* q){
	cout << first << "     " << second << endl;
	if (first == "sequence"){
		ifstream file{second};
		string commands;
		Interpreter I;
		while (getline(file, commands)){
			I.processCommand(commands, q);
		}
	} else if (first == "norandom"){
		q->setSequence(true);
		q->setSequence(second);
		q->updateNext();
	}
}

void execute(const string& s, Quadris* q){
	if (s == "left" || s == "a"){
		q->moveLeft();
	} else if (s == "right" || s == "d") {
		q->moveRight();
	} else if (s == "down" || s == "s") {
		q->moveDown();
	} else if (s == "clockwise" || s == "w"){
		q->clockwise();
	} else if (s == "counterclockwise"){
		q->counterClockwise();
	} else if (s == "levelup"){
		q->levelUp();
	} else if (s == "leveldown"){
		q->levelDown();
	} else if (s == "drop"){
		q->drop();
	} else if (s == "random"){
		q->setSequence(false);
	} else if (s == "restart"){
		q->restart();
	} else if (s == "I"){
		q->setCurrent(Shape::I);
	} else if (s == "J"){
		q->setCurrent(Shape::J);
	} else if (s == "L"){
                q->setCurrent(Shape::L);
        } else if (s == "O"){
                q->setCurrent(Shape::O);
        } else if (s == "S"){
                q->setCurrent(Shape::S);
        } else if (s == "Z"){
                q->setCurrent(Shape::Z);
        } else if (s == "T"){
                q->setCurrent(Shape::T);
        } else if (s == "hint"){
		q->displayHint();
	}
}

bool isDigit(const char& c){
	return (c >= '0') && (c <= '9');
}

// The following method is for processing multiplied command.
void Interpreter::processCommand(const string& command, Quadris* q) {
	stringstream ss1{command};
	string first, second;
	ss1 >> first >> second;
	int numLength = 0;
	while (isdigit(first[numLength])) {
		numLength++;
	}

	string subNum = first.substr(0, numLength);
	string subCommand = first.substr(numLength);
    
	int num = 1;
	stringstream ss2{subNum};
	ss2 >> num;
	string real = node->match(subCommand);
	if (stack == "hint"){
   		q->hintDisappear();
		stack.clear();
	}
	if (real == "hint"){
		stack = "hint";
	}
	if (real == "sequence" || real == "norandom"){
		execute(real, second, q);
	} else if(validMultiply(real)){
		for (int i = 0; i < num; ++i){
		execute(real, q);
	}
	} else {
		execute(real, q);
	}

	if (q->getLevel() >= 3 && (real == "left" || real == "right" || real == "down" ||
	real == "clockwise" || real == "counterclockwise")) {
		q->moveDown();
	} 
}
