#ifndef BLOCK_H
#define BLOCK_H
#include <vector>
#include "constants.h"
#include "info.h"
#include "cell.h"

class InvalidMove{};
class GameOver{};


class Block {
	std::vector<Info> theBlock;
	int level = 0;
	size_t blockSize = 4;
	Shape blockType;

	//for rotate
	size_t height = 1;
	size_t width = 1;
	size_t llrow = 0;	
	size_t llcol = 0; // lower left point of the RECTANGLE

public:
	Block(Shape s, int l); //ctor
	Block(std::vector<Info> theBlock); //ctor
	Block(const Block &other); // copy ctor
	Shape getShape();
	int getLevel();
	std::vector<Info> getBlock();
	bool isInBlock(const Info &info);
	std::vector<Info> downInfo();
	std::vector<Info> cwInfo();
        std::vector<Info> ccwInfo();
	std::vector<Info> leftInfo();
	std::vector<Info> rightInfo();
	void confirmRight();
	void confirmLeft();
	void confirmDown();
	void confirmCw();
	void confirmCcw();
};
#endif
