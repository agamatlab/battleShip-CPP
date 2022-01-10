#pragma once

#define SIZEWBORDER 13
#define SIZE 11

enum Color { BLACK = 0, GREEN = 2, AQUA = 3, RED = 4, DEFAULT = 7, GREY = 8, LIGHTGREEN = 10, LIGHTPURPLE = 13 };
enum orientationSwitch { HORIZONTAL = 1, VERTICAL = 2 };
enum Keys { LEFT = 75, UP = 72, RIGHT = 77, DOWN = 80, ENTER = 13, SPACE = 32 };
enum situation { OFF, ON };
enum size { COORDINATES = 2, SHIPTYPECOUNT = 4, MAXBODYLENGTH = 5 };

int* prevCord = new int[COORDINATES] {};
int* startCord = new int [COORDINATES] {};

#pragma region Variables USED IN SHIP
char SYM_SPACE = ' ';
char SYM_SHIPBODY = 'O';
char SYM_MISS = 'M';
char SYM_HIT = 'H';
char SYM_DESTROYED = char(232);
char SYM_GUESS = char(15);
char SYM_SEARCHEDAREA = char(249);
#pragma endregion

unsigned short stableDir;
short turn = 1;
int* moveLength = new int[2]{};
bitset<4> prohibitedCases = 0;
unsigned short orientation;
unsigned short choice;

bool isHit = OFF;
bool directionFound = OFF;
bool AI = OFF;
bool playerAssist = OFF;

struct Ship {
	int bodySize;
	int** body = new int* [bodySize] {};
};

struct Properties {
	int* shipCount = new int[SHIPTYPECOUNT] {};
	Ship** ships = nullptr;
	int* guessCoordinates = new int[COORDINATES]{};
	char** gameBoard = new char* [SIZEWBORDER] {};
};

Properties* Player = new Properties;
Properties* Enemy = new Properties;
