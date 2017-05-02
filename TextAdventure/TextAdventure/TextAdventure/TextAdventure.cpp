// TextAdventure.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.

//Bibliothken:
#include "stdafx.h"
#include <iostream>
#include "windows.h"
#include "string.h"
#include <sstream>
#include "mmsystem.h"
#include "SDL.h"
#include "SDL_mixer.h"
#pragma comment(lib, "winmm.lib")

using namespace std;

//Funktionen:
void testscreen();
void intro();
void mainmenu();
void startgame();
void loadgame();
void drawscreen(int, int, int, char[]);
void getloc(int);
void getimg(int);
void gettxt(int);
void room(int);
void init();

//Spielstand-Struktur
struct savegame {
	int room;
	int delay;
};

//Globale Variabeln:
//Textgeschwindigkeit
int delay = 50;
//Festlegen der Arraygrößen
const int imgsize = 2500;
const int locsize = 10;
const int txtsize = 1000;
char image[imgsize];
char location[locsize];
char text[txtsize];

//Musik-Pfade:
static const char *titletheme = "..\\Music\\Visager\\TitleTheme.mp3";
static const char *keyclick = "..\\Music\\click.wav";
Mix_Music *music = NULL;
Mix_Chunk *click = NULL;


int main(int argc, char *argv[])
{
	//Testen der Größe des Consolen-Fenster
	testscreen();
	//Laden der Musik-Einstellungen
	init();
	//Abspielen des Intro
	intro();
	//Aufruf des Haupmenü
	mainmenu();
	return 0;
}

void init() {
	int result = 0;
	int flags = MIX_INIT_MP3;

	//Aktivieren von SDL
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		printf("Failed to init SDL\n");
		exit(1);
	}

	//Aktivieren von SDL_Mixer
	if (flags != (result = Mix_Init(flags))) {
		printf("Could not initialize mixer (result: %d).\n", result);
		printf("Mix_Init: %s\n", Mix_GetError());
		exit(1);
	}

	//Audio-Port öffnen
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	//Audiolautstärke
	Mix_VolumeMusic(30);
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
	//Starten der Hintergrundmusik
	Mix_Music *music = Mix_LoadMUS(titletheme);
	Mix_PlayMusic(music, -1);
	//Ausgabe der Intro-Animation
	for (int i = 0; i < 4; i++) {
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
	//Ersten Raum laden
	drawscreen(1, 1, 1, "");
	string answer;
	//Raumnummer
	int n = 1;
	while (true) {
		//Einlesen der Antwort
		getline(cin, answer);
		//SoundFX spielen
		Mix_Chunk *click = Mix_LoadWAV(keyclick);
		Mix_PlayChannel(-1, click, 0);

		if (answer == "geh" || answer == "gehe" || answer == "go" || answer == "lauf") {
			drawscreen(n, n, n, "Wohin willst du gehen?");
			memset(&answer[0], 0, 10);
			cin >> answer;
			if (answer == "geradeaus" || answer == "Norden" || answer == "Nord" || answer == "gerade" || answer == "Tür" || answer == "Door" || answer == "front") {
				n++;
				drawscreen(n, n, n, "");	
			}
			if (answer == "links") {
				
			}
		}
		else {
			if (answer.length() != 0) {
				cout << "Begriff: " << answer << " nicht verstanden" << endl;
			}
		}
	}

}

void loadgame() {

}

void drawscreen(int locint, int imgint, int txtint, char info[]) {
	system("CLS");
	//Modulares System um gleiche Assets mehrmals zu benutzen
	getloc(locint);
	getimg(imgint);
	gettxt(txtint);
	//Ausgabe aller Infos
	cout << image <<
		R"foo(
+---------------------------------------------------------------------------------------------------+
                                 )foo" << location << R"foo(                                                                            
+---------------------------------------------------------------------------------------------------+
)foo"; for (int i = 0; text[i] != NULL; i++) { cout << text[i]; Sleep(delay); }
	for (int i = 0; info[i] != NULL; i++) { cout << info[i]; Sleep(delay); } cout << R"foo(



+---------------------------------------------------------------------------------------------------+)foo" << endl;

}

void getloc(int locint) {
	FILE *datei;
	//Öffnen von locations.txt
	if ((datei = fopen("locations.txt", "r")) == NULL) {
		fprintf(stderr, "Fehler bei der Dateioeffnung von location.txt");
		cout << "Fehler bei der Dateioeffnung von location.txt" << endl;
	}
	//Einlesen in das vorgesehende Array 
	for (int i = 0; i < locint; i++) {
		memset(&location[0], 0, locsize);
		fgets(location, locsize, datei);
		for (int i = 0; i < 10; i++) {
			if (location[i] == '\n') {
				location[i] = '\0';
			}
		}
	}
	fclose(datei);
}

void getimg(int imgint) {
	FILE *datei;
	//Öffnen von images.txt
	if ((datei = fopen("images.txt", "r")) == NULL) {
		fprintf(stderr, "Fehler bei der Dateioeffnung von images.txt");
		cout << "Fehler bei der Dateioeffnung von images.txt" << endl;
	}
	//Temporäres Image-Array
	char newimg[imgsize];
	//Einlesen in das vorgesehende Array
	for (int i = 0; i < imgint; i++) {
		memset(&image[0], 0, sizeof(image));
		while (fgets(newimg, imgsize, datei) != NULL) {
			if (newimg[0] == 'e'&&newimg[1] == 'n'&&newimg[2] == 'd') {
				break;
			}
			//Zusammenführen mit primären Image-Array
			strncat(image, newimg, imgsize - strlen(image) - 1);
		}
	}
	fclose(datei);
}

void gettxt(int txtint) {
	FILE *datei;
	//Öffnen von text.txt
	if ((datei = fopen("text.txt", "r")) == NULL) {
		fprintf(stderr, "Fehler bei der Dateioeffnung von text.txt");
		cout << "Fehler bei der Dateioeffnung von text.txt" << endl;
	}
	//Temporäres Text-Array
	char newtxt[txtsize];
	//Einlesen in das vorgesehende Array
	for (int i = 0; i < txtint; i++) {
		memset(&text[0], 0, sizeof(text));
		while (fgets(newtxt, txtsize, datei) != NULL) {
			if (newtxt[0] == 'e'&&newtxt[1] == 'n'&&newtxt[2] == 'd') {
				break;
			}
			//Zusammenführen mit primären Text-Array
			strncat(text, newtxt, txtsize - strlen(text) - 1);
		}
	}
	fclose(datei);
}

void room(int n) {
	//Schnelles Aufrufen der drawscreen-Funktion
	drawscreen(n, n, n, "");
}