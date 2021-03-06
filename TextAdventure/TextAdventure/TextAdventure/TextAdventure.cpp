// TextAdventure.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.

//Bibliothken:
#include "stdafx.h"
#include <iostream>
#include "windows.h"
#include "time.h"
#include "string.h"
#include <sstream>
#include "mmsystem.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include <algorithm>
#pragma comment(lib, "winmm.lib")

using namespace std;

//Funktionen:
void testscreen();
void intro();
void mainmenu();
void startgame();
void loadgame(bool);
void save();
void drawscreen(int, int, int, string, bool);
void getloc(int);
void getimg(int);
void gettxt(int);
void room(int);
void init();
void combat();
void gameover();
void combatintro();
void listitems();
void wingame();
void help();
void settings();
void dev();

//Spielstand-Struktur
struct savegame {
	int room;
	int delay;
	int health;
	int potions;
};
savegame saves[3];

//Globale Variabeln:
//Textgeschwindigkeit
int delay = 30;
//Lebensvariabel
int health = 100;
//Lebensvariabel der Gegner
int gegnerleben = 100;
//Heilngsitems
int potions = 1;
//Raumnummer
int raumnr = 1;

//Festlegen der Arraygrößen
const int imgsize = 2500;
const int locsize = 10;
const int txtsize = 1000;
char image[imgsize];
char location[locsize];
char text[txtsize];

//Musik-Pfade:
static const char *winmus = "..\\Music\\Visager2\\Visager_-_02_-_Royal_Entrance_Loop.mp3";
static const char *gameovermus = "..\\Music\\Visager2\\Visager_-_23_-_Haunted_Forest_Loop.mp3";
static const char *mausoleum = "..\\Music\\Visager2\\Visager_-_11_-_Eerie_Mausoleum_Loop.mp3";
static const char *icecave = "..\\Music\\Visager\\Visager_-_07_-_Ice_Cave_Loop.mp3";
static const char *throne = "..\\Music\\Visager2\\Visager_-_03_-_Throne_Room_Loop.mp3";
static const char *combatintromusic = "..\\Music\\Visager2\\Visager_-_21_-_Battle_Intro.mp3";
static const char *combatmusic = "..\\Music\\Visager2\\Visager_-_22_-_Battle_Loop.mp3";
static const char *titletheme = "..\\Music\\Visager\\TitleTheme.mp3";
static const char *keyclick = "..\\Music\\click.wav";
static const char *door = "..\\Music\\door.wav";
static const char *punch = "..\\Music\\punch.wav";
Mix_Music *music = NULL;
Mix_Chunk *click = NULL;

//TextFarben:
char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };
char black[] = { 0x1b, '[', '0', ';', '3', '0', 'm', 0 };
char red[] = { 0x1b, '[', '0', ';', '3', '1', 'm', 0 };
char green[] = { 0x1b, '[', '0', ';', '3', '2', 'm', 0 };
char yellow[] = { 0x1b, '[', '0', ';', '3', '3', 'm', 0 };
char blue[] = { 0x1b, '[', '0', ';', '3', '4', 'm', 0 };
char purple[] = { 0x1b, '[', '0', ';', '3', '5', 'm', 0 };
char cyan[] = { 0x1b, '[', '0', ';', '3', '6', 'm', 0 };
char Lgray[] = { 0x1b, '[', '0', ';', '3', '7', 'm', 0 };
char Dgray[] = { 0x1b, '[', '0', ';', '3', '8', 'm', 0 };
char Bred[] = { 0x1b, '[', '1', ';', '3', '1', 'm', 0 };

//Um einige Charaktere richtig anzuzeigen:
const unsigned char AE = static_cast<unsigned char>(142);
const unsigned char ae = static_cast<unsigned char>(132);
const unsigned char OE = static_cast<unsigned char>(153);
const unsigned char oe = static_cast<unsigned char>(148);
const unsigned char UE = static_cast<unsigned char>(154);
const unsigned char ue = static_cast<unsigned char>(129);
const unsigned char ss = static_cast<unsigned char>(225);

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

void testscreen() {
	//Festlegen der minimalen Consolen-Fenstergröße
	cout <<
		R"foo(
+---------------------------------------------------------------------------------------------------------------+
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                                                                                               |
|                                           /|\    /|\    /|\                                                   |
|                                            |      |      |                                                    |
|                                                                                                               |
|                                     Passe das Konsolenfenster so an,                                          |
|                                  das der komplette Kasten zu sehen ist!                                       |
|                                      Nur dann funktioniert alles                                              |
|                               Veraendere das Fenster hiernach nichtmehr!                                      |
|                                                                                                               |
|                                            |      |      |                                                    |
|                                           \|/    \|/    \|/                                                   |
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

                            ,-.
       ___,---.__          /'|`\          __,---,___
    ,-'    \`    `-.____,-'  |  `-.____,-'    //    `-.
  ,'        |           ~'\     /`~           |        `.
 /      ___//              `. ,'          ,  , \___      \
|    ,-'   `-.__   _         |        ,    __,-'   `-.    |
|   /          /\_  `   .    |    ,      _/\          \   |
\  |           \ \`-.___ \   |   / ___,-'/ /           |  /
 \  \           | `._   `\\  |  //'   _,' |           /  /
  `-.\         /'  _ `---'' , . ``---' _  `\         /,-'
     ``       /     \    ,='/ \`=.    /     \       ''
             |__   /|\_,--.,-.--,--._/|\   __|
             /  `./  \\`\ |  |  | /,//' \,'  \
            /   /     ||--+--|--+-/-|     \   \
           |   |     /'\_\_\ | /_/_/`\     |   |
            \   \__, \_     `~'     _/ .__/   /
             `-._,-'   `-._______,-'   `-._,-'
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

                            ,-.
       ___,---.__          /'|`\          __,---,___
    ,-'    \`    `-.____,-'  |  `-.____,-'    //    `-.
  ,'        |           ~'\     /`~           |        `.
 /      ___//              `. ,'          ,  , \___      \
|    ,-'   `-.__   _         |        ,    __,-'   `-.    |
|   /          /\_  `   .    |    ,      _/\          \   |
\  |           \ \`-.___ \   |   / ___,-'/ /          |  /
 \  \           | `._   `\\  |  //'   _,' |          /  /
  `-.\         /'  _ `---'' , . ``---' _  `\        /,-'
     ``       /     \    ,='/ \`=.    /     \      ''
             |__   /|\_,--.,-.--,--._/|\   __|
             /  `./  \\`\ |  |  | /,//' \,'  \
            /   /     ||--+--|--+-/-|     \   \
           |   |      /             \      |   |
            \   \__, /'\_\_\ | /_/_/`\ .__/   /
             `-._,-' \_     `~'     _/ `-._,-'
                       `-._______,-'
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

                            ,-.
       ___,---.__          /'|`\          __,---,___
    ,-'    \`    `-.____,-'  |  `-.____,-'    //    `-.
  ,'        |           ~'\     /`~           |        `.
 /      ___//              `. ,'          ,  , \___      \
|    ,-'   `-.__   _         |        ,    __,-'   `-.    |
|   /          /\_  `.___.   |    ,___,  _/\          \   |
\  |           \ \`     \   |   /     -'/ /           |  /
\  \            | `._   `\\  |  //'   _,' |           /  /
 `-.\          /'  _ `---'' , . ``---' _  `\         /,-'
    ``        /     \    ,='/ \`=.    /     \       ''
             |__   /|\_,--.,-.--,--._/|\   __|
             /  `./  \\`\ |  |  | /,//' \,'  \
            /   /     ||--+--|--+-/-|     \   \
           |   |      /             \      |   |
            \   \__, /'\_\_\ | /_/_/`\ .__/   /
             `-._,-' \_     `~'     _/ `-._,-'
                       `-._______,-'
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

                            ,-.
       ___,---.__          /'|`\          __,---,___
    ,-'    \`    `-.____,-'  |  `-.____,-'    //    `-.
  ,'        |           ~'\     /`~           |        `.
 /      ___//              `. ,'          ,  , \___      \
|    ,-'   `-.__   _         |        ,    __,-'   `-.    |
|   /          /\_  `   .    |    ,      _/\          \   |
\  |           \ \`-.___ \   |   / ___,-'/ /           |  /
 \  \           | `._   `\\  |  //'   _,' |           /  /
  `-.\         /'  _ `---'' , . ``---' _  `\         /,-'
     ``       /     \    ,='/ \`=.    /     \       ''
             |__   /|\_,--.,-.--,--._/|\   __|
             /  `./  \\`\ |  |  | /,//' \,'  \
            /   /     ||--+--|--+-/-|     \   \
           |   |     /'\_\_\ | /_/_/`\     |   |
            \   \__, \_     `~'     _/  .__/   /
             `-._,-'   `-._______,-'    `-._,-'
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

                            ,-.
       ___,---.__          /'|`\          __,---,___
    ,-'    \`    `-.____,-'  |  `-.____,-'    //    `-.
  ,'        |           ~'\     /`~           |        `.
 /      ___//              `. ,'          ,  , \___      \
|    ,-'   `-.__   _         |        ,    __,-'   `-.    |
|   /          /\_  `   .    |    ,      _/\          \   |
\  |           \ \`-.___ \   |   / ___,-'/ /           |  /
 \  \           | `._   `\\  |  //'   _,' |           /  /
  `-.\         /'  _ `---'' , . ``---' _  `\         /,-'
     ``       /     \    ,='/ \`=.    /     \       ''
             |__   /|\_,--.,-.--,--._/|\   __|
             /  `./  \\`\ |  |  | /,//' \,'  \
            /   /     ||--+--|--+-/-|     \   \
           |   |     /'\_\_\ | /_/_/`\     |   |
            \   \__, \_     `~'     _/ .__/   /
             `-._,-'   `-._______,-'   `-._,-'
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

                            ,-.
       ___,---.__          /'|`\          __,---,___
    ,-'    \`    `-.____,-'  |  `-.____,-'    //    `-.
  ,'        |           ~'\     /`~           |        `.
 /      ___//              `. ,'          ,  , \___      \
|    ,-'   `-.__   _         |        ,    __,-'   `-.    |
|   /          /\_  `   .    |    ,      _/\          \   |
\  |           \ \`-.___ \   |   / ___,-'/ /           |  /
 \  \           | `._   `\\  |  //'   _,' |           /  /
  `-.\         /'  _ `---'' , . ``---' _  `\         /,-'
     ``       /     \    ,='/ \`=.    /     \       ''
             |__   /|\_,--.,-.--,--._/|\   __|
             /  `./  \\`\ |  |  | /,//' \,'  \
            /   /     ||--+--|--+-/-|     \   \
           |   |     /'\_\_\ | /_/_/`\     |   |
            \   \__, \_     `~'     _/ .__/   /
             `-._,-'   `-._______,-'   `-._,-'
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

                            ,-.
       ___,---.__          /'|`\          __,---,___
    ,-'    \`    `-.____,-'  |  `-.____,-'    //    `-.
  ,'        |           ~'\     /`~           |        `.
 /      ___//              `. ,'          ,  , \___      \
|    ,-'   `-.__   _         |        ,    __,-'   `-.    |
|   /          /\_  `   .    |    ,      _/\          \   |
\  |           \ \`-.___ \   |   / ___,-'/ /           |  /
 \  \           | `._   `\\  |  //'   _,' |           /  /
  `-.\         /'  _ `---'' , . ``---' _  `\         /,-'
     ``       /     \    ,='/ \`=.    /     \       ''
             |__   /|\_,--.,-.--,--._/|\   __|
             /  `./  \\`\ |  |  | /,//' \,'  \
            /   /     ||--+--|--+-/-|     \   \
           |   |     /'\_\_\ | /_/_/`\     |   |
            \   \__, \_     `~'     _/ .__/   /
             `-._,-'   `-._______,-'   `-._,-'
			)foo";
		Sleep(100);
		system("CLS");
	}
}
void mainmenu() {
	while (true) {
		system("CLS");
		cout << R"foo(
   *--------------------*
   | [1] Neues Spiel    |
   | [2] Spiel laden    |
   | [3] Einstellungen  |
   | [4] Exit           |
   *--------------------*
)foo" << endl;
		//Einlesen der Antwort
		char answer;
		cin >> answer;
		//SoundFX spielen
		Mix_Chunk *click = Mix_LoadWAV(keyclick);
		Mix_PlayChannel(-1, click, 0);
		answer = atoi(&answer);
		switch (answer) {
		case 1:
			//Spiel starten
			startgame();
			break;
			//Spiel laden
		case 2:loadgame(true);
			break;
			// Einstellungen
		case 3:settings();
			break;
			//Exit
		case 4:gameover();
			// Versteckte Optionen
		case 5:dev();
			break;
		}
	}
}

void startgame() {
	//Starten der Hintergrundmusik
	srand(time(NULL));
	//Zufällige Musikauswahl
	int musicchoice = rand() % 100;
	if (musicchoice <= 33) {
		Mix_Music *music = Mix_LoadMUS(mausoleum);
		Mix_PlayMusic(music, -1);
	}
	if (musicchoice >= 66) {
		Mix_Music *music = Mix_LoadMUS(icecave);
		Mix_PlayMusic(music, -1);
	}
	if (musicchoice > 33 && musicchoice < 66) {
		Mix_Music *music = Mix_LoadMUS(throne);
		Mix_PlayMusic(music, -1);
	}
	//Ersten Raum anzeigen
	room(raumnr);
	//Variablen definieren
	string answer;
	int raumnrcheck = 0;
	bool check = false;
	//Schleife für Eingabe
	while (true) {
		//Bedingung für Spielende
		if (raumnr == 19) {
			wingame();
		}
		//Bedingungen für besondere Events
		if (raumnr == 3) {
			potions++;
		}
		if (raumnr == 4) {
			potions = potions + 3;
		}
		//Zufälliger Kampf
		srand(time(NULL));
		//15% Chance,keine zwei Kämpfe im selben Raum, kein Kampf im ersten Raum
		if (rand() % 100 < 15 && raumnrcheck != raumnr&&raumnr != 1) {
			Sleep(1000);
			system("cls");
			raumnrcheck = raumnr;
			cout << "Ein Bandit greift an!" << endl;
			Sleep(1000);
			combat();
		}
		//Einlesen der Antwort
		getline(cin, answer);
		transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
		//SoundFX spielen
		Mix_Chunk *click = Mix_LoadWAV(keyclick);
		Mix_PlayChannel(-1, click, 0);
		//Verschiedene Optionen für die Eingabe:
		//Bewegung
		if (answer == "geh" || answer == "gehe" || answer == "go" || answer == "lauf" || answer == "geradeaus" || answer == "norden" || answer == "nord" || answer == "gerade" || answer == "tür" || answer == "door" || answer == "front") {
			drawscreen(raumnr, raumnr, raumnr, "Willst du in den naechsten Raum gehen? (y/n)", 0);
			memset(&answer[0], 0, 10);
			cin >> answer;
			answer = tolower(answer[0]);
			if (answer == "y") {
				raumnr++;
				//SoundFX spielen
				Mix_Chunk *doorsfx = Mix_LoadWAV(door);
				Mix_PlayChannel(-1, doorsfx, 0);
				drawscreen(raumnr, raumnr, raumnr, " ", 1);
				check = false;
			}
		}
		//Speichern
		if (answer == "save" || answer == "speichern" || answer == "speicher") {
			save();
			check = false;
		}
		//Gegenstände im Raum auflisten
		if (answer == "look" || answer == "guck" || answer == "schau" || answer == "seh") {
			listitems();
			check = false;
		}
		//Zurück ins Hauptmenu
		if (answer == "exit" || answer == "mainmenu" || answer == "menu" || answer == "hauptmenu") {
			mainmenu();
			check = false;
		}
		//Heiltränke nutzen
		if (answer == "heilung" || answer == "trank" || answer == "heiltrank" || answer == "potion" || answer == "potions") {
			if (potions != 0) {
				cout << endl;
				cout << "Du hast noch " << potions << ". Heiltr" << ae << "nke" << endl;
				cout << "Willst du dich heilen? (y/n)" << endl;
				memset(&answer[0], 0, 10);
				cin >> answer;
				answer = tolower(answer[0]);
				if (answer == "y") {
					potions--;
					health = health + (rand() % 50) + 10;
					cout << "Du heilst dich" << endl;
					cout << "Leben: " << health << endl;
				}
				check = false;
			}
			else {
				cout << "Du hast keine Heiltr" << ae << "nke mehr!" << endl;
				check = false;
			}
		}
		//Liste der Kommandos anzeigen
		if (answer == "help" || answer == "hilfe" || answer == "commands" || answer == "info") {
			help();
			check = false;
		}
		//Einstellungen aufrufen
		if (answer == "settings" || answer == "einstellungen" || answer == "einstellung") {
			settings();
			drawscreen(raumnr, raumnr, raumnr, "", 0);
			check = false;
		}
		//Nicht verstandene Begriffe anzeigen
		if (check) {
			if (answer.length() != 0) {
				cout << "Begriff: " << answer << " nicht verstanden" << endl;
			}
		}

		check = true;
	}
}

void loadgame(bool c) {
	FILE* datei;
	//Datei öffnen
	if ((datei = fopen("save.bin", "rb")) == NULL)
	{
		fprintf(stderr, "Fehler bei der Dateioeffnung");
	}
	//3 Datensätze einlesen
	for (int i = 0; i < 4; i++) {
		fread(&saves[i], sizeof(struct savegame), 1, datei);
	}
	//Datei schließen
	fclose(datei);

	if (c) {
		//Spielstand-Info ausgeben
		cout <<
			R"foo(
Welchen Spielstand m)foo" << oe << R"foo(chtest du laden?
[1])foo" << green << saves[0].room << " Raum  " << Bred << saves[0].health << " Leben  " << yellow << saves[0].potions << " Heiltr" << ae << "nke  " << normal << R"foo(
[2])foo" << green << saves[1].room << " Raum  " << Bred << saves[1].health << " Leben  " << yellow << saves[1].potions << " Heiltr" << ae << "nke  " << normal << R"foo(
[3])foo" << green << saves[2].room << " Raum  " << Bred << saves[2].health << " Leben  " << yellow << saves[2].potions << " Heiltr" << ae << "nke  " << normal << R"foo(
[4] Exit
)foo" << endl;
		//Antwort einlesen
		char answer;
		int n;
		cin >> answer;
		if (answer == '1' || answer == '2' || answer == '3') {
			//SoundFX spielen
			Mix_Chunk *click = Mix_LoadWAV(keyclick);
			Mix_PlayChannel(-1, click, 0);
			answer = atoi(&answer);
			n = answer;
			//Eingelesen Daten auf Spieldaten einlesen
			if (saves[n].room != NULL) {
				delay = saves[n].delay;
				health = saves[n].health;
				raumnr = saves[n].room;
				potions = saves[n].potions;
				startgame();
			}
			else {
				cout << "Dieser Spielstand ist leer" << endl;
				char c;
				do {
					cout << "Einen anderen w" << ae << "hlen?(y/n)" << endl;
					cin >> c;
					//SoundFX spielen
					Mix_PlayChannel(-1, click, 0);
					c = tolower(c);
					if (c == 'y') {
						loadgame(true);
					}
					if (c == 'n') {
						mainmenu();
					}
				} while (c != 'y' || c != 'n');
			}
		}
		else {
			cout << "Bitte 1,2,3 oder 4 eingeben" << endl;
		}
	}
}

void save() {
	FILE* datei;
	//Neues Laden der Speicherstände
	loadgame(false);
	//Spielstand-Info ausgeben
	cout <<
		R"foo(
In welchem Slot willst du speichern?
[1])foo" << green << saves[0].room << " Raum  " << Bred << saves[0].health << " Leben  " << yellow << saves[0].potions << " Heiltr" << ae << "nke  " << normal << R"foo(
[2])foo" << green << saves[1].room << " Raum  " << Bred << saves[1].health << " Leben  " << yellow << saves[1].potions << " Heiltr" << ae << "nke  " << normal << R"foo(
[3])foo" << green << saves[2].room << " Raum  " << Bred << saves[2].health << " Leben  " << yellow << saves[2].potions << " Heiltr" << ae << "nke  " << normal << R"foo(
		)foo" << endl;
	char answer;
	cin >> answer;
	//SoundFX spielen
	Mix_Chunk *click = Mix_LoadWAV(keyclick);
	Mix_PlayChannel(-1, click, 0);
	int i = atoi(&answer);
	i--;
	//Koopieren der Spieldaten
	savegame newsave;
	newsave.room = raumnr;
	newsave.delay = delay;
	newsave.health = health;
	newsave.potions = potions;
	saves[i] = newsave;
	//Öffnen der Datei
	if ((datei = fopen("save.bin", "wb")) == NULL) {
		fprintf(stderr, "Fehler bei der Dateioeffnung");
		cout << "Fehler beim Speichern" << endl;
	}
	//Schreiben der Datensätze in die Datei
	fwrite(saves, sizeof(savegame), 3, datei);
	cout << "Erfolgreich gespeichtert" << endl;
	fclose(datei);
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
void drawscreen(int locint, int imgint, int txtint, string info, bool txtswitch) {
	system("CLS");
	//Modulares system um gleiche Assets mehrmals zu benutzen
	getloc(locint);
	getimg(imgint);
	gettxt(txtint);
	//Ausgabe aller Infos
	cout << image << R"foo(
+---------------------------------------------------------------------------------------------------+
                                 )foo" << location << R"foo(
+---------------------------------------------------------------------------------------------------+
)foo";// if (info.length() != NULL) {
	if (txtswitch) {
		for (int i = 0; text[i] != NULL; i++) {
			if (!(i % 98)) {
				if (i > 10) {
					for (i; text[i] != NULL; i++) {
						cout << text[i]; Sleep(delay);
						if (text[i] == ' ') {
							cout << endl;
							break;
						}
					}
				}
			}
			cout << text[i]; Sleep(delay);
		}
	}
	cout << info << R"foo(
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
	//Schließen der Datei
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
	//Schließen der Datei
	fclose(datei);
}

void room(int n) {
	//Schnelles Aufrufen der drawscreen-Funktion
	drawscreen(n, n, n, " ", 1);
}

void combatintro() {
	//Starten der Hintergrundmusik
	Mix_Music *music = Mix_LoadMUS(combatintromusic);
	Mix_PlayMusic(music, -1);
	//Ausgabe der Intro-Animation
	system("CLS");
	cout <<
		R"foo(
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

 )foo";
	Sleep(200);

	system("CLS");
	cout <<
		R"foo(
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 )foo";
	Sleep(200);

	system("CLS");
	cout <<
		R"foo(
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 )foo";
	Sleep(200);

	system("CLS");
	cout <<
		R"foo(
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 )foo";
	Sleep(200);
}

void combat() {
	combatintro();
	//Starten der Hintergrundmusik
	Mix_Music *music = Mix_LoadMUS(combatmusic);
	Mix_PlayMusic(music, -1);
	system("cls");
	int enemyhealth = gegnerleben;
	int enemypotion = 3;
	bool check = true;
	//Zufällige Auswahl des Banditenbild
	srand(time(NULL));
	int graphic = (rand() % 4);
	getimg(20 + graphic);
	//Ausgabe des Kampfbildschirm
	string answer;
	while (true) {
		check = false;
		system("cls");
		cout << image <<
			R"foo(
+---------------------------------------------------------------------------------------------------+
                                          Bandit: )foo";
		//Lebenswert und Farbe des Gegners
		if (enemyhealth >= 66) {
			cout << green;
		}
		if (enemyhealth >= 33 && enemyhealth < 66) {
			cout << yellow;
		}
		if (enemyhealth < 33) {
			cout << Bred;
		}
		cout << enemyhealth << "HP" << normal << R"foo(
+---------------------------------------------------------------------------------------------------+
 [1] Attacke
 [2] Heilen
 [3] Fliehen

)foo";
		//Lebenswert und Farbe
		if (health >= 66) {
			cout << green;
		}
		if (health >= 33 && health < 66) {
			cout << yellow;
		}
		if (health < 33) {
			cout << Bred;
		}
		cout << health << "HP" << normal << "     Potions:" << potions << R"foo(
+---------------------------------------------------------------------------------------------------+)foo" << endl;

		//Kampf-Abruchbedingung
		if (health <= 0) {
			gameover();
		}
		//Kampf-Siegbedingung
		if (enemyhealth <= 0) {
			system("cls");
			cout << "Der Bandit wurde besiegt!" << endl;
			//Zufällige Belohnung
			if (rand() % 100 < 80) {
				potions++;
				cout << "Du sammelst 1 Heilungstrank ein" << endl;
			}
			else {
				potions = potions + 3;
				cout << "Du sammelst 3 Heilungstrank ein" << endl;
			}
			Sleep(2000);
			startgame();
		}

		//Einlesen der Antwort
		getline(cin, answer);
		//SoundFX spielen
		Mix_Chunk *click = Mix_LoadWAV(keyclick);
		Mix_PlayChannel(-1, click, 0);

		//Angriff
		if (answer == "1") {
			enemyhealth = enemyhealth - rand() % 33;
			check = true;
			cout << endl;
			cout << "Du greifst an" << endl;
			//SoundFX spielen
			Mix_Chunk *hit = Mix_LoadWAV(punch);
			Mix_PlayChannel(-1, hit, 0);
		}
		else {
			//Heilung
			if (answer == "2") {
				if (potions != 0) {
					potions--;
					health = health + (rand() % 50) + 10;
					cout << endl;
					cout << "Du heilst dich" << endl;
					check = true;
				}
				else {
					cout << "Du hast keine Heiltr" << ae << "nke mehr!" << endl;
				}
			}
			else {
				//Fliehen
				if (answer == "3") {
					cout << endl;
					cout << "Diese Welt ist nichts f" << ue << "r Weicheier!" << endl;
					check = true;
				}
				else {
					//Falsche Eingabe
					if (answer.length() != NULL) {
						cout << endl;
						cout << "Bitte 1,2 oder 3 w" << ae << "hlen" << endl;
						check = false;
					}
				}
			}
		}
		if (check) {
			if (rand() % 100 < 20 && enemypotion != 0) {
				enemyhealth = enemyhealth + rand() % 33;
				enemypotion--;
				cout << "Der Bandit heilt sich" << endl;
				cout << endl;
			}
			else {
				health = health - rand() % 22;;
				cout << "Der Bandit greift an" << endl;
				cout << endl;
			}
		}
		system("pause");
	}
}

void help() {
	cout << "M" << oe << "gliche Kommandos sind:" << endl;
	cout <<
		R"foo(
)foo" << Bred << R"foo(Bewegung:           Hauptmenu:)foo" << normal << R"foo(
geh                 menu
gehe                hauptmenu
go                  exit
lauf                mainmenu
geradeaus
norden
nord
gerade
t)foo" << ue << R"foo(r
door
front

)foo" << Bred << R"foo(Speichern:          Umgebung:)foo" << normal << R"foo(
save                look
speichern           guck
speicher            schau
                    seh

)foo" << Bred << R"foo(Heilung:            Hilfe:)foo" << normal << R"foo(
heilung             help
trank               hilfe
heiltrank           commands
potion              info
potions
)foo";
}

void settings() {
	system("cls");
	cout <<
		R"foo(
Einstellungen:

[1] Textgeschwindigkeit
[2] Schwierigkeit
[3] Audio
[4] Exit
)foo";
	char answer;
	cin >> answer;
	//SoundFX spielen
	Mix_Chunk *click = Mix_LoadWAV(keyclick);
	Mix_PlayChannel(-1, click, 0);
	answer = atoi(&answer);
	//Text-Einstellungen
	switch (answer) {
	case 1:
		system("cls");
		cout <<
			R"foo(
Textgeschwindigkeit:

[1] Langsam
[2] Normal
[3] Schnell
[4] Hyperdrive
[5] Exit
)foo";
		char answertxt;
		cin >> answertxt;
		Mix_PlayChannel(-1, click, 0);
		answertxt = atoi(&answertxt);

		switch (answertxt) {
		case 1: delay = 75;
			cout << "Textgeschwindigkeit = Langsam" << endl;
			break;
		case 2: delay = 30;
			cout << "Textgeschwindigkeit = Normal" << endl;
			break;
		case 3:delay = 15;
			cout << "Textgeschwindigkeit = Schnell" << endl;
			break;
		case 4:delay = 1;
			cout << "Textgeschwindigkeit = Hyperdrive" << endl;
			break;
		case 5:
			break;
		}
		break;
	case 2:
		//Schwierigkeits-Einstellungen
		system("cls");
		cout <<
			R"foo(
Schwierigkeit:

[1] Einfach
[2] Normal
[3] Schwer
[4] Exit
)foo";
		char answerdiff;
		cin >> answerdiff;
		//SoundFX spielen
		Mix_PlayChannel(-1, click, 0);
		answerdiff = atoi(&answerdiff);

		switch (answerdiff) {
		case 1: gegnerleben = 50;
			cout << "Schwierigkeit = Einfach" << endl;
			break;
		case 2: gegnerleben = 100;
			cout << "Schwierigkeit = Normal" << endl;
			break;
		case 3:gegnerleben = 150;
			cout << "Schwierigkeit = Schwer" << endl;
			break;
		case 4:
			break;
		}
		break;
	case 3:
		//Audio-Einstellungen
		system("cls");
		cout <<
			R"foo(
Audio:

[1] Lautst)foo" << ae << R"foo(rke
[2] Musik
[3] Exit
)foo";
		char answermus;
		cin >> answermus;
		//SoundFX spielen
		Mix_PlayChannel(-1, click, 0);
		answermus = atoi(&answermus);

		switch (answermus) {
		case 1:
			system("cls");
			cout <<
				R"foo(
Lautst)foo" << ae << R"foo(rke:

Gib einen Wert zwischen 0 und 128 ein, um die Lautst)foo" << ae << R"foo(rke zu )foo" << ae << R"foo(ndern.
Normal ist 30
Im Moment ist )foo" << Mix_VolumeMusic(-1) << R"foo( eingestellt)foo" << endl;

			int volume;
			cin >> volume;
			if (volume >= 0 && volume <= 128) {
				Mix_VolumeMusic(volume);
			}
			break;
		case 2:
			system("cls");
			cout <<
				R"foo(
Musik: (Um auch Kampfmusik auszustellen, Lautstärke auf 0 setzen!)
[1] AUS
[2] AN
)foo";
			int musikswitch;
			cin >> musikswitch;
			//SoundFX spielen
			Mix_PlayChannel(-1, click, 0);
			if (musikswitch == 1 && Mix_PausedMusic() == 0) {
				Mix_PauseMusic();
			}if (musikswitch == 2) {
				Mix_ResumeMusic();
			}
			break;
		case 3:
			break;
		}
	}
}

void listitems() {
	string list = "Ich sehe ";
	list += "eine Tuer";
	if (raumnr == 3) {
		list += " und eine Truhe";
	}
	if (raumnr == 4) {
		list += " und einen Tisch";
	}
	if (raumnr == 6) {
		list += " und einen Teppich";
	}
	if (raumnr == 10) {
		list += " und einen Schrank";
	}
	if (raumnr == 18) {
		list += " und eine Leiter";
	}
	drawscreen(raumnr, raumnr, raumnr, list, 0);
}

void dev() {
	while (true) {
		system("CLS");
		cout << R"foo(
   *--------------------*
   | DeveloperMenu      |
   | [1] Teleport       |
   | [2] Kampfsimulation|
   | [3] Spiel laden    |
   | [4] Einstellungen  |
   *--------------------*
)foo" << endl;
		//Einlesen der Antwort
		char answer;
		cin >> answer;
		//SoundFX spielen
		Mix_Chunk *click = Mix_LoadWAV(keyclick);
		Mix_PlayChannel(-1, click, 0);
		answer = atoi(&answer);
		switch (answer) {
		case 1:
			//Teleport-Funktion
			cout << "In welchen Raum gehen?(0-18)" << endl;
			int answerdev;
			cin >> answerdev;
			raumnr = answerdev;
			startgame();
			break;
			//Kampfsimulation
		case 2:combat();
			break;
			//Spiel laden
		case 3:loadgame(true);
			break;
			//Einstellungen
		case 4:settings();
			break;
		}
	}
}

void gameover() {
	//Starten der Hintergrundmusik
	Mix_Music *music = Mix_LoadMUS(gameovermus);
	Mix_PlayMusic(music, -1);
	//Ausgabe der Intro-Animation
	while (true) {
		cout <<
			R"foo(
   _____                         ____
  / ____|                       / __ \
 | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __
 | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__|
 | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |
  \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|
               ...
             ;::::;
           ;::::; :;
         ;:::::'   :;
        ;:::::;     ;.
       ,:::::'       ;           OOO\
       ::::::;       ;          OOOOO\
       ;:::::;       ;         OOOOOOOO
      ,;::::::;     ;'         / OOOOOOO
    ;:::::::::`. ,,,;.        /  / DOOOOOO
  .';:::::::::::::::::;,     /  /     DOOOO
 ,::::::;::::::;;;;::::;,   /  /        DOOO
;`::::::`'::::::;;;::::: ,#/  /          DOOO
:`:::::::`;::::::;;::: ;::#  /            DOOO
::`:::::::`;:::::::: ;::::# /             DOO
`:`:::::::`;:::::: ;::::::#/               OO
 :::`:::::::`;; ;:::::::::##               OO
 ::::`:::::::`;::::::::;:::#               OO
 `:::::`::::::::::::;'`:;::#               O
  `:::::`::::::::;' /  / `:#
   ::::::`:::::;'  /  /   `#
)foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo(
    _____                         ____
  / ____|                       / __ \
 | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __
 | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__|
 | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |
  \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|
               ...
             ;::::;
           ;::::; :;
         ;:::::'   :;
        ;:::::;     ;.
       ,:::::'       ;           OOO\
       ::::::;       ;          OOOOO\
       ;:::::;       ;         OOOOOOOO
      ,;::::::;     ;'         / OOOOOOO
    ;:::::::::`. ,,,;.        /  / DOOOOOO
  .';:::::::::::::::::;,     /  /     DOOOO
 ,::::::;::::::;;;;::::;,   /  /        DOOO
;`::::::`'::::::;;;::::: ,#/  /          DOOO
:`:::::::`;::::::;;::: ;::#  /            DOOO
::`:::::::`;:::::::: ;::::# /              DOO
`:`:::::::`;:::::: ;::::::#/               DOO
 :::`:::::::`;; ;:::::::::##                OO
 ::::`:::::::`;::::::::;:::#                OO
 `:::::`::::::::::::;'`:;::#                O
  `:::::`::::::::;' /  / `:#
   ::::::`:::::;'  /  /   `#
)foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo(
   _____                         ____
   / ____|                       / __ \
 | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __
 | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__|
 | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |
  \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|
               ...
             ;::::;
           ;::::; :;
         ;:::::'   :;
        ;:::::;     ;.
       ,:::::'       ;           OOO\
       ::::::;       ;          OOOOO\
       ;:::::;       ;         OOOOOOOO
      ,;::::::;     ;'         / OOOOOOO
    ;:::::::::`. ,,,;.        /  / DOOOOOO
  .';:::::::::::::::::;,     /  /     DOOOO
 ,::::::;::::::;;;;::::;,   /  /        DOOO
;`::::::`'::::::;;;::::: ,#/  /          DOOO
:`:::::::`;::::::;;::: ;::#  /            DOOO
::`:::::::`;:::::::: ;::::# /             DOO
`:`:::::::`;:::::: ;::::::#/               OO
 :::`:::::::`;; ;:::::::::##               OO
 ::::`:::::::`;::::::::;:::#               OO
 `:::::`::::::::::::;'`:;::#               O
  `:::::`::::::::;' /  / `:#
   ::::::`:::::;'  /  /   `#
)foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo(
   _____                         ____
  / ____|                       / __ \
  | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __
 | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__|
 | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |
  \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|
               ...
             ;::::;
           ;::::; :;
         ;:::::'   :;
        ;:::::;     ;.
       ,:::::'       ;           OOO\
       ::::::;       ;          OOOOO\
       ;:::::;       ;         OOOOOOOO
      ,;::::::;     ;'         / OOOOOOO
    ;:::::::::`. ,,,;.        /  / DOOOOOO
  .';:::::::::::::::::;,     /  /     DOOOO
 ,::::::;::::::;;;;::::;,   /  /        DOOO
;`::::::`'::::::;;;::::: ,#/  /          DOOO
:`:::::::`;::::::;;::: ;::#  /            DOOO
::`:::::::`;:::::::: ;::::# /              DOO
`:`:::::::`;:::::: ;::::::#/               DOO
 :::`:::::::`;; ;:::::::::##                OO
 ::::`:::::::`;::::::::;:::#                OO
 `:::::`::::::::::::;'`:;::#                O
  `:::::`::::::::;' /  / `:#
   ::::::`:::::;'  /  /   `#
)foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo(
   _____                         ____
  / ____|                       / __ \
 | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __
  | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__|
 | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |
  \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|
               ...
             ;::::;
           ;::::; :;
         ;:::::'   :;
        ;:::::;     ;.
       ,:::::'       ;           OOO\
       ::::::;       ;          OOOOO\
       ;:::::;       ;         OOOOOOOO
      ,;::::::;     ;'         / OOOOOOO
    ;:::::::::`. ,,,;.        /  / DOOOOOO
  .';:::::::::::::::::;,     /  /     DOOOO
 ,::::::;::::::;;;;::::;,   /  /        DOOO
;`::::::`'::::::;;;::::: ,#/  /          DOOO
:`:::::::`;::::::;;::: ;::#  /            DOOO
::`:::::::`;:::::::: ;::::# /             DOO
`:`:::::::`;:::::: ;::::::#/               OO
 :::`:::::::`;; ;:::::::::##               OO
 ::::`:::::::`;::::::::;:::#               OO
 `:::::`::::::::::::;'`:;::#               O
  `:::::`::::::::;' /  / `:#
   ::::::`:::::;'  /  /   `#)foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo(
   _____                         ____
  / ____|                       / __ \
 | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __
 | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__|
  | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |
  \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|
               ...
             ;::::;
           ;::::; :;
         ;:::::'   :;
        ;:::::;     ;.
       ,:::::'       ;           OOO\
       ::::::;       ;          OOOOO\
       ;:::::;       ;         OOOOOOOO
      ,;::::::;     ;'         / OOOOOOO
    ;:::::::::`. ,,,;.        /  / DOOOOOO
  .';:::::::::::::::::;,     /  /     DOOOO
 ,::::::;::::::;;;;::::;,   /  /        DOOO
;`::::::`'::::::;;;::::: ,#/  /          DOOO
:`:::::::`;::::::;;::: ;::#  /            DOOO
::`:::::::`;:::::::: ;::::# /              DOO
`:`:::::::`;:::::: ;::::::#/               DOO
 :::`:::::::`;; ;:::::::::##                OO
 ::::`:::::::`;::::::::;:::#                OO
 `:::::`::::::::::::;'`:;::#                O
  `:::::`::::::::;' /  / `:#
   ::::::`:::::;'  /  /   `#
)foo";
		Sleep(100);
		system("CLS");
		srand(time(NULL));
		if ((rand() % 100) < 5) {
			cout <<
				R"foo(
   _____                         ____
  / ____|                       / __ \
 | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __
 | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__|
 | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |
   \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|
               ...
             ;::::;
           ;::::; :;
         ;:::::'   :;
        ;:::::;     ;.
       ,:::::' 0   0 ;           OOO\
       ::::::;   <   ;          OOOOO\
       ;:::::; -___- ;         OOOOOOOO
      ,;::::::;     ;'         / OOOOOOO
    ;:::::::::`. ,,,;.        /  / DOOOOOO
  .';:::::::::::::::::;,     /  /     DOOOO
 ,::::::;::::::;;;;::::;,   /  /        DOOO
;`::::::`'::::::;;;::::: ,#/  /          DOOO
:`:::::::`;::::::;;::: ;::#  /            DOOO
::`:::::::`;:::::::: ;::::# /             DOO
`:`:::::::`;:::::: ;::::::#/               OO
 :::`:::::::`;; ;:::::::::##               OO
 ::::`:::::::`;::::::::;:::#               OO
 `:::::`::::::::::::;'`:;::#               O
  `:::::`::::::::;' /  / `:#
   ::::::`:::::;'  /  /   `#
)foo";
		}
		else {
			cout <<
				R"foo(
   _____                         ____
  / ____|                       / __ \
 | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __
 | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__|
 | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |
   \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|
               ...
             ;::::;
           ;::::; :;
         ;:::::'   :;
        ;:::::;     ;.
       ,:::::'       ;           OOO\
       ::::::;       ;          OOOOO\
       ;:::::;       ;         OOOOOOOO
      ,;::::::;     ;'         / OOOOOOO
    ;:::::::::`. ,,,;.        /  / DOOOOOO
  .';:::::::::::::::::;,     /  /     DOOOO
 ,::::::;::::::;;;;::::;,   /  /        DOOO
;`::::::`'::::::;;;::::: ,#/  /          DOOO
:`:::::::`;::::::;;::: ;::#  /            DOOO
::`:::::::`;:::::::: ;::::# /             DOO
`:`:::::::`;:::::: ;::::::#/               OO
 :::`:::::::`;; ;:::::::::##               OO
 ::::`:::::::`;::::::::;:::#               OO
 `:::::`::::::::::::;'`:;::#               O
  `:::::`::::::::;' /  / `:#
   ::::::`:::::;'  /  /   `#
)foo";
		}
		Sleep(100);
		system("CLS");
	}
}
void wingame() {
	system("CLS");
	//Starten der Hintergrundmusik
	Mix_Music *music = Mix_LoadMUS(winmus);
	Mix_PlayMusic(music, -1);
	//Ausgabe der Intro-Animation
	while (true) {
		cout <<
			R"foo(
 __     __          __          ___
 \ \   / /          \ \        / (_)
  \ \_/ /__  _   _   \ \  /\  / / _ _ __
   \   / _ \| | | |   \ \/  \/ / | | '_ \
    | | (_) | |_| |    \  /\  /  | | | | |
    |_|\___/ \__,_|     \/  \/   |_|_| |_|)foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo(
  __     __          __          ___
 \ \   / /          \ \        / (_)
  \ \_/ /__  _   _   \ \  /\  / / _ _ __
   \   / _ \| | | |   \ \/  \/ / | | '_ \
    | | (_) | |_| |    \  /\  /  | | | | |
    |_|\___/ \__,_|     \/  \/   |_|_| |_|)foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo(
 __     __          __          ___
  \ \   / /          \ \        / (_)
  \ \_/ /__  _   _   \ \  /\  / / _ _ __
   \   / _ \| | | |   \ \/  \/ / | | '_ \
    | | (_) | |_| |    \  /\  /  | | | | |
    |_|\___/ \__,_|     \/  \/   |_|_| |_|)foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo(
 __     __          __          ___
 \ \   / /          \ \        / (_)
   \ \_/ /__  _   _   \ \  /\  / / _ _ __
   \   / _ \| | | |   \ \/  \/ / | | '_ \
    | | (_) | |_| |    \  /\  /  | | | | |
    |_|\___/ \__,_|     \/  \/   |_|_| |_|)foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo(
 __     __          __          ___
 \ \   / /          \ \        / (_)
  \ \_/ /__  _   _   \ \  /\  / / _ _ __
    \   / _ \| | | |   \ \/  \/ / | | '_ \
    | | (_) | |_| |    \  /\  /  | | | | |
    |_|\___/ \__,_|     \/  \/   |_|_| |_|)foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo(
 __     __          __          ___
 \ \   / /          \ \        / (_)
  \ \_/ /__  _   _   \ \  /\  / / _ _ __
   \   / _ \| | | |   \ \/  \/ / | | '_ \
     | | (_) | |_| |    \  /\  /  | | | | |
    |_|\___/ \__,_|     \/  \/   |_|_| |_|)foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo(
 __     __          __          ___
 \ \   / /          \ \        / (_)
  \ \_/ /__  _   _   \ \  /\  / / _ _ __
   \   / _ \| | | |   \ \/  \/ / | | '_ \
    | | (_) | |_| |    \  /\  /  | | | | |
     |_|\___/ \__,_|     \/  \/   |_|_| |_|)foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo(
 __     __          __          ___
 \ \   / /          \ \        / (_)
  \ \_/ /__  _   _   \ \  /\  / / _ _ __
   \   / _ \| | | |   \ \/  \/ / | | '_ \
    | | (_) | |_| |    \  /\  /  | | | | |
    |_|\___/ \__,_|     \/  \/   |_|_| |_|)foo";
		Sleep(100);
		system("CLS");
	}
}