#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "subject.h"
#include "window.h"
#include "info.h"
#include "display.h"
#include "constants.h"
/*
Target design:
*********************************************************
 _______________________
|                       |      Level:          1
|                       |      Score:          0
|                       |      High Score:   100
|                       |
|     TTT               |@BUFFER_STR/2@     @BUFFER_STR/2@
|      T                |<-       ->|       |<-       ->|
|                       |           @BLOCK_SIZE@
|                       |            |<-->|
|                       |  @BLOCK_SIZE + BUFFER_NEXTBLOCK@
|                       |           |<-  ->|
|                     L |      Next: ______ 
|                   LLL |           |      |
|                   J   |           |      |
|             I     J   |           |  T   |       <--- this is a 6 by 6 box.
|             I Z SJJ  T|           |  TT  |
|        OOJ  IZZ SS  TT|           |  T   |
|IIII    OOJJJIZ   S   T|     _     |______|
|_______________________|     |   <- @the height = HEIGHT_NEXT@  
**********************************************************
if we keep the window to be 500 * 500,
main is width (11 + 6 + space for string) * height (15 + 3),
therefore consider the width to be dominate term, the side length is
approximately 500 / (11 + 6 + space for string) = 500 / 25 = 20.

Conclusion: each cell is 20 * 20.
*/

class GraphicsDisplay: public Observer, public ADisplay{
	const int winSize;
	Xwindow xw;
	Shape shape;
public:
	void setShape(Shape newShape);
	GraphicsDisplay(Level* level, Score* score, Shape* nextBlock, int winSize = 500);
	void notify(Subject &whoNotified) override;
	void drawNext();
};
#endif
