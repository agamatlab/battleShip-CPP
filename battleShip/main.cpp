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
	FILE* file;
	unsigned int seed = time(NULL);
	srand(seed);

	fopen_s(&file, "seeds.txt", "a");

	if (file) {
		int lenSeed = numLength(seed);
		char* seedChar = new char[lenSeed] {};
		for (size_t i = 0; seed != 0; i++)
		{

			seedChar[lenSeed - i - 1] = seed % 10 + 48;
			seed /= 10;
		}

		fwrite(seedChar, sizeof(char), lenSeed, file);
		fputc('\n', file);
		fclose(file);
	}

	enterence(); // GUI
	setUPGame(); // İnittiallize && Fill Arrays
	manageShips(); // Mode Seçimi && Gəmi Yerləşməsi

	while (true)
	{
		getGuess();
		checkHit();

		checkWin();
	} 
}
