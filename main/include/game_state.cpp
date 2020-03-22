#include "stdafx.h"
#include "game_state.h"

GameState::GameState(CatanAi & parent): parent(parent)
{
	/*roads = unique_ptr<Roads>(new Roads(*this));
	buildings = unique_ptr<Buildings>(new Buildings(*this));
	players = unique_ptr<Players>(new Players(this));
	bank = unique_ptr<Bank>(new Bank(*this));*/

	roads = std::unique_ptr<Roads>(new Roads(*this));
	buildings = std::unique_ptr<Buildings>(new Buildings(*this));
	players = std::unique_ptr<Players>(new Players(this));
}

int GameState::GetCurrentPlayer() const
{
	return static_cast<int>(current_pID);
}

void GameState::LoadGameState(const Sample & s)
{
	players->LoadPlayers(s.players);
	roads->LoadRoads(s.roads);
	buildings->LoadBuildings(s.buildings);
	players->SetLargestArmyId(s.largest_army);
	players->SetLargestRoadId(s.longest_path);
	roads->UpdateRoadsLength();

	current_pID.SetPlayersCount(parent.getPlayersCount());
}

void GameState::nextTurn()
{
	++current_pID;
}

player_int & player_int::operator++()
{
	current_pID++;	
	if (current_pID == players_count)
		current_pID = 0;
	return *this;
}
