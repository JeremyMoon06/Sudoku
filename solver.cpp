#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

void makePuzzle2D(int[9][9], vector<int>);
void solvePuzzle(int[9][9]);
int getBoxIndex(int, int);
pair<int, int> getNextPosition(int[9][9], int, int);
bool solvePuzzleHelper(int[9][9], int, int, bitset<9>[9], bitset<9>[9], bitset<9>[9]);
string translatePuzzle(int[9][9]);

int main() {
	vector<int> puzzle1{
		0, 0, 0, 8, 0, 0, 4, 2, 0,
		5, 0, 0, 6, 7, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 9, 0, 0, 5,
		7, 4, 0, 1, 0, 0, 0, 0, 0,
		0, 0, 9, 0, 3, 0, 7, 0, 0,
		0, 0, 0, 0, 0, 7, 0, 4, 8,
		8, 0, 0, 4, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 9, 8, 0, 0, 3,
		0, 9, 5, 0, 0, 3, 0, 0, 0
	};
	vector<int> puzzle2{
		0, 0, 4, 0, 5, 0, 0, 0, 0,
		9, 0, 0, 7, 3, 4, 6, 0, 0,
		0, 0, 3, 0, 2, 1, 0, 4, 9,
		0, 3, 5, 0, 9, 0, 4, 8, 0,
		0, 9, 0, 0, 0, 0, 0, 3, 0,
		0, 7, 6, 0, 1, 0, 9, 2, 0,
		3, 1, 0, 9, 7, 0, 2, 0, 0,
		0, 0, 9, 1, 8, 2, 0, 0, 3,
		0, 0, 0, 0, 6, 0, 1, 0, 0
	};
	int puzzle[9][9];
	makePuzzle2D(puzzle, puzzle2);
	cout << translatePuzzle(puzzle) << '\n';
	solvePuzzle(puzzle);
	cout << translatePuzzle(puzzle);
	return 0;
}

string translatePuzzle(int puzzle[9][9]) {
	string s = "[";
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			char c = '0' + puzzle[i][j];
			s += c;
			if (i == 8 && j == 8) {
				continue;
			}
			else {
				s += ",";
			}
		}
	}
	s += "]";
	return s;
}

void makePuzzle2D(int puzzle[9][9], vector<int> v) {
	// Translate vector into 2D array
	int n = v.size();
	for (int i = 0; i < n; i++) {
		puzzle[i / 9][i % 9] = v.at(i);
	}
}

void solvePuzzle(int puzzle[9][9]) {
	// Set up sets of bits to optimally reduce time complexity
	bitset<9> row[9];
	bitset<9> column[9];
	bitset<9> box[9];

	// Initialize bits
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int x = puzzle[i][j];
			if (x != 0) {
				// Reduce x by 1 to get correct index
				int index = x - 1;
				row[i].set(index);
				column[j].set(index);
				int test = ((i / 3) * 3) + (j % 3);
				box[getBoxIndex(i, j)].set(index);
			}
		}
	}
	solvePuzzleHelper(puzzle, 0, 0, row, column, box);
}

int getBoxIndex(int x, int y) {
	return ((x / 3) * 3) + (y / 3);
}

pair<int, int> getNextPosition(int puzzle[9][9], int x, int y) {
	// Start at current position and find next position
	if (puzzle[x][y] == 0) {
		return { x, y };
	}
	for (; x < 9; x++) {
		for (; y < 9; y++) {
			if (puzzle[x][y] == 0) {
				return { x, y };
			}
		}
		y = 0;
	}
	// Return -1 if complete
	return { -1, -1 };
}

bool solvePuzzleHelper(int puzzle[9][9], int x, int y,
	bitset<9> row[9], bitset<9> column[9], bitset<9> box[9]) {
	pair<int, int> position = getNextPosition(puzzle, x, y);
	x = position.first;
	y = position.second;
	// End if complete (-1)
	if (x == -1) {
		return true;
	}
	// Get options by combining bitsets
	bitset<9> options = row[x] | column[y] | box[getBoxIndex(x, y)];
	// Check if everything has already been used at location
	if (options.all()) {
		return false;
	}
	// Find option
	for (int i = 0; i < 9; i++) {
		if (!options[i]) {
			puzzle[x][y] = i + 1;
			row[x].set(i);
			column[y].set(i);
			box[getBoxIndex(x, y)].set(i);
			if (solvePuzzleHelper(puzzle, x, y, row, column, box)) {
				return true;
			}
			row[x].reset(i);
			column[y].reset(i);
			box[getBoxIndex(x, y)].reset(i);
		}
	}
	puzzle[x][y] = 0;
	return false;
}