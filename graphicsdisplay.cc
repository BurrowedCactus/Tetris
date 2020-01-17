
#include <iostream>
#include "graphicsdisplay.h"
#include "info.h"
#include "subject.h"
#include "constants.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(Level* level, Score* score, Shape* nextBlock, int winSize):
			ADisplay{level, score, nextBlock}, winSize{winSize}, xw{winSize, winSize} {
	xw.fillRectangle(0, 0, winSize, winSize, Xwindow::White);
}

void GraphicsDisplay::setShape(Shape newShape){
	shape = newShape;
}

void GraphicsDisplay::drawNext(){
	int cellSize = winSize / (WIDTH + (BLOCK_SIZE + BUFFER_NEXTBLOCK) + BUFFER_STR);
	int row = 10;
	int col = WIDTH + (BUFFER_STR + BUFFER_NEXTBLOCK)/2;
	xw.fillRectangle(col * cellSize, row * cellSize	, 4 * cellSize, 4 * cellSize, Xwindow::White);
	switch(shape){
		case Shape::I:
			xw.fillRectangle(col * cellSize, row * cellSize, 4 * cellSize, cellSize, Xwindow::Grey);
			break;
		case Shape::L:
			xw.fillRectangle((col + 2) * cellSize, row * cellSize, cellSize, cellSize, Xwindow::LightGreen);
			xw.fillRectangle(col * cellSize, (row + 1) * cellSize, 3 * cellSize, cellSize, Xwindow::LightGreen);
//                        xw.fillRectangle((col + 2) * cellSize, (row + 1) * cellSize, cellSize, cellSize, Xwindow::LightGreen);
//			xw.fillRectangle(col * cellSize, row * cellSize, 3 * cellSize, cellSize, Xwindow::LightGreen);
			break;
		case Shape::J:
			xw.fillRectangle(col * cellSize, row * cellSize, cellSize, cellSize, Xwindow::LightPink);
			xw.fillRectangle(col * cellSize, (row + 1) * cellSize, 3 * cellSize, cellSize, Xwindow::LightPink);
			break;
		case Shape::O:
			xw.fillRectangle(col * cellSize, row * cellSize	, 2 * cellSize, 2 * cellSize, Xwindow::LightBlue);
			break;
		case Shape::Z:
			xw.fillRectangle(col * cellSize, row * cellSize, 2 * cellSize, cellSize, Xwindow::Khaki);
			xw.fillRectangle((col + 1) * cellSize, (row + 1) * cellSize, 2 * cellSize, cellSize, Xwindow::Khaki);
			break;
		case Shape::S:
			xw.fillRectangle((col + 1) * cellSize, row * cellSize, 2 * cellSize, cellSize, Xwindow::Coral);
			xw.fillRectangle(col * cellSize, (row + 1) * cellSize, 2 * cellSize, cellSize, Xwindow::Coral);
			break;
		case Shape::T:
                        xw.fillRectangle((col + 1) * cellSize, (row + 1)  * cellSize, cellSize, cellSize, Xwindow::Plum);
			xw.fillRectangle(col * cellSize, row * cellSize, 3 * cellSize, cellSize, Xwindow::Plum);
			break;
		case Shape::EMPTY:
			xw.fillRectangle(col * cellSize, row * cellSize, cellSize, cellSize, Xwindow::White);
			break;
		case Shape::STAR:
			xw.fillRectangle(col * cellSize, row * cellSize, cellSize, cellSize, Xwindow::Brown);
			break;
		case Shape::HINT:
			xw.fillRectangle(col * cellSize, row * cellSize, cellSize, cellSize, Xwindow::Black);
			break;
		default:
			xw.fillRectangle(col * cellSize, row * cellSize, cellSize, cellSize, Xwindow::White);
			break;
	}
	xw.fillRectangle(WIDTH * cellSize + 2 * BUFFER_STR * cellSize / 3, 0 * cellSize, 3 * cellSize, 3 * cellSize, Xwindow::White);
	xw.drawString(WIDTH * cellSize + BUFFER_STR * cellSize / 4 , 1 * cellSize, getLevel());
	xw.drawString(WIDTH * cellSize + BUFFER_STR * cellSize / 4 , 2 * cellSize, getScore());
	xw.drawString(WIDTH * cellSize + BUFFER_STR * cellSize / 4 , 3 * cellSize, getHighScore());
	xw.drawString(WIDTH * cellSize + BUFFER_STR * cellSize / 4 , 7 * cellSize, getStrNext());
}

void GraphicsDisplay::notify(Subject& whoNotified) {
	int row = HEIGHT + BUFFER_HEIGHT - 1 - whoNotified.getInfo().row;
	int col = whoNotified.getInfo().col;
	int cellSize = winSize / (WIDTH + (BLOCK_SIZE + BUFFER_NEXTBLOCK) + BUFFER_STR);
	switch(whoNotified.getInfo().shape) {
		case Shape::I:
			xw.fillRectangle(col * cellSize, row * cellSize, cellSize, cellSize, Xwindow::Grey);
			break;
		case Shape::J:
			xw.fillRectangle(col * cellSize, row * cellSize, cellSize, cellSize, Xwindow::LightPink);
			break;
		case Shape::L:
			xw.fillRectangle(col * cellSize, row * cellSize, cellSize, cellSize, Xwindow::LightGreen);
			break;
		case Shape::O:
			xw.fillRectangle(col * cellSize, row * cellSize, cellSize, cellSize, Xwindow::LightBlue);
			break;
		case Shape::S:
			xw.fillRectangle(col * cellSize, row * cellSize, cellSize, cellSize, Xwindow::Coral);
			break;
		case Shape::Z:
			xw.fillRectangle(col * cellSize, row * cellSize, cellSize, cellSize, Xwindow::Khaki);
			break;
		case Shape::T:
			xw.fillRectangle(col * cellSize, row * cellSize, cellSize, cellSize, Xwindow::Plum);
			break;
		case Shape::EMPTY:
			xw.fillRectangle(col * cellSize, row * cellSize, cellSize, cellSize, Xwindow::White);
			break;
		case Shape::STAR:
			xw.fillRectangle(col * cellSize, row * cellSize, cellSize, cellSize, Xwindow::Brown);
			break;
		case Shape::HINT:
			xw.fillRectangle(col * cellSize, row * cellSize, cellSize, cellSize, Xwindow::Black);
			break;
		default:
			xw.fillRectangle(col * cellSize, row * cellSize, cellSize, cellSize, Xwindow::White);
			break;
	}
}
