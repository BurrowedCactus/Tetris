#include "cell.h"


Cell::Cell(size_t r, size_t c):r{r}, c{c}{
	blockType = Shape::EMPTY;
}

Cell::Cell(size_t r, size_t c, Shape shape):r{r}, c{c}, blockType{shape}{}

Cell::Cell(const Cell &other):r{other.r}, c{other.c}, blockType{other.blockType}{}

void Cell::setShape(Shape shape){
	this->blockType = shape;
}		

      
Info Cell::getInfo() const{
	return Info{r, c, blockType};	
}

void Cell::setKey(int key){
	this->key = key;
}

int Cell::getKey() const {
	return key;
}

