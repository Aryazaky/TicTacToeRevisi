// TicTacToe2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"GameManager.h"

int main()
{
    std::cout << "Hello World!\n";
    GameManager tictactoe;
    tictactoe.ResetGame();
    //tictactoe.SetBoardSize(3, 3);
    //tictactoe.AddPlayers(2);
    tictactoe.LoadSaveFile();
    tictactoe.StartGame();
}

