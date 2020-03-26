Sample TestSample {
	
	//int robber, largest_army, longest_path;
	3, -1, -1,

	//std::vector<Building> buildings;
	{ {
		{ 19, 0, building_types::settelment },
		{ 28, 0, building_types::settelment },
		{ 44, 0, building_types::city },
		{ 8, 1, building_types::settelment },
		{ 31, 1, building_types::settelment }
	} },
	
	//std::vector<Road> roads;
	{ {
		{ 19, 25, 0 },
		{ 28, 34, 0 },
		{ 34, 29, 0 },
		{ 29, 35, 0 },
		{ 35, 30, 0 },
		{ 44, 40, 0 },
		{ 30, 36, 0 },
		{ 8, 13, 1 },
		{ 13, 9, 1 },
		{ 9, 5, 1 },
		{ 5, 2, 1 },
		{ 2, 6, 1 },
		{ 31, 25, 1 }
	} },

	{ {
		//Player 0
		{
			/*sheep, stone, brick, wood, weat*/
			//{ 7, 1, 5, 0, 0 },	//стартовые ресурсы
			{ 0, 1, 0, 1, 1 },	//стартовые ресурсы

			/*knight, monopoly, roads, twoRes, winPoint*/
			{ 0, 0, 0, 0, 0 },	//стартовые карточки игроков
			{ 0, 0, 0, 0, 0 },	//активные карты
			{ 0, 0, 0, 0, 0 },	//использованные карты	
			false				//dev_card_has_been_played
		},

		//Player 1
		{
			//sheep, stone, brick, wood, weat
			{ 1, 0, 1, 1, 0 },	//стартовые ресурсы

								//knight, monopoly, roads, twoRes, winPoint
			{ 0, 0, 0, 0, 0 },	//стартовые карточки игроков
			{ 0, 0, 0, 0, 0 },	//активные карты
			{ 0, 0, 0, 0, 0 },	//использованные карты
			false				//dev_card_has_been_played								
		}/*,

		//Player 3
		{
			//sheep, stone, brick, wood, weat
			{ 0, 0, 2, 2, 2 },	//стартовые ресурсы

			//knight, monopoly, roads, twoRes, winPoint
			{ 0, 0, 0, 0, 0 },	//стартовые карточки игроков
			{ 0, 0, 0, 0, 0 },	//активные карты
			{ 0, 0, 0, 0, 0 },	//использованные карты
			false				//dev_card_has_been_played
			//0, 0				//big_army, long_road
		}*/
		} }

	//R5
	/*vector<Road> roads = { {
		{ 1, 4, 0 },
		{ 1, 5, 0 },
		{ 4, 8, 0 },
		{ 5, 9, 0 },
		{ 8, 12, 0 },
		{ 8, 13, 0 },
		{ 9, 13, 0 },
		{ 9, 14, 0 },
		{ 12, 17, 0 },
		{ 13, 18, 0 },
		{ 14, 19, 0 },
		{ 17, 23, 0 },
		{ 19, 24, 0 },
		{ 18, 23, 0 },
		{ 18, 24, 0 },
		{ 23, 29, 0 },
		{ 24, 30, 0 },
		{ 35, 29, 0 },
		{ 35, 30, 0 }

	}};

	vector<Building> buildings = { {
		{ 4, 0, settelment },
		{ 19, 0, settelment },
		{ 13, 1, settelment },
		{ 23, 1, settelment },
		{ 18, 2, settelment },
		//{ 8, 2, settelment },
	} };*/

	/*vector<Building> buildings = { {
		{ 19, 0, settelment },
		{ 28, 0, settelment },
		{ 9, 1, settelment },
		{ 44, 1, settelment }
	} };*/

	/*vector<Road> roads = { {
	//{29, 35, 1},
	//{40, 35, 0}

	//Player 0
	{16, 22, 0},
	{22, 17, 0},
	{22, 28, 0},
	{28, 34, 0},
	{17, 23, 0},
	{37, 31, 0},
	{37, 32, 0},
	{32, 26, 0},
	{31, 25, 0},
	{25, 20, 0},
	{20, 15, 0},
	{15, 10, 0},
	{10, 14, 0},
	{23, 18, 0},
	//{18, 24, 0},

	//Player 1
	{19, 14, 1},
	{19, 24, 1},
	{24, 30, 1},
	{30, 35, 1},
	{35, 29, 1},
	{14, 9, 1},
	{9, 5, 1},
	{23, 29, 1},

	//Player 2
	{12, 17, 2},
	{12, 8, 2},
	{8, 13, 2},
	{13, 18, 2},
	{4, 1, 2},

	}};*/

	/*vector<Building> buildings = { {
		{31, 0, settelment},
		{19, 1, settelment},
		{23, 1, settelment},
		{4, 2, settelment},
		{12, 2, settelment},

		{20, 0, settelment},
		{16, 0, settelment}
	}};*/
	
};