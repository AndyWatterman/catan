#include "stdafx.h"
#include "players.h"

int Player::GetTotalCardCount(devCard card) const
{	
	return (cards[static_cast<int>(card)] + active_cards[static_cast<int>(card)] + used_cards[static_cast<int>(card)]);
}

/*int Player::GetTotalCardsCount() const
{
	int total_cards = 0;
	for (int i = 0; i < kCardCount; i++) {
		total_cards += cards[i] + active_cards[i] + used_cards[i];
	}
	return 0;
}*/

int Player::GetMaxRoadLength() const
{
	return (max_road_length);	
}

void Player::SetMaxRoadLength(int max)
{
	max_road_length = max;
}

void Player::AddCity(bool decSettelment)
{
	cities_used++;
	if (decSettelment)
		settlements_used--;
}

void Player::DeleteCity()
{
	cities_used--;
}

//Only add 1 used road, no building
void Player::AddRoad()
{	
	roads_used++;
}

void Player::DeleteRoad()
{
	roads_used--;
}

//Only add 1 used settelment, no building
void Player::AddSettelment()
{
	settlements_used++;
}

void Player::DeleteSettelment()
{
	settlements_used--;
}

void Player::ActivateDevCards()
{
	for (int i = 0; i < kCardCount; i++) {
		active_cards[i] += cards[i];
		cards[i] = 0;
	}
}

void Player::UseDevCard(devCard card)
{
	active_cards[static_cast<int>(card)]--;
	used_cards[static_cast<int>(card)]++;
	dev_card_has_been_played = true;
}

void Player::RestoreDevCard()
{
	dev_card_has_been_played = false;
}

int Players::GetPlayerScore(int id, bool addWinningScore = false) const
{
	int score = players[id].GetBuildingScore();
	if (GetLargestArmyId() == id) { score += kLargestArmyBonus; };
	if (GetLargestRoadId() == id) { score += kLongestRoadBonus; };
	if (addWinningScore) {
		//winPoints are always active, so we need to add only active cards
		score += players[id].GetActiveCard(devCard::winPoint);
	}
	return (score);
}

void Players::LoadPlayers(const std::vector<_Player>& _players)
{
	for (auto i = 0; i < _players.size(); i++) {
		Player p(i);
		(_Player&)p = _players[i];
		players.push_back(p);
	}	
}

Player & Players::operator[](size_t index)
{
	return players[index];
}

const Player & Players::operator[](size_t index) const
{
	return players[index];
}