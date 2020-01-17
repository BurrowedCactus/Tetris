#include <vector>
#include "textdisplay.h"
#include "info.h"
#include "constants.h"
using namespace std;

/*
**************************************************
the top and middle part should be finished.
the bottom part is not done, since it does not have access to the next block yet.
**************************************************
*/

vector<string> outputNext(Shape nextBlock){
	vector<string> answer;
	Shape newShape = nextBlock;
	switch(newShape){
		case Shape::I:
			answer.emplace_back(string {"IIII"});
			break;
		case Shape::J:
			answer.emplace_back(string {"J"});
			answer.emplace_back(string {"JJJ"});
			break;
		case Shape::L:
			answer.emplace_back(string {"  L"});
			answer.emplace_back(string {"LLL"});
			break;
		case Shape::O:
			answer.emplace_back(string {"OO"});
			answer.emplace_back(string {"OO"});
			break;
		case Shape::S:
			answer.emplace_back(string {" SS"});
			answer.emplace_back(string {"SS"});
			break;
		case Shape::Z:
			answer.emplace_back(string {"ZZ"});
			answer.emplace_back(string {" ZZ"});
			break;
		case Shape::T:
			answer.emplace_back(string {"TTT"});
			answer.emplace_back(string {" T"});
			break;
		case Shape::EMPTY:
			answer.emplace_back(string {" "});
			break;
		case Shape::STAR:
			answer.emplace_back(string {"*"});
			break;
		case Shape::HINT:
			answer.emplace_back(string {"?"});
			break;
		default:
			answer.emplace_back(string {" "});
			break;
	}
	return answer;
}

TextDisplay::TextDisplay(Level* level, Score* score, Shape* nextBlock): 
		ADisplay{level, score, nextBlock} {
	vector<char> row (WIDTH, ' ');
	for (size_t i = 0; i < HEIGHT + BUFFER_HEIGHT; ++i){
 		theDisplay.emplace_back(row);
 	}
}

void TextDisplay::notify(Subject &whoNotified){
	size_t r = whoNotified.getInfo().row;
	size_t c = whoNotified.getInfo().col;
	switch(whoNotified.getInfo().shape) {
		case Shape::I:
			theDisplay.at(r).at(c) = 'I';
			break;
		case Shape::J:
			theDisplay.at(r).at(c) = 'J';
			break;
		case Shape::L:
			theDisplay.at(r).at(c) = 'L';
			break;
		case Shape::O:
			theDisplay.at(r).at(c) = 'O';
			break;
		case Shape::S:
			theDisplay.at(r).at(c) = 'S';
			break;
		case Shape::Z:
			theDisplay.at(r).at(c) = 'Z';
			break;
		case Shape::T:
			theDisplay.at(r).at(c) = 'T';
			break;
		case Shape::EMPTY:
			theDisplay.at(r).at(c) = ' ';
			break;
		case Shape::STAR:
			theDisplay.at(r).at(c) = '*';
			break;
		case Shape::HINT:
			theDisplay.at(r).at(c) = '?';
			break;
		default:
			theDisplay.at(r).at(c) = ' ';
			break;
	}	
}


ostream &operator<<(ostream &out, const TextDisplay &td){
	out << td.getLevel() << endl;
	out << td.getScore() << endl;
	out << td.getHighScore() << endl; 

	for (int i = HEIGHT + BUFFER_HEIGHT - 1; i >= 0; --i){
		for (size_t j = 0; j < WIDTH; ++j){
			out << td.theDisplay.at(i).at(j);
		}
		out << endl;
	}
	
	out << td.getStrNext() << endl;
	auto temp = outputNext(*(td.getShapePtr()));
	for (auto& line: temp){
		out << line << endl;
	}
	return out;
}
