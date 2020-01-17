#include "level.h"
#include <cstdlib>
using namespace std;

Shape returnShape(int index) noexcept {
	int i = index;
	switch(i){
		case 0:
			return Shape::EMPTY;
			break;
		case 1:
			return Shape::I;
			break;
		case 2:
			return Shape::J;
			break;
		case 3:
			return Shape::L;
			break;
		case 4:
			return Shape::O;
			break;
		case 5:
			return Shape::S;
			break;
		case 6:
			return Shape::Z;
			break;
		case 7:
			return Shape::T;
			break;
		default:
			return Shape::I;
			break;
			
	}
	return Shape::I;
}

void Level::setLevel(int l) noexcept {
	if (l < 0){
		level = 0;
	} else if (level > 4){
		level = 4;
	} else {
		level = l;
	}
}

int Level::getLevel() noexcept {
	return level;	
}

void Level::setSequence(bool isOn){
	useSequence = isOn;
}

Level::Level(int l, string s): useSequence{false} {
	level = l;
	if (!s.empty()){
		setSequence(s);
	}
}

Shape Level::readSequence(){
	Shape temp = sequence.front();
	sequence.erase(sequence.begin());
	if (sequence.size() == 0){
		sequence = seq_backup;
	}
	return temp;
}

Shape Level::getNewShape() noexcept {
	int i = level;
	int random;
	switch(i){
		case 0:
			return readSequence();
			break;
		case 1:
			random = rand() % 6 + 1; //1,2,3,4,5,6
			if (random == 5){
				// returnShape (5 + 0 or 5 + 1)
				return returnShape(random + rand() % 2);
			} else if (random < 5){
				return returnShape(random);
			} else {
				return returnShape(random + 1);
			}
			break;
		case 2:
			return returnShape(rand() % 7 + 1); // 1,2,3,4,5,6,7
			break;
		case 3:
			if (useSequence){
				return readSequence();
			} else {
				//heavy should be handled by other class. 
				random = rand() % 9 + 1; //1,2,3, ... ,9
				if (5 <= random &&  random <= 8){// 5,6,7,8 -> 1,0,1,0
					// returnShape (5 + 0 or 5 + 1)
					return returnShape(5 + random % 2);
				} else if (random < 5){
					return returnShape(random);
				} else {
					return returnShape(random - 2);
				}
			}
			break;
		case 4:
			if (useSequence){
				return readSequence();
			} else {
				//heavy and constructive force should be handled by other class. 
				random = rand() % 9 + 1; //1,2,3, ... ,9
				if (5 <= random &&  random <= 8){// 5,6,7,8 -> 1,0,1,0
					// returnShape (5 + 0 or 5 + 1)
					return returnShape(5 + random % 2);
				} else if (random < 5){
					return returnShape(random);
				} else {
					return returnShape(random - 2);
				}
			}
			break;
	}
	return Shape::I;
}	

void Level::setSequence(string fname) {
	ifstream sequenceFile(fname);
	char shape;
	sequence.clear();
	while (sequenceFile >> shape) {
		if (shape == 'I') {
			sequence.emplace_back(Shape::I);
		}
		if (shape == 'J') {
			sequence.emplace_back(Shape::J);
		}
		if (shape == 'L') {
			sequence.emplace_back(Shape::L);
		}
	        if (shape == 'O') {
			sequence.emplace_back(Shape::O);
		}
		if (shape == 'S') {
			sequence.emplace_back(Shape::S);
		}
	        if (shape == 'Z') {
			sequence.emplace_back(Shape::Z);
		}
		if (shape == 'T') {
			sequence.emplace_back(Shape::T);
		}
	}
	seq_backup = sequence;
}

void Level::restartSequence(){
	sequence = seq_backup;
}
