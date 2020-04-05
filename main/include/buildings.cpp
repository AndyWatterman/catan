#include "stdafx.h"
#include "buildings.h"
#include "roads.h"
#include "players.h"
#include "game_state.h"
//#include "catan.h"

Buildings::Buildings(GameState & parent) : pGameState(&parent)
{

}

void Buildings::AddSettelement(int point, int id)
{	
	auto& currentPlayer = (*pGameState->players)[id];
	if (currentPlayer.GetSettelmentsLeft() > 0) {
		buildings.push_back(Building({ point, id, building_types::settelment }));
		currentPlayer.AddSettelment();	//Update settelement
		(*pGameState->roads).UpdateRoadsLength();	//need to update roads, cuz it might be broken
	}
}

void Buildings::DeleteSettelement(int point)
{	
	for (auto it = buildings.begin(); it != buildings.end(); ++it) {
		if (it->point == point) {
			if (it->type == building_types::settelment) {
				(*pGameState->players)[it->id].DeleteSettelment();
			}
			else {
				(*pGameState->players)[it->id].DeleteCity();
			}
			buildings.erase(it);
			break;
		}
	}
}

void Buildings::DisplayBuildings(int id)
{
	for (size_t  i = 0; i < buildings.size(); i++) {
		if ((id == -1) || (buildings[i].id == id))
			std::cout << i << ": point = " << buildings[i].point << ", type = " << static_cast<int>(buildings[i].type) << ", id = " << buildings[i].id << std::endl;
	}
}

int Buildings::IsBuildingExists(int point) const
{
	for (const auto &building : buildings) {
		if (building.point == point) {
			return (building.id);
		}
	}
	return (-1);
}

bool Buildings::IsThereBuildingsAround(int point) const
{
	bool result = false;

	//if (IsBuildingExists(point) < 0) {
		//check points around
		const std::vector<node>& nodes = pGameState->parent.getNodesRef();
		for (const auto& adj_point : nodes[point]) {
			if (IsBuildingExists(adj_point) >= 0) {
				result = true;
				break;
			}
		}
	//}
	//else {
		//result = true;
	//}

	return result;
}

building_types Buildings::GetBuildingType(int point) const
{
	for (const auto &building : buildings) {
		if (building.point == point) {
			return (building.type);
		}
	}
	return (building_types::none);
}

std::tuple<int, int> Buildings::GetFirstTwoBuildings(int id) const
{
	std::tuple<int, int> temp{ -1, -1 };

	for (const auto &building : buildings) {
		if (building.id == id) {
			if (std::get<0>(temp) < 0) {
				std::get<0>(temp) = building.point;
			}
			else {
				std::get<1>(temp) = building.point;
				break;
			}
		}
	}

	return temp;
}

std::unique_ptr<std::vector<Building*>> Buildings::GetAllBuildings(int id)
{
	if (id < 0)
		id = pGameState->GetCurrentPlayerId();
	
	std::unique_ptr<std::vector<Building*>> arr(new std::vector<Building*>());
	for (auto& building : buildings) {	
		if (building.id == id) {			
			arr->push_back(&building);
		}
	}

	return arr;
}

Building * Buildings::getBuilding(int point)
{
	for (auto &building : buildings) {
		if (building.point == point) {
			return (&building);
		}
	}
	return nullptr;
}

void Buildings::LoadBuildings(const std::vector<Building>& _buildings)
{
	buildings = _buildings;
	//remaining_cities.resize(Catan::GetPlayersCount(), kMaxCities);
	//remaining_cities.resize(pGameState->parent.GetPlayersCount(), kMaxCities);
	//remaining_settelments.resize(pGameState->parent.GetPlayersCount(), kMaxSettelments);
	UpdateBuildingsScore();
}

void Buildings::UpgradeBuilding(int point)
{
	if (IsBuildingExists(point) >= 0) {
		Building& building = (*pGameState->buildings)[point];
		auto& currentPlayer = (*pGameState->players)[building.id];

		if (currentPlayer.GetCitiesLeft() > 0) {
			building.type = building_types::city;
			currentPlayer.AddCity();
		}
	}
}

void Buildings::UpdateBuildingsScore()
{
	for (size_t  i = 0; i < buildings.size(); i++) {
		if (buildings[i].type == building_types::settelment) {
			(*pGameState->players)[buildings[i].id].AddSettelment();	//Update settelments
		}
		else {
			(*pGameState->players)[buildings[i].id].AddCity(false);	//Update cities
		}

	}
}

Building & Buildings::operator[](size_t index)
{
	for (size_t i = 0; i < buildings.size(); i++) {
		if (buildings[i].point == index)
			return buildings[i];
	}
	exit(-1);
	/*just to handle a warning*/
	return (*(new Building()));
}

const Building & Buildings::operator[](size_t index) const
{
	for (size_t i = 0; i < buildings.size(); i++) {
		if (buildings[i].point == index)
			return buildings[i];
	}
	exit(-1);
	/*just to handle a warning*/
	return (*(new Building()));
}
