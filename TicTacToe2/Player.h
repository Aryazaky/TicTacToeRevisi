#pragma once
#include<vector>
#include<string>
#include"MiscStuff.h"
class Player
{
	CellType cell_type;
	std::string name;
	struct MatchHistory
	{
		MatchState match_state;
		std::string opponent_name;
	};
public:
	std::vector<MatchHistory> history;
	// Return string yang sudah ditata biar bisa langsung dimasukkan ke fungsi display ke console
	std::string DisplayMatchHistory();
	Player(std::string _name, CellType _cell_type) {
		name = _name;
		cell_type = _cell_type;
	}
	std::string GetName();
};

