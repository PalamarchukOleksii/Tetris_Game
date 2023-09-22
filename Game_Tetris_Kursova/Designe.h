#pragma once
#include <string>
#include <Windows.h> 

static HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

#define SPACE 32
#define ENTER 13
#define ESC 27
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

struct frameElem {
	char LUA;
	char LDA;
	char RUA;
	char RDA;
	char VE;
	char HE;
};

static frameElem stdFr{ char(457),char(456),char(443),char(444),char(442),char(461) };
static frameElem oneLineFr{ char(0xDA),char(0xC0),char(0xBF), char(0xD9),char(0xB3),char(0xC4) };

class Position {
protected:
	int x;
	int y;
public:
	Position();
	Position(int x, int y);
	Position(const Position& otherObj);
	~Position();
	void setNewPos(int newX, int newY);
	void setX(int newX);
	void setY(int newY);
	virtual int getX() const;
	virtual int getY() const;
	Position& operator=(Position otherObj);
};

class AbstRect :public Position {
protected:
	int height;
	int width;
	int color;
public:
	AbstRect();
	AbstRect(int height, int width, int x, int y, int color);
	AbstRect(const AbstRect& otherObj);
	~AbstRect();
	virtual void print() const;
	int getHeight() const;
	int getWidth() const;
	AbstRect& operator=(AbstRect otherObj);
	void setColor(int newColor);
};

class Rect :public AbstRect {
protected:
	char simb;
public:
	Rect();
	Rect(int color, int height, int width, int x, int y, char simb = char(0xDB));
	~Rect();
	void print() const override;
};

class Frame : public AbstRect {
protected:
	frameElem elem;
public:
	Frame();
	Frame(int height, int width, int x, int y, int color = 112, frameElem elem = stdFr);
	Frame(const Frame& otherObj);
	~Frame();
	void print() const override;
	Frame& operator=(Frame otherObj);
	frameElem getFrameElem() const;
};

class Text :public Position {
protected:
	std::string startTx;
	std::string text;
	int color;
	void printFullInstr() const;
public:
	Text();
	Text(std::string text, int color, int x, int y);
	~Text();
	void printTx() const;
	std::string getTx() const;
	void addTx(std::string tx);
	int getColor() const;
	void setColor(int newColor);
};

class Button : public Rect, public Text {
private:
	bool choise;
public:
	Button();
	Button(bool choise, int x, int y, std::string text, int tColor, int rColor, int height, int width, char simb = char(0xBD));
	~Button();
	void print() const override;
	bool getChoise() const;
	int getX() const override;
	int getY() const override;
	void setChoise(bool newChoise);
};

class Wind : public Rect, public Frame {
public:
	Wind(int x, int y, int rColor, int fColor, int height, int width, char simb = char(0xDB), frameElem elem = stdFr);
	~Wind();
	void print() const override;
	int getHeight() const;
	int getWidth() const;
	int getX() const override;
	int getY() const override;
};

class InfWind : public Wind, public Text {
private:
	int centering;
	void setTxPos();
public:
	InfWind(std::string text, int x, int y, int rColor, int fColor, int tColor, int height, int width, int centering = 0, char simb = char(0xDB), frameElem elem = stdFr);
	~InfWind();
	void print() const override;
	void addText(std::string addTx);
	int getX() const override;
	int getY() const override;
};

class Menu {
private:
	Button* buttons;
	Frame menuFr;
	int btnCount;
	int position;
	void setFrPos();
public:
	Menu(Button* btns, int buttonCount, frameElem elem = oneLineFr);
	~Menu();
	void print() const;
	void clean() const;
	void move(int direction);
	int action(int& screen);
};

class LogoLetter:public Rect {
private:
	char letter;
public:
	LogoLetter();
	LogoLetter(char letter, int color, int height, int width, int x, int y, char simb = char(0xDB));
	~LogoLetter();
	void print() const override;
	LogoLetter& operator=(LogoLetter otherObj);
};

class Logo : public Wind {
private:
	LogoLetter* letters;
	int lettersCount;
public:
	Logo(int lettersCount, LogoLetter* ltrs, int x, int y, int rColor, int fColor, int height, int width, char simb = char(0xDB), frameElem elem = stdFr);
	~Logo();
	void print() const override;
};
