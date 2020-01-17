#include "hint.h"
#include <vector>
#include "block.h"
#include "grid.h"
#include "constants.h"
#include "string"

using namespace std;

//fields::

const int A = -1;
const int B = -10;
const int C = 5;
const int D = 1;
const int E = 1;
const int F = 1;


Hint::Hint(const Grid& raw, const Block& block): raw{raw}, block{block}{
}

vector<vector<Info>> format(const vector<vector<Cell>> list){
	vector<vector<Info>> answer;
	vector<Info> temp;
	for (auto& line: list){
		for (auto& one: line){
			temp.emplace_back(one.getInfo());
		}
		answer.emplace_back(temp);
		temp.clear();
	}
	return answer;
}

int height(const vector<vector<Info>> &g){
	int score = 0;
	for (auto& line: g){
		for (auto& one: line){
			if (one.shape != Shape::EMPTY){
				score += one.row;
			}
		}
	}
	return score;
}

int cliff(const vector<vector<Info>> &g){
	int score = 0;
	int width = g[0].size();
	int height = g.size();
        for (int w = 0; w < width; ++w){
		bool solid = false;
                for (int h = height - 1; h >= 0; --h){
                        if (g[h][w].shape != Shape::EMPTY){
				solid = true;
				continue;
			}
			if (solid && g[h][w].shape == Shape::EMPTY){
				++score;
			}
                }
        }
        return score;
}

int clear(const vector<vector<Info>> &g){
	int score = 0;
	for (auto& line: g){
		bool clean = true;
		for (auto& one: line){
			if (one.shape == Shape::EMPTY){
				clean = false;
			}
		}
		if (clean){
			++score;
		}
	}
	return score;
}


int calculate(const vector<vector<Info>> &g, const vector<Info> &b){
	int a = height(g);
	int bb = cliff(g);
	int c = clear(g);
	return A * a + B * bb + C * c;
}

vector<Info> Hint::answer(){
	Block c{block};
	int score = -100;
	vector<Info> answer;
	for (size_t i = 0; i <= WIDTH; ++i){
		for (int j = 0; j < 4; ++j){
			Block b {block};
			Grid g{raw};
			for (int J = 0; J < j-1; ++J){
				try {
					g.clockwise(&b);
				} catch (...){

				}
			}
			for (size_t I = 1; I < i; ++I){
				try {
					g.moveRight(&b);
				} catch (...){
					
				}
			}
			try {
				while(true){
					g.moveDown(&b);
				}
			} catch (...) {
			}
			int currentScore = calculate (format(g.theGrid), b.getBlock());
			if(currentScore > score){
				score = currentScore;
				answer = b.getBlock();
			}
		}
	}
	return answer;
}

