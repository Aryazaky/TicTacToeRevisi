#pragma once
#include<string>
enum class CellType {
	empty,
	X,
	O,
	draw
};
enum class MatchState {
	empty,
    draw,
	win,
	lose
};
enum class GameState {
	idle,
	ready,
	playing,
	finished
};

