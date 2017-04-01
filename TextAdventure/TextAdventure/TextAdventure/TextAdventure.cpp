// TextAdventure.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
#include "windows.h"
using namespace std;

void intro();
void testscreen();
void drawscreen(char picture[]);

int main()
{
	testscreen();
	intro();
	char picture[] = { R"foo(   
      ,,,,
     /   '
    /.. /
   ( c  D
    \- '\_
     `-'\)\
        |_ \
        |U \\
       (__,//
       |. \/
       LL__I
        |||
        |||
       -``'
)foo" };
	drawscreen(picture);
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

