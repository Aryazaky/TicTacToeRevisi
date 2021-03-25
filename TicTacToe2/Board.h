#pragma once
#include<vector>
#include"MiscStuff.h"
class Board
{
	std::vector<CellType> cells;
public:
	void GenerateEmptyCells(int cell_count);
	void DisplayBoard();
	void SetCellAt(int index, CellType to_state);
	CellType CheckHorizontal();
	CellType CheckVertical();
	CellType CheckDiagonal();
	// mengosongkan cells. Size jadi 0
	void ClearCells();
	int Size();
};

