#include "stdafx.h"
#include "board.h"

#include <math.h>

void Board::Init()
{
	//load hex board

	int hex_x = kHexBoardX, hex_y = kHexBoardY;
	const sf::IntRect hex_rect = catan->GetSprite(Sprites::ID::hex_free).getTextureRect();

	for (auto i = 3, x = hex_x, y = hex_y; i < 6; i++, x -= hex_rect.width / 2, hex_y += kHexBoardYStep, hex_x = x) {
		for (auto j = 0, _x = x; j < i; j++, _x += hex_rect.width) {
			addObject<BoardHex>("BoardHex" + std::to_string(BoardHex::hex_id), _x, hex_y);
		}
	}
	for (auto i = 6, x = hex_x + hex_rect.width, y = hex_y; i > 4; i--, x += hex_rect.width / 2, hex_y += kHexBoardYStep, hex_x = x) {
		for (auto j = i, _x = x; j > 2; j--, _x += hex_rect.width) {
			addObject<BoardHex>("BoardHex" + std::to_string(BoardHex::hex_id), _x, hex_y);
		}
	}

	//borders with harbors
	addObject<BoardBorder>("BoardBorder1", 223, 76, 30);
	addObject<BoardBorder>("BoardBorder2", 759, -4, 90);
	addObject<BoardBorder>("BoardBorder3", 1098, 419, 150);
	addObject<BoardBorder>("BoardBorder4", 900, 924, 210);
	addObject<BoardBorder>("BoardBorder5", 363, 1004, 270);
	addObject<BoardBorder>("BoardBorder6", 24, 581, 330);
	
	//button generate hex
	addObject<Btn>("ButtonGenHex", 1200, 900, 65, 24, 0,
		sf::Color(89, 89, 89, 255), 2, sf::Color(255, 60, 0, 255),
		sf::Color(255, 0, 0, 255), sf::Color(89, 89, 89, 255), sf::Color(255, 255, 255, 255),
		sf::Color(213, 126, 3), sf::Color(89, 89, 89, 255), sf::Color(255, 255, 255, 255),
		sf::Color(255, 255, 255, 255), "Generate", 11,
		objButtonEvents::genHexes);		

	//PlayerContainer
	addObject<PlayerContainer>("PlayerContainer", 1397+250, 3+644/2, kPlayerContainerWidth, kPlayerContainerHeight);
	addObject<Label>("LabelLargestRoad", 1641, 14, 0, sf::Color(100, 228, 255, 255), "L. Road (0)", 18);
	addObject<Label>("LabelLargestArmy", 1745, 14, 0, sf::Color(100, 228, 255, 255), "L. Army (0)", 18);	

	addObject<Label>("AIName", 1450, 14, 0, sf::Color(255, 255, 255, 255), "AI #1", 18);
	addObject<Rectangl>("RobotIcon", BoardObjects::icon, Sprites::ID::robot, 1397 + 25, 10 + 25, 26, 30, 0);

	addObject<Rectangl>("ScoreSquare", BoardObjects::icon, sf::Color(255, 255, 255, 255), 2, sf::Color(255, 0, 0, 0), 1534+70, 10+30/2, 26, 26, 0);
	addObject<Label>("LabelScore", 1534 + 62, 13, 0, sf::Color(255, 255, 255, 255), "7", 18);
	addObject<Label>("LabelScoreScore", 1530, 14, 0, sf::Color(255, 255, 255, 255), "Score:", 18);

	addObject<Label>("SoldRoadSetCities", 1450, 45, 0, sf::Color(255, 255, 255, 255), "Soldiers:  3    Roads:  4    Settelments: 2    Cities:  4", 18);	
	addObject<Label>("ResDev", 1450, 70, 0, sf::Color(255, 255, 255, 255), "Total res.:  3    Dev. cards:  4", 18);	

	if (catan->catan_ai->getPlayersCount() > 1) {
		addObject<PlayerContainer>("PlayerContainer0", 1397 + 250, 3 + 644 + 98 / 2 + 3, kPlayerContainerWidth, 98);
		addObject<Label>("LabelLargestRoad0", 1641, 14 + 3 + 644, 0, sf::Color(100, 228, 255, 255), "L. Road (0)", 18);
		addObject<Label>("LabelLargestArmy0", 1745, 14 + 3 + 644, 0, sf::Color(100, 228, 255, 255), "L. Army (0)", 18);

		addObject<Rectangl>("RobotIcon0", BoardObjects::icon, Sprites::ID::robot, 1397 + 25, 10 + 30 / 2 + 3 + 644, 26, 30, 0);
		addObject<Label>("AIName0", 1450, 14 + 3 + 644, 0, sf::Color(255, 255, 255, 255), "AI #2", 18);

		addObject<Rectangl>("ScoreSquare0", BoardObjects::icon, sf::Color(255, 255, 255, 255), 2, sf::Color(255, 0, 0, 0), 1534 + 70, 10 + 30 / 2 + 3 + 644, 26, 26, 0);
		addObject<Label>("LabelScore0", 1534 + 62, 13 + 3 + 644, 0, sf::Color(255, 255, 255, 255), "7", 18);
		addObject<Label>("LabelScoreScore0", 1530, 14 + 3 + 644, 0, sf::Color(255, 255, 255, 255), "Score:", 18);

		addObject<Label>("SoldRoadSetCities0", 1450, 45 + 3 + 644, 0, sf::Color(255, 255, 255, 255), "Soldiers:  3    Roads:  4    Settelments: 2    Cities:  4", 18);
		addObject<Label>("ResDev0", 1450, 70 + 3 + 644, 0, sf::Color(255, 255, 255, 255), "Total res.:  3    Dev. cards:  4", 18);
	}
	if (catan->catan_ai->getPlayersCount() > 2) {
		addObject<PlayerContainer>("PlayerContainer1", 1397 + 250, 3 + 644 + 98 / 2 + 3 + 98 + 3, kPlayerContainerWidth, 98);
		addObject<Label>("LabelLargestRoad1", 1641, 14 + 3 + 644 + 3 + 98, 0, sf::Color(100, 228, 255, 255), "L. Road (0)", 18);
		addObject<Label>("LabelLargestArmy1", 1745, 14 + 3 + 644 + 3 + 98, 0, sf::Color(100, 228, 255, 255), "L. Army (0)", 18);

		addObject<Rectangl>("RobotIcon1", BoardObjects::icon, Sprites::ID::robot, 1397 + 25, 10 + 30 / 2 + 3 + 644 + 3 + 98, 26, 30, 0);
		addObject<Label>("AIName1", 1450, 14 + 3 + 644 + 3 + 98, 0, sf::Color(255, 255, 255, 255), "AI #3", 18);

		addObject<Rectangl>("ScoreSquare1", BoardObjects::icon, sf::Color(255, 255, 255, 255), 2, sf::Color(255, 0, 0, 0), 1534 + 70, 10 + 30 / 2 + 3 + 644 + 3 + 98, 26, 26, 0);
		addObject<Label>("LabelScore1", 1534 + 62, 13 + 3 + 644 + 3 + 98, 0, sf::Color(255, 255, 255, 255), "7", 18);
		addObject<Label>("LabelScoreScore1", 1530, 14 + 3 + 644 + 3 + 98, 0, sf::Color(255, 255, 255, 255), "Score:", 18);

		addObject<Label>("SoldRoadSetCities1", 1450, 45 + 3 + 644 + 3 + 98, 0, sf::Color(255, 255, 255, 255), "Soldiers:  3    Roads:  4    Settelments: 2    Cities:  4", 18);
		addObject<Label>("ResDev1", 1450, 70 + 3 + 644 + 3 + 98, 0, sf::Color(255, 255, 255, 255), "Total res.:  3    Dev. cards:  4", 18);
	}
	if (catan->catan_ai->getPlayersCount() > 3) {
		addObject<PlayerContainer>("PlayerContainer2", 1397+250, 3+644+98/2+3+98+98+3+3, kPlayerContainerWidth, 98);
		addObject<Label>("LabelLargestRoad2", 1641, 14 + 3 + 644 + 3 + 98 + 3 + 98, 0, sf::Color(100, 228, 255, 255), "L. Road (0)", 18);		
		addObject<Label>("LabelLargestArmy2", 1745, 14 + 3 + 644 + 3 + 98 + 3 + 98, 0, sf::Color(100, 228, 255, 255), "L. Army (0)", 18);

		addObject<Rectangl>("RobotIcon2", BoardObjects::icon, Sprites::ID::robot, 1397 + 25, 10 + 30 / 2 + 3 + 644 + 3 + 98 + 3 + 98, 26, 30, 0);
		addObject<Label>("AIName2", 1450, 14 + 3 + 644 + 3 + 98 + 3 + 98, 0, sf::Color(255, 255, 255, 255), "AI #4", 18);

		addObject<Rectangl>("ScoreSquare2", BoardObjects::icon, sf::Color(255, 255, 255, 255), 2, sf::Color(255, 0, 0, 0), 1534 + 70, 10 + 30 / 2 + 3 + 644 + 3 + 98 + 3 + 98, 26, 26, 0);
		addObject<Label>("LabelScore2", 1534 + 62, 13 + 3 + 644 + 3 + 98 + 3 + 98, 0, sf::Color(255, 255, 255, 255), "7", 18);
		addObject<Label>("LabelScoreScore2", 1530, 14 + 3 + 644 + 3 + 98 + 3 + 98, 0, sf::Color(255, 255, 255, 255), "Score:", 18);

		addObject<Label>("SoldRoadSetCities2", 1450, 45 + 3 + 644 + 3 + 98 + 3 + 98, 0, sf::Color(255, 255, 255, 255), "Soldiers:  3    Roads:  4    Settelments: 2    Cities:  4", 18);
		addObject<Label>("ResDev2", 1450, 70 + 3 + 644 + 3 + 98 + 3 + 98, 0, sf::Color(255, 255, 255, 255), "Total res.:  3    Dev. cards:  4", 18);
	}

	//button next turn
	addObject<Btn>("ButtonNextTurn", 1773+115/2, 595+44/2, 115, 44, 0,
		sf::Color(89, 89, 89, 255), 2, sf::Color(142, 205, 246, 255),
		sf::Color(103, 161, 199, 255), sf::Color(89, 89, 89, 255), sf::Color(255, 255, 255, 255),
		sf::Color(213, 126, 3), sf::Color(89, 89, 89, 255), sf::Color(255, 255, 255, 255),
		sf::Color(255, 255, 255, 255), "Done", 17,
		objButtonEvents::nextTurn);	

	//Roads && Cities hooker

	int city_hook_x = kHexBoardX;
	int city_hook_y = kHexBoardY - 200/2;
	int counter = 1;

	for (auto i = 0, j = 3; i < 7; i++, j += counter) {
		for (auto l = 0; l < 2; l++) {
			for (auto k = 0; k < j; k++) {

				//roads
				if ((l == 0) && ((i != 0) && (i != 6))) {					
					addObject<roadHooks>("roadHooks" + std::to_string(roadHooks::road_hook_id), 
						city_hook_x + 3, city_hook_y + kRoadHeight / 2 + 2, 0);
				}

				if ((l != 0) || (i == 0)) {
					if ((k < (j - 1)) || (i < 3)) {
						addObject<roadHooks>("roadHooks" + std::to_string(roadHooks::road_hook_id), 
							city_hook_x + kCityWidth - kRoadWidth / 2 - 2, city_hook_y + kCityWidth / 2 - 4, -60.2f);
					}

					if ((k > 0) || (i < 3)) {
						addObject<roadHooks>("roadHooks" + std::to_string(roadHooks::road_hook_id),
							static_cast<float>(city_hook_x - kCityWidth + kRoadWidth), city_hook_y + kCityHeight / 2 - 4, 60.2f);
					}
				}
				
				addObject<buildingHooks>("BuildingHook" + std::to_string(buildingHooks::building_hook_id), city_hook_x, city_hook_y);

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
	
	addObject<BoardBuilding>("BoardBuildingCity", Sprites::ID::redCity, 1397 + 421, 171);
	addObject<BoardBuilding>("BoardBuildingSettelment", Sprites::ID::redSet, 1397 + 421, 171 - 56 - 10);
	addObject<BoardRoad>("BoardRoad", Sprites::ID::redRoad, 1397 + 421 + 56/2 +15, 171-30);

	addObject<UpdateAbstractClass>("UpdClass");
}

template<typename T1, typename ...Types>
void Board::addObject(const std::string& name, Types&& ...args)
{
	std::unique_ptr<T1> obj(new T1(name, std::forward<Types>(args)...));
	auto inserted = Objects.insert(std::make_pair(Key(obj->getObjectId(), name), std::move(obj)));
	assert(inserted.second);
}

std::unique_ptr<Drag> Board::drag = std::unique_ptr<Drag>(new Drag());

Board::Board()
{
	//drag = std::unique_ptr<Drag>(new Drag());
}

Object * Board::GetObject(int x, int y) {

	for (auto it = Objects.rbegin(); it != Objects.rend(); ++it) {
		if (it->second->OnMouseOver(x, y)) {
			
			if (drag->IsDraggring()) {
				if ((drag->get() == it->second.get()) || (!it->second->IsDragObjectAcceptable(drag->get()))) {
					std::cout << "ID: " << it->second->getObjectId() << ", X = " << x << ", Y = " << y << std::endl;
					//return nullptr;
					continue;
				}
			}

			std::cout << "ID: " << it->second->getObjectId() << ", X = " << x << ", Y = " << y << std::endl;

			return &(*it->second);
		}
	}
	return nullptr;
}

Object* Board::GetObjectByName(const std::string& name)
{
	for (auto const& obj : Objects) {
		if (obj.first.name == name) {
			return (obj.second.get());
		}
	}
	return nullptr;
}

void Board::Draw()
{
	for (auto it = Objects.begin(); it != Objects.end(); ++it)
	{
		if (!(it->second->IsHidden())) {			
			it->second->OnDraw();
		}
	}
}

void Board::Update()
{
	for (auto it = Objects.begin(); it != Objects.end(); ++it)
	{
		if (!(it->second->IsHidden())) {
			it->second->Update();
		}
	}
	drag->Update();
}

void Board::handleMouseEvent(sf::Event event)
{
	objUnderCursor = Board::GetObject(catan->mouse.x, catan->mouse.y);

	if (event.type == sf::Event::MouseButtonPressed) {
		if (objUnderCursor != nullptr) {
			objPressed = objUnderCursor;
			objPressed->OnMouseDown(catan->mouse.x, catan->mouse.y, event.mouseButton.button);
		}		
	}

	if (event.type == sf::Event::MouseButtonReleased) {
		if (objPressed != nullptr) {
			if (drag->IsDraggring()) {	//if object dragging

				bool acceptedDrag = false;	//check if dragged object is accepted
				if (objUnderCursor != nullptr) {	//is object under cursor
					acceptedDrag = objUnderCursor->OnDragDrop(drag->get());	//try to drop dragged object and check if it was accepted
				}

				drag->Stop(acceptedDrag);	//finish dragging
			}
			else {
				objPressed->OnMouseUp(event.mouseButton.button);
			}
			objPressed = nullptr;
		}
	}

	if (event.type == sf::Event::MouseMoved) {
		if (objPressed != nullptr) {
			if (!drag->IsDraggring()) {
				if (objPressed->IsDraggable()) {	//true if object draggable
					drag->Start(objPressed);		//start dragging
				}
				else {
					if (objUnderCursor != nullptr) {
						objUnderCursor->OnMouseMove();
					}
				}
			}
			else {
				if (objUnderCursor != nullptr) {
					objUnderCursor->OnDragOver(drag->get());
				}
				objPressed->OnDrag();
			}
		}
		else {
			if (objUnderCursor != nullptr) {
				objUnderCursor->OnMouseMove();
			}
		}

		if ((lastobjUnderCursor != objUnderCursor) && (lastobjUnderCursor != nullptr)) {
			lastobjUnderCursor->OnMouseLeave();
		}
	}

	if (event.type == sf::Event::MouseLeft) {
		if (objPressed != nullptr) {
			if (drag->IsDraggring()) {
				drag->Stop();
			}
			else {
				objPressed->OnMouseUp(event.mouseButton.button);
			}
			objPressed = nullptr;
		}
		if (lastobjUnderCursor != nullptr)
		{
			lastobjUnderCursor->OnMouseLeave();
			lastobjUnderCursor = nullptr;
		}		
	}

	lastobjUnderCursor = objUnderCursor;
}
