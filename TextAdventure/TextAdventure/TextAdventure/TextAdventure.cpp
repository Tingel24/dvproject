// TextAdventure.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
#include "windows.h"
#include "mmsystem.h"
#pragma comment(lib, "winmm.lib")
using namespace std;



void testscreen();
void intro();
void mainmenu();
void startgame();
void loadgame();
void drawscreen(int,int);
void getloc(int);
void getimg(int);
//void setloc();
//void setimg();

const int imgsize = 1500;
const int locsize = 10;
char image[imgsize];
char location[locsize];

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
	PlaySound(TEXT("..\\Music\\Visager\\TitleTheme.wav"), NULL, SND_FILENAME | SND_ASYNC);
	cout<<
		R"foo(
			 | |  | |     | |                              | |  | |               
			 | |  | |_ __ | | ___ __   _____      ___ __   | |__| | ___ _ __ ___  
			 | |  | | '_ \| |/ / '_ \ / _ \ \ /\ / / '_ \  |  __  |/ _ \ '__/ _ \ 
			 | |__| | | | |   <| | | | (_) \ V  V /| | | | | |  | |  __/ | | (_) |
			  \____/|_| |_|_|\_\_| |_|\___/ \_/\_/ |_| |_| |_|  |_|\___|_|  \___/ 
)foo";
	Sleep(1000);
system("CLS");                                                                                  																							
}

void mainmenu() {
	system("CLS");
	cout << R"foo(
	[1] Start New Game
	[2] Load Game
)foo" << endl;
	char answer;
	cin >> answer;
	answer = atoi(&answer);
	switch (answer) {
		case 1:startgame();
		break;
		case 2:loadgame();
		break;
	}
}

void startgame() {
	drawscreen(2,1);
};

void loadgame() {

}

void drawscreen(int locint,int imgint) {
	system("CLS");
	getloc(locint);
	getimg(imgint);
	cout<<image<<
		R"foo(
+---------------------------------------------------------------------------------------------------+
                                 )foo"<<location<<R"foo(                                                                            
+---------------------------------------------------------------------------------------------------+




+---------------------------------------------------------------------------------------------------+)foo";
	char answer;
	cin >> answer;
}

void getloc( int locint) {
	FILE *datei;
	if ((datei = fopen("locations.txt", "r")) == NULL) {
		fprintf(stderr, "Fehler bei der Dateioeffnung von location.txt");
		cout << "Fehler bei der Dateioeffnung von location.txt" << endl;
	}
	//locint--;
	//fseek(datei, locsize*locint, SEEK_SET);
	for (int i = 0;i < locint;i++) {
		memset(&location[0], 0, locsize);
		fgets(location, locsize, datei);
		for (int i = 0;i < 10;i++) {
			if (location[i] == '\n') {
				location[i] = '\0';
			}
		}
	}
	fclose(datei);
}

void getimg(int imgint) {
	FILE *datei;
	if ((datei = fopen("images.txt", "r")) == NULL) {
		fprintf(stderr, "Fehler bei der Dateioeffnung von images.txt");
		cout << "Fehler bei der Dateioeffnung von images.txt" << endl;
	}
	/*imgint--;
	fseek(datei, imgsize*imgint, SEEK_SET);*/
	char newimg[imgsize];
	for (int i = 0;i < imgint;i++) {
		memset(&image[0], 0, sizeof(image));
		while (fgets(newimg, imgsize, datei) != NULL) {
			if (newimg[0] == 'e'&&newimg[1] == 'n'&&newimg[2] == 'd') {
				break;
			}
			strncat(image, newimg, imgsize - strlen(image) - 1); //-1 for null-termination
		}
	}
	fclose(datei);
}

//void setloc() {
//	char newloc[10];
//	cout << "Enter new location name(not more than 10 characters):";
//	cin >> newloc;
//	FILE *datei;
//	if ((datei = fopen("locations.txt", "a")) == NULL) {
//	fprintf(stderr, "Fehler bei der Dateioeffnung von location.txt");
//	cout << "Fehler bei der Dateioeffnung von location.txt" << endl;
//	}
//	fprintf(datei,newloc);
//	fprintf(datei,"\n");
//	fclose(datei);
//	char antwort;
//	do {
//		cout << "Noch einmal?(j/n)" << endl;
//		cin >> antwort;
//		antwort = char(toupper(antwort));
//		if (antwort == 'J') {
//			setloc();
//		}
//		if (antwort == 'N') {
//			debug();
//		}
//
//	} while ((antwort != 'J') && (antwort != 'N'));
//}
//
//void setimg() {
//
//}

