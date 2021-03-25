#include "GameManager.h"
#include<iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

GameManager::GameManager()
{
    srand(time(NULL));
    game_state = GameState::idle;
    match_state = MatchState::none;
    winner = CellType::empty;
    turn = -1;
    turn_count = 0;
}

bool GameManager::LoadGameFromTxt(std::string raw_text)
{
    // TODO: Add your implementation code here.
    return false;
}


bool GameManager::SaveGameAsTxt()
{
    // TODO: Add your implementation code here.
    return false;
}


// Ngisi data player di dalam fungsi
void GameManager::AddPlayers(int count)
{
    // TODO: Add your implementation code here.
}

// Mengacak isi vector. Index vector = turn
void GameManager::RandomizeTurn()
{
    turn = rand() % player_list.size();
}


// Kalau siap main, bisa jalan
void GameManager::StartGame()
{
    IsReadyToPlay();
    if (game_state==GameState::ready) {
        GameLoop();
    }
    else
    {
        std::cout << "Game belum siap atau sedang berlangsung!\n";
    }
}


void GameManager::GameLoop()
{
    game_state = GameState::playing;
    while (match_state==MatchState::none)
    {
        // 
        // TODO: Add your implementation code here.
    }
}


CellType GameManager::CheckWin()
{
    // TODO: Add your implementation code here.
    return CellType();
}


// Menampilkan game ke console
void GameManager::DisplayGame()
{
    // TODO: Add your implementation code here.
}


// Menghapus list player dan cell di board
void GameManager::ResetGame()
{
    board.ClearCells();
    turn_count = 0;
}


void GameManager::SetBoardSize(int size)
{
    if (game_state==GameState::playing || game_state==GameState::finished) {
        std::cout << "Tidak bisa merubah setting ketika permainan sedang berlangsung!\n";
    }
    else
    {
        board.ClearCells();
        board.GenerateEmptyCells(size);
    }
}


// Mengecek apakah board size > 0, player > 0, dan turncount == 0
bool GameManager::IsReadyToPlay()
{
    if (board.Size() > 0 && player_list.size() > 0 && turn_count == 0) {
        return true;
    }
    return false;
}


void GameManager::NextTurn()
{
    turn += 1;
    turn %= player_list.size();
}
