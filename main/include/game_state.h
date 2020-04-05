#pragma once

#include "catan_ai.h"
#include "roads.h"
#include "buildings.h"
#include "players.h"


struct Sample {
	int robber, largest_army, longest_path;
	std::vector<Building> buildings;
	std::vector<Road> roads;
	std::vector<_Player> players;	
};

class player_int {
private:
	int current_pID = 0;		//сначала всегда ходит player 0
	int players_count = -1;

public:
	player_int(int players_count) : players_count(players_count) {};

	void SetPlayersCount(int _players_count) {
		players_count = _players_count;
	}

	//copy assigment
	player_int& operator=(const int& p) // copy assignment
	{
		current_pID = p;
		return *this;
	};

	player_int& operator=(const player_int& pc) // copy assignment
	{
		current_pID = pc.current_pID;
		players_count = pc.players_count;
		return *this;
	};

	//static_cast<int>
	operator int() const {
		return (current_pID);
	}

	// prefix ++
	player_int& operator++ ();
};

class GameState {
private:
	player_int current_pID = 0;

public:
	GameState(CatanAi &parent);
	GameState() = delete;

	void LoadGameState(const Sample& s);

	CatanAi &parent;

	std::unique_ptr<Roads> roads;
	std::unique_ptr<Buildings> buildings;
	std::unique_ptr<Players> players;
	std::unique_ptr<Bank> bank;

	//all variants how we can spend cost
	std::unique_ptr<std::vector<std::array<int, kResCount>>> CheckPossibilityOfBuyingOrBuilding(const std::array<int, kResCount>& cost, bool exchange_res = false, int pId = -1);

	//how many resources we can get paying cost
	unsigned howManyResourcesWeCanGetUsingPort(const std::array<int, kResCount>& cost, int pId = -1);
	bool checkIfExchangeWasSuccessfull(const std::array<int, kResCount>& cost);

	int GetCurrentPlayerId() const;	
	void nextTurn();
};