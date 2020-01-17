#ifndef CELL_H
#define CELL_H
#include "subject.h"
#include "info.h"
#include <string>


//class Block {}

class Cell : public Subject{
	const size_t r, c;
	Shape blockType;
	int key = 0; //identify of the block

public:
	Cell(size_t r, size_t c);
	Cell(size_t r, size_t c, Shape shape);
	Cell(const Cell &other);
	//only supports set shape to shapeless or shapeless to shape, sign shape to shape
	//throws exception
	void setShape(Shape newShape);
	//void move(std::string direction);
	Info getInfo() const override;
	void setKey(int key); 
        int getKey() const;
};
#endif
