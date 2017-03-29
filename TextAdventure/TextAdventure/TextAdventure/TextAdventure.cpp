// TextAdventure.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
#include "windows.h"
using namespace std;

void intro();

int main()
{
	intro();
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

                                                                                   
																								
}
