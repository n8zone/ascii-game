#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include "Entity.h"



using namespace std;


typedef struct {
	Point pos;
} Player;


void setRawMode() {
	struct termios tty;
	tcgetattr(STDIN_FILENO, &tty);									// Retrieves terminal attributes
	tty.c_lflag &= ~(ICANON | ECHO);								// Disable canonical mode & echo.

	 /* Bitwise and assignment: This operator performs a bitwise AND operation between variable on the left and expression on the right and assigns the result back to the variable
			Ex: a &= b is equivalent to a = a & b


			Bitwise or assignment: This operator performs a bitwise OR operation between the variable on the left and the expression on the right and assigns the result back to the variable
			ex: a |= b == a = a | b


			Bitwise not: This operator inverts all bits of its operand.
			ex: if a == 01 then ~a == 10

			*/



	/* Canonical mode (line buffering) refers to the way data is temporarily stored before being processed. By default
			this is set to "line buffered" where data is stored in a buffer and processed once a newline character is entered

			Here we set it to unbuffered, which means data is processed IMMEDIATELY.*/


	tcsetattr(STDIN_FILENO, TCSANOW, &tty);				// Set terminal attributes
}

void resetMode() {
	struct termios tty;
	tcgetattr(STDIN_FILENO, &tty);
	tty.c_lflag |= (ICANON | ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void DisplayMap(vector<vector<char> >& map, const vector<Entity>& entities) {

	for (const Entity& ent : entities) {
		Point entPos = ent.pos;
		map[entPos.y][entPos.x] = ent.sprite;
	}

	system("clear");
	for (const auto& row : map) {
		for (const auto& cell : row) {
			cout << cell;
		}
		cout << endl;
	}
}

vector<vector<char> > CreateMap(const int sizeX, const int sizeY) {
	vector<vector<char> > map(sizeY, vector<char>(sizeX, ' '));
	for (int i = 0; i < sizeY; i++) {
		for(int j = 0; j < sizeX; j++) {
			if (i == 0 || i == (sizeY - 1) || j == 0 || j == (sizeX - 1)) {
				map[i][j] = 'H';
			} else {
				map[i][j] = '.';
			}
		}
	}
	return map;
}

bool nextIsObstacle(const vector<vector<char> >& map, Point pos) {
	char gridContains = map[pos.y][pos.x];
	bool isObstacle = gridContains == 'H' || gridContains == '*';
	return isObstacle;
}



int main() {
	char c;
	// MAP SETUP //

	int inpX, inpY;

	Point testPoint = {1, 1};
	Point scaledPoint = 5 * testPoint;

	cout << scaledPoint << endl;
	cout << scaledPoint * 5 << endl;

	do {
		cout << "Enter the width and height of the map: ";
		cin >> inpX >> inpY;
	} while ((inpX < 4) && (inpY > 15 && inpY < 4));

	setRawMode();													// Set terminal to not buffer input before processing

	const int MAP_X = inpX, MAP_Y = inpY;
	vector<vector<char> > map = CreateMap(MAP_X, MAP_Y);

	// PLAYER SETUP //
	vector<Entity> entities;

	Point plySpawn = {1, 1};
	Entity ply;
	ply.sprite = '@';
	ply.pos = plySpawn;

	Point obstacleSpawn = {3, 1};
	Entity obstacle;
	obstacle.sprite = '#';
	obstacle.pos = obstacleSpawn;

	entities.insert(entities.end(), ply);

	entities.insert(entities.begin(), obstacle);
	entities.insert(entities.begin(), obstacle);
	
	Entity * plyPtr = &entities.back();



	// MAIN LOOP //

	map[plyPtr->pos.y][plyPtr->pos.x] = plyPtr->sprite;
	DisplayMap(map, entities);
	while (true) {
		bool moved = false;

		c = getchar();
		map[plyPtr->pos.y][plyPtr->pos.x] = '.';

		if (c == 'Q') {
			break;
		}

		if (c == 'd' || c == 'C') {
			Point direction = {1, 0};
			moved = plyPtr->Move(direction, map);
		}

		if (c == 'a' || c == 'D') {
			Point direction = {-1, 0};
			moved = plyPtr->Move(direction, map);
		}

		if (c == 'w' || c == 'A') {
			Point direction = {0, -1};
			moved = plyPtr->Move(direction, map);
		}

		if (c == 's' || c == 'B') {
			Point direction = {0, 1};
			moved = plyPtr->Move(direction, map);
		}


//		map[ply.pos.y][ply.pos.x] = '@';

		if ( moved ) {
			DisplayMap(map, entities);
			cout << "HP: 100 | MANA : 15" << endl; 
		}

		//cout << "You pressed: " << c << " (ASCII: " << static_cast<int>(c) << ")\n";
	}
	resetMode();
	return 0;
}
