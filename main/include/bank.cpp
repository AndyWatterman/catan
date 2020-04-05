#include "stdafx.h"
#include "bank.h"

Bank::Bank(GameState* parent) : 
	pGameState(parent), resources{kMaxBankResources}, cards (max_dev_cards)
{

}

int Bank::UpdateResources()
{
	int res;
	Players* players = pGameState->players.get();
	for (int i = 0; i < kResCount; i++)
	{
		res = 0;
		for (auto& player : *players) {
			res += player.GetResourceCount(static_cast<resource>(i));
		}		
		resources[i] = kMaxBankResources - res;

		//case if not enougth resources. need it? dont' know now
		if ((res = resources[i]) < 0) {
			break;
		}
	}
	return res;
}

void Bank::UpdateCards()
{
	int _cards;
	Players* players = pGameState->players.get();
	for (int i = 0; i < kCardCount; i++)
	{
		_cards = 0;
		for (auto& player : *players) {
			_cards += player.GetTotalCardCount(static_cast<devCard>(i));
		}
		cards[i] = max_dev_cards[i] - _cards;
	}
}
