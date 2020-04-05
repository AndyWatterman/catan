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

const int CatanAi::getCurrentPlayerId() const
{
	return (game_state->GetCurrentPlayerId());
}

Player& CatanAi::getCurrentPlayer()
{
	return ((*game_state->players.get())[getCurrentPlayerId()]);
	//Player* p = &(*game_state->players)[getCurrentPlayerId()];
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
