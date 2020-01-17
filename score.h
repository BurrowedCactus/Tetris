#ifndef SCORE_H
#define SCORE_H

class Score{
	int score;
	int highScore;
public:
	void setHighScore(int newHS) noexcept;
	void setCurrentScore(int newCS) noexcept;
	int getHighScore() noexcept;
	int getCurrentScore() noexcept;
};

#endif
