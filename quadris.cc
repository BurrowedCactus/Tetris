#include "quadris.h"
using namespace std;

Quadris::Quadris(bool graphFlag): //int winSize
	level{make_unique<Level>()},
	score{make_unique<Score>()},
	//Shape generated from level
	td{make_unique<TextDisplay>(level.get(), score.get(), &nextShape)},
	gd{graphFlag ? make_unique<GraphicsDisplay>(level.get(), score.get(),&nextShape, WIN_SIZE) : nullptr},
	g{make_unique<Grid>(td.get())}{} 


void Quadris::genBlock(){
	if (nextShape == Shape::EMPTY) {
		nextShape = level->getNewShape();
		if (graphFlag)  {
			gd->setShape(nextShape);
		}
	}

		currentBlock = make_unique<Block>(nextShape, level->getLevel());
		g->setBlock(currentBlock.get());

		nextShape = level->getNewShape();
		if (graphFlag)  {
			gd->setShape(nextShape);
		        gd->drawNext();
		}
}

	
void Quadris::displayHint(){
	auto h = make_unique<Hint>(*g, *currentBlock);
	hint = h->answer();
	g->displayHint(hint);
}

void Quadris:: hintDisappear() {
	g->hintDisappear(hint);
}


//NOTE: each time you update observer, you may also need to print out result / update score / level next block if needed

void Quadris::drop(){

	try {
		while(true){
			g->moveDown(currentBlock.get());
		} 
	} catch (InvalidMove&) {}	
	
	++unclearBlocks;
        
	// clear full lines, if any
	vector<size_t> clear = g->checkClear();
	for (auto &cRow : clear) {
		g->clearLine(cRow);
	}
	
	//level 4
	if (clear.size() != 0 ) {
		unclearBlocks = 0;
	} else if  (unclearBlocks % 5 == 0 && unclearBlocks != 0 && level->getLevel() == 4) {
		g->setStarBlock();
	}


	if (clear.size() != 0) { // if any line is cleared
		g->updateObserver();
		// update current scores, 2 steps
		score->setCurrentScore(score->getCurrentScore() + pow (level->getLevel() + 1, 2) * clear.size());

		for (auto &it : g->getBlockList()) {
			if (it.second < 10) {
				score->setCurrentScore(score->getCurrentScore() + pow (1 + it.second, 2));
			it.second = 100;
			}
		}	
		// update Highest Score
		if (score->getCurrentScore() > score->getHighScore()) {
			score->setHighScore(score->getCurrentScore()); 
		}

	}	
	genBlock();
       
}


void Quadris::moveLeft(){
	try {
		g->moveLeft(currentBlock.get());
	} catch (InvalidMove &) {}
}


void Quadris::moveRight(){
	try {
		g->moveRight(currentBlock.get());
	} catch (InvalidMove &) {}	
}

void Quadris::moveDown(){
	try {
		g->moveDown(currentBlock.get());
	} catch (InvalidMove &) {}
}

void Quadris::clockwise(){
	try {
		g->clockwise(currentBlock.get());
	} catch (InvalidMove &) {}
}

void Quadris::counterClockwise(){
	try {
		g->counterclockwise(currentBlock.get());
	} catch (InvalidMove &) {}
}


void Quadris::init(bool graphFlag, int l){
	this->graphFlag = graphFlag;
	if (graphFlag) {
		g->setGraphics(gd.get());
	}
	level->setLevel(l);
	genBlock();
}

void Quadris::setSequence(string fname){
	if (level->getLevel() == 0) level->setSequence(fname);
}

void Quadris::setSequence(bool isOn){
	level->setSequence(isOn);
}

void Quadris::levelUp(){
	if (level->getLevel() < 4) {
		int newLevel = 1 + level->getLevel();
		level->setLevel(newLevel);	
		if (graphFlag)  {
			gd->drawNext();
		}
		if (level->getLevel() == 4) {
			unclearBlocks = 0;
		}
	}
}

void Quadris::levelDown(){
	int newLevel = level->getLevel() - 1;
	if (newLevel >= 0){
		level->setLevel(newLevel);
		if (graphFlag)  {
			gd->drawNext();
		}
	}
}

void Quadris::setCurrent(Shape current){
	g->unsetBlock(currentBlock.get());
	currentBlock = make_unique<Block>(current, level->getLevel());
	g->setBlock(currentBlock.get());
}


void Quadris::updateNext(){
	nextShape = level->getNewShape();
	if (graphFlag)  {
		gd->setShape(nextShape);
		gd->drawNext();
	}
}

void Quadris::restart(){
	nextShape = Shape::EMPTY;
	score->setCurrentScore(0);
	td = make_unique<TextDisplay>(level.get(), score.get(), &nextShape);
        gd = graphFlag ? make_unique<GraphicsDisplay>(level.get(), score.get(),&nextShape, WIN_SIZE) : nullptr;
	level->restartSequence();
	g = make_unique<Grid>(td.get());
	init(graphFlag, level->getLevel());
}


int Quadris::getLevel() const{
	return level->getLevel();
}


ostream &operator<<(std::ostream &out, const Quadris &q){
 out << *(q.td);
 return out;
}

