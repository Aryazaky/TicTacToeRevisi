#pragma once
enum class CellType {
	empty,
	X,
	O
};
enum class MatchState {
	none,
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