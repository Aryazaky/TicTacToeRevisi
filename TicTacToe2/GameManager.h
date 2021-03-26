#pragma once
#include<vector>
#include<string>
#include"Board.h"
#include"Player.h"
#include<iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include<conio.h>
#include<random>
#include<algorithm>

class GameManager
{
	std::vector<Player> player_list;
	Board board;
	int turn;
	GameState game_state;
	int turn_count;
	CellType winner;
	int cursor;
public:
	GameManager();
	bool LoadGameFromTxt(std::string raw_text);
	// Ngisi data player di dalam fungsi
	void AddPlayers(int count);
	// Jika ready to play, bisa jalan
	void StartGame();
	// Menghapus list player dan cell di board
	void ResetGame();
	void SetBoardSize(int width, int height);
private:
	bool SaveGameAsTxt();
	CellType CheckWin();
	void RandomizeTurn();
	void GameLoop();
	// Menampilkan game ke console
	void DisplayGame();
	// Mengecek apakah board size > 0, player > 0, dan turncount == 0
	bool IsReadyToPlay();
	void NextTurn();
	CellType AssignCellType();
	MatchState GetMatchStateOf(Player player);
};
