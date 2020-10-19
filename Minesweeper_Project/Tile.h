#pragma once
#include<iostream>
#include <vector>
using std::string;
using std::vector;

class Tile
{
private:
	int numNearMines;
	bool hasMine;
	int row;
	int column;
	bool revealed;
	bool flagged;
	vector<Tile*> adjacentTiles;
public:
	Tile();
	Tile(int widthIndex, int heightIndex, bool hasMine = false, int numNearMines = -1, string state = "tile_hidden");
	int GetNearMines();
	void SetNearMines(int numNearMines);
	bool HasMine();
	void setMine(bool hasMine = true);
	int GetRow();
	int GetColumn();
	int GetIndex();
	void Reveal(bool toReveal = true);
	bool IsRevealed();
	void Flag(bool toFlag = true);
	bool IsFlagged();
	void SetNeighbor(Tile* neighbor);
	vector<Tile*> GetNeighbors();
};

