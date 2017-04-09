// TextAdventure.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
#include "windows.h"
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

void intro();
void testscreen();
void drawscreen(char picture[]);
void getloc(char[],int j);
void getimg();
void setloc();
void setimg();
void mainmenu();
void startgame();
void loadgame();
void debug();

int main()
{
	testscreen();
	intro();

	char loc[10];
	getloc(loc, 1);
	
	cout << loc << endl;
	system("Pause");

	mainmenu();
//	char picture[] = { R"foo(   
//      ,,,,
//     /   '
//    /.. /
//   ( c  D
//    \- '\_
//     `-'\)\
//        |_ \
//        |U \\
//       (__,//
//       |. \/
//       LL__I
//        |||
//        |||
//       -``'
//)foo" };
//	drawscreen(picture);
    return 0;
}

void intro() {
	cout<<
		R"foo(
              _                 _                    _____     _                 _ 
     /\      | |               | |                  |_   _|   | |               | |
    /  \   __| |_   _____ _ __ | |_ _   _ _ __ ___    | |  ___| | __ _ _ __   __| |
   / /\ \ / _` \ \ / / _ \ '_ \| __| | | | '__/ _ \   | | / __| |/ _` | '_ \ / _` |
  / ____ \ (_| |\ V /  __/ | | | |_| |_| | | |  __/  _| |_\__ \ | (_| | | | | (_| |
 /_/    \_\__,_| \_/ \___|_| |_|\__|\__,_|_|  \___| |_____|___/_|\__,_|_| |_|\__,_|
)foo";
	Sleep(3000);
system("CLS");                                                                                  																							
}

void testscreen() {
	cout <<
		R"foo(
+----------------------------------------------------------------------------------+
|                                                                                  |
|                                                                                  |
|                                                                                  |
|                                                                                  |
|                                                                                  |
|                                                                                  |
|                       Resize to show complete box                                |
|                        for game to work correctly                                |
|                                                                                  |
|                                                                                  |
|                                                                                  |
|                                                                                  |
|                                                                                  |
|                                                                                  |
+----------------------------------------------------------------------------------+
)foo";
	system("PAUSE");
	system("CLS");
}

void mainmenu() {
	system("CLS");
	cout << R"foo(
	[1] Start New Game
	[2] Load Game
	[3] Debug
)foo" << endl;
	char answer;
	cin >> answer;
	answer = atoi(&answer);
	switch (answer) {
		case 1:startgame();
		break;
		case 2:loadgame();
		break;
		case 3:debug();
		break;
	}
}

void drawscreen(char picture[]) {
	
	cout <<picture
		 <<
		R"foo(
+-------------------------------------------------------------------------------------------------+
|                                                                                                 |
+-------------------------------------------------------------------------------------------------+
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
+-------------------------------------------------------------------------------------------------+
)foo";
}

void getloc(char newloc[],int j) {
	FILE *datei;
	if ((datei = fopen("locations.txt","r")) == NULL) {
		fprintf(stderr, "Fehler bei der Dateioeffnung von location.txt");
		cout << "Fehler bei der Dateioeffnung von location.txt" << endl;
	}
	fread(&newloc, sizeof(char[10]),j,datei);
	fclose(datei);
}

void startgame() {

};

void loadgame() {

}

void debug() {
	system("CLS");
	char answer;
	system("cls");
	cout << "MapEdit" << endl;
	cout << endl;
	cout << R"foo(
	[1] Location
	[2] Image
	[3] Exit
)foo" << endl;
	cin >> answer;
	answer = atoi(&answer);
	switch (answer) {
	case 1:setloc();
		break;
	case 2:setimg();
		break;
	case 3:mainmenu();
		break;
	}
}

void setloc() {
	char newloc[10];
	cout << "Enter new location name(not more than 10 characters):";
	cin >> newloc;
	FILE *datei;
	if ((fopen_s(&datei, "locations.txt", "ab")) == NULL) {
	fprintf(stderr, "Fehler bei der Dateioeffnung von location.txt");
	cout << "Fehler bei der Dateioeffnung von location.txt" << endl;
	}
	fprintf(datei,newloc);
	fclose(datei);
	char antwort;
	do {
		cout << "Noch einmal?(j/n)" << endl;
		cin >> antwort;
		antwort = char(toupper(antwort));
		if (antwort == 'J') {
			setloc();
		}
		if (antwort == 'N') {
			debug();
		}

	} while ((antwort != 'J') && (antwort != 'N'));
}

void setimg() {

}

void getimg() {

}