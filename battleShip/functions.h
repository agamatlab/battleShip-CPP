#pragma once

int sumArray(const int* arr, int size)
{
	/*
	* Array'da göndərilən dəyərlərin
	* cəmini taparaq qaytarır.
	*/
	if (arr == nullptr || size < 1) return 0;
	int sum = 0;
	for (size_t i = 0; i < size; i++)
		sum += arr[i];
	return sum;
}


template<typename T>
void delete2DArray(T**& arr, unsigned short size)
{
	// Verilən arrayın ölçü qədər silinməsi.
	if (arr == nullptr || size < 1) return;

	for (size_t i = 0; i < size; i++)
		delete[] arr[i];
	delete[] arr;
	arr = nullptr;
}

bool manageChoice(unsigned short& choice, unsigned short& answerCount)
{
	// Uİ'da dəyərlərin keyboardla idarəsini təmin edir.

	char kb = _getch();
	if (kb == 224 || kb == -32) kb = _getch();

	switch (kb)
	{
	case 'w':
	case 'W':
	case 'a':
	case 'A':
	case UP:
	case LEFT:
		if (choice == 0) choice = answerCount;
		choice--;
		return true;
	case 's':
	case 'S':
	case 'd':
	case 'D':
	case DOWN:
	case RIGHT:
		choice++;
		choice %= answerCount;
		return true;
	case ENTER:
		return false;
		break;
	default:
		return true;
	}
}

void mySetColor(int fg, int bg) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, fg | (bg << 4));
}


bool checkCollision(char**& arr, int**& shipBodyCoordinates)
{
	/*
	* Verilən GƏMİ kordinatlarınin arraydə boş yerlərə uyğun
	* gəlib-gəlmədiyini təyin edir.
	*/

	if (arr == nullptr || shipBodyCoordinates == nullptr) return false;

	for (size_t i = 0; i < MAXBODYLENGTH; i++)
	{
		if (shipBodyCoordinates[i][0] == 0 && shipBodyCoordinates[i][1] == 0) continue;
		if (shipBodyCoordinates[i][0] < 1 || shipBodyCoordinates[i][0] > SIZE
			|| shipBodyCoordinates[i][1] < 1 || shipBodyCoordinates[i][1] > SIZE)
		{
			return true;
		}
		if (arr[shipBodyCoordinates[i][1]][shipBodyCoordinates[i][0]] == SYM_SHIPBODY
			|| arr[shipBodyCoordinates[i][1]][shipBodyCoordinates[i][0]] == SYM_SEARCHEDAREA)
		{
			return true;
		}
	}
	return false;
}

void showGameBoard(bool onlyPlayer = false, int** shipBodyCoordinates = nullptr)
{
	// Verilən dəyişənlərin dəyərinə uyğun bir və ya hər iki istifadəçinin arrayini çıxarır.

	bool isCollision = checkCollision(Player->gameBoard, shipBodyCoordinates);

	cout << setw(18) << right << "Player Board";
	if (!onlyPlayer)cout << setw(32) << right << "Enemy Board";
	cout << endl;

	for (size_t i = 0; i < SIZEWBORDER; i++)
	{
		for (size_t k = 0; k < SIZEWBORDER; k++)
		{
			if (Enemy->guessCoordinates[0] == k && Enemy->guessCoordinates[1] == i && i != 0) mySetColor(LIGHTPURPLE, BLACK);
			else if (Player->gameBoard[i][k] == SYM_HIT) mySetColor(GREEN, BLACK);
			else if (Player->gameBoard[i][k] == SYM_DESTROYED) mySetColor(AQUA, BLACK);
			else if (Player->gameBoard[i][k] == SYM_MISS) mySetColor(RED, BLACK);

			if (shipBodyCoordinates != nullptr)
			{
				bool isFound = false;
				for (size_t j = 0; j < MAXBODYLENGTH && !isFound; j++)
					if (shipBodyCoordinates[j][0] == k && shipBodyCoordinates[j][1] == i && shipBodyCoordinates[j][1] != 0)
					{
						if (isCollision) mySetColor(RED, BLACK);
						else mySetColor(GREEN, BLACK);
						cout << "O ";
						isFound = true;
						mySetColor(DEFAULT, BLACK);
					}
				if (isFound) continue;
			}

			if ((i == 0 || i == SIZEWBORDER - 1) && (k != SIZEWBORDER - 1)) cout << Player->gameBoard[i][k] << char(205);
			else if (Player->gameBoard[i][k] == SYM_SEARCHEDAREA) cout << "  ";
			else cout << Player->gameBoard[i][k] << " ";
			mySetColor(DEFAULT, BLACK);
		}

		if (!onlyPlayer)
		{
			cout << "\t";

			for (size_t k = 0; k < SIZEWBORDER; k++)
			{
				if (i == Player->guessCoordinates[1] && k == Player->guessCoordinates[0])
				{
					if ((Enemy->gameBoard[i][k] == SYM_HIT || 
						Enemy->gameBoard[i][k] == SYM_MISS || 
						Enemy->gameBoard[i][k] == SYM_DESTROYED)
						|| (playerAssist && (Enemy->gameBoard[i][k] == SYM_SEARCHEDAREA)))
					{
						mySetColor(LIGHTPURPLE, BLACK); cout << Enemy->gameBoard[i][k] << " ";
					}
					else
					{
						mySetColor(GREEN, BLACK); cout << SYM_GUESS << ' ';
					}

					mySetColor(DEFAULT, BLACK);
				}
				else
				{
					if (Enemy->gameBoard[i][k] == SYM_HIT) mySetColor(GREEN, BLACK);
					else if (Enemy->gameBoard[i][k] == SYM_DESTROYED) mySetColor(AQUA, BLACK);
					else if (Enemy->gameBoard[i][k] == SYM_MISS) mySetColor(RED, BLACK);

					if ((i == 0 || i == SIZEWBORDER - 1) && (k != SIZEWBORDER - 1)) cout << Enemy->gameBoard[i][k] << char(205);
					else if (Enemy->gameBoard[i][k] == SYM_SEARCHEDAREA || Enemy->gameBoard[i][k] == SYM_SHIPBODY) cout << "  ";
					else cout << Enemy->gameBoard[i][k] << " ";
					mySetColor(DEFAULT, 0);
				}
			}

		}
		cout << endl;
	}
	if (!onlyPlayer) cout << "Player Remaining Ships: " << sumArray(Player->shipCount, SHIPTYPECOUNT) << "\t"
		<< "Enemy Remaining Ships: " << sumArray(Enemy->shipCount, SHIPTYPECOUNT) << endl;
	if (isCollision) cout << "CHECK COLLISION !" << endl;
}

void directionAdjust(unsigned short& choice)
{
	if (choice == 1) choice = 2;
	else if (choice == 2) choice = 1;
	else if (choice == 3) choice = 4;
	else if (choice == 4) choice = 3;
}

template<typename T>void init2DArray(T**& arr, int sizeRow, int sizeColumn)
{
	// 2D Arraylarin Daxilini BOŞ COLUMN'larla Doldurur.
	if (arr == nullptr || sizeRow < 1 || sizeColumn < 1) return;

	for (size_t i = 0; i < sizeRow; i++)
		arr[i] = new T[sizeColumn]{};
}

int smallestİndex(int*& shipSizes)
{
	/*
	* Verilmiş arrayda 0-a bərabər olmayan
	* ilk elementin indeksini qaytarır.
	*/
	if (shipSizes == nullptr) return -1;

	for (size_t i = 0; i < SHIPTYPECOUNT; i++)
		if (shipSizes[i] != 0 && i != 0) return i;
	return 0;
}

void surroundArea(unsigned short x, unsigned short y, char**& arr)
{
	// Verilmiş kordinatın ətrafını verilmiş functionda işarəliyir.
	if (arr == nullptr || x < 1 || y < 1) return;

	if (arr[y][x + 1] == SYM_SPACE) arr[y][x + 1] = SYM_SEARCHEDAREA;
	if (arr[y][x - 1] == SYM_SPACE) arr[y][x - 1] = SYM_SEARCHEDAREA;
	if (arr[y + 1][x + 1] == SYM_SPACE) arr[y + 1][x + 1] = SYM_SEARCHEDAREA;
	if (arr[y + 1][x - 1] == SYM_SPACE) arr[y + 1][x - 1] = SYM_SEARCHEDAREA;
	if (arr[y + 1][x] == SYM_SPACE) arr[y + 1][x] = SYM_SEARCHEDAREA;
	if (arr[y - 1][x] == SYM_SPACE) arr[y - 1][x] = SYM_SEARCHEDAREA;
	if (arr[y - 1][x + 1] == SYM_SPACE) arr[y - 1][x + 1] = SYM_SEARCHEDAREA;
	if (arr[y - 1][x - 1] == SYM_SPACE) arr[y - 1][x - 1] = SYM_SEARCHEDAREA;
}

void surroundShip(Ship*& ship, char** board)
{
	// Gəminin hər bir kordinatının ətrafını tək-tək alt function sayəsində işarəliyir.
	if (ship == nullptr || board == nullptr) return;

	for (size_t i = 0; i < ship->bodySize; i++)
		surroundArea(ship->body[i][0], ship->body[i][1], board);
}

void shipRemove(Properties*& Playing, unsigned short index)
{
	/*
	* Verilmiş index'dəki GƏMİ verilmiş OYUNÇUNUN arrayindən silinir,
	* ölçu isə bir vahid azalır.
	*/
	if (Playing == nullptr || index < 0) return;

	unsigned short sizeShip = Playing->ships[index]->bodySize;
	unsigned short sum = sumArray(Playing->shipCount, SHIPTYPECOUNT);

	Ship** newShips = new Ship * [sum - 1];
	for (size_t i = 0, k = 0; i < sum; i++)
		if (i != index) newShips[k++] = Playing->ships[i];
		else { delete[] Playing->ships[i]->body; delete Playing->ships[i]; }

	delete[] Playing->ships;
	Playing->shipCount[sizeShip - 1]--;
	Playing->ships = newShips;
}

void addShipinShips(Ship*& ship, Properties*& Playing)
{
	// Müvafiq gəmi göndərilən OYUNÇUNUN GƏMİLƏRİNƏ əlavə edilir.
	if (ship == nullptr || Playing == nullptr) return;

	int sum = sumArray(Playing->shipCount, SHIPTYPECOUNT);
	if (Playing->ships == nullptr) { Playing->ships = new Ship * [] {ship}; Playing->shipCount[ship->bodySize - 1]++; return; }

	Ship** tempPtr = new Ship * [sum + 1];

	for (size_t i = 0; i < sum; i++)
		tempPtr[i + 1] = Playing->ships[i];

	tempPtr[0] = ship;

	delete[] Playing->ships;
	Playing->shipCount[ship->bodySize - 1]++;
	Playing->ships = tempPtr;
}


template<typename T> 
void resetArray(T* arr, int size)
{
	// Verilmiş Array'in dəyərləri sıfırlanır - sıfıra bərabər edir.
	if (arr == nullptr || size < 1) return;

	for (size_t i = 0; i < size; i++)
		arr[i] = 0;
}

void checkDestroyed(Properties*& Playing)
{
	/*
	* Göndərilmiş istifadəçinin gəmisinin/gəmilərinin
	* hansı hissələrinin vurulub-vurulmadığını yolxayır
	* və əgər hər-hansı gəminin bütün hissələri vurulubsa
	* buna uyğun tənzimlənmələr edir.
	*/
	if (Playing == nullptr) return;

	int sum = sumArray(Playing->shipCount, SHIPTYPECOUNT); // Gəmilərin toplam sayı tapılır.
	for (size_t i = 0; i < sum; i++)
	{
		bool empty = true;

		for (size_t k = 0; k < Playing->ships[i]->bodySize; k++)
			if (Playing->gameBoard[Playing->ships[i]->body[k][1]][Playing->ships[i]->body[k][0]] != SYM_HIT) { empty = false; break; }
		// Yalnız istifadəçinin gəmisinin hər bir nöqtəsi vurulduqda empty = true olaraq qalır və şərtə daxil olur.

		if (empty)
		{
			if (turn % 2 == 0) // BOT
			{
				surroundShip(Playing->ships[i], Playing->gameBoard); // Gəminin hər bir hissəsini
				// vurduqdan sonra yenidən ətrafını vurmamaq üçün işarəliyir.
				AI = OFF;
				directionFound = OFF;


				resetArray(moveLength, 2);
				prohibitedCases = 0;
				resetArray(startCord, COORDINATES);
			}
			else // Player
			{
				if (playerAssist)
					surroundShip(Playing->ships[i], Playing->gameBoard);
			}

			for (size_t k = 0; k < Playing->ships[i]->bodySize; k++)
				Playing->gameBoard[Playing->ships[i]->body[k][1]][Playing->ships[i]->body[k][0]] = SYM_DESTROYED;

			shipRemove(Playing, i); // Bütün hissələri vurulmuş OYUNÇUNUN GƏMİLƏRİ siyahısından çıxarılır.

			return;
		}
	}
}

Ship* createShip(int**& shipBodyCoordinates)
{
	// Verilmiş bodyCoordinates'ə sahib Ship STRUCT yaradılıb "return" edilir.

	if (shipBodyCoordinates == nullptr) return nullptr;

	int count = 0;
	for (size_t i = 0; i < MAXBODYLENGTH; i++)
		if (shipBodyCoordinates[i][0] != 0 && shipBodyCoordinates[i][1] != 0) count++;

	int** tempCoordinates = new int* [count] {};
	for (size_t i = 0; i < count; i++)
		tempCoordinates[i] = new int[2];

	for (size_t i = 0, indexTemp = 0; i < MAXBODYLENGTH; i++)
		if (shipBodyCoordinates[i][0] != 0 && shipBodyCoordinates[i][1] != 0)

		{
			tempCoordinates[indexTemp][0] = shipBodyCoordinates[i][0];
			tempCoordinates[indexTemp++][1] = shipBodyCoordinates[i][1];
		}

	Ship* newShip = new Ship{ count, tempCoordinates };
	return newShip;
}


bool movementGuess(int& x, int& y, Properties*& Opennent)
{
	/*
	* İstifadəçinin inputuna görə "guessCoordinates"in
	* davranışlarını təyin edir və müəyyən tənzimlənmələr edir.
	*/

	// Oxunaqlılıq qorunsun deyə REFERENCElərdən istifadə olunur.
	
	if (Opennent == nullptr) return false;

	char input = _getch();
	if (input == -32 || input == 224) input = _getch();

	switch (input)
	{
	case 'A':
	case 'a':
	case LEFT:
		if (x - 1 != 0) x--;
		break;
	case 'W':
	case 'w':
	case UP:
		if (y - 1 != 0) y--;
		break;
	case 'D':
	case 'd':
	case RIGHT:
		if (x + 1 != SIZEWBORDER - 1) x++;
		break;
	case 'S':
	case 's':
	case DOWN:
		if (y + 1 != SIZEWBORDER - 1) y++;
		break;
	case ENTER:
		if (Opennent->gameBoard[y][x] == SYM_SHIPBODY)
		{
			Opennent->gameBoard[y][x] = SYM_HIT;
			isHit = ON;
		}
		else if ((playerAssist && Opennent->gameBoard[y][x] == SYM_SEARCHEDAREA) || 
			   (Opennent->gameBoard[y][x] == SYM_HIT ||
				Opennent->gameBoard[y][x] == SYM_MISS ||
				Opennent->gameBoard[y][x] == SYM_DESTROYED)) { cout << '\a'; return false; }
		else
			Opennent->gameBoard[y][x] = SYM_MISS;
		return true;
	default:
		break;
	}
	return false;
}

void winMenu();

void getGuessPlayer()
{
	/*
	* Alt functionlar sayəsində KEYBOARD-CONTROLLED
	* MENU'lar ilə təxmin alınır və gameBoard'a yüklənir.
	*/

	bool isBreak = false;

	while (!isBreak)
	{
		system("cls");
		showGameBoard();
		isBreak = movementGuess(Player->guessCoordinates[0], Player->guessCoordinates[1], Enemy);

	}
}

void getMoveLength(int& startX, int& startY)
{
	// Verilmiş Kordinatdan eninə və uzununa edilə bilən addımlar hesablanır, moveLENGTH update olunur.
	unsigned short x = 1, y = 1, i = 1;
	bool* blocks = new bool[4]{};
	char sym;

	do
	{
		if (startY - i <= 0) blocks[0] = true;
		else
		{
		sym = Player->gameBoard[startY - i][startX];
		if (sym != SYM_HIT && sym != SYM_MISS && sym != SYM_DESTROYED && sym != SYM_SEARCHEDAREA && !blocks[0]) y++;
		else blocks[0] = true;

		}


		if (startY + i > SIZE) blocks[1] = true;
		else {
		sym = Player->gameBoard[startY + i][startX];
		if (sym != SYM_HIT && sym != SYM_MISS && sym != SYM_DESTROYED && sym != SYM_SEARCHEDAREA && !blocks[1]) y++;
		else blocks[1] = true;
		}


		if (startX - i <= 0) blocks[2] = true;
		else
		{
		sym = Player->gameBoard[startY][startX - i];
		if (sym != SYM_HIT && sym != SYM_MISS && sym != SYM_DESTROYED && sym != SYM_SEARCHEDAREA && !blocks[2]) x++;
		else blocks[2] = true;
		}



		if (startX + i > SIZE) blocks[3] = true;
		else {
		sym = Player->gameBoard[startY][startX + i];
		if (sym != SYM_HIT && sym != SYM_MISS && sym != SYM_DESTROYED && sym != SYM_SEARCHEDAREA && !blocks[3]) x++;
		else blocks[3] = true;

		}

		i++;
	} while (!(blocks[0] == true && blocks[1] == true && blocks[2] == true && blocks[3] == true));

	moveLength[1] = y;
	moveLength[0] = x;

	delete[] blocks;
}

void getGuessBot()
{
	/*
	* Bota beyin yazılam hissədir:
	*
	* M1 ~ Bot vurulan yerlərə bir daha vurmur;
	*
	* M2 ~ Vurduğu yer əgər böyük bir gəminin hissəsidirsə
	*    geri qalan hissələrini axtarmağa və lazımi şərtləri
	*    yoxlamağa davam edir;
	*
	* M3 ~ Partlamış gəmilərin ətrafına vurmur;
	*
	* M4 ~ Ata biləcəyi addımların sayı ən kiçik gəminin
	*    gəminin ölçüsündən kiçik olan yerlərə düşmür;
	*/
	int sumPlayer = sumArray(Player->shipCount, SHIPTYPECOUNT); // Gəmilərin sayını alır
	showGameBoard();

	// Kod uzun və nisbətən qarışıq görünməsin deyə alias'lardan /reference'lərdən istifade etdim.
	int& y = Enemy->guessCoordinates[1];
	int& x = Enemy->guessCoordinates[0];

	if (AI) // Aİ - gəminin bir hissəsi vurulduqdan sonra digər hissələrin tapılmalı olduğu müddətdə "ON(1)" olur. 
	{
		if (moveLength[0] == 0 && moveLength[1] == 0) getMoveLength(startCord[0], startCord[1]);

		if (!directionFound) // getGuessBot dokumentariyasındakı M4 maddəsini yoxlayır.
		{
			int smallestShipSize = smallestİndex(Player->shipCount) + 1;
			if (moveLength[1] < smallestShipSize && moveLength[1] != 0) { prohibitedCases = pow(2, 2) + pow(2, 3); } // case 3 | 4
			else if (moveLength[0] < smallestShipSize && moveLength[0] != 0) { prohibitedCases = pow(2, 0) + pow(2, 1); } // case 1 | 2
		}


		do // getGuessBot Dokumentariyası M2 
		{
			if (!directionFound) choice = rand() % SHIPTYPECOUNT + 1; // Düzgün istiqamət tapılana qədər choice random seçilir.

			switch (choice) // Həmin seçimi uyğun guessCoordinates tənzimlənir.
			{
			case 1:
				x = prevCord[0] + 1;
				y = prevCord[1];
				break;
			case 2:
				x = prevCord[0] - 1;
				y = prevCord[1];
				break;
			case 3:
				x = prevCord[0];
				y = prevCord[1] + 1;
				break;
			case 4:
				x = prevCord[0];
				y = prevCord[1] - 1;
				break;
			default:
				break;
			}

			if ((Player->gameBoard[y][x] != SYM_SPACE && Player->gameBoard[y][x] != SYM_SHIPBODY) // guessCoordinatesin göstərdiyi nöqtəyə addım
				// || Player->gameBoard[y][x] == SYM_SEARCHEDAREA
				)  //  atılib-atılmamağının mümkünlüyü təyin olunur.
			{
				// Burada hər vəziyyətə uyğun istiqamət tənzimlənməsi baş verir. 
				x = 0;
				if (directionFound)
				{
					directionAdjust(choice); // choice'i əks istiqamətə yönləndirmək üçün dəyişir.
					prevCord[0] = startCord[0];
					prevCord[1] = startCord[1];
				}
			}

		} while (x <= 0 || x > SIZE
			|| y == 0 || y > SIZE
			|| prohibitedCases[choice - 1]
			|| Player->gameBoard[y][x] == SYM_SEARCHEDAREA
			);
	}
	else
	{
		// Random GUESS - M4'ün tətəbiqi burada da mövcuddur.
		int smallestShipSize = smallestİndex(Player->shipCount) + 1;
		do
		{
			x = rand() % SIZE + 1;
			y = rand() % SIZE + 1;
			getMoveLength(x, y); // verilmiş kordinatdan edə biləcəyi
			// şauqili və üfüqi hərkətlərin sayısını alır və moveLength'ə köçürür.
		} while (!(Player->gameBoard[y][x] != SYM_SEARCHEDAREA
			&& Player->gameBoard[y][x] != SYM_HIT
			&& Player->gameBoard[y][x] != SYM_MISS
			&& Player->gameBoard[y][x] != SYM_DESTROYED
			&& (smallestShipSize <= moveLength[0] || smallestShipSize <= moveLength[1] || smallestShipSize == 1)));

		resetArray(moveLength, 2); // İstifadədən sonra qalan datalar təmizlənir.
	}

	if (Player->gameBoard[y][x] == SYM_SHIPBODY)
	{
		// istənilən hit hadisəsi zamanı "Aİ" "ON" olur,
		// və gəminin digər hissələri varsa onu axtarmaq üçün hazırlıqlar edilir.

		if (AI) { directionFound = true; }
		Player->gameBoard[y][x] = SYM_HIT;

		AI = ON;
		if (startCord[0] == 0 && startCord[1] == 0)
		{
			startCord[0] = x;
			startCord[1] = y;
		}
		prevCord[0] = x;
		prevCord[1] = y;

		isHit = true;
	}
	else
	{
		Player->gameBoard[y][x] = SYM_MISS;
		if (directionFound)
			/*
			* Məsələn 4-lük gəmi var: O O O O
			* Random gəlir və 2-ci hissəsini vurur: O X O O
			* Sonra sağa vurur və HİT olduğundan vurmağa davam edir: O X X X
			* Bir dənə də sağa vuranda isə MİSS(M) yazısı gəlir: O X X X M
			* Lakin gəmi hələ partlamayıb.
			* Məhz bu kod getməli olduğu kordinatı ilk vurduğu
			* 2-ci hissənin kordinatına gətirir və "directionAdjust" ilə
			* də indiyə kimi getdiyi kordinatın əksinə gedərək;
			* Indiyə kimi: x + 1 (1 sağa vurmaq)
			* Indi: x - 1 (1 sola vurmaq)
			* digər hissələrini də tapır: X X X X O
			*/
		{
			directionAdjust(choice);
			prevCord[0] = startCord[0];
			prevCord[1] = startCord[1];
		}
	}
	//Sleep(300);
}


int numLength(int num)
{
	short count = 0;
	while (num != 0)
	{
		num /= 10;
		count++;
	}

	return count;
}

void updateGameBoard(char**& arr, int**& shipBodyCoordinates)
{
	// Verilmiş gəmi kordinatlarını array'ə yerləşdirir.

	if (arr == nullptr || shipBodyCoordinates == nullptr) return;

	for (size_t i = 0; i < MAXBODYLENGTH; i++)
	{
		if (shipBodyCoordinates[i][0] == 0) continue;
		arr[shipBodyCoordinates[i][1]][shipBodyCoordinates[i][0]] = SYM_SHIPBODY;
	}

	for (size_t i = 0; i < MAXBODYLENGTH; i++)
	{
		if (shipBodyCoordinates[i][0] == 0) continue;
		surroundArea(shipBodyCoordinates[i][0], shipBodyCoordinates[i][1], arr);
	}
}



template <typename T>
void reset2DArray(T**& arr, const int& row, const int& column)
{
	/*
	* Kordinatların Tənzimlənməsi üçün nəzərdə tutulub.
	* Belə sıfırlandıqda keçmiş istifadədən qalan artıq
	* datalar ləğv olunur.
	*/

	if (arr == nullptr || row  < 1 || column < 1) return;

	for (size_t i = 0; i < row; i++)
		for (size_t k = 0; k < column; k++)
			arr[i][k] = 0;
}

void buildShipSturcture(const int& posX, const int& posY, const int& sizeShip, int**& shipBodyCoordinates)
{
	/*
	* Gəmi strukturu - bədən kordinatları arrayda saxlanılır.
	* Məlumatlarda verilən kordinata və ölçüyə görə array
	* doldurmaq isə bu funksiyanın işidir.
	*/

	if (shipBodyCoordinates == nullptr || posX < 1 || posY < 1 || sizeShip < 1) return;

	reset2DArray(shipBodyCoordinates, MAXBODYLENGTH, COORDINATES);

	unsigned short middle = 2;
	unsigned short frontLength = sizeShip / 2;
	unsigned short tailLength = sizeShip - 1 - frontLength;

	shipBodyCoordinates[middle][0] = posX;
	shipBodyCoordinates[middle][1] = posY;

	for (size_t i = 0; i < frontLength; i++)
	{
		if (orientation == VERTICAL)
		{
			shipBodyCoordinates[middle + i + 1][0] = posX;
			shipBodyCoordinates[middle + i + 1][1] = posY + i + 1;
		}

		if (orientation == HORIZONTAL)
		{
			shipBodyCoordinates[middle + i + 1][0] = posX + i + 1;
			shipBodyCoordinates[middle + i + 1][1] = posY;
		}
	}

	for (size_t i = 0; i < tailLength; i++)
	{
		if (orientation == VERTICAL)
		{
			shipBodyCoordinates[middle - i - 1][0] = posX;
			shipBodyCoordinates[middle - i - 1][1] = posY - i - 1;
		}

		if (orientation == HORIZONTAL
			)
		{
			shipBodyCoordinates[middle - i - 1][0] = posX - i - 1;
			shipBodyCoordinates[middle - i - 1][1] = posY;
		}
	}

}

void placeDownShipsRandom(Properties*& Playing, unsigned short& selectedShip)
{
	/*
	* Verilmiş ölçülərə və istifadəçiyə uyğun olaraq
	* Gəmi Strukturunun hazırlanması və Array üzərində
	* mümkün olan nöqtələrə yerləşdirilməsi.
	*/

	if (Playing == nullptr) return;

	int** shipBodyCoordinates = new int* [MAXBODYLENGTH] {};
	init2DArray(shipBodyCoordinates, MAXBODYLENGTH, COORDINATES);

	while (true)
	{
		orientation = 1 + rand() % 2;
		int posXLocal = rand() % SIZE + 1, posYLocal = rand() % SIZE + 1;


		buildShipSturcture(posXLocal, posYLocal, selectedShip, shipBodyCoordinates);
		if (!checkCollision(Playing->gameBoard, shipBodyCoordinates)) break;

	}

	updateGameBoard(Playing->gameBoard, shipBodyCoordinates);
	Ship* newShip = createShip(shipBodyCoordinates);
	addShipinShips(newShip, Playing);

	delete2DArray(shipBodyCoordinates, MAXBODYLENGTH);

}



bool movementShip(Properties*& Playing, unsigned short& shipSize, int**& shipBodyCoordinates)
{
	/*
	* Lazımi yoxlamalar çərçivəsində OYUNÇUNUN GƏMİ kordinatlarını
	* KEYBOARD-BASED kontrollarla idarəsini yerinə yetirir.
	*/

	if (Playing == nullptr || shipBodyCoordinates == nullptr || shipSize < 1) return false;

	char input = _getch();
	if (input == -32 || input == 224) input = _getch();

	unsigned short middle = 2, frontLength = shipSize / 2, tailLength = shipSize - shipSize / 2 - 1;
	// Buradakı məntiq isə kifayət qədər maraqlıdır:
	// Nə Gəminin bədəninin ölçüsünün, nə də ORİANTATİON'a ehtiyac olmadan 
	// cəmi bircə hissəsini yoxlayaraq bütün gəminin borderdan çıxıb çıxmadığını anlayır
	// və nəticədə gedib-getməməsinə nəzaret edir.

	switch (input)
	{
	case 'A':
	case 'a':
	case LEFT:
		if (shipBodyCoordinates[middle - tailLength][0] - 1 != 0)
		{
			for (size_t i = 0; i < MAXBODYLENGTH; i++)
			{
				if (shipBodyCoordinates[i][0] == 0) continue;
				else shipBodyCoordinates[i][0] -= 1;
			}
		}
		else cout << '\a';
		break;
	case 'D':
	case 'd':
	case RIGHT:
		if (shipBodyCoordinates[middle + frontLength][0] + 1 != SIZEWBORDER - 1)
		{
			for (size_t i = 0; i < MAXBODYLENGTH; i++)
			{
				if (shipBodyCoordinates[i][0] == 0) continue;
				else shipBodyCoordinates[i][0] += 1;
			}
		}
		else cout << '\a';

		break;
	case 'W':
	case 'w':
	case UP:
		if (shipBodyCoordinates[middle - tailLength][1] - 1 != 0)
		{
			for (size_t i = 0; i < MAXBODYLENGTH; i++)
			{
				if (shipBodyCoordinates[i][0] == 0) continue;
				else shipBodyCoordinates[i][1] -= 1;
			}
		}
		else cout << '\a';
		break;
	case 'S':
	case 's':
	case DOWN:
		if (shipBodyCoordinates[middle + frontLength][1] + 1 != SIZEWBORDER - 1)
		{
			for (size_t i = 0; i < MAXBODYLENGTH; i++)
			{
				if (shipBodyCoordinates[i][0] == 0) continue;
				else shipBodyCoordinates[i][1] += 1;
			}
		}
		else cout << '\a';
		break;
	case Keys::SPACE:
	case 'r':
	case 'R':
		if (orientation == HORIZONTAL && shipBodyCoordinates[middle][1] - tailLength > 0
			&& shipBodyCoordinates[middle][1] + frontLength <= SIZE)
		{
			for (size_t i = 0; i < MAXBODYLENGTH; i++)
			{
				if (shipBodyCoordinates[i][0] == 0) continue;

				if (i < middle)
				{
					shipBodyCoordinates[i][0] += (middle - i);
					shipBodyCoordinates[i][1] -= (middle - i);
				}
				else if (i > middle)
				{
					shipBodyCoordinates[i][0] += (middle - i);
					shipBodyCoordinates[i][1] -= (middle - i);
				}
			}
			orientation = VERTICAL;
		}
		else if (orientation == VERTICAL && shipBodyCoordinates[middle][0] - tailLength > 0
			&& shipBodyCoordinates[middle][0] + frontLength <= SIZE)
		{
			for (size_t i = 0; i < MAXBODYLENGTH; i++)
			{
				if (shipBodyCoordinates[i][0] == 0) continue;

				if (i < middle)
				{
					shipBodyCoordinates[i][0] -= (middle - i);
					shipBodyCoordinates[i][1] += (middle - i);
				}
				else if (i > middle)
				{
					shipBodyCoordinates[i][0] -= (middle - i);
					shipBodyCoordinates[i][1] += (middle - i);
				}
			}
			orientation = HORIZONTAL;

		}
		else cout << '\a';

		break;
	case ENTER:
		if (checkCollision(Playing->gameBoard, shipBodyCoordinates)) { cout << "\a"; break; }
		updateGameBoard(Playing->gameBoard, shipBodyCoordinates);
		Ship* newShip = createShip(shipBodyCoordinates);
		addShipinShips(newShip, Playing);
		reset2DArray(shipBodyCoordinates, MAXBODYLENGTH, COORDINATES);
		return false;
	}
	return true;
}

void getGuess()
{
	// "turn"a uyğun olaraq müvafiq OYUNÇUDAN təxmin alınır.
	if (turn % 2)
		getGuessPlayer();
	else
		getGuessBot();
}

void placeDownShipsManual(Properties*& Playing, unsigned short& selectedShip)
{
	// Gəmilərin KEYBOARD-BASED Kontrollarla MANUAL yerləşməsi tətbiq olunur.

	if (Playing == nullptr) return;

	int** shipBodyCoordinates = new int* [MAXBODYLENGTH] {};
	init2DArray(shipBodyCoordinates, MAXBODYLENGTH, COORDINATES);

	orientation = HORIZONTAL;
	int posXLocal = 5, posYLocal = 5;

	buildShipSturcture(posXLocal, posYLocal, selectedShip, shipBodyCoordinates);
	bool isContinue = true;

	while (isContinue)
	{
		system("cls");
		checkCollision(Playing->gameBoard, shipBodyCoordinates);
		showGameBoard(true, shipBodyCoordinates);
		isContinue = movementShip(Playing, selectedShip, shipBodyCoordinates);
	}

	delete2DArray(shipBodyCoordinates, MAXBODYLENGTH);
}


void fillArraywBorder(char**& arr, int row, int column)
{
	// Göndərilən Array Verilmiş Ölçülərdə BORDER ilə Doldurulur.
	
	if (arr == nullptr) return;

	for (size_t i = 0; i < row; i++)
		for (size_t k = 0; k < column; k++)
		{
			if (i == 0 && k == 0) arr[i][k] = 201;
			else if (i == 0 && k == column - 1) arr[i][k] = 187;
			else if (i == row - 1 && k == 0) arr[i][k] = 200;
			else if (i == row - 1 && k == column - 1) arr[i][k] = 188;
			else if (i == 0 || i == row - 1) arr[i][k] = 205;
			else if (k == 0 || k == column - 1) arr[i][k] = 186;
			else arr[i][k] = SYM_SPACE;
		}
}

void setUpArray(Properties*& Playing)
{
	// Oyun üçün önəmli olan ARRAY'lərin yaradılması və doldurulması
	if (Playing == nullptr) return;

	init2DArray(Playing->gameBoard, SIZEWBORDER, SIZEWBORDER);
	fillArraywBorder(Playing->gameBoard, SIZEWBORDER, SIZEWBORDER);
}


char getRMChoice();
void getAssistChoice();
void getShipChoice(unsigned short&, int*&);

void removeSearchBorders(char**& arr, unsigned short row, unsigned short column)
{
	if (arr == nullptr) return;

	for (size_t i = 0; i < row; i++)
		for (size_t k = 0; k < column; k++)
			if (arr[i][k] == SYM_SEARCHEDAREA) arr[i][k] = SYM_SPACE;
}

template<typename T>
bool checkEmpty(T* arr, unsigned short size)
{
	// Array daxilindəki datanın mövcudluğunu yoxlayır.
	if (arr == nullptr ) return false;

	for (size_t i = 0; i < size; i++)
		if (arr[i] != 0) return false;
	return true;
}

void manageShips()
{
	// Gəmilərin seçimlərdən asılı olaraq MANUAL-RANDOM yerləşdirilməsi
	char answer = getRMChoice();
	int* shipSizes = new int[SHIPTYPECOUNT] { 4, 3, 2, 1 }; //

	while (true)
	{
		unsigned short selectedShip = 0;

		system("cls");
		if (answer == 'm') // Manual
		{
			getShipChoice(selectedShip, shipSizes); // Istifadəçidən seçimi alan funksiya
			placeDownShipsManual(Player, selectedShip); // Manual yerləşməni təmin edən function (daxilində köməkçi functionlar da var)
		}
		else // Random
		{
			selectedShip = smallestİndex(shipSizes) + 1; // Random üçün gəmi seçilir (sayısı 0-dan çox olan ən kiçik gəmi)
			placeDownShipsRandom(Player, selectedShip); // Verilmiş ölçüdə struktur yaranır və yerləşdirilir.
		}

		placeDownShipsRandom(Enemy, selectedShip); // Verilmiş ölçüdə struktur yaranır və yerləşdirilir.
		shipSizes[selectedShip - 1]--;

		if (checkEmpty(shipSizes, SHIPTYPECOUNT)) break; // Sayların hamısı 0-a bərabər olanda dövrdən çıxır.
	}

	removeSearchBorders(Player->gameBoard, SIZEWBORDER, SIZEWBORDER);
	removeSearchBorders(Enemy->gameBoard, SIZEWBORDER, SIZEWBORDER);
	delete[] shipSizes;

	getAssistChoice();

}

void checkHit()
{
	/*
	* Oyun boyunca hər hansı "HİT" hadisəsi baş verdikdə
	* Bu funksiya "turn" dəyişənindən müvafiq oyunçunu
	* təyin ederək "checkDestroyed()" funksiyasını çağırır,
	* əksi təqdirdə isə sıranı digər oyunçuya verir.
	*/

	if (isHit)
	{
		isHit = false;
		if (turn % 2)checkDestroyed(Enemy);
		else checkDestroyed(Player);
	}
	else turn++;
	Sleep(100);
}

void deleteProperties(Properties*& Playing)
{
	if (Playing == nullptr) return;

	unsigned short shipCount = sumArray(Playing->shipCount, SHIPTYPECOUNT);
	for (size_t i = 0; i < shipCount; i++)
	{
		delete2DArray(Playing->ships[i]->body, Playing->ships[i]->bodySize);
		delete[] Playing->ships[i];
	}

	delete2DArray(Playing->gameBoard, SIZEWBORDER);

	delete[] Playing->guessCoordinates;
	delete[] Playing->shipCount;

}


void deleteHeap()
{
	delete[] moveLength;
	delete[] prevCord;
	delete[] startCord;

	deleteProperties(Player);
	deleteProperties(Enemy);
}

void checkWin()
{
	// Geri qalan gəmilərin sayından asılı olaraq "winMenu"un cağırılması və kodun sonlanması
	system("cls");
	if (sumArray(Enemy->shipCount, SHIPTYPECOUNT) == 0 || sumArray(Player->shipCount, SHIPTYPECOUNT) == 0)
	{
		deleteHeap();
		winMenu();
		exit(777);
	}
}

void setUPGame()
{
	// Hər iki oyunçunun fundemental dəyişənləri İnitiallize  edilir.
	setUpArray(Player);
	setUpArray(Enemy);

}