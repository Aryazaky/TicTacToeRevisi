#pragma once
#include<vector>
#include<string>
#include"Board.h"
#include"Player.h"
#include<iostream>
#include<fstream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include<conio.h>
#include<random>
#include<algorithm>
#include<windows.h>

class GameManager
{
	int cursor;
	std::string filepath;

	struct GameData {
		std::vector<Player> player_list;
		Board board;
		int turn;
		GameState game_state;
		int turn_count;
		CellType winner;
	};
	GameData savedata;
	GameData G;
public:
	GameManager();
	void ProcessLine(std::string& line);
	void LoadSaveFile();
	// Ngisi data player di dalam fungsi
	void AddPlayers(int count);
	// Jika ready to play, bisa jalan
	void StartGame();
	// Menghapus list player dan cell di board
	void ResetGame();
	void SetBoardSize(int width, int height);
	// Mengubah filepath save/load file. Jika tidak dispesifikasikan nama file, defaultnya saves.txt
	void SetFilepath();
private:
	// Private karena auto save
	bool SaveGameAsTxt();
	bool LoadGameFromTxt(std::string raw_text);

	CellType CheckWin();
	void RandomizeTurn();

	void GameLoop();
	void AddMatchHistoryToAll();
	void PlayTurn();
	void AIControl(bool& done);
	void KeyboardControl(int& clicks, bool& done);

	// Menampilkan game ke console
	void DisplayGame();

	// Mengecek apakah board size > 0, player > 0, dan turncount == 0
	bool IsReadyToPlay();
	void NextTurn();

	CellType AssignCellType();
	MatchState GetMatchStateOf(Player player);
};
