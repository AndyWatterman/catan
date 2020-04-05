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
	bank = std::unique_ptr<Bank>(new Bank(this));
}

std::unique_ptr<std::vector<std::array<int, kResCount>>>
	GameState::CheckPossibilityOfBuyingOrBuilding(const std::array<int, kResCount>& cost, bool exchange_res, int pId)
{		
	if (pId < 0)
		pId = GetCurrentPlayerId();

	//check if we already have enough resources
	//substract all current resources and cost
	int need_resources = 0;
	std::array<int, kResCount> current_resouses = (*players)[pId].resources;
	for (int i = 0; i < kResCount; i++) {
		if ((current_resouses[i] -= cost[i]) < 0) {
			need_resources += current_resouses[i];
		}
	}

	//enough?	
	if (need_resources >= 0) {	
		std::unique_ptr<std::vector<std::array<int, kResCount>>> rest_resources(new std::vector<std::array<int, kResCount>>());
		rest_resources->push_back(current_resouses);						
		return rest_resources;
	}
	else {
		if (!exchange_res) {
			return nullptr;
		}
	}				

	/*------------========here we do not have enough resources, need to exchange======-----------*/

	//set maximum exchange price for each resource
	std::array<int, kResCount> harbors;
	unsigned bank_price = kMaxBankExchangePrice;
	harbors.fill(bank_price);

	//find all our harbors and decrease exchange price if we can
	auto player_buildings = buildings->GetAllBuildings(pId);
	auto board_harbors = parent.getHarborsRef();

	for (const auto& building_point : *player_buildings) {
		auto res = board_harbors[building_point->point];		//try to get port at the building place
		if (res == resource::tin1) {							//if it is 3:1 then decrease bank price for all resources
			bank_price = k3in1ExchangePrice;
		}
		else
			if (res != resource::non)
				harbors[static_cast<int>(res)] = kResourceHarborExchangePrice;		//if it is 2:1, then decrease specific price
	}

	//if we found 3:1 harbor
	if (bank_price != kMaxBankExchangePrice) {
		//change the price of exchange for all resources
		for (auto& harbor : harbors) {
			if (harbor == kMaxBankExchangePrice)
				harbor = bank_price;
		}
	}

	//now harbor array has the cost of exchanging for each resource

	std::array<int, kResCount> _resources;
	std::unique_ptr<std::vector<std::array<int, kResCount>>> pBuf1(new std::vector<std::array<int, kResCount>>());
	std::unique_ptr<std::vector<std::array<int, kResCount>>> pBuf2(new std::vector<std::array<int, kResCount>>({ current_resouses }));

	do {		
		swap(pBuf1, pBuf2);
		pBuf2->clear();

		for (const auto& ress : *pBuf1) {
			//переберем все ресурсы
			for (int i = 0; i < kResCount; i++) {
				//найдем ресурс, которого не хватает
				if (ress[i] < 0) {
					//снова переберем все ресурсы
					for (int j = 0; j < kResCount; j++) {
						//если это не нехватающий ресурс
						if (i != j) {
							//если можем ресурс поменять
							if (ress[j] >= harbors[j]) {
								_resources = ress;
								_resources[j] -= harbors[j];		//вычтем ресурсы для обмена
								_resources[i]++;					//добавим 1-н недостающий ресурс								
								pBuf2->push_back(_resources);		//сохраним
							}
						}
					}
				}
			}
		}
	} while (pBuf2->size() != 0);

	//удалим неизбежные повторы
	std::sort(pBuf1->begin(), pBuf1->end());
	pBuf1->erase(unique(pBuf1->begin(), pBuf1->end()), pBuf1->end());

	return pBuf1;
}

unsigned GameState::howManyResourcesWeCanGetUsingPort(const std::array<int, kResCount>& cost, int pId)
{
	unsigned result = 0;

	if (pId < 0)
		pId = GetCurrentPlayerId();

	//set maximum exchange price for each resource
	std::array<int, kResCount> harbors;
	unsigned bank_price = kMaxBankExchangePrice;
	harbors.fill(bank_price);

	//find all our harbors and decrease exchange price if we can
	auto player_buildings = buildings->GetAllBuildings(pId);
	auto board_harbors = parent.getHarborsRef();

	for (const auto& building_point : *player_buildings) {
		auto res = board_harbors[building_point->point];		//try to get port at the building place
		if (res == resource::tin1) {							//if it is 3:1 then decrease bank price for all resources
			bank_price = k3in1ExchangePrice;
		}
		else
			if (res != resource::non)
				harbors[static_cast<int>(res)] = kResourceHarborExchangePrice;		//if it is 2:1, then decrease specific price
	}

	//if we found 3:1 harbor
	if (bank_price != kMaxBankExchangePrice) {
		//change the price of exchange for all resources
		for (auto& harbor : harbors) {
			if (harbor == kMaxBankExchangePrice)
				harbor = bank_price;
		}
	}

	//now we have cost of exchanging each resource
	for (auto i = 0; i < kResCount; i++) {
		result += cost[i] / harbors[i];

		//prevent spending more resources
		if (cost[i] % harbors[i] != 0)
			return 0;
	}

	return result;
}

bool GameState::checkIfExchangeWasSuccessfull(const std::array<int, kResCount>& cost)
{
	for (const auto& res : cost) {
		if (res < 0)
			return false;
	}
	return true;
}

int GameState::GetCurrentPlayerId() const
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

	bank->UpdateResources();
	bank->UpdateCards();
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
