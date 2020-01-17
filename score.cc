#include "score.h"

void Score::setHighScore(int newHS) noexcept{
	highScore = newHS;
}

void Score::setCurrentScore(int newCS) noexcept{
	score = newCS;
}

int Score::getHighScore() noexcept{
	return highScore;
}

int Score::getCurrentScore() noexcept{
	return score;
}
