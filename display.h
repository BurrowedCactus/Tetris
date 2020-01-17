#ifndef DISPLAY_H
#define DISPLAY_H
#include <iostream>
#include <vector>
// #include "observer.h"
#include "info.h"
#include <string>
#include "constants.h"
#include "level.h"
#include "score.h"


class Cell;

class ADisplay {
	Level* level;
	Score* score;
	Shape* nextBlock;
public:
	std::string getLevel() const;
	std::string getScore() const;
	std::string getHighScore() const;
	std::string getStrNext() const;
	Level* getLevelPtr() const;
	Score* getScorePtr() const;
	Shape* getShapePtr() const;
	ADisplay(Level* level, Score* score, Shape* nextBlock);
	//virtual void notify(Subject &whoNotified) = 0;
	virtual ~ADisplay() = default;
};

#endif
