#pragma once

#include "header.h"
#include "game_state.h"

class Bank {
private:
	GameState* pGameState;

	//wood, brick, sheep, weat, stone
	std::array<int, kResCount> resources;	//сколько карточек ресурсов осталось в банке

	//knight, monopoly, roads, twoRes, winPoint
	std::array<int, kCardCount> cards;		//сколько карт развития осталось в банкe

public:
	Bank(GameState* parent);

	void SetNewGameState(GameState* _pGameState) {
		pGameState = _pGameState;
	};

	int UpdateResources();
	void UpdateCards();

	//int GetCardsCount(card _card);
	//void DrawCard(card _card);
};