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
			addObject<BoardHex>(_x, hex_y);
		}
	}
	for (auto i = 6, x = hex_x + hex_rect.width, y = hex_y; i > 4; i--, x += hex_rect.width / 2, hex_y += kHexBoardYStep, hex_x = x) {
		for (auto j = i, _x = x; j > 2; j--, _x += hex_rect.width) {
			addObject<BoardHex>(_x, hex_y);
		}
	}

	//borders with harbors
	addObject<BoardBorder>(223, 76, 30);
	addObject<BoardBorder>(759, -4, 90);
	addObject<BoardBorder>(1098, 419, 150);
	addObject<BoardBorder>(900, 924, 210);
	addObject<BoardBorder>(363, 1004, 270);
	addObject<BoardBorder>(24, 581, 330);

	//button generate hex
	addObject<Btn>(1830, 900, 65, 24, 0,
		sf::Color(89, 89, 89, 255), 2, sf::Color(255, 60, 0, 255),
		sf::Color(255, 0, 0, 255), sf::Color(89, 89, 89, 255), sf::Color(255, 255, 255, 255),
		sf::Color(213, 126, 3), sf::Color(89, 89, 89, 255), sf::Color(255, 255, 255, 255),
		sf::Color(255, 255, 255, 255), "Generate", 11,
		objButtonEvents::genHexes);		

	//PlayerContainer
	addObject<PlayerContainer>(1397+250, 3+644/2);	

	//label longest road
	addObject<Label>(1641, 14, 0, sf::Color(100, 228, 255, 255), "L. Road (0)", 16);

	//button next turn
	addObject<Btn>(1773+115/2, 595+44/2, 115, 44, 0,
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
					addObject<roadHooks>(city_hook_x + 3, city_hook_y + kRoadHeight / 2 + 2, 0);
				}

				if ((l != 0) || (i == 0)) {
					if ((k < (j - 1)) || (i < 3)) {
						addObject<roadHooks>(city_hook_x + kCityWidth - kRoadWidth / 2 - 2, city_hook_y + kCityWidth / 2 - 4, -60.2f);
					}

					if ((k > 0) || (i < 3)) {
						addObject<roadHooks>(static_cast<float>(city_hook_x - kCityWidth + kRoadWidth), city_hook_y + kCityHeight / 2 - 4, 60.2f);
					}
				}
				
				addObject<buildingHooks>(city_hook_x, city_hook_y);

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

	addObject<BoardBuilding>(Sprites::ID::redCity, 1397 + 421, 171);
	addObject<BoardBuilding>(Sprites::ID::redSet, 1397 + 421, 171 - 56 - 10);
	addObject<BoardRoad>(Sprites::ID::redRoad, 1397 + 421 + 56/2 +15, 171-30);	

}

template<typename T, typename ...Types>
void Board::addObject(Types&& ...args)
{
	std::unique_ptr<T> obj(new T(std::forward<Types>(args)...));
	auto inserted = Objects.insert(std::make_pair(obj->getObjectId(), std::move(obj)));
	assert(inserted.second);
}

std::unique_ptr<Drag> Board::drag = std::unique_ptr<Drag>(new Drag());

Board::Board()
{
	//drag = std::unique_ptr<Drag>(new Drag());
}

Object * Board::GetObject(int x, int y) {

	for (std::map<unsigned int, std::unique_ptr<Object>>::reverse_iterator it = Objects.rbegin(); it != Objects.rend(); ++it) {
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
