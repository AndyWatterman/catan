#pragma once

#include "header.h"

struct Road {
	int from, to, id;
};

class Roads {
private:
	const GameState *pGameState;
	std::vector<Road> roads;

	//void UpdateRoadsCount();
public:
	Roads(GameState &parent);

	void AddRoad(int from, int to, int id);
	void AddRoad(const Road & road);
	void DeleteRoad(int from, int to);
	void DisplayRoads(int id = -1);

	const std::vector<int> GetAdjascentPoints(int point, int pID = -1) const;
	int GetTheLongestRoad(int id = -1);
	int IsRoadExists(int from, int to) const;
	bool IsRoadPointExists(int point) const;
	Road* getRoad(int from, int to);
	void LoadRoads(const std::vector<Road> & _roads);
	void UpdateRoadsLength();	//update all roads
	void UpdateSpecificRoadLength(int id);	//update specific player road
	void UpdateRoadsCount();	//update used roads count

	//нужно для for...each
	/*---===Iterators===---*/
	typedef typename std::vector<Road>::iterator iterator;
	typedef typename std::vector<Road>::const_iterator const_iterator;
	iterator begin() { return roads.begin(); }
	const_iterator begin() const { return roads.begin(); }
	const_iterator cbegin() const { return roads.cbegin(); }
	iterator end() { return roads.end(); }
	const_iterator end() const { return roads.end(); }
	const_iterator cend() const { return roads.cend(); }
};

class DFSTracePathPoints {
private:
	std::tuple<int, int> firstTwoBuildings;

protected:
	const GameState &pGameState;
	const Roads &roads;
	const Buildings &buildings;

	int pID;
	std::vector<int> stack;
	std::vector<Road> new_roads;
	std::set<int> extreme_points;
	bool buildings_connected = false;

	template <class T>
	void PrintPathPoints(T &pSet) const;

public:
	DFSTracePathPoints(const GameState &parent, int _pID = -1);
	virtual ~DFSTracePathPoints() {};
	DFSTracePathPoints() = default;

	int GetAllPathPoints();
	int GetExtremePoints();
	bool IsItPossibleToBuildRoad(int from, int to);
	//vector<int>* GetAllFreeForBuildingPoints(int _pID = -1);
	//vector<Road>* GetAllPossibleNewRoads(int _pID = -1);

	void PrintAllPathPoints() const;
	void PrintExtremePoints() const;

	std::set<int> all_path_points;
};

class DFSSearchLongPath : private DFSTracePathPoints {
private:
	int max_path = 0;
	int GetLongestPathNoRecursive(int start_point);

public:
	DFSSearchLongPath(const GameState &parent, int _pID = -1);
	DFSSearchLongPath() = default;

	int GetLongestPath();

	operator int() const {
		return (max_path);
	}
};