#pragma once

#include "header.h"

struct _Player {
	std::array<int, kResCount> resources;		//player's resources
	std::array<int, kCardCount> cards;			//development cards on hand
	std::array<int, kCardCount> active_cards;	//active dev cards
	std::array<int, kCardCount> used_cards;		//used dev cards
	bool dev_card_has_been_played = false;	//have we played dev card this turn?
};

class Player : private _Player {
private:
	int max_road_length = 0,				//max road length		
		roads_used = 0,
		settlements_used = 0,
		cities_used = 0;

public:
	Player(int _pID) : id(_pID) {};	

	const int id;							//player id
	
	int GetResourceCount(resource res) const{ return (resources[res]); };

	int GetActiveCard(devCard card) const { return (active_cards[card]); };
	int GetCards(devCard card) const { return (cards[card]); };	//already bought, but not ready to use
	int GetTotalCardCount(devCard card) const;
	int GetTotalCardsCount() const;
	int GetUsedCard(devCard card) const { return (used_cards[card]); };

	int GetBuildingScore() const 
		{ return (settlements_used * kSettelmentScore + cities_used * kCityScore); };
	int GetCitiesLeft() const { return (kMaxCities - cities_used); };
	int GetMaxRoadLength() const;
	int GetRoadsLeft() const { return (kMaxRoads - roads_used); };
	int GetSettelmentsLeft() const { return (kMaxSettelments - settlements_used); };

	void SetMaxRoadLength(int max);
	void AddCity(bool decSettelment = true);
	void AddRoad();
	void AddSettelment();

	void ActivateDevCards();
	void UseDevCard(devCard card);	
	void RestoreDevCard();
};

class Players {
private:
	const GameState *pGameState;
	std::vector <Player> players;

	int largest_army_id = -1,
		longest_road_id = -1;
		//current_player_id = 0;

public:
	Players(GameState *parent) : pGameState(parent) {};

	//TODO: add function void AddPlayer(_Player &p);	

	//int GetCurrentPlayer() const { return (current_player_id); };
	int GetLargestArmyId() const { return (largest_army_id); };
	int GetLargestRoadId() const { return (longest_road_id); };
	int GetPlayersCount() const { return (static_cast<int>(players.size())); };
	int GetPlayerScore(int id) const;

	void LoadPlayers(const std::vector <_Player> & _players);
	void SetLargestArmyId(int id) { largest_army_id = id; };
	void SetLargestRoadId(int id) { longest_road_id = id; };

	//Overloading
	Player& operator[] (size_t index);					//чтобы работать как с массивом []
	const Player& operator[] (size_t index) const;		//чтобы работать как с массивом []	

	//нужно для for...each
	/*---===Iterators===---*/
	typedef typename std::vector<Player>::iterator iterator;
	typedef typename std::vector<Player>::const_iterator const_iterator;
	iterator begin() { return players.begin(); }
	const_iterator begin() const { return players.begin(); }
	const_iterator cbegin() const { return players.cbegin(); }
	iterator end() { return players.end(); }
	const_iterator end() const { return players.end(); }
	const_iterator cend() const { return players.cend(); }
};