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
void loadgame();
void save();
void drawscreen(int, int, int, string);
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
int delay = 50;
//Lebensvariabel
int health = 100;
//Lebensvariabel der Gegner
int gegnerleben = 100;
//Heilngsitems
int potions = 3;
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
static const char *winmus = "..\\Music\\Visager2\\Visager_-_02_-_Royal_Entrance.mp3";
static const char *gameovermus = "..\\Music\\Visager2\\Visager_-_23_-_Haunted_Forest_Loop.mp3";
static const char *mausoleum = "..\\Music\\Visager2\\Visager_-_11_-_Eerie_Mausoleum.mp3";
static const char *icecave = "..\\Music\\Visager\\Visager_-_07_-_Ice_Cave.mp3";
static const char *combatintromusic = "..\\Music\\Visager2\\Visager_-_21_-_Battle_Intro.mp3";
static const char *combatmusic = "..\\Music\\Visager2\\Visager_-_22_-_Battle_Loop.mp3";
static const char *titletheme = "..\\Music\\Visager\\TitleTheme.mp3";
static const char *keyclick = "..\\Music\\click.wav";
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
|                                      Resize to show complete box                                              |
|                                       for game to work correctly                                              |
|                                                                                                               |
|                                        dont resize after this!                                                |
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
	system("CLS");
	cout << R"foo(
   *--------------------*
   | [1] Start New Game |
   | [2] Load Game      |
   *--------------------*
)foo" << endl;
	char answer;
	cin >> answer;
	answer = atoi(&answer);
	switch (answer) {
	case 1:
		//Spiel starten
		startgame();
		break;
	case 2:loadgame();
		break;
	}
}

void startgame() {
	if (raumnr == 19) {
		wingame();
	}
	room(raumnr);
	//Starten der Hintergrundmusik
	Mix_Music *music = Mix_LoadMUS(mausoleum);
	Mix_PlayMusic(music, -1);
	string answer;
	int raumnrcheck = 0;
	bool check = false;
	while (true) {
		srand(time(NULL));
		if (rand() % 100 < 10 && raumnrcheck != raumnr&&raumnr != 1) {
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

		if (answer == "geh" || answer == "gehe" || answer == "go" || answer == "lauf" || answer == "geradeaus" || answer == "norden" || answer == "nord" || answer == "gerade" || answer == "tür" || answer == "door" || answer == "front") {
			drawscreen(raumnr, raumnr, raumnr, "Willst du in den nächsten Raum gehen? (y/n)");
			memset(&answer[0], 0, 10);
			cin >> answer;
			answer = tolower(answer[0]);
			if (answer == "y") {
				raumnr++;
				drawscreen(raumnr, raumnr, raumnr, " ");
				check = false;
			}
		}
		if (answer == "save" || answer == "speichern" || answer == "speicher") {
			save();
			check = false;
		}
		if (answer == "look" || answer == "guck" || answer == "schau" || answer == "seh") {
			listitems();
			check = false;
		}
		if (answer == "heilung" || answer == "trank" || answer == "heiltrank" || answer == "potion" || answer == "potions") {
			if (potions != 0) {
				potions--;
				health = health + (rand() % 50) + 10;
				cout << endl;
				cout << "Du heilst dich" << endl;
				check = false;
			}
			else {
				cout << "Du hast keine Heiltränke mehr!" << endl;
				check = false;
			}
		}
		if (check) {
			if (answer.length() != 0) {
				cout << "Begriff: " << answer << " nicht verstanden" << endl;
			}
		}
		check = true;
	}

}

void loadgame() {
	FILE* datei;
	if ((datei = fopen("save.bin", "rb")) == NULL)
	{
		fprintf(stderr, "Fehler bei der Dateioeffnung");
	}
	for (int i = 0; (fread(&saves[i], sizeof(struct savegame), 1, datei)) != NULL; i++) {
		if (i == 3)
		{
			cout << "ACHTUNG: Die zulässige Anzahl an Datensätzen wurde überschritten<<" << endl;
			break;
		}
	}
	fclose(datei);
	cout <<
		R"foo(
Welchen Spielstand möchtest du laden?
[1]
[2]
[3]
)foo" << endl;
	char answer;
	int n;
	cin >> answer;
	answer = atoi(&answer);
	n = answer;
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
			cout << "Einen anderen wählen?(y/n)" << endl;
			cin >> c;
			c = tolower(c);
			if (c == 'y') {
				loadgame();
			}
			if (c == 'n') {
				mainmenu();
			}
		} while (c != 'y' || c != 'n');
	}
}

void save() {
	int i;
	for (i = 3; saves[i].room != NULL; i--) {

	}
	savegame newsave;
	newsave.room = raumnr;
	newsave.delay = delay;
	newsave.health = health;
	newsave.potions = potions;

	saves[i] = newsave;
	FILE* datei;
	if ((datei = fopen("save.bin", "w")) == NULL) {
		fprintf(stderr, "Fehler bei der Dateioeffnung");
		cout << "Fehler beim Speichern" << endl;
	}
	cout <<
		R"foo(
In welchem Slot willst du speichern?
[1]
[2]
[3]
		)foo" << endl;
	char answer;
	cin >> answer;
	answer = atoi(&answer);

	switch (answer) {
	case 1:fwrite(saves, sizeof(savegame), 1, datei);
		break;
	case 2: fseek(datei, sizeof(savegame), SEEK_SET); fwrite(saves, sizeof(savegame), 1, datei);
		break;
	case 3:fseek(datei, sizeof(savegame)*2, SEEK_SET); fwrite(saves, sizeof(savegame), 1, datei);
		break;
	}

	fwrite(saves, sizeof(savegame), 1, datei);
	cout << "Erfolgreich gespeichtert" << endl;
	fclose(datei);
}

void drawscreen(int locint, int imgint, int txtint, string info) {
	system("CLS");
	//Modulares system um gleiche Assets mehrmals zu benutzen
	getloc(locint);
	getimg(imgint);
	gettxt(txtint);
	//Ausgabe aller Infos
	cout << image <<
		R"foo(
+---------------------------------------------------------------------------------------------------+
                                 )foo" << location << R"foo(                                                                            
+---------------------------------------------------------------------------------------------------+
)foo"; if (info.length() != NULL) {
		for (int i = 0; text[i] != NULL; i++) {
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
	drawscreen(n, n, n, " ");
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
	srand(time(NULL));
	int graphic = (rand() % 4) - 1;
	getimg(20 + graphic);
	string answer;
	while (true) {
		check = false;
		system("cls");
		cout << image <<
			R"foo(
+---------------------------------------------------------------------------------------------------+
                                          Bandit: )foo";
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

)foo"; if (health >= 66) {
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

		if (health <= 0) {
			gameover();
		}
		if (enemyhealth <= 0) {
			system("cls");
			cout << "Der Bandit wurde besiegt!" << endl;
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

		if (answer == "1") {
			enemyhealth = enemyhealth - rand() % 33;
			check = true;
			cout << endl;
			cout << "Du greifst an" << endl;
		}
		else {
			if (answer == "2") {
				if (potions != 0) {
					potions--;
					health = health + (rand() % 50)+10;
					cout << endl;
					cout << "Du heilst dich" << endl;
					check = true;
				}
				else {
					cout << "Du hast keine Heiltränke mehr!" << endl;
				}
			}
			else {
				if (answer == "3") {
					cout << endl;
					cout << "Diese Welt ist nichts für Weicheier!" << endl;
					check = true;
				}
				else {
					if (answer.length() != NULL) {
						cout << endl;
						cout << "Bitte 1,2 oder 3 wählen" << endl;
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
				health = health - rand() % 33;;
				cout << "Der Bandit greift an" << endl;
				cout << endl;
			}
		}
		system("pause");
	}
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
  \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|   )foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo( 
    _____                         ____                 
  / ____|                       / __ \                
 | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ 
 | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__|
 | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |   
  \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|   )foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo( 
   _____                         ____                 
   / ____|                       / __ \                
 | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ 
 | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__|
 | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |   
  \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|   )foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo( 
   _____                         ____                 
  / ____|                       / __ \                
  | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ 
 | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__|
 | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |   
  \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|   )foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo( 
   _____                         ____                 
  / ____|                       / __ \                
 | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ 
  | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__|
 | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |   
  \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|   )foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo( 
   _____                         ____                 
  / ____|                       / __ \                
 | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ 
 | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__|
  | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |   
  \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|   )foo";
		Sleep(100);
		system("CLS");
		cout <<
			R"foo( 
   _____                         ____                 
  / ____|                       / __ \                
 | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ 
 | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__|
 | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |   
   \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|   )foo";
		Sleep(100);
		system("CLS");
	}
}
void listitems() {
	string list = "Ich sehe ";
	if (raumnr != 6 || raumnr != 12 || raumnr != 18) {
		list += "eine Tür";
	}
	drawscreen(raumnr, raumnr, raumnr, list);
}
void wingame() {
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
	}
}
