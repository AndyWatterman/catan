#pragma once

#include "header.h"

struct Building {
	int point, id;
	building_types type;	//вид (поселение/город)	
};

class Buildings {
private:
	GameState *pGameState;

	std::vector <Building> buildings;
public:
	Buildings(GameState &parent);
	Buildings() = default;

	void AddSettelement(int point, int id);
	void DeleteSettelement(int point);
	void DisplayBuildings(int id = -1);
	int IsBuildingExists(int point) const;
	bool IsThereBuildingsAround(int point) const;
	building_types GetBuildingType(int point) const;
	std::tuple<int, int> GetFirstTwoBuildings(int id) const;

	std::unique_ptr<std::vector<Building*>> GetAllBuildings(int id = -1);

	Building* getBuilding(int point);

	void LoadBuildings(const std::vector <Building> & _buildings);
	void UpdateBuildingsScore();
	void UpgradeBuilding(int point);

	//нужно для for...each
	/*---===Iterators===---*/
	typedef typename std::vector<Building>::iterator iterator;
	typedef typename std::vector<Building>::const_iterator const_iterator;
	iterator begin() { return buildings.begin(); }
	const_iterator begin() const { return buildings.begin(); }
	const_iterator cbegin() const { return buildings.cbegin(); }
	iterator end() { return buildings.end(); }
	const_iterator end() const { return buildings.end(); }
	const_iterator cend() const { return buildings.cend(); }

	//Overloading
	Building& operator[] (size_t index);					//чтобы работать как с массивом []
	const Building& operator[] (size_t index) const;		//чтобы работать как с массивом []	
};