#ifndef GRID_H
#define GRID_H
#include <vector>
#include <map>
#include "cell.h"
#include "info.h"
#include "subject.h"
#include "constants.h"
#include "block.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"

class Level;
class GameOver;

class Grid {
	std::vector<std::vector<Cell>> theGrid;
	TextDisplay *td = nullptr; 
	GraphicsDisplay *gd = nullptr;  

	// key is the identity of block (0 reserver for empty), value is blockSize * 10 + level
	std::map<int,int> blockList;
	friend class Hint;

	bool isLineFull(size_t line);
	void update(std::vector<Info> original, std::vector<Info> newBlock);
	void updateGrid(std::vector<Info> original, std::vector<Info> newBlock);

public:
	Grid(TextDisplay* td);
	Grid(const Grid &other); // copy ctor
	void setGraphics(GraphicsDisplay* gd);
	void updateObserver();
	void setBlock(Block *b);
	void unsetBlock(Block *b); // b must be current block in Quadris
	void moveRight(Block *b);
	void moveLeft(Block *b);
	void moveDown(Block *b);
	void clockwise(Block *b);
	void counterclockwise (Block *b);
	std::vector<size_t> checkClear();
	void clearLine(size_t line);
	std::map<int, int>&  getBlockList();
	void setStarBlock();
	void displayHint(std::vector<Info> hint);
	void hintDisappear(std::vector<Info> hint);
};

#endif
