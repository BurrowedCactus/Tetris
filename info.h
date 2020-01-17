#ifndef _INFO_H_
#define _INFO_H_
#include <cstddef>

enum class Shape {I, J, L, O, S, Z, T, EMPTY, STAR, HINT};

struct Info {
	size_t row;
	size_t col;
	Shape shape;
};

#endif
