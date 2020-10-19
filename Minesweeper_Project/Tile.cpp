#include "Tile.h"
#include <iostream>
#include <vector>
using std::vector;
using namespace std;

Tile::Tile() {
	numNearMines = -1;
	hasMine = false;
	row = 0;
	column = 0;
	revealed = false;
	flagged = false;
}

Tile::Tile(int row, int column, bool hasMine, int numNearMines, string state) {
	this->row = row;
	this->column = column;
	this->numNearMines = numNearMines;
	this->hasMine = hasMine;
	revealed = false;
	flagged = false;
}
void Tile::SetNearMines(int numNearMines) {
	this->numNearMines = numNearMines;
}

int Tile::GetNearMines() {
	return numNearMines;
}

bool Tile::HasMine() {
	return hasMine;
}

void Tile::setMine(bool hasMine) {
	this->hasMine = true;
}

int Tile::GetRow() {
	return row;
}

int Tile::GetColumn() {
	return column;
}

int Tile::GetIndex() {
	return ((25 * row) + column);
}

void Tile::Reveal(bool toReveal) {
	revealed = toReveal;
}

bool Tile::IsRevealed(){
	return revealed;
}

void Tile::Flag(bool toFlag) {
	if (!revealed) {
		flagged = toFlag;
	}
}

bool Tile::IsFlagged() {
	return flagged;
}

void Tile::SetNeighbor(Tile* neighbor) {
	adjacentTiles.push_back(neighbor);
}

vector<Tile*> Tile::GetNeighbors() {
	return adjacentTiles;
}