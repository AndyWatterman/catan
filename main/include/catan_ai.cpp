#include "stdafx.h"
#include "catan_ai.h"

#include "TestSample.h"

CatanAi::CatanAi(::_Board & b): AiGameBoard(b)
{
	game_state = std::unique_ptr<GameState>(new GameState(*this));
	game_state->LoadGameState(TestSample);
}

const int CatanAi::getPlayersCount() const
{	
	return (game_state->players->GetPlayersCount());
}

const int CatanAi::getCurrentPlayer() const
{
	return (game_state->GetCurrentPlayer());
}

/*Building * CatanAi::getBuilding(int point) const
{
	return (game_state->buildings->getBuilding(point));
}*/

void CatanAi::nextTurn()
{
	if (getPlayersCount()) {
		game_state->nextTurn();
	}
}
