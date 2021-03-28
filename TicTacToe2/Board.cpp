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
        if (i == 0) {
            std::cout << "#############\n";
        }
        for (int j = 0; j < height; j++) {
            std::cout << "#";
            if ((i * height) + j == cursor_location) {
                std::cout << "[";
            }
            else
            {
                std::cout << " ";
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
            else
            {
                std::cout << " ";
            }
            if (j == width - 1) {
                std::cout << "#\n";
            }
        }
        if (i == width - 1) {
            std::cout << "#############\n";
        }
    }
    return out;
}


bool Board::SetCellAt(int index, CellType type)
{
    if (index > cells.size() - 1 || index < 0) {
        std::cout << "Cell ini tidak ada!\n";
        return false;
    }
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
    int w = width;
    int h = height;
    int reqO, reqX;
    while (h--)
    {
        reqO = width;
        reqX = width;
        w = width;
        while (w--)
        {
            if (cells[(height - h - 1) * height + (width - w - 1)] == CellType::O) {
                reqO--;
            }
            else if (cells[(height - h - 1) * height + (width - w - 1)] == CellType::X) {
                reqX--;
            }
            if (reqO == 0) {
                return CellType::O;
            }
            else if (reqX == 0) {
                return CellType::X;
            }
        }
    }
    return CellType::empty;
}


CellType Board::CheckVertical()
{
    int w = width;
    int h = height;
    int reqO, reqX;
    while (h--)
    {
        reqO = height;
        reqX = height;
        w = width;
        while (w--)
        {
            if (cells[(height - h - 1) + (width - w - 1) * width] == CellType::O) {
                reqO--;
            }
            else if (cells[(height - h - 1) + (width - w - 1) * width] == CellType::X) {
                reqX--;
            }
            if (reqO == 0) {
                return CellType::O;
            }
            else if (reqX == 0) {
                return CellType::X;
            }
        }
    }
    return CellType::empty;
}


CellType Board::CheckDiagonal()
{
    int min = width > height ? height : width;
    if (width != height) {
        std::cout << "Warning! CekDiagonal() masih belum mendukung untuk nilai width dan height yang tidak sama. Akan return empty.";
        return CellType::empty;
    }
    int reqO, reqX;
    reqO = width > height ? height : width;
    reqX = width > height ? height : width;
    while (min--)
    {
        if (cells[(height - min - 1) + (width - min - 1)] == CellType::O) {
            reqO--;
        }
        else if (cells[(height - min - 1) + (width - min - 1)] == CellType::X) {
            reqX--;
        }
        if (reqO == 0) {
            return CellType::O;
        }
        else if (reqX == 0) {
            return CellType::X;
        }
    }
    min = width > height ? height : width;
    reqO = min;
    reqX = min;
    while (min--)
    {
        if (cells[2 * ((height - min - 1) + (width - min - 1))] == CellType::O) {
            reqO--;
        }
        else if (cells[2 * ((height - min - 1) + (width - min - 1))] == CellType::X) {
            reqX--;
        }
        if (reqO == 0) {
            return CellType::O;
        }
        else if (reqX == 0) {
            return CellType::X;
        }
    }
    return CellType::empty;
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
