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
void drawscreen(int,int,int);
void getloc(int);
void getimg(int);
void gettxt(int);
void room(int);

int delay = 100;
const int imgsize = 2500;
const int locsize = 10;
const int txtsize = 1000;
char image[imgsize];
char location[locsize];
char text[txtsize];

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
+---------------------------------------------------------------------------------------------------------------+
|                                                                                                               |
|                                     Resize to show complete box                                               |
|                                      for game to work correctly                                               |
|                                                                                                               |
|                                       Dont resize after this!                                                 |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
+---------------------------------------------------------------------------------------------------------------+
)foo";
	system("PAUSE");
	system("CLS");
}

void intro() {
	PlaySound(TEXT("..\\Music\\Visager\\TitleTheme.wav"), NULL, SND_FILENAME | SND_ASYNC);
	for (int i = 0;i < 4;i++) {
		cout <<
			R"foo(
| |  | |     | |                              | |  | |               
| |  | |_ __ | | ___ __   _____      ___ __   | |__| | ___ _ __ ___  
| |  | | '_ \| |/ / '_ \ / _ \ \ /\ / / '_ \  |  __  |/ _ \ '__/ _ \ 
| |__| | | | |   <| | | | (_) \ V  V /| | | | | |  | |  __/ | | (_) |
 \____/|_| |_|_|\_\_| |_|\___/ \_/\_/ |_| |_| |_|  |_|\___|_|  \___/ 
			)foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo(
 | |  | |     | |                              | |  | |               
| |  | |_ __ | | ___ __   _____      ___ __   | |__| | ___ _ __ ___  
| |  | | '_ \| |/ / '_ \ / _ \ \ /\ / / '_ \  |  __  |/ _ \ '__/ _ \ 
| |__| | | | |   <| | | | (_) \ V  V /| | | | | |  | |  __/ | | (_) |
 \____/|_| |_|_|\_\_| |_|\___/ \_/\_/ |_| |_| |_|  |_|\___|_|  \___/ 
			)foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo(
| |  | |     | |                              | |  | |               
 | |  | |_ __ | | ___ __   _____      ___ __   | |__| | ___ _ __ ___  
| |  | | '_ \| |/ / '_ \ / _ \ \ /\ / / '_ \  |  __  |/ _ \ '__/ _ \ 
| |__| | | | |   <| | | | (_) \ V  V /| | | | | |  | |  __/ | | (_) |
 \____/|_| |_|_|\_\_| |_|\___/ \_/\_/ |_| |_| |_|  |_|\___|_|  \___/ 
			)foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo(
| |  | |     | |                              | |  | |               
| |  | |_ __ | | ___ __   _____      ___ __   | |__| | ___ _ __ ___  
 | |  | | '_ \| |/ / '_ \ / _ \ \ /\ / / '_ \  |  __  |/ _ \ '__/ _ \ 
| |__| | | | |   <| | | | (_) \ V  V /| | | | | |  | |  __/ | | (_) |
 \____/|_| |_|_|\_\_| |_|\___/ \_/\_/ |_| |_| |_|  |_|\___|_|  \___/ 
			)foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo(
| |  | |     | |                              | |  | |               
| |  | |_ __ | | ___ __   _____      ___ __   | |__| | ___ _ __ ___  
| |  | | '_ \| |/ / '_ \ / _ \ \ /\ / / '_ \  |  __  |/ _ \ '__/ _ \ 
 | |__| | | | |   <| | | | (_) \ V  V /| | | | | |  | |  __/ | | (_) |
 \____/|_| |_|_|\_\_| |_|\___/ \_/\_/ |_| |_| |_|  |_|\___|_|  \___/ 
			)foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo(
| |  | |     | |                              | |  | |               
| |  | |_ __ | | ___ __   _____      ___ __   | |__| | ___ _ __ ___  
| |  | | '_ \| |/ / '_ \ / _ \ \ /\ / / '_ \  |  __  |/ _ \ '__/ _ \ 
| |__| | | | |   <| | | | (_) \ V  V /| | | | | |  | |  __/ | | (_) |
  \____/|_| |_|_|\_\_| |_|\___/ \_/\_/ |_| |_| |_|  |_|\___|_|  \___/ 
			)foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo(
| |  | |     | |                              | |  | |               
| |  | |_ __ | | ___ __   _____      ___ __   | |__| | ___ _ __ ___  
| |  | | '_ \| |/ / '_ \ / _ \ \ /\ / / '_ \  |  __  |/ _ \ '__/ _ \ 
| |__| | | | |   <| | | | (_) \ V  V /| | | | | |  | |  __/ | | (_) |
 \____/|_| |_|_|\_\_| |_|\___/ \_/\_/ |_| |_| |_|  |_|\___|_|  \___/ 
			)foo";
		Sleep(100);
		system("CLS");
	}
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
	room(1);
	char answer;
	int n=1;
	while (true) {
		cin >> answer;
		if (answer == '1') {
			n++;
		}
		if (answer == '2') {
			n--;
		}
		room(n);
	}
}

void loadgame() {

}

void drawscreen(int locint,int imgint,int txtint) {
	system("CLS");
	getloc(locint);
	getimg(imgint);
	gettxt(txtint);
	cout << image <<
		R"foo(
+---------------------------------------------------------------------------------------------------+
                                 )foo" << location << R"foo(                                                                            
+---------------------------------------------------------------------------------------------------+
)foo"; for (int i = 0;text[i]!=NULL;i++) { cout << text[i];Sleep(delay); } cout << R"foo(



+---------------------------------------------------------------------------------------------------+)foo"<<endl;
	
}

void getloc( int locint) {
	FILE *datei;
	if ((datei = fopen("locations.txt", "r")) == NULL) {
		fprintf(stderr, "Fehler bei der Dateioeffnung von location.txt");
		cout << "Fehler bei der Dateioeffnung von location.txt" << endl;
	}
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
	char newimg[imgsize];
	for (int i = 0;i < imgint;i++) {
		memset(&image[0], 0, sizeof(image));
		while (fgets(newimg, imgsize, datei) != NULL) {
			if (newimg[0] == 'e'&&newimg[1] == 'n'&&newimg[2] == 'd') {
				break;
			}
			strncat(image, newimg, imgsize - strlen(image) - 1); 
		}
	}
	fclose(datei);
}

void gettxt(int txtint) {
	FILE *datei;
	if ((datei = fopen("text.txt", "r")) == NULL) {
		fprintf(stderr, "Fehler bei der Dateioeffnung von text.txt");
		cout << "Fehler bei der Dateioeffnung von text.txt" << endl;
	}
	char newtxt[txtsize];
	for (int i = 0;i < txtint;i++) {
		memset(&text[0], 0, sizeof(text));
		while (fgets(newtxt, txtsize, datei) != NULL) {
			if (newtxt[0] == 'e'&&newtxt[1] == 'n'&&newtxt[2] == 'd') {
				break;
			}
			strncat(text, newtxt, txtsize - strlen(text) - 1);
		}
	}
	fclose(datei);
}

void room(int n) {
	drawscreen(n,n,n);
}

