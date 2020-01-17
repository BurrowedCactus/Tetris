#include "display.h"
#include <string>
#include <sstream>
using namespace std;

string duplicate(char c, int i){
	string s;
	while(i > 0){
		s += c;
		--i;
	}
	return s;
}

int digit(int input){
	int answer = 1;
	while (input >= 10){
		input /= 10;
		++answer;
	}
	return answer;
}

int format(Score* score, Level* level){
	int temp = (digit(score->getCurrentScore()) > digit(score->getHighScore()))?
		digit(score->getCurrentScore()) : digit(score->getHighScore());
	return (temp > digit(level->getLevel()))? temp : digit(level->getLevel());
}

Level* ADisplay::getLevelPtr() const{
	return level;
}

Score* ADisplay::getScorePtr() const{
	return score;
}

Shape* ADisplay::getShapePtr() const{
	return nextBlock;
}

string ADisplay::getLevel() const {
	stringstream ss;
	ss << level->getLevel(); 
	return "Level:       " + duplicate(' ', format(score, level) - digit(level->getLevel())) +
				ss.str();
}

string ADisplay::getScore() const {
	stringstream ss;
	ss << score->getCurrentScore(); 
	return "Score:       " + duplicate(' ', format(score, level) - digit(score->getCurrentScore())) +
				ss.str();
}

string ADisplay::getHighScore() const{
	stringstream ss;
	ss << score->getHighScore();
	return "Hi Score:    " + duplicate(' ', format(score, level) - digit(score->getHighScore())) +
				ss.str(); 
}

string ADisplay::getStrNext() const{
	return "Next:";
}


ADisplay::ADisplay(Level* level, Score* score, Shape* nextBlock):
		level{level}, score{score}, nextBlock{nextBlock} {}
//string strNext = "Next:";






