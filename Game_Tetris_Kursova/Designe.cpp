#include "Designe.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cctype>

Position::Position()
	:x(0), y(0)
{
}

Position::Position(int x, int y)
	:x(x), y(y)
{
}

Position::Position(const Position& otherObj)
	:x(otherObj.x), y(otherObj.y)
{
}

Position::~Position()
{
}

void Position::setNewPos(int newX, int newY)
{
	setX(newX);
	setY(newY);
}

void Position::setX(int newX)
{
	x = newX;
}

void Position::setY(int newY)
{
	y = newY;
}

int Position::getX() const
{
	return x;
}

int Position::getY() const
{
	return y;
}

Position& Position::operator=(Position otherObj)
{
	x = otherObj.x;
	y = otherObj.y;
	return *this;
}

AbstRect::AbstRect()
	:Position(), height(0), width(0), color(0)
{
}

AbstRect::AbstRect(int height, int width, int x, int y, int color)
	:Position((SHORT)x, (SHORT)y), height(height), width(width), color(color)
{
}

AbstRect::AbstRect(const AbstRect& otherObj)
	:Position(otherObj), height(otherObj.height), width(otherObj.width), color(otherObj.color)
{
}

AbstRect::~AbstRect()
{
}

void AbstRect::print() const
{
}

int AbstRect::getHeight() const
{
	return height;
}

int AbstRect::getWidth() const
{
	return width;
}

AbstRect& AbstRect::operator=(AbstRect otherObj)
{
	height = otherObj.height;
	width = otherObj.width;
	color = otherObj.color;
	Position::operator=(otherObj);
	return *this;
}

void AbstRect::setColor(int newColor)
{
	color = newColor;
}

Rect::Rect()
	:AbstRect(), simb(' ')
{
}

Rect::Rect(int color, int height, int width, int x, int y, char simb)
	:AbstRect(height, width, x, y, color), simb(simb)
{
}

Rect::~Rect()
{
}

void Rect::print() const
{
	COORD position{ x,y };
	SetConsoleCursorPosition(hStdOut, position);
	SetConsoleTextAttribute(hStdOut, color);
	for (int i = 0;i < height;i++) {
		for (int j = 0;j < width;j++) {
			std::cout << (char)simb;
		}
		position.Y++;
		SetConsoleCursorPosition(hStdOut, position);
	}
}

Frame::Frame()
	:AbstRect(), elem(stdFr)
{
}

Frame::Frame(int height, int width, int x, int y, int color, frameElem elem)
	:AbstRect(height, width, x, y, color), elem(elem)
{
}

Frame::Frame(const Frame& otherObj)
	:AbstRect(otherObj), elem(otherObj.elem)
{
}

Frame::~Frame()
{
}

void Frame::print() const
{
	SetConsoleTextAttribute(hStdOut, color);
	COORD curPos{ x,y };
	SetConsoleCursorPosition(hStdOut, curPos);
	std::cout << elem.LUA;
	curPos.X++;
	for (int i = 0;i < width - 1;i++) {
		std::cout << elem.HE;
		curPos.Y += height;
		SetConsoleCursorPosition(hStdOut, curPos);
		std::cout << elem.HE;
		curPos.Y -= height;
		curPos.X++;
		SetConsoleCursorPosition(hStdOut, curPos);
	}
	std::cout << elem.RUA;
	curPos.X = x;
	curPos.Y = y + 1;
	SetConsoleCursorPosition(hStdOut, curPos);
	for (int i = 0;i < height - 1;i++) {
		std::cout << elem.VE;
		curPos.X += width;
		SetConsoleCursorPosition(hStdOut, curPos);
		std::cout << elem.VE;
		curPos.X -= width;
		curPos.Y++;
		SetConsoleCursorPosition(hStdOut, curPos);
	}
	std::cout << elem.LDA;
	curPos.X += width;
	SetConsoleCursorPosition(hStdOut, curPos);
	std::cout << elem.RDA;
}

Frame& Frame::operator=(Frame otherObj)
{
	AbstRect::operator=(otherObj);
	elem = otherObj.elem;
	return *this;
}

frameElem Frame::getFrameElem() const
{
	return elem;
}

void Text::printFullInstr() const
{
	SetConsoleTextAttribute(hStdOut, 240);
	COORD pos{ x,y };
	int temp = pos.X;
	pos.X = (100 - 48) / 2;
	SetConsoleCursorPosition(hStdOut, pos);
	std::cout << "Instructions for the program and rules for game:";
	pos.X = temp;
	pos.Y ++;
	SetConsoleCursorPosition(hStdOut, pos);
	std::cout << "- Use the up and down arrow keys to navigate menus and make selections with Enter.";
	pos.Y++;
	SetConsoleCursorPosition(hStdOut, pos);
	std::cout << "- During the game, press Enter to activate the pause menu and make selections.";
	pos.Y++;
	SetConsoleCursorPosition(hStdOut, pos);
	std::cout << "- View and erase the top 15 game results.";
	pos.Y++;
	SetConsoleCursorPosition(hStdOut, pos);
	std::cout << "- The game follows classic rules.";
	pos.Y++;
	SetConsoleCursorPosition(hStdOut, pos);
	std::cout << "- Tetraminoes fall from the top of the playing field.";
	pos.Y++;
	SetConsoleCursorPosition(hStdOut, pos);
	std::cout << "- Use the arrow keys to move the tetramino left or right, space bar to rotate it, and down ";
	pos.Y++;
	SetConsoleCursorPosition(hStdOut, pos);
	std::cout << "  arrow to force it down.";
	pos.Y++;
	SetConsoleCursorPosition(hStdOut, pos);
	std::cout << "- The piece stops when it reaches the bottom or collides with a fixed piece.";
	pos.Y++;
	SetConsoleCursorPosition(hStdOut, pos);
	std::cout << "- A new shape appears at the top, and the next shape is shown in a separate field.";
	pos.Y++;
	SetConsoleCursorPosition(hStdOut, pos);
	std::cout << "- Fill a row to remove it, shift everything above down, and score 10 points.";
	pos.Y++;
	SetConsoleCursorPosition(hStdOut, pos);
	std::cout << "- The level increases every 50 points scored.";
	pos.Y++;
	SetConsoleCursorPosition(hStdOut, pos);
	std::cout << "- Aim to score as many points as possible, tracked in a special window.";
	pos.Y++;
	SetConsoleCursorPosition(hStdOut, pos);
	std::cout << "- Higher points increase the level, making pieces fall faster.";
	pos.Y++;
	SetConsoleCursorPosition(hStdOut, pos);
	std::cout << "- The game ends when a new tetramino collides immediately.";
	pos.Y++;
	SetConsoleCursorPosition(hStdOut, pos);
	std::cout << "- The result is saved. Result not saved on self-exit.";
	pos.Y ++;
	pos.X = (100 - 33) / 2;
	SetConsoleCursorPosition(hStdOut, pos);
	std::cout << "Game made by Palamarchuk Oleksii.";
	pos.Y++;
	pos.X = (100 - 10) / 2;
	SetConsoleCursorPosition(hStdOut, pos);
	std::cout << "Year 2023.";
}

Text::Text()
	:Position(), color(0), text(""), startTx("")
{
}

Text::Text(std::string text, int color, int x, int y)
	:color(color), Position(x, y), text(text), startTx(text)
{
}

Text::~Text()
{
}

void Text::printTx() const
{
	if (text == "FullInstTx") {
		printFullInstr();
	}
	else {
		COORD pos{ x,y };
		SetConsoleCursorPosition(hStdOut, pos);
		SetConsoleTextAttribute(hStdOut, color);
		std::cout << text;
	}
}

std::string Text::getTx() const
{
	return text;
}

void Text::addTx(std::string tx)
{
	text = startTx + tx;
}

int Text::getColor() const
{
	return color;
}

void Text::setColor(int newColor)
{
	color = newColor;
}

Button::Button()
	:choise(false), Rect(), Text()
{
}

Button::Button(bool choise, int x, int y, std::string text, int tColor, int rColor, int height, int width, char simb)
	:Rect(rColor, height, width, x, y, simb), Text(text, tColor, x + (width - text.length()) / 2, y + height / 2), choise(choise)
{
}

Button::~Button()
{
}

void Button::print() const
{
	Rect::print();
	Text::printTx();
}

bool Button::getChoise() const
{
	return choise;
}

int Button::getX() const
{
	return Rect::getX();
}

int Button::getY() const
{
	return Rect::getY();
}

void Button::setChoise(bool newChoise)
{
	choise = newChoise;
}

Wind::Wind(int x, int y, int rColor, int fColor, int height, int width, char simb, frameElem elem)
	:Frame(height, width, x, y, fColor, elem), Rect(rColor, height - 1, width - 3, x + 2, y + 1, simb)
{
}

Wind::~Wind()
{
}

void Wind::print() const
{
	Rect::print();
	Frame::print();
}

int Wind::getHeight() const
{
	return Frame::height;
}

int Wind::getWidth() const
{
	return Frame::width;
}

int Wind::getX() const
{
	return Frame::x;
}

int Wind::getY() const
{
	return Frame::y;
}

InfWind::InfWind(std::string text, int x, int y, int rColor, int fColor, int tColor, int height, int width, int centering, char simb, frameElem elem)
	:Wind(x, y, rColor, fColor, height, width, simb, elem), centering(centering)
{

	Text::text = text;
	Text::startTx = text;
	Text::color = tColor;
	setTxPos();
}

InfWind::~InfWind()
{
}

void InfWind::print() const
{
	Wind::print();
	Text::printTx();
}

void InfWind::setTxPos()
{
	if (!centering) {
		Text::x = Wind::Rect::x + (Rect::width - text.length()) / 2;
		Text::y = Wind::Rect::y + Rect::height / 2;
	}
	if (centering == 1) {
		Text::x = Wind::Rect::x + (Rect::width - text.length()) / 2;
		Text::y = Wind::Rect::y + 1;
	}
}

void InfWind::addText(std::string addTx)
{
	Text::addTx(addTx);
	setTxPos();
	Text::printTx();
}

int InfWind::getX() const
{
	return Wind::Frame::x;
}

int InfWind::getY() const
{
	return Wind::Frame::y;
}

Menu::Menu(Button* btns, int buttonCount, frameElem elem)
	:btnCount(buttonCount), position(0)
{
	buttons = new Button[buttonCount];
	for (int i = 0;i < buttonCount;i++) {
		buttons[i] = btns[i];
	}
	for (int i = 0;i < btnCount;i++) {
		if (buttons[i].getChoise() == true) {
			Frame temp{ buttons[i].getHeight() + 1,buttons[i].getWidth() + 3,buttons[i].Rect::getX() - 2,buttons[i].Rect::getY() - 1,112,elem };
			menuFr = temp;
			position = i;
		}
	}
}

Menu::~Menu()
{
	delete[] buttons;
}

void Menu::print() const
{
	for (int i = 0;i < btnCount;i++) {
		buttons[i].print();
	}
	menuFr.print();
}

void Menu::clean() const
{
	Frame tempF = menuFr;
	tempF.setColor(119);
	tempF.print();
	Rect* tempBR = new Rect[btnCount];
	Text* tempBT = new Text[btnCount];
	for (int i = 0;i < btnCount;i++) {
		tempBR[i] = buttons[i];
		tempBR[i].setColor(119);
		tempBR[i].print();
		tempBT[i] = buttons[i];
		tempBT[i].setColor(119);
		tempBT[i].printTx();
	}
	delete[] tempBR;
	delete[] tempBT;
}

void Menu::move(int direction)
{
	menuFr.setColor(119);
	menuFr.print();
	if (direction == UP) {
		if (position == 0) {
			buttons[position].setChoise(false);
			position = btnCount - 1;
		}
		else {
			buttons[position].setChoise(false);
			position--;
		}
	}
	if (direction == DOWN) {
		if (position == btnCount - 1) {
			buttons[position].setChoise(false);
			position = 0;
		}
		else {
			buttons[position].setChoise(false);
			position++;
		}
	}
	buttons[position].setChoise(true);
	setFrPos();
	menuFr.setColor(112);
	menuFr.print();
}

void Menu::setFrPos()
{
	for (int i = 0;i < btnCount;i++) {
		if (buttons[i].getChoise() == true) {
			Frame temp{ buttons[i].getHeight() + 1,buttons[i].getWidth() + 3,buttons[i].Rect::getX() - 2,buttons[i].Rect::getY() - 1,112,menuFr.getFrameElem() };
			menuFr = temp;
			position = i;
		}
	}
}

int Menu::action(int& screen)
{
	COORD pos{ 1,1 };
	int key{};
	int temp{};
	do {
		SetConsoleCursorPosition(hStdOut, pos);
		key = _getch();
		if (key == UP || key == DOWN) {
			if (btnCount != 1) {
				move(key);
			}
		}
	} while (key != ENTER);
	int i{};
	for (i = 0;i < btnCount;i++) {
		if (buttons[i].getChoise() == true) {
			break;
		}
	}
	return i;
}

LogoLetter::LogoLetter()
	:Rect(), letter(' ')
{
}

LogoLetter::LogoLetter(char letter, int color, int height, int width, int x, int y, char simb)
	:Rect(color, height, width, x, y, simb), letter(letter)
{
}

LogoLetter::~LogoLetter()
{
}

void LogoLetter::print() const
{
	COORD curPos{ x,y };
	SetConsoleTextAttribute(hStdOut, color);
	if (isupper(letter)) {
		for (int i = 0;i < height;i++, curPos.Y++) {
			if ((letter == 'T' && i > 0) || ((letter == 'E' || letter == 'S') && (i == 1 || i == 3)) || (letter == 'I' && (i == 1 || i == 2 || i == 3)) || (letter == 'R' && (i == 1 || i == 3 || i == 4))) {
				if (letter == 'T' || letter == 'I') {
					curPos.X += 2;
				}
				if (letter == 'S' && i == 3) {
					curPos.X += 4;
				}
				SetConsoleCursorPosition(hStdOut, curPos);
					std::cout << simb << simb;
					if (letter == 'R' && (i == 1 || i == 3 || i == 4)) {
						curPos.X += 4;
						SetConsoleCursorPosition(hStdOut, curPos);
						std::cout << simb << simb;
					}
				if (letter == 'T' || letter == 'I') {
					curPos.X -= 2;
				}
				if ((letter == 'S' && i == 3) || letter == 'R') {
					curPos.X -= 4;
				}
				continue;
			}
			if ((letter == 'E' && (i == 0 || i == 2 || i == 3)) || (letter == 'R' && i == 2)) {
				SetConsoleCursorPosition(hStdOut, curPos);
				std::cout << simb << simb << simb << simb;
				continue;
			}
			SetConsoleCursorPosition(hStdOut, curPos);
			for (int i = 0;i < width;i++) {
				std::cout << simb;
			}
		}
	}
	if (islower(letter)) {
		COORD posTemp{};
		for (int i = 0;i < height;i++) {
			if (((letter == 'g' || letter == 'e') && (i == 0 || i == 4)) || (letter == 'a' && i == 3)) {
				posTemp.Y = curPos.Y + i;
				posTemp.X = curPos.X;
				SetConsoleCursorPosition(hStdOut, posTemp);
				for (int i = 0;i < width;i++) {
					std::cout << simb;
				}
			}
			if (((letter == 'e' || letter == 'r') && (i == 2)) || (letter == 'r' && i == 0)) {
				posTemp.Y = curPos.Y + i;
				posTemp.X = curPos.X;
				SetConsoleCursorPosition(hStdOut, posTemp);
				for (int i = 0;i < width - 2;i++) {
					std::cout << simb;
				}
			}
			if (letter == 'o' && (i == 0 || i == 4)) {
				posTemp.X = curPos.X+2;
				posTemp.Y = curPos.Y + i;
				SetConsoleCursorPosition(hStdOut, posTemp);
				for (int i = 0;i < width - 4;i++) {
					std::cout << simb;
				}
			}
			if ((letter == 'g' && i == 3) || (letter == 'a' && (i == 2 || i == 4) || (letter == 'm' && (i == 0 || i == 3 || i == 4)) || (letter == 'o' && (i == 1 || i == 2 || i == 3)) || (letter == 'v' && (i == 0 || i == 1 || i == 2)) || (letter == 'r' && (i == 1 || i == 3 || i == 4)))) {
				posTemp.X = curPos.X;
				posTemp.Y = curPos.Y + i;
				SetConsoleCursorPosition(hStdOut, posTemp);
				std::cout << simb << simb;
				posTemp.X = curPos.X+width-2;
				SetConsoleCursorPosition(hStdOut, posTemp);
				std::cout << simb << simb;
			}
			if ((letter == 'a'  && i == 1) || (letter == 'v' && i == 3)) {
				posTemp.X = curPos.X + 2;
				posTemp.Y = curPos.Y + i;
				SetConsoleCursorPosition(hStdOut, posTemp);
				std::cout << simb << simb;
				posTemp.X = curPos.X + 6;
				SetConsoleCursorPosition(hStdOut, posTemp);
				std::cout << simb << simb;
			}
			if (letter == 'm' && i == 1) {
				posTemp.X = curPos.X;
				posTemp.Y = curPos.Y + i;
				SetConsoleCursorPosition(hStdOut, posTemp);
				std::cout << simb << simb << simb << simb;
				posTemp.X = curPos.X+6;
				posTemp.Y = curPos.Y + i;
				SetConsoleCursorPosition(hStdOut, posTemp);
				std::cout << simb << simb << simb << simb;
			}
			if (letter == 'g' && i == 2) {
				posTemp.X = curPos.X;
				posTemp.Y = curPos.Y + i;
				SetConsoleCursorPosition(hStdOut, posTemp);
				std::cout << simb << simb;
				posTemp.X = curPos.X + 4;
				SetConsoleCursorPosition(hStdOut, posTemp);
				for (int i = 0;i < width - 4;i++) {
					std::cout << simb;
				}
			}
			if ((letter == 'e' && (i == 1 || i == 3) || (letter == 'g' && i == 1))) {
				posTemp.X = curPos.X;
				posTemp.Y = curPos.Y + i;
				SetConsoleCursorPosition(hStdOut, posTemp);
				std::cout << simb << simb;
			}
			if ((letter == 'a' && i == 0) || (letter == 'v' && i == 4)) {
				posTemp.X = curPos.X+4;
				posTemp.Y = curPos.Y + i;
				SetConsoleCursorPosition(hStdOut, posTemp);
				std::cout << simb<<simb;
			}
			if (letter == 'm' && i == 2) {
				posTemp.X = curPos.X;
				posTemp.Y = curPos.Y + i;
				SetConsoleCursorPosition(hStdOut, posTemp);
				std::cout << simb << simb;
				posTemp.X = curPos.X + 4;
				SetConsoleCursorPosition(hStdOut, posTemp);
				std::cout << simb << simb;
				posTemp.X = curPos.X + 8;
				SetConsoleCursorPosition(hStdOut, posTemp);
				std::cout << simb << simb;
			}
		}
	}
}

LogoLetter& LogoLetter::operator=(LogoLetter otherObj)
{
	letter = otherObj.letter;
	Rect::operator=(otherObj);
	return *this;
}

Logo::Logo(int lettersCount, LogoLetter* ltrs, int x, int y, int rColor, int fColor, int height, int width, char simb, frameElem elem)
	:Wind(x, y, rColor, fColor, height, width, simb, elem), lettersCount(lettersCount)
{
	letters = new LogoLetter[lettersCount];
	for (int i = 0;i < lettersCount;i++) {
		letters[i] = ltrs[i];
	}
}

Logo::~Logo()
{
	delete[] letters;
}

void Logo::print() const
{
	Wind::print();
	for (int i = 0;i < lettersCount;i++) {
		letters[i].print();
	}
}