// TextAdventure.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
#include "windows.h"
#include "mmsystem.h"
#pragma comment(lib, "winmm.lib")
using namespace std;
#define _CRT_SECURE_NO_WARNINGS


void testscreen();
void intro();
void mainmenu();
void startgame();
void loadgame();
void debug();
void drawscreen(int,int);
void getloc(char[],int);
void getimg(char[],int);
void setloc();
void setimg();

char location[10];
const int imgsize = 500;
char image[imgsize];

int main()
{
	testscreen();
	intro();
	mainmenu();
    return 0;
}

void testscreen() {
	cout <<
		R"foo(
+-------------------------------------------------------------------------------------------------+
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                       Resize to show complete box                                               |
|                        for game to work correctly                                               |
|                                                                                                 |
|                         Dont resize after this!                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
+-------------------------------------------------------------------------------------------------+
)foo";
	system("PAUSE");
	system("CLS");
}

void intro() {
	PlaySound(TEXT("C:\\Users\\LUCA\\Source\\Repos\\dvproject\\TextAdventure\\Music\\Ataraxia.wav"), NULL, SND_FILENAME | SND_ASYNC);
	cout<<
		R"foo(
			 | |  | |     | |                              | |  | |               
			 | |  | |_ __ | | ___ __   _____      ___ __   | |__| | ___ _ __ ___  
			 | |  | | '_ \| |/ / '_ \ / _ \ \ /\ / / '_ \  |  __  |/ _ \ '__/ _ \ 
			 | |__| | | | |   <| | | | (_) \ V  V /| | | | | |  | |  __/ | | (_) |
			  \____/|_| |_|_|\_\_| |_|\___/ \_/\_/ |_| |_| |_|  |_|\___|_|  \___/ 
)foo";
	Sleep(5000);
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

void startgame() {
	drawscreen(1,1);
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

void drawscreen(int locint,int imgint) {
	getloc(location,locint);
	getimg(image,imgint);
	system("CLS");
	cout<<image
		<<
		R"foo(
+-------------------------------------------------------------------------------------------------+
|                                 )foo"<<location<<R"foo(                                                         |
+-------------------------------------------------------------------------------------------------+
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
|                                                                                                 |
+-------------------------------------------------------------------------------------------------+)foo";
	char answer;
	cin >> answer;
}

void getloc(char newloc[],int locint) {
	FILE *datei;
	if ((datei = fopen("locations.txt","r")) == NULL) {
		fprintf(stderr, "Fehler bei der Dateioeffnung von location.txt");
		cout << "Fehler bei der Dateioeffnung von location.txt" << endl;
	}
	fgets(newloc,10,datei);
	fclose(datei);
}

void getimg(char image[], int imgint) {
	FILE *datei;
	if ((datei = fopen("images.txt", "r")) == NULL) {
		fprintf(stderr, "Fehler bei der Dateioeffnung von images.txt");
		cout << "Fehler bei der Dateioeffnung von images.txt" << endl;
	}
	int i = 0;
	fseek(datei, imgsize*imgint, SEEK_SET);
	while (fgets(image, imgsize, datei) != "\n") {
		image[i] = fgetc(datei);
		i++;
	}
	fclose(datei);
}

void setloc() {
	char newloc[10];
	cout << "Enter new location name(not more than 10 characters):";
	cin >> newloc;
	FILE *datei;
	if ((datei = fopen("locations.txt", "a")) == NULL) {
	fprintf(stderr, "Fehler bei der Dateioeffnung von location.txt");
	cout << "Fehler bei der Dateioeffnung von location.txt" << endl;
	}
	fprintf(datei,newloc);
	fprintf(datei,"\n");
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

