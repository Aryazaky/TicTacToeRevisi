#include "Board.h"


void Board::GenerateEmptyCells(int cell_count)
{
    // TODO: Add your implementation code here.
}


void Board::DisplayBoard()
{
    // TODO: Add your implementation code here.
}


void Board::SetCellAt(int index, CellType to_state)
{
    // TODO: Add your implementation code here.
}


CellType Board::CheckHorizontal()
{
    // TODO: Add your implementation code here.
    return CellType();
}


CellType Board::CheckVertical()
{
    // TODO: Add your implementation code here.
    return CellType();
}


CellType Board::CheckDiagonal()
{
    // TODO: Add your implementation code here.
    return CellType();
}


// mengosongkan cells. Size jadi 0
void Board::ClearCells()
{
    cells.clear();
}

int Board::Size()
{
    return cells.size();
}
