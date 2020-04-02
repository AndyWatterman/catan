#include "stdafx.h"
#include "game_board.h"

void AiGameBoard::clearHarbors()
{
	for (auto &harbor : harbors) {
		harbor = resource::non;
	}
}

void AiGameBoard::genNewHexes()
{
	//shuffle hexes
	//if (resources.size() == 0)
		resources = hexForShuffling;

	std::shuffle(resources.begin(), resources.end(), rng);

	//shuffle dices
	std::uniform_int_distribution<size_t> uni(0, hexSequence.size()-1);
	auto random_int = uni(rng);
	auto res = getResourcesRef();	

	for (auto i = 0, j = 0; i < kHexCount; i++)
	{
		int current_hex = hexSequence[random_int][i];

		if (res[current_hex] == resource::non) {
			dices[current_hex] = 0;
			continue;
		}
		else {
			dices[current_hex] = diceSequence[j++];
		}
	}	

	//shuffle harbors
	clearHarbors();
	std::array<int, 6> harborsP = { { 0, 1, 2, 3, 4, 5 } };	
	std::shuffle(harborsP.begin(), harborsP.end(), rng);	
	for (auto i = 0; i < 6; i++) {
		int rowP = i * 5;
		int rowR = harborsP[i] * 5;
		for (auto j = 0; j < 5; j++) {
			setHarborResource(harborPoints[rowP+j], 
				static_cast<resource>(harborResources[rowR+j]));
		}
	}	
}

void AiGameBoard::setHexResource(unsigned int hex, resource res)
{
	getResourcesRef()[hex] = res;
}

void AiGameBoard::setHarborResource(unsigned int point, resource res)
{
	getHarborsRef()[point] = res;
}

//0..5, harbor_stone..harbor_wood
void AiGameBoard::setBorderType(int border_pos, resource border_type)
{
	for (auto j = 0; j < 5; j++) {
		setHarborResource(harborPoints[border_pos*5 + j], harborResources[static_cast<int>(border_type)*5 + j]);
	}
}

AiGameBoard::AiGameBoard(_Board & b) : _Board(b)
{
	//genNewHexes();
}

const std::vector<node> & AiGameBoard::getNodesRef() const { return (nodes); };
const std::vector<node> & AiGameBoard::getPointsToHexRef() const { return (points_to_hex); };
const std::vector<hex_point> & AiGameBoard::getHexToPointsRef() const { return (hex_to_points); };

std::vector<resource> & AiGameBoard::getHarborsRef() { return (harbors); };
std::vector<int> & AiGameBoard::getDicesRef() { return (dices); };
std::vector<resource> & AiGameBoard::getResourcesRef() { return (resources); };

const int AiGameBoard::getDiceFromHex(int nHex)
{
	return (dices[nHex]);
}
