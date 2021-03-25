#pragma once
#include<vector>
#include<string>
#include"Board.h"
#include"Player.h"
class GameManager
{
	std::vector<Player> player_list;
	Board board;
	int turn;
	GameState game_state;
	int turn_count;
	MatchState match_state;
	CellType winner;
public:
	GameManager();
	bool LoadGameFromTxt(std::string raw_text);
	bool SaveGameAsTxt();
	// Ngisi data player di dalam fungsi
	void AddPlayers(int count);
	// Jika ready to play, 
	void StartGame();
	// Menghapus list player dan cell di board
	void ResetGame();
	void SetBoardSize(int size);
private:
	CellType CheckWin();
	void RandomizeTurn();
	void GameLoop();
	// Menampilkan game ke console
	void DisplayGame();
	// Mengecek apakah board size > 0, player > 0, dan turncount == 0
	bool IsReadyToPlay();
	void NextTurn();
};

