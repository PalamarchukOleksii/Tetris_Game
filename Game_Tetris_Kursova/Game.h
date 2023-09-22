#pragma once
#include "Designe.h"

#define POLEHIGHT 20
#define POLEWIDTH 10

static int elem[7][4] = {
		1,2,3,4,
		1,2,3,5,
		1,2,4,6,
		2,3,4,5,
		1,3,4,6,
		1,3,5,7,
		1,3,4,5
};

class OneSq:public Position {
private:
	int color;
public:
	OneSq();
	OneSq(int x, int y, int color);
	~OneSq();
	int getColor();
	void setColor(int newColor);
	void printSq();
	OneSq& operator=(OneSq otherObj);
};

class GamePole: public Position{
private:
	OneSq scrPole[POLEHIGHT][POLEWIDTH];
	int imPole[POLEHIGHT][POLEWIDTH];
	int color;
public:
	GamePole(int angleX, int angleY, int color);
	~GamePole();
	void setIm(int x, int y, int color);
	int getIm(int x, int y);
	void convertIm();
	void printPole();
	int* checkLine();
	void cleanLine(int line);
};

class Figure {
private:
	int line;
	int color;
	OneSq fig[4];
	void spinFig(GamePole& pole);
	void moveFig(GamePole& pole, int direction);
	void addFigurePole(GamePole& pole);
	int checkHitHorizontal(GamePole pole);
	int getLine();
	void setLine(int newLine);
	void setColor(int newColor);
	int getColor();
public:
	Figure();
	Figure(int color, int line, GamePole pole);
	Figure(int color, int line, Rect rePole);
	Figure(const Figure& otherObj);
	~Figure();
	void printFigure();
	void move(GamePole& pole, int key);
	void falinFig(GamePole pole);
	int checkHitVertical(GamePole pole);
	void ifHit(Rect nextFigPole, Figure& nextFig, GamePole& gamePole);
	Figure& operator=(Figure otherObj);
};

class GameInf {
private:
	int score;
	int level;
	int speed;
public:
	GameInf(int score = 0, int level = 1, int speed = 200);
	int getScore();
	int getLevel();
	int getSpeed();
	void setScore(int newScore);
	void setLevel(int newLevel);
	void setSpeed(int newSpeed);
};

class BestResult : public Position {
private:
	int resultCount;
	int* bestResArr;
	std::string fileName;
	int color;
	void sortResultArr(int arr[], int size);
	void addToArr(int newRes);
	int writeToFile();
	void deleteResArr();
	void cleanFile();
public:
	BestResult(int resCount, std::string fileName, int color, int x, int y);
	~BestResult();
	void addResult(int newRes);
	void writeFromFile();
	void print() const;
	void deleteResult();
};