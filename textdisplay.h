#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "subject.h"
#include "observer.h"
#include <string>
#include "display.h"

class TextDisplay: public Observer, public ADisplay {
	std::vector<std::vector<char>> theDisplay;
public:
	TextDisplay(Level* level, Score* score, Shape* nextBlock);
	void notify(Subject &whoNotified) override;
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
