#include <iostream>
#include <conio.h>
#include "Designe.h"
#include "Game.h"
#include <stdlib.h>

int main() {
	HWND hwnd = GetConsoleWindow();
	RECT rectC;

	GetClientRect(hwnd, &rectC);
	MoveWindow(hwnd, rectC.left, rectC.top, 100 * 8, 34 * 16, TRUE);
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	system("mode con cols=100 lines=34");
	SetConsoleTitleW(L"Tetris");

	CONSOLE_SCREEN_BUFFER_INFO csbuf;
	GetConsoleScreenBufferInfo(hStdOut, &csbuf);
	SMALL_RECT coord = csbuf.srWindow;

	Frame scrFrame{ coord.Bottom,coord.Right,0,0 };

	Button* bArr = new Button[4];
	bArr[0] = { true,(coord.Right - 19) / 2,coord.Bottom / 2 - 3,"START",32,34,3,20 };
	bArr[1] = { false,bArr[0].getX(),bArr[0].getY() + bArr[0].getHeight() + 2,"RESULT",16,17,3,20 };
	bArr[2] = { false,bArr[1].getX(),bArr[1].getY() + bArr[1].getHeight() + 2,"INSTRUCTION",96,102,3,20 };
	bArr[3] = { false,bArr[2].getX(),bArr[2].getY() + bArr[2].getHeight() + 2,"EXIT",64,68,3,20 };
	Menu menu{ bArr,4 };
	delete[] bArr;

	LogoLetter* lArr = new LogoLetter[6];
	lArr[0] = { 'T',68,5,6,(coord.Right - 46) / 2 + 4,((coord.Bottom / 2) - 8) / 2 };
	lArr[1] = { 'E',51,5,4,lArr[0].getX() + lArr[0].getWidth() + 1,lArr[0].getY()};
	lArr[2] = { 'T',102,5,6,lArr[1].getX() + lArr[1].getWidth() + 1,lArr[1].getY() };
	lArr[3] = { 'R',34,5,6,lArr[2].getX() + lArr[2].getWidth() + 1,lArr[2].getY() };
	lArr[4] = { 'I',17,5,6,lArr[3].getX() + lArr[3].getWidth() + 1,lArr[3].getY() };
	lArr[5] = { 'S',85,5,6,lArr[4].getX() + lArr[4].getWidth() + 1,lArr[4].getY() };
	Logo logo{ 6,lArr,(coord.Right - 46) / 2,((coord.Bottom / 2) - 8) / 2 - 2 ,0,112,8,46 };
	delete[] lArr;

	Frame gamePoleFr{ POLEHIGHT + 1,POLEWIDTH * 2 + 3 ,(coord.Right / 2) - 11 ,(coord.Bottom - 21) / 2 };

	InfWind scoreWind{ "SCORE: " ,gamePoleFr.getX() + gamePoleFr.getWidth() + 3,gamePoleFr.getY(),102,112,96,4,19 };
	InfWind levelWind{ "LEVEL: " ,scoreWind.getX(),scoreWind.getY() + scoreWind.getHeight() + 2,34,112,32,4,19 };
	InfWind nextFigureWind{ "NEXT FIGURE:",levelWind.getX(),levelWind.getY() + levelWind.getHeight() + 2,255,112,240,9,19,1 };

	Rect rect{ 119,14,53,(coord.Right - 54) / 2 + 1,(coord.Bottom - 15) / 2 };
	
	lArr = new LogoLetter[8];
	lArr[0] = { 'g',255,5,10,rect.getX() + 4,rect.getY() + 2 };
	lArr[1] = { 'a',255,5,10,lArr[0].getX() + lArr[0].getWidth() + 2,lArr[0].getY() };
	lArr[2] = { 'm',255,5,10,lArr[1].getX() + lArr[1].getWidth() + 2,lArr[1].getY() };
	lArr[3] = { 'e',255,5,10,lArr[2].getX() + lArr[2].getWidth() + 2,lArr[2].getY() };
	lArr[4] = { 'o',68,5,10,lArr[0].getX(),lArr[0].getY() + lArr[0].getHeight() + 1 };
	lArr[5] = { 'v',68,5,10,lArr[4].getX() + lArr[4].getWidth() + 2,lArr[4].getY() };
	lArr[6] = { 'e',68,5,10,lArr[5].getX() + lArr[5].getWidth() + 2,lArr[5].getY() };
	lArr[7] = { 'r',68,5,10,lArr[6].getX() + lArr[6].getWidth() + 2,lArr[6].getY() };
	Logo gameOverL{ 8,lArr,rect.getX(),rect.getY(),0,112,rect.getHeight(),rect.getWidth() };
	delete[] lArr;

	InfWind menuW{ "MENU",gamePoleFr.getX() - 23,gamePoleFr.getY(),85,112,80,4,20 };
	Button* bPause = new Button{ true,menuW.getX()+2,menuW.getY() + menuW.getHeight() + 3,"PAUSE",16,17,3,17 };
	Menu pauseMenu{ bPause,1 };

	bArr = new Button[2];
	bArr[0] = { true,bPause->getX(),bPause->getY(),"CONTINUE GAME",32,34,3,17 };
	bArr[1] = { false, bArr[0].getX(),bArr[0].getY() + bArr[0].getHeight() + 2,"FINISHE GAME",64,68,3,17 };
	Menu gameMenu{ bArr,2 };
	delete[] bArr;

    InfWind bestRw{ "BEST RESULTS",(coord.Right/2 - 25) / 2+10,2,17,112,16,4,25 };
	Wind resW{ (coord.Right/2-25)/2+10,bestRw.getY()+bestRw.getHeight()+3,0,112,18,25};
	BestResult bestRes{ 15,"best_result_tetris.txt",15,resW.getX() + 4,resW.getY() + 2 };
	bestRes.writeFromFile();

	InfWind menuRW{ "MENU",(coord.Right / 2 - 25) / 2 + coord.Right / 2-10,bestRw.getY(),51,112,48,4,24 };
	
	bArr = new Button[2];
	bArr[0] = { true,menuRW.getX()+2,resW.getY()+1,"DELETE RESULTS",96,102,3,21};
	bArr[1] = { false,bArr[0].getX(),bArr[0].getY() + bArr[0].getHeight() + 2,"BACK TO MENU",64,68,3,21 };
	Menu resMenu1{ bArr,2 };

	InfWind deleteW{ "DELETE RESULTS?",menuRW.getX(),menuRW.getY(),51,112,48,4,24 };
	
	Button* bArr2 = new Button[2];
	bArr2[0] = { true,bArr[0].getX(),bArr[0].getY(),"YES",32,34,3,21 };
	bArr2[1] = { false,bArr[1].getX(),bArr[1].getY() ,"NO",64,68,3,21 };
	Menu resMenu2{ bArr2,2 };
	delete[] bArr;
	delete[] bArr2;

	InfWind instInfW{ "INSTRUCTION",(coord.Right - 25) / 2,1,102,112,96,4,25 };
	Wind instW{ 2,instInfW.getY() + instInfW.getHeight() + 1,255,112,21,95 };
	Text instrTx{ "FullInstTx",240,(SHORT)instW.getX() + 3,(SHORT)instW.getY() + 2 };

	Button* bBack = new Button{ true,instInfW.getX(),instW.getY() + instW.getHeight()+2,"BACK TO MENU",64,68,3,26 };
	Menu backMenu{ bBack,1 };

	int screen = 1;
	int act{};
	do {
		SetConsoleTextAttribute(hStdOut, 119);
		system("cls");
		scrFrame.print();
		if (screen == 1) {
			menu.print();
			logo.print();
			screen = menu.action(screen) + 2;
			continue;
		}
		if (screen == 2) {
			gamePoleFr.print();
			scoreWind.print();
			levelWind.print();
			nextFigureWind.print();
			menuW.print();

			srand((unsigned)time(NULL));
			int elem = rand() % 7;
			int nextElem = rand() % 7;
			int elemCol = rand() % 6 + 1;
			int nextElemCol = rand() % 6 + 1;

			GamePole gamePole(gamePoleFr.getX() + 2, gamePoleFr.getY() + 1, 0);
			Figure figure(elemCol, elem, gamePole);
			Figure nextFigure(nextElemCol, nextElem, nextFigureWind);

			gamePole.printPole();
			nextFigure.printFigure();
			figure.printFigure();

			GameInf gameInf{};
			scoreWind.addText(std::to_string(gameInf.getScore()));
			levelWind.addText(std::to_string(gameInf.getLevel()));
			pauseMenu.print();

			int hit{};
			do {
				figure.printFigure();
				hit = 0;
				int key{};
				bool move = false;
				if (_kbhit()) {
					switch (key = _getch()) {
					case ENTER: {
						pauseMenu.clean();
						gameMenu.print();
						act = gameMenu.action(screen);
						if (act) {
							screen = 1;
							break;
						}
						if (!act) {
							gameMenu.clean();
							pauseMenu.print();
						}
					}
					default: { 
						figure.move(gamePole, key);
						move = true;
					}
					}
					if (screen == 1) {
						break;
					}
				}
 				hit = figure.checkHitVertical(gamePole);
				if (!hit&&!move) {
					figure.falinFig(gamePole);
					Sleep(gameInf.getSpeed());
				}
				if (hit == 2) {
					nextFigureWind.print();
					figure.ifHit(nextFigureWind, nextFigure, gamePole);
				}
				if (hit == 3) {
					Sleep(gameInf.getSpeed());
					break;
				}
				int* lineInf = new int[2];
				lineInf = gamePole.checkLine();
				while (lineInf[0] == 1) {
					gamePole.cleanLine(lineInf[1]);
					gameInf.setScore(gameInf.getScore() + 10);
					scoreWind.addText(std::to_string(gameInf.getScore()));
					lineInf = gamePole.checkLine();
					if ((gameInf.getScore() != 0) && (gameInf.getScore() % 50 == 0)) {
						if (gameInf.getSpeed() >= 50) {
							gameInf.setSpeed(gameInf.getSpeed() - 10);
							gameInf.setLevel(gameInf.getLevel() + 1);
							levelWind.addText(std::to_string(gameInf.getLevel()));
						}
					}
				}
			} while (true);
			if (hit == 3) {
				rect.print();
				gameOverL.print();
				backMenu.print();
				backMenu.action(screen);
				bestRes.addResult(gameInf.getScore());
			}
			screen = 1;
			scoreWind.addText("");
			levelWind.addText("");
			continue;
		}
		if (screen == 3) {
			bestRw.print();
			resW.print();
			bestRes.print();
			menuRW.print();
			resMenu1.print();
			act = resMenu1.action(screen);
			if (act == 1) {
				screen = 1;
				continue;
			}
			if (act == 0) {
				resMenu1.clean();
				resMenu2.print();
				deleteW.print();
				act = resMenu2.action(screen);
				if (act == 0) {
					bestRes.deleteResult();
					bestRes.print();
				}
				resMenu2.clean();
			}
			continue;
		}
		if (screen == 4) {
			instInfW.print();
			instW.print();
			instrTx.printTx();
			backMenu.print();
			backMenu.action(screen);
			screen = 1;
			continue;
		}
	} while (screen != 5);
	system("cls");
	return 0;
}