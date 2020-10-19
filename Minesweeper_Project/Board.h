#pragma once

#include "Tile.h"
#include <vector>
using std::vector;
class Board
{
	//A class to represent the board. This represents the core data object in the game.
private:
	vector<Tile> tiles;
	int numRows;
	int numColumns;
public:
	Board();
	Board(vector<Tile>& tiles);
	Tile GetIndexedTile(int index);
	Tile* GetTileRef(int index);
	Tile GetTile(int row, int column);
	vector<Tile>& GetTiles();
	void SetNearMines(int index, int numMines);
	void AssignNeighbors();
	void SetNearMines();
	int GetNumRows();
	int GetNumColumns();
	void Reveal(int index, bool toReveal = true);
	bool IsRevealed(int index);
	void Flag(int index, bool toFlag = true);
	bool IsFlagged(int index);
	int GetNumMines();
};

