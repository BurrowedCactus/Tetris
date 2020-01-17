#ifndef QUADRIS_H
#define QUADRIS_H
#include <memory>
#include <vector>
#include <math.h>
#include <iostream>
#include "level.h"
#include "score.h"
#include "cell.h"
#include "block.h"
#include "grid.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "hint.h"


class Quadris{

private:	
	std::unique_ptr<Level> level;
	std::unique_ptr<Score> score;
	std::unique_ptr<TextDisplay> td;
        std::unique_ptr<GraphicsDisplay> gd = nullptr;	
	std::unique_ptr<Grid> g;
	std::unique_ptr<Block> currentBlock;
	Shape nextShape = Shape::EMPTY;
	bool graphFlag = 1;
	int unclearBlocks = 0;
	std::vector<Info> hint;

public:
	Quadris(bool); //int winSize = 500
	void init(bool graphFlag, int l);
	void genBlock();
	void drop();
	void moveLeft();
	void moveRight();
	void setSequence(bool isOn);
	void moveDown();
	void clockwise();
	void counterClockwise();
	void setSequence(std::string fname);
	void setCurrent(Shape current); //change neme needed
	void updateNext(); // for non random sequence
	void levelUp();
	void levelDown();
	void restart();
	int getLevel() const;
	void displayHint();
	void hintDisappear();
	friend std::ostream &operator<<(std::ostream &out, const Quadris &q);
};

#endif
