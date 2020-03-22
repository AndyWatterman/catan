#pragma once

//#include "CatanGUI.h"
#include "header.h"

struct _Board {
	std::vector<resource> resources;
	std::vector<int> dices;
	std::vector<node> nodes;
	std::vector<node> points_to_hex;
	std::vector<hex_point> hex_to_points;
	std::vector<resource> harbors;
};

class AiGameBoard : private _Board {
private:

public:
	AiGameBoard(_Board& b);
	AiGameBoard() = delete;
	
	const std::vector<node> & getNodesRef() const;
	const std::vector<node> & getPointsToHexRef() const;
	const std::vector<hex_point> & getHexToPointsRef() const;
	const int getDiceFromHex(int nHex);

	std::vector<int> & getDicesRef();
	std::vector<resource> & getHarborsRef();	
	std::vector<resource> & getResourcesRef();
	
	void clearHarbors();
	void genNewHexes();
	void setHexResource(unsigned int hex, resource res);	//set specific resourse for hex
	void setHarborResource(unsigned int point, resource res);	//set specific resourse for hex
	void setBorderType(unsigned int border_pos, unsigned int border_type);
};