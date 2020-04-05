#pragma once

#include "header.h"

struct _Player {
	std::array<int, kResCount> resources;		//player's resources
	std::array<int, kCardCount> cards;			//development cards on hand
	std::array<int, kCardCount> active_cards;	//active dev cards (ready to use)
	std::array<int, kCardCount> used_cards;		//used dev cards
	bool dev_card_has_been_played = false;		//have we played dev card this turn?
};

class Player : public _Player {
private:
	int max_road_length = 0,				//max road length		
		roads_used = 0,
		settlements_used = 0,
		cities_used = 0;

public:
	explicit Player(int _pID) : id(_pID) {};
	//explicit Player(Player& p) : id(p.id) {};	

	Player() = delete;
	~Player() = default;

	const int id;							//player id
	
	unsigned GetResourceCount(resource res) const{ return (resources[static_cast<int>(res)]); };
	int GetTotalResourceCount() const { return (std::accumulate(std::begin(resources), std::end(resources), 0)); };	

	int GetActiveCard(devCard card) const { return (active_cards[static_cast<int>(card)]); };	//cards are ready to use
	int GetUsedCard(devCard card) const { return (used_cards[static_cast<int>(card)]); };		//used dev card
	int GetCards(devCard card) const { return (cards[static_cast<int>(card)]); };				//already bought, but not ready to use (this turn)
	int GetAllClosedDevCardsCount() const { return (std::accumulate(std::begin(cards), std::end(cards), 0)
		+ std::accumulate(std::begin(active_cards), std::end(active_cards), 0)); };				//count of all not played cards
	
	int GetTotalCardCount(devCard card) const;		//specific card
	//int GetTotalCardsCount() const;					//all cards

	int GetBuildingScore() const 
		{ return (settlements_used * kSettelmentScore + cities_used * kCityScore); };
	int GetMaxRoadLength() const;
	void SetMaxRoadLength(int max);

	int GetRoadsLeft() const { return (kMaxRoads - roads_used); };
	void AddRoad();
	void DeleteRoad();

	int GetSettelmentsLeft() const { return (kMaxSettelments - settlements_used); };
	void AddSettelment();
	void DeleteSettelment();

	int GetCitiesLeft() const { return (kMaxCities - cities_used); };	
	void AddCity(bool decSettelment = true);
	void DeleteCity();	

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
	int GetPlayerScore(int id, bool addWinningScore) const;			//addWinningScore if TRUE then we add hidden player cards

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