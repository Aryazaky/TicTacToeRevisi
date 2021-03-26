#pragma once
#include<vector>
#include<string>
#include"MiscStuff.h"
class Board
{
	std::vector<CellType> cells;
	int filled_cells;
	int width, height;
public:
	Board();
	void GenerateEmptyCells(int _width, int _height);
	std::string DisplayBoard(int cursor_location);
	void SetCellAt(int index, CellType type);
	CellType CheckHorizontal();
	CellType CheckVertical();
	CellType CheckDiagonal();
	// mengosongkan cells. Size jadi 0
	void ClearCells();
	int Size();
	bool IsFull();
};

