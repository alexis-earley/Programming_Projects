#include "Board.h"
#include <vector>
using std::vector;
#include<iostream>
using namespace std;

Board::Board() {
	numRows = 25;
	numColumns = 16;
}

Board::Board(vector<Tile>& tiles) {
	this->tiles = tiles;
	numRows = 16;
	numColumns = 25;
}

Tile Board::GetIndexedTile(int index) {
	return tiles[index];
}

Tile* Board::GetTileRef(int index) {
	Tile* tile = &(tiles[index]);
	return tile;
}

Tile Board::GetTile(int row, int column) {
	int index = (row * 25) + column;
	return tiles[index];
}

vector<Tile>& Board::GetTiles() {
	return tiles;
}

void Board::SetNearMines(int index, int numMines) {
	tiles[index].SetNearMines(numMines);
}

void Board::AssignNeighbors() {

	for (unsigned int i = 0; i < tiles.size(); i++) {
		Tile currentTile = tiles[i];
		int row = currentTile.GetRow();
		int column = currentTile.GetColumn();

		bool topRow = false;
		if (row == 0) {
			topRow = true;
		}
		bool bottomRow = false;
		if (row == (numRows - 1)) {
			bottomRow = true;
		}
		bool leftColumn = false;
		if (column == 0) {
			leftColumn = true;
		}
		bool rightColumn = false;
		if (column == (numColumns - 1)) {
			rightColumn = true;
		}
		if (!topRow && !leftColumn) {
			Tile* topLeft = &(tiles[((25 * (row - 1)) + (column - 1))]);
			tiles[i].SetNeighbor(topLeft);
		}

		if (!topRow) {
			Tile* top = &(tiles[((25 * (row - 1)) + (column))]);
			tiles[i].SetNeighbor(top);
		}

		if (!topRow && !rightColumn) {
			Tile* topRight = &(tiles[((25 * (row - 1)) + (column + 1))]);
			tiles[i].SetNeighbor(topRight);
		}

		if (!leftColumn) {
			Tile* left = &(tiles[((25 * (row)) + (column - 1))]);
			tiles[i].SetNeighbor(left);
		}

		if (!rightColumn) {
			Tile* right = &(tiles[((25 * (row)) + (column + 1))]);
			tiles[i].SetNeighbor(right);
		}

		if (!bottomRow && !leftColumn) {
			Tile* bottomLeft = &(tiles[((25 * (row + 1)) + (column - 1))]);
			tiles[i].SetNeighbor(bottomLeft);
		}

		if (!bottomRow) {
			Tile* bottom = &(tiles[((25 * (row + 1)) + (column))]);
			tiles[i].SetNeighbor(bottom);
		}

		if (!bottomRow && !rightColumn) {
			Tile* bottomRight = &(tiles[((25 * (row + 1)) + (column + 1))]);
			tiles[i].SetNeighbor(bottomRight);
		}
	}
}

void Board::SetNearMines() {
	if (tiles[0].GetNeighbors().size() == 0) {
		AssignNeighbors();
	}
	
	for (unsigned int i = 0; i < tiles.size(); i++) {
		int numMines = 0;
		vector<Tile*> neighbors = tiles[i].GetNeighbors();
		for (Tile* neighbor : neighbors) {
			if (neighbor->HasMine()) {
				numMines++;
			}
		}
		tiles[i].SetNearMines(numMines);
	}
}

int Board::GetNumRows() {
	return numRows;
}

int Board::GetNumColumns() {
	return numColumns;
}

void Board::Reveal(int index, bool toReveal) {
	tiles[index].Reveal(toReveal);
}

bool Board::IsRevealed(int index) {
	return tiles[index].IsRevealed();
}

void Board::Flag(int index, bool toFlag) {
	tiles[index].Flag(toFlag);
}

bool Board::IsFlagged(int index) {
	return tiles[index].IsFlagged();
}

int Board::GetNumMines() {
	int mineCount = 0;
	for (Tile tile : tiles) {
		if (tile.HasMine()) {
			mineCount++;
		}
	}
	return mineCount;
}