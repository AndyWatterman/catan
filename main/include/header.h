#pragma once

#define DEBUG 1

#define ALL_SPRITES_FILENAME "C:/Projects/CatanGUI_0_2a/x64/Debug/textures/sprites.png"
#define BG_TEXTURE_FILENAME "C:/Projects/CatanGUI_0_2a/x64/Debug/textures/bg.jpg"

#define _USE_MATH_DEFINES

const int kHexBoardY = 100;		//position of drawable hex board
const int kHexBoardX = 300;
const int kHexBoardYStep = 150;

const int kCityHeight = 56;
const int kCityWidth = 56;
const int kRoadHeight = 102;
const int kRoadWidth = 16;
const int kHexWidth = 174;

const int kMaxConnections = 3;	//each point connects to 3 others maximum 
const int kHex_to_points = 6;	//number of points on one hex

//const int kPlayersCount = 2;	//temporary players count const
const int kMaxPlayerCount = 6;	//temporary players count const
const int kHexCount = 19;	//temporary players count const

const int kMaxSettelments = 5;			//максимальное количество поселений одного игрока
const int kMaxCities = 4;				//максимальное количество городов одного игрока
const int kMaxRoads = 15;				//максимальное количество дорог у одного игрока

const int kResCount = 5;				//количество рзновидностей ресурсов в игре
const int kCardCount = 5;				//количество рзновидностей карт развития в игре
const int kMaxBankResources = 19;		//максимальное количество каждого из ресурсов в игре

const int kMinLongestPath = 5;			//минимальная длина пути, чтобы получить очки
const int kLargestArmyBonus = 2;		//бонус за самое большое войско
const int kLongestRoadBonus = 2;		//бонус за самое большое войско
const int kSettelmentScore = 1;
const int kCityScore = 2;

const int kPlayerContainerWidth = 500;
const int kPlayerContainerHeight = 644;

const std::string kFont = "C:/Windows/Fonts/RobotoSlab-Regular.ttf";

//поселение/город
enum building_types { settelment, city, none };

//карты развития
enum devCard {
	knight,		//рыцарь
	monopoly,	//монополия
	roads,		//строительство 2-х дорог
	twoRes,		//два любых ресурса из банка
	winPoint,	//1 победное очко	
};

const std::array<sf::Color, kMaxPlayerCount> kPlayerColors = {
	sf::Color(255, 110, 110, 255),
	sf::Color(71, 135, 232, 255),
	sf::Color(88, 165, 85, 255),
	sf::Color(205, 131, 52, 255),
	sf::Color(0, 0, 0, 255),
	sf::Color(0, 0, 0, 255)
};

static std::random_device rd;
static std::mt19937 rng(rd());

namespace Resources
{
	enum ID : int
	{
		all = 1000,
		background
	};
}

namespace Sprites {
	enum ID : int {
		stone = 0,
		brick,
		sheep,
		wheat,
		wood,
		desert,
		hex_free,
		hex_hover,		
		redSet,
		blueSet,
		greenSet,		
		orangeSet,
		whiteSet,
		brownSet,		
		redCity,		
		blueCity,
		greenCity,
		orangeCity,
		whiteCity,
		brownCity,		
		selectedCity,
		hookCity,
		selRedSet,		
		selBlueSet,
		selGreenSet,
		selOrangeSet,
		selWhiteSet,
		selBrownSet,		
		selRedCity,		
		selBlueCity,
		selGreenCity,
		selOrangeCity,
		selWhiteCity,
		selBrownCity,		
		n2,
		n3,
		n4,
		n5,
		n6,
		n8,
		n9,
		n10,
		n11,
		n12,
		redRoad,
		blueRoad,
		greenRoad,
		orangeRoad,
		whiteRoad,
		brownRoad,		
		selectedRoad,
		hookRoad,
		selRedRoad,
		selBlueRoad,
		selGreenRoad,
		selOrangeRoad,
		selWhiteRoad,
		selBrownRoad,		
		harbor_stone,
		harbor_3_brick,
		harbor_3_sheep,
		harbor_3,
		harbor_3_weat,
		harbor_wood,
		btnGenHexesUp,
		btnGenHexesDown,
		background,
		none
	};

	const int count = Sprites::none;

	struct SpriteTable {
		int left, top, height, width;
		Resources::ID rId;
		Sprites::ID id;
	};

	//SpriteTable sprite_table
	const std::array<SpriteTable, count> sprite_table {
		{
			{0, 0, 200, 174, Resources::ID::all, stone},
			{174, 0, 200, 174, Resources::ID::all, brick},
			{348, 0, 200, 174, Resources::ID::all, sheep},
			{522, 0, 200, 174, Resources::ID::all, wheat},
			{696, 0, 200, 174, Resources::ID::all, wood},
			{870, 0, 200, 174, Resources::ID::all, desert},
			{1044, 0, 200, 174, Resources::ID::all, hex_free},
			{1218, 0, 200, 174, Resources::ID::all, hex_hover},

			{0, 200, 56, 56, Resources::ID::all, redSet},
			{112, 200, 56, 56, Resources::ID::all, blueSet},
			{56, 200, 56, 56, Resources::ID::all, greenSet},			
			{280, 200, 56, 56, Resources::ID::all, orangeSet},
			{168, 200, 56, 56, Resources::ID::all, whiteSet},
			{224, 200, 56, 56, Resources::ID::all, brownSet},

			{336, 200, 56, 56, Resources::ID::all, redCity},
			{448, 200, 56, 56, Resources::ID::all, blueCity},
			{392, 200, 56, 56, Resources::ID::all, greenCity},			
			{616, 200, 56, 56, Resources::ID::all, orangeCity},
			{504, 200, 56, 56, Resources::ID::all, whiteCity},
			{560, 200, 56, 56, Resources::ID::all, brownCity},		

			{672, 200, 56, 56, Resources::ID::all, selectedCity},
			{728, 200, 56, 56, Resources::ID::all, hookCity},

			{ 784, 200, 56, 56, Resources::ID::all, selRedSet},
			{ 896, 200, 56, 56, Resources::ID::all, selBlueSet},
			{ 840, 200, 56, 56, Resources::ID::all, selGreenSet},			
			{ 1064, 200, 56, 56, Resources::ID::all, selOrangeSet},
			{ 952, 200, 56, 56, Resources::ID::all, selWhiteSet},
			{ 1008, 200, 56, 56, Resources::ID::all, selBrownSet},	

			{ 1120, 200, 56, 56, Resources::ID::all, selRedCity},
			{ 1232, 200, 56, 56, Resources::ID::all, selBlueCity},
			{ 1176, 200, 56, 56, Resources::ID::all, selGreenCity},			
			{ 1400, 200, 56, 56, Resources::ID::all, selOrangeCity},
			{ 1288, 200, 56, 56, Resources::ID::all, selWhiteCity},
			{ 1344, 200, 56, 56, Resources::ID::all, selBrownCity},		

			{ 1456, 200, 56, 56, Resources::ID::all, n2 },
			{ 1512, 200, 56, 56, Resources::ID::all, n3 },
			{ 1568, 200, 56, 56, Resources::ID::all, n4 },
			{ 1624, 200, 56, 56, Resources::ID::all, n5 },
			{ 1680, 200, 56, 56, Resources::ID::all, n6 },
			{ 1736, 200, 56, 56, Resources::ID::all, n8 },
			{ 1792, 200, 56, 56, Resources::ID::all, n9 },
			{ 1848, 200, 56, 56, Resources::ID::all, n10 },
			{ 1904, 200, 56, 56, Resources::ID::all, n11 },
			{ 1960, 200, 56, 56, Resources::ID::all, n12 },

			{0, 256, 102, 16, Resources::ID::all, redRoad},
			{32, 256, 102, 16, Resources::ID::all, blueRoad},
			{16, 256, 102, 16, Resources::ID::all, greenRoad},			
			{80, 256, 102, 16, Resources::ID::all, orangeRoad },
			{48, 256, 102, 16, Resources::ID::all, whiteRoad },
			{64, 256, 102, 16, Resources::ID::all, brownRoad },

			{96, 256, 102, 16, Resources::ID::all, selectedRoad },
			{112, 256, 102, 16, Resources::ID::all, hookRoad },

			{128, 256, 102, 16, Resources::ID::all, selRedRoad },
			{160, 256, 102, 16, Resources::ID::all, selBlueRoad },
			{144, 256, 102, 16, Resources::ID::all, selGreenRoad },			
			{208, 256, 102, 16, Resources::ID::all, selOrangeRoad },
			{176, 256, 102, 16, Resources::ID::all, selWhiteRoad },
			{192, 256, 102, 16, Resources::ID::all, selBrownRoad },

			{0, 359, 547, 153, Resources::ID::all, harbor_stone },
			{154, 359, 547, 153, Resources::ID::all, harbor_3_brick },
			{308, 359, 547, 153, Resources::ID::all, harbor_3_sheep },
			{462, 359, 547, 153, Resources::ID::all, harbor_3 },
			{616, 359, 547, 153, Resources::ID::all, harbor_3_weat },
			{770, 359, 547, 153, Resources::ID::all, harbor_wood },
			{1392, 0, 27, 96, Resources::ID::all, btnGenHexesUp},
			{1392, 27, 27, 96, Resources::ID::all, btnGenHexesDown},
			{0, 0, 1080, 1920, Resources::ID::background, background }
		} 
	};
}

//this is for behavior of objects
namespace BoardObjects {
	enum ID: int
	{
		deck = 10000,
		hex,
		city,
		road,
		settelment,
		cityHooks,
		roadHooks,
		borders,
		button,
		label,
		rectangle
	};	
}

enum btnStates: int {normal = 0, hover, pressed};
enum objButtonEvents: int {genHexes = 0, nextTurn, nothing};

//typedef int node[kMaxConnections];
typedef std::array<int, kMaxConnections> node;

//каждому гексу принадлежит 6 точек
typedef std::array<int, kHex_to_points> hex_point;

//ресурсы и порты в игре, где tin1 - порт 3:1, non - отсутствие ресурса (для гексов без ресурса)
enum resource { stone, brick, sheep, weat, wood, non, tin1 };

//standart dices for 4ppl board
const int kStandartDiceSequence = 18;
const std::array<int, kStandartDiceSequence> diceSequence = {5, 2, 6, 3, 8, 10, 9, 12, 11, 4, 8, 10, 9, 4, 5, 6, 3, 11};
const std::array<std::array<int, kHexCount>, 6> hexSequence = { {
	{0, 3, 7, 12, 16, 17, 18, 15, 11, 6, 2, 1, 4, 8, 13, 14, 10, 5, 9 },
	{7, 12, 16, 17, 18, 15, 11, 6, 2, 1, 0, 3, 8, 13, 14, 10, 5, 4, 9 },
	{16, 17, 18, 15, 11, 6, 2, 1, 0, 3, 7, 12, 13, 14, 10, 5, 4, 8, 9 },
	{18, 15, 11, 6, 2, 1, 0, 3, 7, 12, 16, 17, 14, 10, 5, 4, 8, 13, 9 },
	{11, 6, 2, 1, 0, 3, 7, 12, 16, 17, 18, 15, 10, 5, 4, 8, 13, 14, 9 },
	{2, 1, 0, 3, 7, 12, 16, 17, 18, 15, 11, 6, 5, 4, 8, 13, 14, 10, 9 }
}};

/*const std::array<std::array<int, 3>, 72> road_id_to_from_to = { {
	{0, 0, 4},	{1, 0, 3},	{2, 1, 5},	{3, 1, 4},	{4, 2, 6},	{5, 2, 5},	{6, 3, 7},	{7, 4, 8},	{8, 5, 9},	{9, 6, 10},
	{10, 7, 12}, {11, 7, 11}, {12, 8, 13}, {13, 8, 12},	{14, 9, 14}, {15, 9, 13}, {16, 10, 15},	{17, 10, 14}, {18, 11, 16},	{19, 12, 17},
	{20, 13, 18}, {21, 14, 19},	{22, 15, 20}, {23, 16, 22},	{24, 16, 21}, {25, 17, 23}, {26, 17, 22}, {27, 18, 24},	{28, 18, 23}, {29, 19, 25},
	{30, 19, 24}, {31, 20, 26},	{32, 20, 25}, {33, 21, 27}, {34, 22, 28}, {35, 23, 29},	{36, 24, 30}, {37, 25, 31},	{38, 26, 32}, {39, 27, 33},
	{40, 28, 34},	{41, 28, 33},	{42, 29, 35},	{43, 29, 34},	{44, 30, 36}, {45, 30, 35}, {46, 31, 37}, {47, 31, 36},	{48, 32, 37},	{49, 33, 38},
	{50, 34, 39},	{51, 35, 40},	{52, 36, 41},	{53, 37, 42},	{54, 38, 43},	{55, 39, 44},	{56, 39, 43},	{57, 40, 45},	{58, 40, 44},	{59, 41, 46},
	{60, 41, 45},	{61, 42, 46},	{62, 43, 47},	{63, 44, 48},	{64, 45, 49},	{65, 46, 50},	{66, 47, 51},	{67, 48, 52},	{68, 48, 51},	{69, 49, 53},
	{70, 48, 52},	{71, 50, 53}	
} }*/;

const std::array<std::array<int, 2>, 72> road_id_to_from_to = { {
	{0, 4},	{0, 3},	{1, 5},	{1, 4},	{2, 6},	{2, 5},	{3, 7},	{4, 8},	{5, 9},	{6, 10},
	{7, 12}, {7, 11}, {8, 13}, {8, 12},	{9, 14}, {9, 13}, {10, 15},	{10, 14}, {11, 16},	{12, 17},
	{13, 18}, {14, 19},	{15, 20}, {16, 22},	{16, 21}, {17, 23}, {17, 22}, {18, 24},	{18, 23}, {19, 25},
	{19, 24}, {20, 26},	{20, 25}, {21, 27}, {22, 28}, {23, 29},	{24, 30}, {25, 31},	{26, 32}, {27, 33},
	{28, 34},	{28, 33},	{29, 35},	{29, 34},	{30, 36}, {30, 35}, {31, 37}, {31, 36},	{32, 37},	{33, 38},
	{34, 39},	{35, 40},	{36, 41},	{37, 42},	{38, 43},	{39, 44},	{39, 43},	{40, 45},	{40, 44},	{41, 46},
	{41, 45},	{42, 46},	{43, 47},	{44, 48},	{45, 49},	{46, 50},	{47, 51},	{48, 52},	{48, 51},	{49, 53},
	{48, 52},	{50, 53}
} };

//standart ports for 4ppl board
const std::array<int, 30> harborPoints =
{ {
		16, 11, 7, 21, 27,	//0
		4, 1, 5, 0, 3,		//1
		10, 15, 20, 2, 6,	//2
		37, 42, 46, 26, 32,	//3
		49, 52, 48, 50, 53,	//4
		43, 38, 33, 47, 51	//5
	} };

const std::array<int, 30> harborResources =
{ {
	stone, stone, non, non, non,	//harbor_stone
	non, brick, brick, tin1, tin1,	//harbor_3_brick
	non, sheep, sheep, tin1, tin1,	//harbor_3_sheep
	tin1, tin1, non, non, non,		//harbor_3	
	non, weat, weat, tin1, tin1,	//harbor_3_weat
	wood, wood, non, non, non		//harbor_wood
} };

//hexes for shuffle
const std::vector<resource> hexForShuffling = { wood, wood, wood, wood, brick, brick, brick, sheep, sheep, sheep, sheep, weat, weat, weat, weat, stone, stone, stone, non };

class CatanGUI;
class Board;
class Object;
class Drag;
class AiGameBoard;
class CatanAi;
class GameState;
class Roads;
class Players;
class Buildings;
struct _Board;
struct Sample;