#include "Board.h"
#include<iostream>

Board::Board()
{
    filled_cells = 0;
    width = -1;
    height = -1;
}

void Board::GenerateEmptyCells(int _width, int _height)
{
    int val = _width * _height;
    while (val--)
    {
        cells.push_back(CellType::empty);
    }
    width = _width;
    height = _height;
}


std::string Board::DisplayBoard(int cursor_location)
{
    std::string out;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (i == 0 || i == width - 1) {
                std::cout << "####";
            }
            else
            {
                std::cout << "#";
                if ((i * height) + j == cursor_location) {
                    std::cout << "[";
                }
                if (cells[(i * height) + j] == CellType::X) {
                    std::cout << "X";
                }
                else if (cells[(i * height) + j] == CellType::O)
                {
                    std::cout << "O";
                }
                else
                {
                    std::cout << " ";
                }
                if ((i * height) + j == cursor_location) {
                    std::cout << "]";
                }
            }
            if (j == width - 1) {
                std::cout << "#\n";
            }
        }
    }
    return out;
}


bool Board::SetCellAt(int index, CellType type)
{
    if (cells[index] == CellType::empty) {
        cells[index] = type;
        filled_cells++;
        return true;
    }
    else
    {
        std::cout << "Cell ini sudah diisi!\n";
        return false;
    }
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
    filled_cells = 0;
}

int Board::Size()
{
    return cells.size();
}


bool Board::IsFull()
{
    if (filled_cells >= (int)cells.size()) {
        return true;
    }
    return false;
}
