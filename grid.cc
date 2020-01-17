#include "grid.h"

using namespace std;

Grid::Grid(TextDisplay* text):td{text}{
	for (size_t i = 0; i < HEIGHT + BUFFER_HEIGHT; ++i){
		vector<Cell> temp;
		for (size_t j = 0; j < WIDTH; ++j){
			Cell newCell{i, j, Shape::EMPTY};
			temp.emplace_back(newCell);
		}
		theGrid.emplace_back(temp);
	}

	for (size_t i = 0; i < HEIGHT + BUFFER_HEIGHT; ++i){
		for (size_t j = 0; j < WIDTH; ++j) {
			theGrid.at(i).at(j).attach(td);
		}
	}
}


Grid::Grid(const Grid &other): theGrid{other.theGrid},
			td{nullptr}, gd{nullptr}, blockList{other.blockList}{}


void Grid::setBlock(Block *b){
	int index = static_cast<int>(blockList.size());
	blockList[index + 1] = 4 * 10 + b->getLevel();
	vector<Info> newBlock = b->getBlock();	
	for (size_t i = 0; i < 4; ++i) {
		auto r = newBlock.at(i).row;
		auto c = newBlock.at(i).col;
		if (theGrid.at(r).at(c).getInfo().shape != Shape::EMPTY) {
			throw GameOver{};
		}
		auto s = newBlock.at(i).shape;
		theGrid.at(r).at(c).setShape(s);
		theGrid.at(r).at(c).notifyObservers();
	}
}


void Grid::unsetBlock(Block *b) {
	blockList.erase(static_cast<int>(blockList.size())); //erase current block
	vector<Info> newBlock = b->getBlock();
	for (size_t i = 0; i < 4; ++i) {
		auto r = newBlock.at(i).row;
		auto c = newBlock.at(i).col;
		theGrid.at(r).at(c).setShape(Shape::EMPTY);
		theGrid.at(r).at(c).notifyObservers();
	}
}


void Grid::update(vector<Info> original, vector<Info> newBlock){
	for (size_t i = 0; i < 4; ++i) {
		auto r = original.at(i).row;
		auto c = original.at(i).col;
		theGrid.at(r).at(c).setShape(Shape::EMPTY);
		theGrid.at(r).at(c).setKey(0);
	}
	for (size_t i = 0; i < 4; ++i) {
		auto r = newBlock.at(i).row;
		auto c = newBlock.at(i).col;
		auto s = newBlock.at(i).shape;
		theGrid.at(r).at(c).setShape(s);
		theGrid.at(r).at(c).setKey(static_cast<int>(blockList.size()));
	}
}


void Grid::updateGrid(vector<Info> original, vector<Info> newBlock){
	for (size_t i = 0; i < 4; ++i) {
		theGrid.at(original.at(i).row).at(original.at(i).col).notifyObservers();
	}
	for (size_t i = 0; i < 4; ++i) {
		theGrid.at(newBlock.at(i).row).at(newBlock.at(i).col).notifyObservers();
	}
}


void Grid::moveRight(Block *b){
	vector<Info> newBlock = b->rightInfo();
	vector<Info> original = b->getBlock();
	for (size_t i = 0; i < 4; ++i) {
		auto r = newBlock.at(i).row;
		auto c = newBlock.at(i).col;
		if ((!b->isInBlock(newBlock.at(i))) && theGrid.at(r).at(c).getInfo().shape != Shape::EMPTY) throw InvalidMove{};
	}
	update(original, newBlock);
	updateGrid(original, newBlock);	
	b->confirmRight();
}


void Grid::moveLeft(Block *b){
	vector<Info> newBlock = b->leftInfo();
	vector<Info> original = b->getBlock();
	for (size_t i = 0; i < 4; ++i) {
		auto r = newBlock.at(i).row;
		auto c = newBlock.at(i).col;
		if ((!b->isInBlock(newBlock.at(i))) && theGrid.at(r).at(c).getInfo().shape != Shape::EMPTY) throw InvalidMove{};
	}
	update(original, newBlock);
	updateGrid(original, newBlock);
	b->confirmLeft();
}


void Grid::moveDown(Block *b){
	vector<Info> newBlock = b->downInfo();
	vector<Info> original = b->getBlock();
	for (size_t i = 0; i < 4; ++i) {
		auto r = newBlock.at(i).row;
		auto c = newBlock.at(i).col;
		if ((!b->isInBlock(newBlock.at(i))) && theGrid.at(r).at(c).getInfo().shape != Shape::EMPTY) throw InvalidMove{};
	}
	update(original, newBlock);
	updateGrid(original, newBlock);
	b->confirmDown();
}


void Grid::clockwise (Block *b){
	vector<Info> newBlock = b->cwInfo();
	vector<Info> original = b->getBlock();
	for (size_t i = 0; i < 4; ++i) {
		auto r = newBlock.at(i).row;
		auto c = newBlock.at(i).col;
		if ((!b->isInBlock(newBlock.at(i))) && theGrid.at(r).at(c).getInfo().shape != Shape::EMPTY)  throw InvalidMove{};
	}
	update(original, newBlock);
	updateGrid(original, newBlock);
	b->confirmCw();
}

void Grid::counterclockwise (Block *b){
	vector<Info> newBlock = b->ccwInfo();
	vector<Info> original = b->getBlock();
	for (size_t i = 0; i < 4; ++i) {
		auto r = newBlock.at(i).row;
		auto c = newBlock.at(i).col;
		if ((!b->isInBlock(newBlock.at(i))) && theGrid.at(r).at(c).getInfo().shape != Shape::EMPTY)  throw InvalidMove{};
        }
	update(original, newBlock);
	updateGrid(original, newBlock);
	b->confirmCcw();
}


void Grid::setGraphics(GraphicsDisplay * graphics){
	gd = graphics;
	for (size_t i = 0; i < HEIGHT + BUFFER_HEIGHT; ++i){
		for (size_t j = 0; j < WIDTH; ++j) {
			theGrid.at(i).at(j).attach(gd);
		}
	}
}


void Grid::updateObserver(){
	for (size_t i = 0; i < HEIGHT + BUFFER_HEIGHT; ++i){
		for (size_t j = 0; j < WIDTH; ++j) {
			theGrid.at(i).at(j).notifyObservers();
		}
	}
}


void Grid::clearLine(size_t line){
	// clear line
	for (size_t i = 0; i < WIDTH; ++i){
		theGrid.at(line).at(i).setShape(Shape::EMPTY);
		auto it = blockList.find(theGrid.at(line).at(i).getKey());
		if (it != blockList.end()) it->second = it->second - 10;
		theGrid.at(line).at(i).setKey(0);
	}
	
	// all cells downward
	if (line != HEIGHT - 1) {
		for (size_t cr = line; cr < HEIGHT - 1; ++cr) {
			for (size_t cc = 0; cc < WIDTH; ++cc) {
				theGrid.at(cr).at(cc).setShape(theGrid.at(cr + 1).at(cc).getInfo().shape);
				theGrid.at(cr).at(cc).setKey(theGrid.at(cr + 1).at(cc).getKey());	
			}	
		}		
 	}
}


bool Grid::isLineFull(size_t line){
	for(size_t i = 0; i < WIDTH; ++i){
		auto cell = theGrid.at(line).at(i);
		if(cell.getInfo().shape == Shape::EMPTY){
			return false;
		}
	}
	return true;
}

vector<size_t> Grid::checkClear(){
	vector<size_t> clearLines;
	for (size_t row = HEIGHT; row != 0; --row){
		if (isLineFull(row - 1)){
			clearLines.emplace_back(row - 1);
		}
	}
	return clearLines;
}

map<int, int>& Grid::getBlockList() {
	return blockList;
}

void Grid::setStarBlock(){
	size_t row = HEIGHT;
	while(row != 0) {
		if (theGrid.at(row - 1).at(WIDTH / 2).getInfo().shape != Shape::EMPTY) break;
		--row;
	}
	if (row == HEIGHT) {
		throw GameOver{};
	}
	
	theGrid.at(row).at(WIDTH / 2).setShape(Shape::STAR);
	theGrid.at(row).at(WIDTH / 2).notifyObservers();
}

void Grid::displayHint(vector<Info> hint){
	for (auto &cell : hint) {
		size_t hr = cell.row;
		size_t hc = cell.col;
		theGrid.at(hr).at(hc).setShape(Shape::HINT);
		theGrid.at(hr).at(hc).notifyObservers();
	}
}


void Grid::hintDisappear(vector<Info> hint){
        for (auto &cell : hint) {
                size_t hr = cell.row;
                size_t hc = cell.col;
                theGrid.at(hr).at(hc).setShape(Shape::EMPTY);
                theGrid.at(hr).at(hc).notifyObservers();
        }
}
