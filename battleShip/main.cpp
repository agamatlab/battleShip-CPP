#include <iostream>
#include <windows.h>
#include <cmath>
#include <iomanip>
#include <conio.h>
#include <bitset>
using namespace std;


#include "variables.h"
#include "functions.h"
#include "GUI.h"


int main()
{
	srand(time(NULL));

	enterence(); // GUIsgdgdsgdsgdsgdsgdsgdgsdgsgsdg
	setUPGame(); // İnittiallize && Fill Arrays
	manageShips(); // Mode Seçimi && Gəmi Yerləşməsigsdsdg

	while (true)
	{
		getGuess();
		checkHit();

		checkWin();
	} 
}
