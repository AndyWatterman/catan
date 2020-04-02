#pragma once

//#include "CatanGUI.h"
#include "game_board.h"
#include "game_state.h"
#include "buildings.h"
#include "players.h"
//#include "header.h"

class CatanAi : public AiGameBoard {
private:
	//unsigned int players_count;

	//GameState* initial_game_state;	

public:
	//CatanAi(int players_count);
	CatanAi(::_Board & b);
	//CatanAi() = default;

	std::unique_ptr<GameState> game_state;

	const int getPlayersCount() const;
	const int getCurrentPlayerId() const;
	Player* getCurrentPlayer();

	void nextTurn();
};
