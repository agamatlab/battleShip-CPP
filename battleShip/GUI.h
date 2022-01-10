#pragma once

template<typename T>
void animatedText(T& text)
{
	unsigned short lenText = strlen(text);
	for (size_t i = 0; i < lenText; i++)
	{
		if (_kbhit()) { char sym = _getch(); if (sym == 224 || sym == -32)_getch(); cout << &text[i]; break;  }
		else cout << text[i];
		Sleep(50);
	}
}

void enterence();
void enterGame();

void infoGame()
{
	system("cls");

	animatedText("Battle Ship is Originally a Table Game Desgined to be Played with 2 PLAYER.\nGoal is to Locate\
 Enemy Ships with Assumptions you have made. There are Total of 10 Ships in This Gamemode.\nWith the sizes differing \
from one to four. To Play the Game WASD or the ARROW KEYS are almost the only things you Need.\nYou may Find Useful \
Settings such as Player Game Assist, Placing Ships Manually or Random on the Player's Behalf.\nGame is COLOR-CODED so \
Here is a Quick Run Through of the Colors and the Meanings of them:\n");

	animatedText("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PLACING DOWN SHIPS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	mySetColor(RED, BLACK);
	animatedText(R"('O' (Ship's Body in RED) - Indicates the Tiles That You are Going to Place the Ship on are Already ccupied.)");
	cout << endl;

	mySetColor(LIGHTGREEN, BLACK);
	animatedText(R"('O' (Ship's Body in GREEN) - Indicates the Tiles That You are Going to Place the Ship on are Empty.)");
	cout << endl;

	mySetColor(DEFAULT, BLACK);
	animatedText(R"(ALERT SOUND - Indicates that the Process that You Want to Do is Unacceptable.)");
	cout << endl;

	mySetColor(GREEN, BLACK);
	animatedText("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~DURING GAMEPLAY~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	
	mySetColor(LIGHTGREEN, BLACK);
	animatedText(R"('H' (HIT) - Indicates the Tile You have Guessed Posseses a Ship Body Part.)");
	cout << endl;

	mySetColor(RED, BLACK);
	animatedText(R"('M' (MISS) - Indicates the Tile You have Guessed Does not Posses a Ship Body Part.)");
	cout << endl;

	mySetColor(LIGHTPURPLE, BLACK);
	animatedText(R"('M' (MISS LAST) - Indicates the Last Missed Guess by the Enemy.)");
	cout << endl;

	mySetColor(AQUA, BLACK);
	cout << "'" << char(232) << "'";
	animatedText(R"( (DESTROYED SHIP) - Indicates that the Ship's all Body Parts that has been Hit/Destroyed.)");
	cout << endl;

	mySetColor(LIGHTGREEN, BLACK);
	cout << "'" << char(15) << "'";
	animatedText(R"( (PLAYER GUESS) - Indicates the Tile that Player's Guess is.)");
	cout << endl;

	mySetColor(DEFAULT, BLACK);
	cout << "'" << char(249) << "'";
	animatedText(R"( (UNWANTED TILE) - According to the Game Logic Indicates the Tiles that haven't got Chance to Contain Ship.)");
	cout << endl;

	mySetColor(LIGHTPURPLE, BLACK);
	cout << "'" << char(249) << "'";
	cout << " '" << char(232) << "'";
	animatedText(R"( 'H' 'M' (PLAYER GUESS) - Indicates the Tile that Player's Guess Collapses with other Symbols.)");
	cout << endl;
	cout << "\nPress any key to exit..." << endl;
	
	char sym = _getch();
	if (sym == -32 || sym == 224) _getch();
	enterence();
}

void enterence()
{
	bool notFound = true;

	mySetColor(GREEN,0);
	
	cout << "\n\n\n";

	unsigned short answerCount = 3;
	char** answers = new  char* [answerCount] {new char[] {"PLAY GAME"}, new char[] {"HOW TO PLAY"}, new char[] {"EXIT"}};
	unsigned short largestText = strlen(answers[1]), defaultSpace = 50;

	
	while (notFound)
	{
		system("cls");
		cout << R"(   _______       __  ___________  ___________  ___       _______   ________  __    __   __       _______   )" << endl;
		cout << R"(  |   _  "\     /""\("     _   ")("     _   ")|"  |     /"     "| /"       )/" |  | "\ |" \     |   __ "\ )" << endl;
		cout << R"(  (. |_)  :)   /    \)__/  \\__/  )__/  \\__/ ||  |    (: ______)(:   \___/(:  (__)  :)||  |    (. |__) :))" << endl;
		cout << R"(  |:     \/   /' /\  \  \\_ /        \\_ /    |:  |     \/    |   \___  \   \/      \/ |:  |    |:  ____/ )" << endl;
		cout << R"(  (|  _  \\  //  __'  \ |.  |        |.  |     \  |___  // ___)_   __/  \\  //  __  \\ |.  |    (|  /     )" << endl;
		cout << R"(  |: |_)  :)/   /  \\  \\:  |        \:  |    ( \_|:  \(:      "| /" \   :)(:  (  )  :)/\  |\  /|__/ \    )" << endl;
		cout << R"(  (_______/(___/    \___)\__|         \__|     \_______)\_______)(_______/  \__|  |__/(__\_|_)(_______)   )" << endl;

		cout << endl << endl;

		for (size_t i = 0; i < answerCount; i++)
		{
			cout << setw(defaultSpace + ((largestText - strlen(answers[i])) / 2)) << ' ' << right;
			if (i == choice) mySetColor(LIGHTGREEN, GREY);
			cout << answers[i] << endl;
	 
			mySetColor(LIGHTGREEN, BLACK);
		}
		notFound = manageChoice(choice, answerCount);
	}

	delete2DArray(answers, answerCount)                                                                                                                                     ;

	if (choice == 0)enterGame();
	else if (choice == 1)infoGame();
	else exit(0);
	
}

void enterGame()
{
	int pic = 0;
	for (size_t i = 0; i < 100; i++)
	{
		system("cls");
		if(i % 2)mySetColor(rand() % 10, BLACK);

		cout << "    ";
		cout << "[";

		for (size_t j = 0; j < i && j < 48; j++)
				cout << char(254);
				
		if (i <= 50) cout << setw(50 - i);
		cout << i << "%";
		

		if (i > 50)
		{
			for (int j = 0; j < i - 50; j++)
				cout << char(254);
			cout << setw(100 - i);
		}
		else cout << setw(50);


		cout << "]";
		cout << endl << "    ";

		cout << endl << endl;

		if(i % 10 == 0)pic = rand() % 3;
		switch (pic)
		{
		case 0:
			cout << setw(67) << right << R"(        _    _         )" << endl;
			cout << setw(67) << right << R"(     __|_|__|_|__      )" << endl;
			cout << setw(67) << right << R"(   _|____________|__   )" << endl;
			cout << setw(67) << right << R"(  |o o o o o o o o /   )" << endl;
			cout << setw(67) << right << R"(~'`~'`~'`~'`~'`~'`~'`~ )" << endl;
			break;

		case 1:
			cout << setw(78) << right << R"(                               v  ~.      v     )" << endl;
			cout << setw(78) << right << R"(          v           /|                        )" << endl;
			cout << setw(78) << right << R"(                     / |          v             )" << endl;
			cout << setw(78) << right << R"(              v     /__|__                      )" << endl;
			cout << setw(78) << right << R"(                  \--------/                    )" << endl;
			cout << setw(78) << right << R"(~~~~~~~~~~~~~~~~~~~`~~~~~~'~~~~~~~~~~~~~~~~~~~~~)" << endl;
			break;
		case 2:
			cout << setw(75) << right << R"(              |    |    |              )" << endl;
			cout << setw(75) << right << R"(             )_)  )_)  )_)             )" << endl;
			cout << setw(75) << right << R"(            )___))___))___)\           )" << endl;
			cout << setw(75) << right << R"(           )____)____)_____)\\         )" << endl;
			cout << setw(75) << right << R"(         _____|____|____|____\\\__     )" << endl;
			cout << setw(75) << right << R"(---------\                   /---------)" << endl;
			cout << setw(75) << right << R"(  ^^^^^ ^^^^^^^^^^^^^^^^^^^^^          )" << endl;
			cout << setw(75) << right << R"(    ^^^^      ^^^^     ^^^    ^^       )" << endl;
			cout << setw(75) << right << R"(         ^^^^      ^^^                 )" << endl;
			break;
		default:
			break;
		}

		if (_kbhit()) { char sym = _getch(); if (sym == 224 || sym == -32)_getch(); break; }
		Sleep(i * 1.1);
	}

	Sleep(1000);
	system("cls");
	mySetColor(DEFAULT, BLACK);

}


void winMenu()
{
	char* winText = nullptr;

	if (turn % 2) winText = new char[] { "Congrats! Player Has Won!..." };
	else winText = new char[] { "Congrats! Bot Has Won!..." };

	short lenText = strlen(winText);
	short count = 0;

	for (size_t i = 0; i < lenText; i++)
	{
		system("cls");

		mySetColor(count++, BLACK);
		count %= 10;

		cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
		cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&(((@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
		cout << "@@@@@@@@@@@@@@%@@@@@@@@@@@(((((((((@@@@@@@@@@@@@@,,,,,@@@@@@@@(*@@@@@@" << endl;
		cout << "@@@@@@@@@@@((((@@@@@@@@@((((((((((((@@@@@@@@*@@@@,,,,@@@@********@@@@@" << endl;
		cout << "@@@@@@@@@@(((((@@@@@@@(((((%@@@@@@@@@@@@@****@@@@@@@@@@@@@*******@@@@@" << endl;
		cout << "@@@@@@@@@@@@@@@@@@@@@@((((@@@@@((((%@@@@@*****@@@@@@@@@@@@@/******@@@@" << endl;
		cout << "@@@@******@@@@@@@@@@@@((((@(((((((((((#@@@@@@@@@@@@@@@@@@@@@******&@@@" << endl;
		cout << "@@@@@@****@@@@@@@@@@@@(((((((((@@@@((((#@@@@**********@@@@@@******%@@@" << endl;
		cout << "@@@@@@@@@@@@@@%#@@@@@@@@((((((@@@&(((((@@@************************@@@@" << endl;
		cout << "@@@@@@@@@@@@@,,,,,,@@@@@##((((((((((((@@@@******@@@@*************@@@@@" << endl;
		cout << "@@@@@@@@@@@@@@,,,,@@@@@@@####@@@@@@@@@@@@@*******@@@@@@@@@@@@@@@@@@@@@" << endl;
		cout << "@@@@@@@@@@@@@@@@@@@@@,,,,(((((,,@@@@@@@@@@@******@@@@****@@@@@@@@@@@@@" << endl;
		cout << "@@@@@@@@@@@@@@@@@@,,,/####((((##/,,,%@@%*********@@@@@**#@@@@@@@@@@@@@" << endl;
		cout << "@@@@@@@@@@@@@@@@,,,,%%%%##((((#####*************@@@@@@@@@@@@@@@((((@@@" << endl;
		cout << "@@@@@@@@@@@@@@@,,,,#%%%%#((((####/******,@@@@@@@@@@(@@@@@@(((((((((@@@" << endl;
		cout << "@@@@@@@@@@@@@@*,,,.#%%%(((((####*****###,,,@@@@@((((((@@@((((((((((@@@" << endl;
		cout << "@@@@@@@@@@@@@**,,...%%%%%#%#####***######,,,@@@@@@((#@@@((((((@@@@@@@@" << endl;
		cout << "@@@@@@@@@@@@,***.....%%%%%%%%%##########((((#@@@@@@@@@@((((((@@@@@@@@@" << endl;
		cout << "@@@@@@@@@@@,,,,,....,,,%%%%%%%#((((((((((((((((((@@@@@@((((((@@@@@@@@@" << endl;
		cout << "@@@@@@@@@@,,,..,,..,,,,,,%%%%%(((((((((((*,,((((((((((((((((#@@@@@@@@@" << endl;
		cout << "@@@@@@@@@**,....,**,,,,,,,,,,%%%%#######,,,@@@@((((((((((((@@@@@@@@@@@" << endl;
		cout << "@@@@@@@@,**,...,,****,,,,,,,,,,,,,,,,,,,,@@@@@@@@@@@@%@@@@@@@******@@@" << endl;
		cout << "@@@@@@@,,,,,,,,,,,,,*****,,,,,,,,,,,,%@@@@@@@@@@@@@(@@@@@@@@@*****%@@@" << endl;
		cout << "@@@@@@**....***,,,,,,,,,*******(@@@@@@@@@@@@@@@@(((((@@@@@@@@@@@@@@@@@" << endl;
		cout << "@@@@@@,,,.,,,,****,,,,,,,,@@@@@@@@@@@@@@@@@@@@@@@(((((@@@@@@@@/*/@@@@@" << endl;
		cout << "@@@@@,..***,,,,,,,**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@(******@@@" << endl;
		cout << "@@@@,,,,,,****@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@***@@@@" << endl;
		cout << "@@@@(,,*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;


   //      cout << "  ▄████  ▄▄▄       ███▄ ▄███▓▓█████     ▒█████   ██▒   █▓▓█████  ██▀███                 " << endl;
   //      cout << " ██▒ ▀█▒▒████▄    ▓██▒▀█▀ ██▒▓█   ▀    ▒██▒  ██▒▓██░   █▒▓█   ▀ ▓██ ▒ ██▒               " << endl;
   //      cout << "▒██░▄▄▄░▒██  ▀█▄  ▓██    ▓██░▒███      ▒██░  ██▒ ▓██  █▒░▒███   ▓██ ░▄█ ▒               " << endl;
   //      cout << "░▓█  ██▓░██▄▄▄▄██ ▒██    ▒██ ▒▓█  ▄    ▒██   ██░  ▒██ █░░▒▓█  ▄ ▒██▀▀█▄                 " << endl;
   //      cout << "░▒▓███▀▒ ▓█   ▓██▒▒██▒   ░██▒░▒████▒   ░ ████▓▒░   ▒▀█░  ░▒████▒░██▓ ▒██▒ ██▓  ██▓  ██▓ " << endl;
   //      cout << " ░▒   ▒  ▒▒   ▓▒█░░ ▒░   ░  ░░░ ▒░ ░   ░ ▒░▒░▒░    ░ ▐░  ░░ ▒░ ░░ ▒▓ ░▒▓░ ▒▓▒  ▒▓▒  ▒▓▒ " << endl;
   //      cout << "  ░   ░   ▒   ▒▒ ░░  ░      ░ ░ ░  ░     ░ ▒ ▒░    ░ ░░   ░ ░  ░  ░▒ ░ ▒░ ░▒   ░▒   ░▒  " << endl;
   //      cout << "░ ░   ░   ░   ▒   ░      ░      ░      ░ ░ ░ ▒       ░░     ░     ░░   ░  ░    ░    ░   " << endl;
   //      cout << "      ░       ░  ░       ░      ░  ░       ░ ░        ░     ░  ░   ░       ░    ░    ░  " << endl;
		 //cout << "                                                     ░                     ░    ░    ░  " << endl;
		
		for (size_t k = 0; k < i; k++)
			cout << winText[k];

		Sleep(100);
	}


	delete[] winText;
	Sleep(3000);
}


char getRMChoice()
{
	// KEYBOARD - CONTROLLED Menu ilə MOD Seçimi

	system("cls");

	bool notFound = true;
	unsigned short answerCount = 2;
	char** answers = new  char* [answerCount] {new char[] {"Random"}, new char[] {"Manually"}};

	char* text = new char[] {"Welcome To BattleShips!\nWould you like ships to be placed Random or Manually?"};
	short lenText = strlen(text);

	mySetColor(GREEN, BLACK);

	animatedText(text);

	unsigned short choice = 0;

	while (notFound)
	{
		system("cls");
		cout << text << endl;
		for (size_t i = 0; i < answerCount; i++)
		{
			char prefix = ' ';
			if (i == choice) { mySetColor(LIGHTGREEN, GREY); prefix = char(254); }
			cout << ' ' << prefix << " <<" << answers[i] << ">>" << endl;
			mySetColor(LIGHTGREEN, BLACK);
		}
		notFound = manageChoice(choice, answerCount);
	}


		mySetColor(DEFAULT, 0);

		delete[] text;
		delete2DArray(answers, answerCount);


		if (choice == 0) return 'r';
		else return 'm';

}

void getAssistChoice()
{
	// KEYBOARD - CONTROLLED Menu ilə MOD Seçimi

	system("cls");

	bool notFound = true;
	unsigned short answerCount = 2;
	char** answers = new  char* [answerCount] {new char[] {"Assist = ON"}, new char[] {"Assist = OFF"}};

	char* text = new char[] {"Would you like to ENABLE << PLAYER Assist MODE >> ?"};
	short lenText = strlen(text);

	mySetColor(DEFAULT, BLACK);

	unsigned short choice = 0;
	animatedText(text);

	while (notFound)
	{
		int fgColor = 7;
		system("cls");
		mySetColor(fgColor, BLACK);
		cout << text << endl;
		for (size_t i = 0; i < answerCount; i++)
		{
			if (i) fgColor = 4;
			else fgColor = 10;

			mySetColor(fgColor, BLACK);

			char prefix = ' ';
			if (i == choice) { mySetColor(fgColor, GREY); prefix = char(254); }
			cout << ' ' << prefix << " <<" << answers[i] << ">>" << endl;
			mySetColor(LIGHTGREEN, BLACK);
		}
		notFound = manageChoice(choice, answerCount);
	}


	mySetColor(DEFAULT, BLACK);

	delete[] text;
	delete2DArray(answers, answerCount);


	if (choice == 0) playerAssist = ON;
}

void getShipChoice(unsigned short& selectedShip, int*& shipSizes)
{
	// KEYBOARD - CONTROLLED Menu ilə GƏMİ Seçimi

	unsigned short answerCount = 4;
	char** answers = new char* [answerCount]
	{new char[] { "Destroyer(1)" },
		new char[] {"SubMarine(2)"},
		new char[] {"BattleShip(3)"},
		new char[] {"Carrier(4)"}
	};
	bool isContinue;
	do
	{
		isContinue = true;
		showGameBoard(true);

		cout << " Remaining WarShips: " << endl;
		//cout << " <<NAME(SIZE)>> ~ COUNT\n\n";
		for (size_t i = 0; i < answerCount; i++)
		{
			char prefix = i != selectedShip  ? ' ' : char(254);
			if (i == selectedShip) mySetColor(BLACK, DEFAULT);
			cout << ' ' << prefix << " <<" << answers[i] << ">>" << " ~ " << shipSizes[i] << endl;
			mySetColor(DEFAULT, BLACK);
		}
		isContinue = manageChoice(selectedShip, answerCount);
		system("cls");

	} while (isContinue || shipSizes[selectedShip] == 0);

	delete2DArray(answers, answerCount);
	selectedShip++;
}

