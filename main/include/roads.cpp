#include "stdafx.h"
#include "roads.h"
#include "buildings.h"
#include "players.h"
#include "game_state.h"

Roads::Roads(GameState & parent) : pGameState(&parent)
{

}

void Roads::AddRoad(int from, int to, int id)
{
	roads.push_back(Road({ from, to, id }));
	(*pGameState->players)[id].AddRoad();
	UpdateSpecificRoadLength(id);
}

void Roads::AddRoad(const Road & road)
{
	roads.push_back(road);
	(*pGameState->players)[road.id].AddRoad();	
	UpdateSpecificRoadLength(road.id);
}

void Roads::DeleteRoad(int from, int to)
{
	for (auto it = roads.begin(); it != roads.end(); it++) {
		if (((it->from == from) || (it->from == to)) && ((it->to == from) || (it->to == to))) {
			int pId = it->id;
			roads.erase(it);
			//UpdateSpecificRoadLength(pId);
			UpdateRoadsLength();
			break;
		}
	}
}

void Roads::DisplayRoads(int id)
{
	for (size_t i = 0; i < roads.size(); i++) {
		if ((id == -1) || (id == roads[i].id)) {
			std::cout << i << ": (" << roads[i].from << ", " << roads[i].to << "), ID = " << roads[i].id << std::endl;
		}
	}
}

//ѕолучение всех точек тракта определЄнного игрока
int DFSTracePathPoints::GetAllPathPoints()
{
	for (const auto &road : roads) {
		if (road.id == pID) {
			all_path_points.insert(road.from);
			all_path_points.insert(road.to);
		}
	}
	return static_cast<int>(all_path_points.size());
}

//—тандртный конструктор
DFSTracePathPoints::DFSTracePathPoints(const GameState & parent, int _pID) :
	pGameState(parent), roads(*pGameState.roads), buildings(*pGameState.buildings)
{
	if (_pID < 0) {
		pID = pGameState.GetCurrentPlayer();
	}
	else {
		pID = _pID;
	}
	GetAllPathPoints();
	//pID = _pID;
	//GetExtremePoints();
}

int Roads::GetTheLongestRoad(int id)
{
	DFSSearchLongPath path(*pGameState, id);
	//cout << "MAX_PATH: " << path << endl;
	//(*pGameState->players)[id].SetMaxRoadLength(path);
	return path;	
}

int Roads::IsRoadExists(int from, int to) const
{
	for (const auto& road : roads) {
		if (((road.from == from) && (road.to == to))
			|| ((road.from == to) && (road.to == from))) {
			return (road.id);
		}
	}

	return (-1);
}

bool Roads::IsRoadPointExists(int point) const
{
	DFSTracePathPoints AllPathPoints(*pGameState);

	for (auto& p : AllPathPoints.all_path_points) {
		if (p == point) {
			return (true);
		}
	};
	return false;
}

Road* Roads::getRoad(int from, int to)
{
	for (auto& road : roads) {
		if (((road.from == from) && (road.to == to)) 
			|| ((road.from == to) && (road.to == from))) {
			return (&road);
		}
	}
	return nullptr;
}

DFSSearchLongPath::DFSSearchLongPath(const GameState & parent, int _pID) :
	DFSTracePathPoints(parent, _pID)
{
	if (extreme_points.size() == 0)
		GetExtremePoints();
	GetLongestPath();
}

//ѕолучает точки, св¤занные с point, учитыва¤ наличие дорог у игрока
const std::vector<int> Roads::GetAdjascentPoints(int point, int pID) const
{
	std::vector<int> temp;

	for (const auto &road : roads) {
		if (road.id == pID) {
			if (road.from == point) {
				temp.push_back(road.to);
			}
			else {
				if (road.to == point) {
					temp.push_back(road.from);
				}
			}
		}
	}

	return(temp);
}

//ѕолучаем все возможные точки дл¤ построени¤ самого длинного тракта, а именно
//перекрЄстки трЄх дорог или конечные дороги
int DFSTracePathPoints::GetExtremePoints()
{
	std::vector<int> adj_roads;
	for (const auto &point : all_path_points) {
		adj_roads = roads.GetAdjascentPoints(point, pID);

		int b = buildings.IsBuildingExists(point);
		//если это перекресток 3-х дорог или конец дороги, или дорога рабита строением другого игрока
		if ((adj_roads.size() != 2) || ((b >= 0) && (b != pID)))
			extreme_points.insert(point);	//...добавим		
	}

	//случай сомкнутых дорог
	firstTwoBuildings = buildings.GetFirstTwoBuildings(pID);
	//перва¤ дорога в любом случае на первом поселении
	extreme_points.insert(std::get<0>(firstTwoBuildings));

	int second_building = std::get<1>(firstTwoBuildings);
	if (second_building >= 0) {
		extreme_points.insert(second_building);
	}

	return 0;
}

bool DFSTracePathPoints::IsItPossibleToBuildRoad(int from, int to)
{
	if (roads.IsRoadExists(from, to) >= 0)
		return (false);	

	for (const auto& point : all_path_points) {
		if ((point == from) || (point == to)) {

			//we can not build road from the point with enemy set/city		
			int buildingId = buildings.IsBuildingExists(point);
			//if ((buildingId >= 0) && (buildingId != pGameState.GetCurrentPlayer())) {
			if ((buildingId >= 0) && (buildingId != pID)) {
				//std::cout << "Current player: " << pGameState.players->GetCurrentPlayer() << std::endl;
				continue;
			}
			else {
				return true;
			}
		}
	}
	return false;
}

void Roads::LoadRoads(const std::vector<Road> & _roads)
{
	roads = _roads;

	//remaining_roads.resize(pGameState->parent.GetPlayersCount(), kMaxRoads);
	UpdateRoadsCount();
}

//TODO: what if equal?!

void Roads::UpdateRoadsLength()
{	
	//(*pGameState->players).SetLargestRoadId(-1);

	/*int lrid = (*pGameState->players).GetLargestRoadId();
	if (lrid != -1) {
		int temp_path = GetTheLongestRoad(lrid);
		if (temp_path < kMinLongestPath) {
			(*pGameState->players).SetLargestRoadId(-1);
		}
	}

	for (int i = 0; i < pGameState->players->GetPlayersCount(); i++) {
		if (i == lrid) {
			continue;
		}
		UpdateSpecificRoadLength(i);
	}*/	

	//Do we need to update owner of L.R?
	int lrid = (*pGameState->players).GetLargestRoadId();	
	//int temp_path = -1;
	if (lrid != -1) {
		int temp_path = GetTheLongestRoad(lrid);
		(*pGameState->players)[lrid].SetMaxRoadLength(temp_path);

		if (temp_path < kMinLongestPath) {
			(*pGameState->players).SetLargestRoadId(-1);
		}
	}

	for (int i = 0; i < pGameState->players->GetPlayersCount(); i++) {
		if (i != lrid)
			UpdateSpecificRoadLength(i);
	}
}

//Use only when player "id" ADD new road!!!
void Roads::UpdateSpecificRoadLength(int id)
{	
	int temp_path = GetTheLongestRoad(id);
	(*pGameState->players)[id].SetMaxRoadLength(temp_path);

	if (temp_path >= kMinLongestPath) {
		int lrid = (*pGameState->players).GetLargestRoadId();
		if ((lrid == -1) || ((*pGameState->players)[lrid].GetMaxRoadLength() < temp_path)) {
			(*pGameState->players).SetLargestRoadId(id);
		}
	}
}

template<class T>
void DFSTracePathPoints::PrintPathPoints(T & pSet) const
{
	for (const auto &i : pSet)
		std::cout << i << " ";
	std::cout << std::endl;
}

void DFSTracePathPoints::PrintExtremePoints() const
{
	PrintPathPoints(extreme_points);
}

void DFSTracePathPoints::PrintAllPathPoints() const
{
	PrintPathPoints(all_path_points);
}

int DFSSearchLongPath::GetLongestPathNoRecursive(int start_point) {

	//это чтобы супер длинные пути провер¤ть
#ifdef DEBUG
	std::array<int, 40> current_path, next_points_size, next_points;
#else	
	std::array<int, 16> current_path, next_points_size;
	std::array<int, 36> next_points;
#endif

	current_path.fill(0);
	next_points.fill(0);
	next_points_size.fill(0);

	int cp, nps, np, current_point, new_point, _max_path, owner;
	cp = nps = np = -1;
	_max_path = 0;

	//добавим первую точку
	next_points[++np] = start_point;
	next_points_size[++nps] = 1;

	do {
		//если на текущий уровень можем добавить элемент
		if (next_points_size[nps] > 0) {
			//возьмем 1-н элемент и добавим на текущий уровень
			current_point = current_path[nps] = next_points[np--];
			//уменьшим кол-во доступных элементов тек-го уровн¤ и перейдЄм на следующий			
			next_points_size[nps]--;

			//если есть разрыв другим поселением
			owner = buildings.IsBuildingExists(current_point);
			if (!(((owner >= 0) && (owner != pID)) && (nps > 0))) {
				nps++;
				//получим следующие точки						
				for (const auto &road : roads) {
					if (road.id == pID) {
						if (road.from == current_point) {
							new_point = road.to;
						}
						else {
							if (road.to == current_point) {
								new_point = road.from;
							}
							else {
								goto next_point;
							}
						}
						//проверим не добавили ли мы еще эту дорогу
						for (int i = 0; i < (nps - 1); i++) {
							if (((current_path[i] == road.from) && (current_path[i + 1] == road.to)) || ((current_path[i] == road.to) && (current_path[i + 1] == road.from)))
							{
								goto next_point;
							}
						}
						//добавим новую точку пути
						next_points[++np] = new_point;
						next_points_size[nps]++;
						if (nps > _max_path) {
							_max_path = nps;
							//PrintPathPoints(current_path);
							/*#ifdef DEBUG
							for (auto i = 0; i < nps; i++)
							cout << current_path[i] << " ";
							cout << endl;
							#endif*/
						}
					next_point:;
					}
				}
			}
		}
		else {
			nps--;
		}

	} while (nps != 0);

	return _max_path;
}

int DFSSearchLongPath::GetLongestPath()
{
	int temp_path = max_path = 0;
	for (const auto &point : extreme_points) {
		;
		if ((temp_path = GetLongestPathNoRecursive(point)) > max_path)
			max_path = temp_path;
	}
	return max_path;
}

void Roads::UpdateRoadsCount()
{
	for (size_t i = 0; i < roads.size(); i++) {
		(*pGameState->players)[roads[i].id].AddRoad();	//Update roads
	}
}
