#ifndef HINT_H
#define HINT_H

#include "grid.h"
#include "cell.h"
#include <vector>

class Hint{
	Grid raw;
	Block block;
public:
	Hint(const Grid& raw, const Block& block);
	std::vector<Info> answer();
};

#endif
