#pragma once
enum class CellType {
	empty,
	X,
	O,
	draw
};
enum class MatchState {
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
