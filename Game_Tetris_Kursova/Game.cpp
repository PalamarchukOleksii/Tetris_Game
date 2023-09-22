#include "Game.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <fstream>

OneSq::OneSq()
	:Position(), color(1)
{
}

OneSq::OneSq(int x, int y, int color)
	:Position(x, y), color(color)
{
}

OneSq::~OneSq()
{
}

int OneSq::getColor()
{
	return color;
}

void OneSq::setColor(int newColor)
{
	color = newColor;
}

void OneSq::printSq()
{
	SetConsoleTextAttribute(hStdOut, this->color);
	COORD pos{ (SHORT)x,(SHORT)y };
	SetConsoleCursorPosition(hStdOut, pos);
	std::cout << char(219) << char(219);
	pos.X = 1;
	pos.Y = 1;
	SetConsoleCursorPosition(hStdOut, pos);
}

OneSq& OneSq::operator=(OneSq otherObj)
{
	Position::operator=(otherObj);
	color = otherObj.color;
	return *this;
}

GamePole::GamePole(int angleX, int angleY, int color)
	:color(color), Position(angleX, angleY)
{
	scrPole[0][0].setX(this->x);
	scrPole[0][0].setY(this->y);
	scrPole[0][0].setColor(color);
	imPole[0][0] = scrPole[0][0].getColor();
	for (int i = 0;i < POLEHIGHT;i++) {
		for (int j = 0;j < POLEWIDTH;j++) {
			if (i == 0 && j == 0)continue;
			scrPole[i][j].setX(angleX + (j * 2));
			scrPole[i][j].setY(angleY + i);
			scrPole[i][j].setColor(color);
			imPole[i][j] = 0;
		}
	}
}

GamePole::~GamePole()
{
}

void GamePole::printPole()
{
	for (int i = 0;i < POLEHIGHT;i++) {
		for (int j = 0;j < POLEWIDTH;j++) {
			scrPole[i][j].printSq();
		}
	}
}

void GamePole::convertIm()
{
	for (int i = 0;i < POLEHIGHT;i++) {
		for (int j = 0;j < POLEWIDTH;j++) {
			scrPole[i][j].setColor(imPole[i][j]);
		}
	}
}

void GamePole::setIm(int x, int y, int color)
{
	imPole[y][x] = color;
}

int GamePole::getIm(int x, int y)
{
	return imPole[y][x];
}

int* GamePole::checkLine()
{
	int* inf = new int[2];
	inf[0] = 0;
	inf[1] = 0;
	for (int i = 0;i < POLEHIGHT;i++) {
		if (imPole[i][0] != 0) {
			inf[0] = 1;
			for (int j = 0;j < POLEWIDTH;j++) {
				if (imPole[i][j] == 0) {
					inf[0] = 0;
				}
			}
			if (inf[0] == 1) {
				inf[1] = i;
				return inf;
			}
		}
	}
	return inf;
}

void GamePole::cleanLine(int line)
{
	for (int j = 0;j < POLEWIDTH;j++) {
		imPole[line][j] = 0;
	}
	for (int i = line;i > 0;i--) {
		for (int j = 0;j < POLEWIDTH;j++) {
			imPole[i][j] = imPole[i - 1][j];
		}
	}
	for (int j = 0;j < POLEWIDTH;j++) {
		imPole[0][j] = 0;
	}
	convertIm();
	printPole();
}

Figure::Figure(int color, int line, GamePole pole)
	:line(line), color(color)
{
	for (int i = 0;i < 4;i++) {
		if (elem[line][i] == 1) {
			fig[i] = { 8 + pole.getX()  , pole.getY(), color };
		}
		if (elem[line][i] == 2) {
			fig[i] = { 10 + pole.getX()  ,pole.getY(), color };
		}
		if (elem[line][i] == 3) {
			fig[i] = { 8 + pole.getX() ,1 + pole.getY(),color };
		}
		if (elem[line][i] == 4) {
			fig[i] = { 10 + pole.getX() ,1 + pole.getY() ,color };
		}
		if (elem[line][i] == 5) {
			fig[i] = { 8 + pole.getX()  ,2 + pole.getY(), color };
		}
		if (elem[line][i] == 6) {
			fig[i] = { 10 + pole.getX()  ,2 + pole.getY(), color };
		}
		if (elem[line][i] == 7) {
			fig[i] = { 8 + pole.getX() ,3 + pole.getY(),color };
		}
	}
}

Figure::Figure(int color, int line, Rect rePole)
	:color(color), line(line)
{
	for (int i = 0;i < 4;i++) {
		if (elem[line][i] == 1) {
			fig[i] = { 6 + rePole.getX(),rePole.getY() + 3, color };
		}
		if (elem[line][i] == 2) {
			fig[i] = { 8 + rePole.getX(),rePole.getY() + 3, color };
		}
		if (elem[line][i] == 3) {
			fig[i] = { 6 + rePole.getX(),4 + rePole.getY(),color };
		}
		if (elem[line][i] == 4) {
			fig[i] = { 8 + rePole.getX(),4 + rePole.getY() ,color };
		}
		if (elem[line][i] == 5) {
			fig[i] = { 6 + rePole.getX(),5 + rePole.getY(), color };
		}
		if (elem[line][i] == 6) {
			fig[i] = { 8 + rePole.getX(),5 + rePole.getY(), color };
		}
		if (elem[line][i] == 7) {
			fig[i] = { 6 + rePole.getX(),6 + rePole.getY(),color };
		}
	}
}

Figure::Figure()
	:line(0), color(0)
{
	for (int i = 0;i < 4;i++) {
		fig[i] = {};
	}
}

Figure::Figure(const Figure& otherObj)
{
	line = otherObj.line;
	color = otherObj.color;
	for (int i = 0;i < 4;i++) {
		fig[i] = otherObj.fig[i];
	}
}

Figure::~Figure()
{
}

void Figure::addFigurePole(GamePole& pole)
{
	for (int i = 0;i < 4;i++) {
		pole.setIm((fig[i].getX() - pole.getX() + 1) / 2, fig[i].getY() - pole.getY(), color);
	}
	pole.convertIm();
}

void Figure::printFigure()
{
	for (int i = 0;i < 4;i++) {
		fig[i].printSq();
	}
}

void Figure::move(GamePole& pole, int key)
{
	int tempC = color;
	this->setColor(0);
	this->printFigure();
	switch (key) {
	case SPACE: {
		spinFig(pole);
	}break;
	case LEFT: {
		moveFig(pole, -1);
	}break;
	case RIGHT: {
		moveFig(pole, 1);
	}break;
	case DOWN: {
		falinFig(pole);
	}break;
	}
	this->setColor(tempC);
	this->printFigure();
}

void Figure::spinFig(GamePole& pole)
{
	if (line != 0) {
		Figure tempFig{ *this };
		Position pivot = fig[1];
		for (int i = 0;i < 4;i++) {
			int dy = (tempFig.fig[i].getX() - pole.getX()) / 2 - (pivot.getX() - pole.getX()) / 2;
			int dx = tempFig.fig[i].getY() - pivot.getY();
			tempFig.fig[i].setX(((pivot.getX() - pole.getX()) / 2 - dx) * 2 + pole.getX());
			tempFig.fig[i].setY(pivot.getY() + dy);
		}
		int hitH = tempFig.checkHitHorizontal(pole);
		int hitV = tempFig.checkHitVertical(pole);
		if (!hitV && !hitH) {
			*this = tempFig;
			return;
		}
		else {
			if (!hitV) {
				if (hitH == 1 || hitH == 4) {
					for (int i = 0;i < 4;i++) {
						tempFig.moveFig(pole, 1);
						hitH = tempFig.checkHitHorizontal(pole);
						hitV = tempFig.checkHitVertical(pole);
						if (!hitV && !hitH) {
							*this = tempFig;
							break;
						}
					}
				}
				if (hitH == 2 || hitH == 3) {
					for (int i = 0;i < 3;i++) {
						tempFig.moveFig(pole, -1);
						hitH = tempFig.checkHitHorizontal(pole);
						if (!hitV && !hitH) {
							*this = tempFig;
							break;
						}
					}
				}
			}
		}
	}
}


void Figure::moveFig(GamePole& pole, int direction) {
	int hitH = checkHitHorizontal(pole);
	int hitV = checkHitVertical(pole);
	if ((((hitH != 1 && hitH != 4) && direction == -1) || ((hitH != 3 && hitH != 2) && direction == 1) || !hitH) && !hitV) {
		for (int i = 0;i < 4;i++) {
			fig[i].setX(fig[i].getX() + direction * 2);
		}
	}
}

void Figure::setColor(int newColor)
{
	for (int i = 0;i < 4;i++) {
		fig[i].setColor(newColor);
	}
}

int Figure::getColor()
{
	return color;
}

void Figure::falinFig(GamePole pole)
{
	int tempC = color;
	this->setColor(0);
	this->printFigure();
	int hitV = checkHitVertical(pole);
	if (!hitV) {
		for (int i = 0; i < 4; i++) {
			fig[i].setY(fig[i].getY() + 1);
		}
	}
	this->setColor(tempC);
	this->printFigure();
}

void Figure::ifHit(Rect nextFigPole, Figure& nextFig, GamePole& gamePole)
{
	addFigurePole(gamePole);
	Figure f(nextFig.getColor(), nextFig.getLine(), gamePole);
	*this = f;
	int num = rand() % 7;
	int color = rand() % 6 + 1;
	Figure nextF(color, num, nextFigPole);
	nextFig = nextF;
	nextFig.printFigure();
}

int Figure::checkHitHorizontal(GamePole pole)
{
	for (int i = 0;i < 4;i++) {
		bool temp1 = (pole.getIm((fig[i].getX() - pole.getX() + 1) / 2 + 1, fig[i].getY() - pole.getY()) != 0);
		bool temp2 = (pole.getIm((fig[i].getX() - pole.getX() + 1) / 2 - 1, fig[i].getY() - pole.getY()) != 0);
		if (fig[i].getX() == pole.getX()) {
			return 1;
		}
		if (fig[i].getX() + 2 == pole.getX() + POLEWIDTH * 2) {
			return 3;
		}
		if (temp1) {
			return 2;
		}
		if (temp2) {
			return 4;
		}
	}
	return 0;
}

int Figure::checkHitVertical(GamePole pole)
{
	for (int i = 0;i < 4;i++) {
		if (fig[i].getY()+1 == pole.getY() + POLEHIGHT) {
			return 2;
		}
		if (pole.getIm((fig[i].getX() - pole.getX() + 1) / 2, fig[i].getY() - pole.getY() + 1) != 0) {
			int temp = 2;
			for (int i = 0;i < 4;i++) {
				if (fig[i].getY() == pole.getY()) {
					temp = 3;
					break;
				}
			}
			return temp;
		}
	}
	return 0;
}

int Figure::getLine()
{
	return line;
}

void Figure::setLine(int newLine)
{
	line = newLine;
}

Figure& Figure::operator=(Figure otherObj)
{
	line = otherObj.line;
	color = otherObj.color;
	for (int i = 0;i < 4;i++) {
		fig[i] = otherObj.fig[i];
	}
	return *this;
}

GameInf::GameInf(int score, int level, int speed)
	:score(score), level(level), speed(speed)
{
}

int GameInf::getScore()
{
	return score;
}

int GameInf::getLevel()
{
	return level;
}

int GameInf::getSpeed()
{
	return speed;
}

void GameInf::setScore(int newScore)
{
	score = newScore;
}

void GameInf::setLevel(int newLevel)
{
	level = newLevel;
}

void GameInf::setSpeed(int newSpeed)
{
	speed = newSpeed;
}

BestResult::BestResult(int resCount, std::string fileName, int color, int x, int y)
	:resultCount(resCount), fileName(fileName), color(color), Position(x, y)
{
	bestResArr = new int[resultCount];
	for (int i = 0;i < resultCount;i++) {
		bestResArr[i] = 0;
	}
}

void BestResult::addResult(int newRes)
{
	addToArr(newRes);
	writeToFile();
}

void BestResult::addToArr(int newRes)
{
	int* tempArr = new int[resultCount + 1];
	for (int i = 0;i < resultCount + 1;i++) {
		tempArr[i] = bestResArr[i];
		if (i == resultCount) {
			tempArr[resultCount] = newRes;
		}
	}
	sortResultArr(tempArr, resultCount + 1);
	for (int i = 0;i < resultCount ;i++) {
		bestResArr[i] = tempArr[i];
	}
	delete[] tempArr;
}

void BestResult::sortResultArr(int arr[], int size)
{
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (arr[j] < arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

int BestResult::writeToFile()
{
	cleanFile();
	std::ofstream file("D:\\прога\\Game_Tetris_Kursova\\" + fileName);
	if (file.is_open()) {
		for (int i = 0; i < resultCount; i++) {
			file << bestResArr[i] << std::endl;
		}
		file.close();
		return 0;
	}
	return 1;
}

void BestResult::print() const
{
	COORD pos{ (SHORT)x,(SHORT)y };
	SetConsoleCursorPosition(hStdOut, pos);
	SetConsoleTextAttribute(hStdOut, color);
	for (int i = 0;i < resultCount;i++) {
		pos.Y = y + i;
		SetConsoleCursorPosition(hStdOut, pos);
		std::cout << i + 1 << ") ";
		if (bestResArr[i] != 0) {
			std::cout << bestResArr[i];
		}
	}
}

void BestResult::deleteResult()
{
	deleteResArr();
	cleanFile();
}

void BestResult::writeFromFile()
{
	std::ifstream file("D:\\прога\\Game_Tetris_Kursova\\" + fileName);
	int number;
	int numberCount = 0;
	if (file.is_open()) {
		while (file >> number && numberCount < resultCount) {
			bestResArr[numberCount] = number;
			numberCount++;
		}
		file.close();
	}
}

void BestResult::cleanFile()
{
	std::ofstream file("D:\\прога\\Game_Tetris_Kursova\\" + fileName, std::ofstream::out | std::ofstream::trunc);
	file.close();
}

void BestResult::deleteResArr()
{
	for (int i = 0;i < resultCount;i++) {
		bestResArr[i] = 0;
	}
}

BestResult::~BestResult()
{
	delete[] bestResArr;
}
