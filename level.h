#ifndef LEVEL_H
#define LEVEL_H

#include "info.h"
#include <vector>
#include <string>
#include <fstream>

class Level{
	int level;
	bool useSequence;
	std::vector<Shape> sequence;
	std::vector<Shape> seq_backup;
	Shape readSequence();
public:
	Level(int l = 0, std::string s = "");
	void setLevel(int l) noexcept;
	int getLevel() noexcept;
	Shape getNewShape() noexcept;	
	void setSequence(std::string fname);
	void setSequence(bool isON);
	void restartSequence();
};

#endif
