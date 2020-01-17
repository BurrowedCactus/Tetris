#include "block.h"

using namespace std;


Block::Block(Shape s, int l):blockType{s}{
	switch(s) {
		case Shape::I:
			blockSize = 4;
			level = l;
			llrow = HEIGHT - 1;
			llcol = 0;	
			height = 1;
			width = 4;
			for (size_t i = 0; i < blockSize; ++i) {
				theBlock.emplace_back(Info{HEIGHT - 1, i, s}); //top left corner
			}
			break;
		case Shape::J:
			blockSize = 4;
			level = l;
			llrow = HEIGHT - 2;
			llcol = 0;
			height = 2;
			width = 3;
			for (size_t i = 0; i < 3; ++i){
				theBlock.emplace_back(Info{HEIGHT - 2, i, s});
			}
			theBlock.emplace_back(Info{HEIGHT - 1, 0, s});
			break;
		case Shape::L:
			blockSize = 4;
			level = l;
			llrow = HEIGHT - 2;
			llcol = 0;
			height = 2;
			width = 3;
			for (size_t i = 0; i < 3; ++i){
				theBlock.emplace_back(Info{HEIGHT - 2, i, s});
			}
			theBlock.emplace_back(Info{HEIGHT - 1, 2, s});
			break;
		case Shape::O:
			blockSize = 4;
			level = l;
			llrow = HEIGHT - 2;
			llcol = 0;
			height = 2;
			width = 2;
			for (size_t i = 2; i > 0; --i){
				for (size_t j = 0; j < 2; ++j){
					theBlock.emplace_back(Info{HEIGHT - i, j, s});	
				}
			}
			break;
		case Shape::S:
			blockSize = 4;
			level = l;
			llrow = HEIGHT - 2;
			llcol = 0;
			height = 2;
			width = 3;
			theBlock.emplace_back(Info{HEIGHT - 2, 0, s});
			theBlock.emplace_back(Info{HEIGHT - 2, 1, s});
			theBlock.emplace_back(Info{HEIGHT - 1, 1, s});
			theBlock.emplace_back(Info{HEIGHT - 1, 2, s});
			break;
		case Shape::Z:
			blockSize = 4;
			level = l;
			llrow = HEIGHT - 2;
			llcol = 0;
			height = 2;
			width = 3;
			theBlock.emplace_back(Info{HEIGHT - 2, 1, s});
			theBlock.emplace_back(Info{HEIGHT - 2, 2, s});
			theBlock.emplace_back(Info{HEIGHT - 1, 0, s});
			theBlock.emplace_back(Info{HEIGHT - 1, 1, s});
			break;
		case Shape::T:
			blockSize = 4;
			level = l;
			llrow = HEIGHT - 2;
			llcol = 0;
			height = 2;
			width = 3;
			theBlock.emplace_back(Info{HEIGHT - 2, 1, s});
			for (size_t i = 0; i < 3; ++i){
				theBlock.emplace_back(Info{HEIGHT - 1, i, s});
			}
			break;
		default:
			blockSize = 0;
	}
}


Block::Block(const Block &other):theBlock{other.theBlock}, 
	level{other.level}, 
	blockSize{other.blockSize}, 
	blockType{other.blockType},
	height{other.height}, 
	width{other.width}, 
	llrow{other.llrow}, 
	llcol{other.llcol}{}


Block::Block(vector<Info> theBlock):theBlock{theBlock}{}


vector<Info> Block::getBlock() {
	return theBlock;	
}

int Block::getLevel() {
	return level;	
}


bool Block::isInBlock(const Info &info){
	for (size_t i = 0; i < blockSize; ++i){
		if (theBlock.at(i).row == info.row && theBlock.at(i).col == info.col) return true;
	}
	return false;
}


vector<Info> Block::leftInfo(){
	vector<Info> toReturn;
	for(size_t i = 0; i < blockSize; ++i){
		Info info = theBlock.at(i);
		if (info.col == 0) throw InvalidMove{};
		toReturn.emplace_back(Info{info.row, info.col - 1, info.shape});
	}
	return toReturn;
}


vector<Info> Block::rightInfo(){
	vector<Info> toReturn;
	for(size_t i = 0; i < blockSize; ++i){
		Info info = theBlock.at(i);
		if (info.col == WIDTH - 1) throw InvalidMove{};
		toReturn.emplace_back(Info{info.row, info.col + 1, info.shape});
	}
	return toReturn;
}


vector<Info> Block::downInfo(){
	vector<Info> toReturn;
	for(size_t i = 0; i < blockSize; ++i){
		Info info = theBlock.at(i);
		if (info.row == 0) throw InvalidMove{};
		toReturn.emplace_back(Info{info.row - 1, info.col, info.shape});
	}
	return toReturn;
}


void Block::confirmRight() {
	llcol = llcol + 1;
	for (size_t i = 0; i < blockSize; ++i) {
		theBlock.at(i).col = theBlock.at(i).col + 1;
	}
}

void Block::confirmLeft() {
	llcol = llcol - 1;
	for (size_t i = 0; i < blockSize; ++i) {
		theBlock.at(i).col = theBlock.at(i).col - 1;
	}
}

void Block::confirmDown(){
	llrow = llrow - 1; 
	for (size_t i = 0; i < blockSize; ++i) {
		theBlock.at(i).row = theBlock.at(i).row - 1;
	}	
}


vector<Info> Block::cwInfo() {
	vector<Info> toReturn;
	if (llcol + height > WIDTH) throw InvalidMove{};
	for (size_t row = llrow; row  < llrow + height; ++row) {
		for (size_t col = llcol; col < llcol + width; ++col) {
			if (isInBlock(Info{row, col, blockType})) {
				toReturn.emplace_back(Info{width - 1 - col + llrow + llcol, row - llrow + llcol, blockType});
			}
		}
	}
	return toReturn;
}


vector<Info> Block:: ccwInfo(){
	vector<Info> toReturn;	
	if (llcol + height > WIDTH) throw InvalidMove{};
	for (size_t row = llrow; row  < llrow + height; ++row) {
		for (size_t col = llcol; col < llcol + width; ++col) {
			if (isInBlock(Info{row, col, blockType})) {
				toReturn.emplace_back(Info{col - llcol +llrow, height - 1 - row + llrow + llcol, blockType}); 
			}
		} 
	}
	return toReturn;
}


void Block::confirmCcw() {
	theBlock = ccwInfo();
	size_t temp = height;
	height = width;
	width = temp;
}

void Block::confirmCw() {
	theBlock = cwInfo();
	size_t temp = height;
	height = width;
	width = temp;	
}


Shape Block::getShape(){
	return blockType;
}

