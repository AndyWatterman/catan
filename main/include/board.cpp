#include "stdafx.h"
#include "board.h"

#include <math.h>

/*template <typename T, typename... Types>
void addObject(Types... args) {
	std::unique_ptr<T> obj(new T(args));
	auto inserted = Board.Objects.insert(std::make_pair(obj->getObjectId(), std::move(obj)));
	assert(inserted.second);
};*/

void Board::CreateStandartObjects()
{
	//load hex board
	
	int hex_x = kHexBoardX, hex_y = kHexBoardY;	
	const sf::IntRect hex_rect = catan.GetSprite(Sprites::hex_free).getTextureRect();	

	for (auto i = 3, x = hex_x, y = hex_y; i < 6; i++, x -= hex_rect.width / 2, hex_y += kHexBoardYStep, hex_x = x) {
		for (auto j = 0, _x = x; j < i; j++, _x += hex_rect.width) {

			std::unique_ptr<BoardHex> obj(new BoardHex(catan, _x, hex_y, 0));			
			auto inserted = Objects.insert(std::make_pair(obj->getObjectId(), std::move(obj)));
			assert(inserted.second);
		}
	}
	for (auto i = 6, x = hex_x + hex_rect.width, y = hex_y; i > 4; i--, x += hex_rect.width / 2, hex_y += kHexBoardYStep, hex_x = x) {
		for (auto j = i, _x = x; j > 2; j--, _x += hex_rect.width) {

			std::unique_ptr<BoardHex> obj(new BoardHex(catan, _x, hex_y, 0));			
			auto inserted = Objects.insert(std::make_pair(obj->getObjectId(), std::move(obj)));
			assert(inserted.second);
		}
	}

	{
		//button generate hex
		std::unique_ptr<Btn> obj(new Btn(catan, 900, 0, Sprites::btnGenHexesUp, Sprites::btnGenHexesDown, objButtonEvents::genHexes));
		auto inserted = Objects.insert(std::make_pair(obj->getObjectId(), std::move(obj)));
		assert(inserted.second);
	}

	{
		//borders with harbors

		{
			std::unique_ptr<BoardBorder> obj(new BoardBorder(catan, Sprites::harbor_stone, 223, 76, 30));
			auto inserted = Objects.insert(std::make_pair(obj->getObjectId(), std::move(obj)));
			assert(inserted.second);
		}
		{			
			std::unique_ptr<BoardBorder> obj(new BoardBorder(catan, Sprites::harbor_stone, 759, -4, 90));
			auto inserted = Objects.insert(std::make_pair(obj->getObjectId(), std::move(obj)));
			assert(inserted.second);
		}
		{
			std::unique_ptr<BoardBorder> obj(new BoardBorder(catan, Sprites::harbor_stone, 1098, 419, 150));
			auto inserted = Objects.insert(std::make_pair(obj->getObjectId(), std::move(obj)));
			assert(inserted.second);
		}
		{
			std::unique_ptr<BoardBorder> obj(new BoardBorder(catan, Sprites::harbor_stone, 900, 924, 210));
			auto inserted = Objects.insert(std::make_pair(obj->getObjectId(), std::move(obj)));
			assert(inserted.second);
		}
		{
			std::unique_ptr<BoardBorder> obj(new BoardBorder(catan, Sprites::harbor_stone, 363, 1004, 270));
			auto inserted = Objects.insert(std::make_pair(obj->getObjectId(), std::move(obj)));
			assert(inserted.second);
		}
		{
			std::unique_ptr<BoardBorder> obj(new BoardBorder(catan, Sprites::harbor_stone, 24, 581, 330));
			auto inserted = Objects.insert(std::make_pair(obj->getObjectId(), std::move(obj)));
			assert(inserted.second);
		}
	}	

	//PlayerContainer

	{
		std::unique_ptr<PlayerContainer> obj(new PlayerContainer(catan, BoardObjects::rectangle, 0, 1397, 3));
		auto inserted = Objects.insert(std::make_pair(obj->getObjectId(), std::move(obj)));
		assert(inserted.second);
	}

	//button next turn
	{		
		std::unique_ptr<Btn> obj(
			new Btn(catan, 1773, 595, 115, 44, 0,
				sf::Color(89, 89, 89, 255), 2, sf::Color(142, 205, 246, 255),
				sf::Color(103, 161, 199, 255), sf::Color(89, 89, 89, 255),
				sf::Color(213, 126, 3), sf::Color(89, 89, 89, 255),
				sf::Color(255, 255, 255, 255), "Done", 17,
				objButtonEvents::nextTurn));
		auto inserted = Objects.insert(std::make_pair(obj->getObjectId(), std::move(obj)));
		assert(inserted.second);
	}		

	addObject<Label>(catan, 1641, 14, 0, sf::Color(100, 228, 255, 255), "L. Road (0)", 16, nothing);

	//Roads && Cities hooker

	int city_hook_x = kHexBoardX + kHexWidth / 2;
	int city_hook_y = kHexBoardY;
	int counter = 1;

	for (auto i = 0, j = 3; i < 7; i++, j += counter) {
		for (auto l = 0; l < 2; l++) {
			for (auto k = 0; k < j; k++) {

				//roads
				if ((l == 0) && ((i != 0) && (i != 6))) {
					std::unique_ptr<roadHooks> obj(new roadHooks(catan, 
						static_cast<float>(city_hook_x+3), 
						static_cast<float>(city_hook_y + kRoadHeight/2 +2), 0));
					auto inserted = Objects.insert(std::make_pair(obj->getObjectId(), std::move(obj)));
					assert(inserted.second);
				}

				if ((l != 0) || (i == 0)) {
					if ((k < (j - 1)) || (i < 3)) {
						std::unique_ptr<roadHooks> obj(new roadHooks(catan,
							static_cast<float>(city_hook_x + kCityWidth - kRoadWidth/2 - 2),
							static_cast<float>(city_hook_y  + kCityWidth/2 - 4), -60.2f));
						auto inserted = Objects.insert(std::make_pair(obj->getObjectId(), std::move(obj)));
						assert(inserted.second);
					}

					if ((k > 0) || (i < 3)) {
						std::unique_ptr<roadHooks> obj(new roadHooks(catan,
							static_cast<float>(city_hook_x - kCityWidth + kRoadWidth),
							static_cast<float>(city_hook_y + kCityHeight / 2 - 4), 60.2f));
						auto inserted = Objects.insert(std::make_pair(obj->getObjectId(), std::move(obj)));
						assert(inserted.second);
					}
				}
				
				std::unique_ptr<cityHooks> obj(new cityHooks(catan, city_hook_x, city_hook_y));
				auto inserted = Objects.insert(std::make_pair(obj->getObjectId(), std::move(obj)));
				assert(inserted.second);

				city_hook_x += kHexWidth - 1;
			}
			city_hook_x -= (kHexWidth - 1)*(j);

			if ((i == 0) || (i == 6))
				break;

			if (l == 0)
				city_hook_y += 104;
		}
		if (i < 3) {
			city_hook_x -= kHexWidth / 2;
		}
		else {
			city_hook_x += kHexWidth / 2;
			counter = -1;
		}

		city_hook_y += 46;
	}	

	//city	
	{
		std::unique_ptr<City> obj(new City(catan, Sprites::redCity, 1800, 150));
		auto inserted = Objects.insert(std::make_pair(obj->getObjectId(), std::move(obj)));
		assert(inserted.second);
	}

	//road
	{
		std::unique_ptr<BoardRoad> obj(new BoardRoad(catan, Sprites::redCity, 1850, 150));
		auto inserted = Objects.insert(std::make_pair(obj->getObjectId(), std::move(obj)));
		assert(inserted.second);
	}
	
	//settelment
	{
		std::unique_ptr<Settelment> obj(new Settelment(catan, Sprites::redSet, 1800, 70));
		auto inserted = Objects.insert(std::make_pair(obj->getObjectId(), std::move(obj)));
		assert(inserted.second);
	}
}

template<typename T, typename ...Types>
void Board::addObject(Types&& ...args)
{
	std::unique_ptr<T> obj(new T(std::forward<Types>(args)...));
	auto inserted = Objects.insert(std::make_pair(obj->getObjectId(), std::move(obj)));
	assert(inserted.second);
}

Board::Board(CatanGUI & _catan) : catan(_catan)
{
	CreateStandartObjects();
}


Object * Board::GetObject(int x, int y) {
	for (std::map<unsigned int, std::unique_ptr<Object>>::reverse_iterator it = Objects.rbegin(); it != Objects.rend(); ++it)
	{
		if (!(it->second->IsHidden())) {
			if (it->second->getGlobalBounds().contains(x, y)) {

				bool objFound = false;

				//if ((!it->second->getTexture()) || (!it->second->IsTextureUsedForDrop())) {	//no texture, only shape					
				//	objFound = true;
				//}
				//else {
					sf::Vector2f vec = it->second->getTransform().getInverse().transformPoint(x, y);

					sf::FloatRect lBounds = it->second->getLocalBounds();
					if ((vec.x < lBounds.width) && (vec.x >= 0)
						&& (vec.y < lBounds.height) && (vec.y >= 0)) {

						if ((!it->second->getTexture()) || (!it->second->IsTextureUsedForDrop())) {	//no texture, only shape
							objFound = true;
						}
						else {

							sf::IntRect rect = it->second->getTextureRect();
							const sf::Image& image = catan.GetMainImage();
							sf::Color pColor = image.getPixel(static_cast<unsigned int>(vec.x + rect.left),
								static_cast<unsigned int>(vec.y + rect.top));
							if (pColor.a) {
								objFound = true;
							}
						}
					}
				//}
				if (objFound) {
					if (catan.drag->IsDraggring()) {
						if ((catan.drag->GetObject() == &(*it->second))
							|| (!it->second->IsDragObjectAcceptable(catan.drag->GetObject()))) {
							continue;
						}
					}		
					//if (it->second->getObjectType() == BoardObjects::roadHooks)
					//	std::cout << "Road_ID: " << dynamic_cast<roadHooks*>(it->second.get())->getRoadId() << ", X = " << x << ", Y = " << y << std::endl;
					//else
						std::cout << "ID: " << it->second->getObjectId() << ", X = " << x << ", Y = " << y << std::endl;

					return &(*it->second);					
				}
			}
		}
	}

	//std::cout << "NONE" << std::endl;
	return nullptr;
}

void Board::Draw()
{
	for (std::map<unsigned int, std::unique_ptr<Object>>::iterator it = Objects.begin(); it != Objects.end(); ++it)
	{
		if (!(it->second->IsHidden())) {			
			it->second->OnDraw();
		}
	}
}

void Board::Update()
{
	for (std::map<unsigned int, std::unique_ptr<Object>>::iterator it = Objects.begin(); it != Objects.end(); ++it)
	{
		if (!(it->second->IsHidden())) {
			it->second->Update();
		}
	}
}

void Board::UpdateHexesAndDices()
{
	std::vector<resource> & res = catan.catan_ai->getResourcesRef();
	std::vector<int> & dices = catan.catan_ai->getDicesRef();
	std::vector<resource> & harbors = catan.catan_ai->getHarborsRef();

	for (std::map<unsigned int, std::unique_ptr<Object>>::iterator it = Objects.begin(); it != Objects.end(); ++it)
	{
		//Update hex objects
		if (it->second->getObjectType() == BoardObjects::hex) {
			BoardHex* so = dynamic_cast<BoardHex*>(it->second.get());
			auto currentHexId = so->getCurrentHexId();
			so->setSpriteID(static_cast<Sprites::ID>(res[currentHexId]));

			//update dice from dice array			
			auto _dice = dices[currentHexId];
			if (_dice > 0) {
				(_dice < 7) ? (_dice += 32) : (_dice += 31);
				so->setDice(static_cast<Sprites::ID>(_dice));
			}
			else {
				so->setDice(0);
			}
		};

		//Update border objects
		if (it->second->getObjectType() == BoardObjects::borders) {
			BoardBorder* so = dynamic_cast<BoardBorder*>(it->second.get());
			auto current_border_id = so->getCurrentBorderId();

			for (size_t i = 0; i < 6; i++)
			{
				bool found = true;
				int rowHPoints = current_border_id * 5;
				int rowHRes = static_cast<int>(i * 5);
				for (size_t j = 0; j < 5; j++) 
				{
					if (harbors[harborPoints[rowHPoints + j]] != harborResources[rowHRes + j]) {
						found = false;
						break;
					}
				}
				if (found) {
					so->setHarbor(rowHRes / 5);
					break;
				}
			}			
		}
	}
}
