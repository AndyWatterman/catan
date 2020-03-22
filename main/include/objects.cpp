#include "stdafx.h"
#include "objects.h"

unsigned int Object::ObjectIDs = 0;
unsigned int BoardHex::hex_id = 0;
unsigned int BoardBorder::border_id = 0;

Object::Object(CatanGUI & _catan, BoardObjects::ID _type) :
	catan(_catan), objectType(_type), objectId(ObjectIDs)
{
	ObjectIDs++;
}

BoardHex::BoardHex(CatanGUI & _catan, float x, float y, float angle):	
	RectangleObject(_catan, BoardObjects::hex, Sprites::hex_free, 176, 200, x, y, angle)
{
	current_hex_id = hex_id++;
		
	diceSprite = catan.GetSprite(Sprites::n10);
	sf::FloatRect fr = getGlobalBounds();
	diceSprite.setPosition(fr.left + fr.width / 2 - 56 / 2, fr.top + fr.height / 2 - 56 / 2);
}

const unsigned int BoardHex::getCurrentHexId()
{
	return (current_hex_id);
}

const int BoardHex::getDice()
{
	return (dice);
}

void BoardHex::OnMouseDown(int x, int y, sf::Mouse::Button button)
{
	isPressed = true;
}

void BoardHex::OnMouseMove(float x, float y)
{
	if (getSpriteID() == Sprites::hex_free) {
		setTextureRect(catan.GetSprite(Sprites::hex_hover).getTextureRect());
	}
}

void BoardHex::OnMouseLeave()
{	
	setTextureRect(catan.GetSprite(getSpriteID()).getTextureRect());
	isPressed = false;
}

void BoardHex::OnMouseUp(sf::Mouse::Button button)
{
	if (isPressed) {
		isPressed = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
			if (getSpriteID() >= Sprites::desert) {
				setSpriteID(Sprites::stone);
			}
			else {
				setSpriteID(static_cast<Sprites::ID>(getSpriteID() + 1));
			}

			catan.catan_ai->setHexResource(getCurrentHexId(), static_cast<resource>(getSpriteID()));
		}
	}
}

void BoardHex::OnDraw()
{
	catan.GetWindow().draw(*this);
	if (getDice() > 0) {
		catan.GetWindow().draw(diceSprite);
	}
}

void BoardHex::setDice(int _dice)
{
	if (_dice > 0) {		
		diceSprite.setTextureRect(catan.GetSprite(static_cast<Sprites::ID>(_dice)).getTextureRect());		
	}	
	dice = _dice;
}

Btn::Btn(CatanGUI & _catan, float x, float y, Sprites::ID normal, Sprites::ID pressed, objButtonEvents event) :	
	RectangleObject(_catan, BoardObjects::button, normal, 96, 27, x, y, 0)
{
	Btn::pressed = catan.GetSprite(pressed);	
	Btn::pressed.setPosition(x, y);
	Btn::event = event;	
}

Btn::Btn(CatanGUI & _catan, float x, float y, int width, int height, float angle,
	const sf::Color & OutlineColor, float OutlineThickness, const sf::Color & FillColor,
	const sf::Color & HoverFillColor, const sf::Color & HoverOutlineColor,
	const sf::Color & PressedFillColor, const sf::Color & PressedOutlineColor,
	const sf::Color &textColor, const std::string & text, int textSize,
	objButtonEvents event) :
	RectangleObject(_catan, BoardObjects::button, OutlineColor, OutlineThickness, FillColor,
		x, y, width, height, angle),
	OutlineColor(OutlineColor), FillColor(FillColor), HoverFillColor(HoverFillColor), HoverOutlineColor(HoverOutlineColor),
	PressedFillColor(PressedFillColor), PressedOutlineColor(PressedOutlineColor), text(text),
	event(event)
{
	font.loadFromFile(kFont);
	caption.setFont(font);
	caption.setString(text);
	caption.setCharacterSize(textSize);
	caption.setFillColor(textColor);

	const sf::FloatRect bounds(caption.getLocalBounds());
	const sf::Vector2f box(RectangleObject::getSize());
	caption.setPosition(x, y);
	caption.setRotation(angle);
	//caption.setStyle(sf::Text::Bold);
	caption.setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);
}

void Btn::setBtnState(btnStates state)
{
	switch (state) {
		case normal:
			setOutlineColor(OutlineColor);
			setFillColor(FillColor);
			break;

		case hover:
			setOutlineColor(HoverOutlineColor);
			setFillColor(HoverFillColor);
			break;

		case btnStates::pressed:
			setOutlineColor(PressedOutlineColor);
			setFillColor(PressedFillColor);
	}
}


void Btn::OnMouseDown(int x, int y, sf::Mouse::Button button)
{
	isPressed = true;
	if (!getTexture()) {
		setBtnState(btnStates::pressed);
	}
}

void Btn::OnMouseLeave()
{
	isPressed = false;
	if (!getTexture()) {
		setBtnState(btnStates::normal);
	}
}

void Btn::OnMouseMove(float x, float y)
{
	if (!getTexture()) {
		setBtnState(btnStates::hover);
	}
}

void Btn::OnMouseUp(sf::Mouse::Button button)
{
	if (isPressed) {
		isPressed = false;

		if (!getTexture()) {
			setBtnState(btnStates::hover);
		}

		processBtnEvent(catan, event);
	}
}

void Btn::OnDraw()
{
	if (getTexture()) {
		if (!isPressed) {
			catan.GetWindow().draw(*this);
		}
		else {
			catan.GetWindow().draw(pressed);
		}
	}
	else {
		catan.GetWindow().draw(*this);
		catan.GetWindow().draw(caption);
	}
}

void Btn::processBtnEvent(CatanGUI & catan, objButtonEvents event)
{
	switch (event) {
        case genHexes:
			std::cout << "genHexesPressed" << std::endl;
			catan.catan_ai->genNewHexes();
			catan.board->UpdateHexesAndDices();
			break;

        case nextTurn:
			std::cout << "nextTurnPressed" << std::endl;
			catan.catan_ai->nextTurn();
			break;
    }
}

BoardBorder::BoardBorder(CatanGUI & _catan, Sprites::ID spriteId, float x, float y, double angle):	
	RectangleObject(_catan, BoardObjects::borders, spriteId, 153, 547, x, y, angle)
{	
	current_border_id = border_id++;
}

const unsigned int BoardBorder::getCurrentBorderId()
{
	return (current_border_id);
}

void BoardBorder::OnMouseUp(sf::Mouse::Button button)
{
	if (isPressed) {
		isPressed = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
			if (getSpriteID() >= Sprites::harbor_wood) {
				setSpriteID(Sprites::harbor_stone);
			}
			else {
				setSpriteID(static_cast<Sprites::ID>(getSpriteID() + 1));
			}

			catan.catan_ai->setBorderType(getCurrentBorderId(), static_cast<resource>(getSpriteID() - Sprites::harbor_stone));
		}
	}
}

void BoardBorder::OnMouseDown(int x, int y, sf::Mouse::Button button)
{
	isPressed = true;
}

void BoardBorder::OnMouseLeave()
{
	isPressed = false;
}

void BoardBorder::setHarbor(int h)
{
	Sprites::ID sId;

	switch (h) {
		case 0: sId = Sprites::harbor_stone;
			break;
		case 1: sId = Sprites::harbor_3_brick;
			break;
		case 2: sId = Sprites::harbor_3_sheep;
			break;
		case 3: sId = Sprites::harbor_3;
			break;
		case 4: sId = Sprites::harbor_3_weat;
			break;
		case 5: sId = Sprites::harbor_wood;
			break;

	default:
		break;
	}

	setSpriteID(sId);
}

RectangleObject::RectangleObject(CatanGUI & _catan, BoardObjects::ID _type, 
	sf::Color OutlineColor, float OutlineThickness, sf::Color FillColor,
	float x, float y, int width, int height, float angle)
	:Object(_catan, _type)
{
	setSize(sf::Vector2f(width, height));
	setRotation(angle);
	setOutlineColor(OutlineColor);
	setOutlineThickness(OutlineThickness);
	RectangleShape::setPosition(x, y);
	setFillColor(FillColor);	
}

//Load only sprite
RectangleObject::RectangleObject(CatanGUI & _catan, BoardObjects::ID _type, 
	Sprites::ID spriteId, int width, int height, float x, float y, float angle)
	:Object(_catan, _type)
{
	setSize(sf::Vector2f(width, height));
	setRotation(angle);
	RectangleShape::setPosition(x, y);
	
	RectangleObject::sprite_id = spriteId;

	if (RectangleObject::sprite_id != Sprites::ID::none) {
		setTexture(&catan.GetTexture(Resources::all));
		setTextureRect(catan.GetSprite(spriteId).getTextureRect());
	};
}

void RectangleObject::setSpriteID(Sprites::ID sp)
{
	sprite_id = sp;

	if (sprite_id != Sprites::ID::none) {
		setTexture(&catan.GetTexture(Resources::all), true);
		setTextureRect(catan.GetSprite(sp).getTextureRect());
	}
	else {
		setTexture(nullptr, true);
	};
}

PlayerContainer::PlayerContainer(CatanGUI & _catan, BoardObjects::ID _type,
	int player_id, float x, float y) :
	RectangleObject(_catan, _type, sf::Color(85, 85, 85, 255), 3,
		kPlayerColors[_catan.catan_ai->getCurrentPlayer()], x, y,
		kPlayerContainerWidth, kPlayerContainerHeight, 0)
{

}

void PlayerContainer::Update()
{
	setFillColor(kPlayerColors[catan.catan_ai->getCurrentPlayer()]);
}

unsigned int cityHooks::city_hook_id = 0;

cityHooks::cityHooks(CatanGUI & _catan, float x, float y):
	RectangleObject(_catan, BoardObjects::cityHooks, sf::Color(), 0,
		sf::Color(0,0,0,0), x, y, 56, 56, 0)
{
	point = city_hook_id++;

	sf::Vector2f orig = getSize();
	setOrigin(orig.x / 2, orig.y / 2);

	setDragRectangle(true);
}

bool cityHooks::IsDragObjectAcceptable(Object* obj)
{
	bool result = false;

	if (obj != nullptr) {
		const Sprites::ID _id = obj->getSpriteID();
		if ((_id >= Sprites::redSet) && (_id <= Sprites::brownCity))		
			result = true;		
	}

	return (result);
}

bool cityHooks::OnDragDrop(Object* obj)
{
	catan.drag->GetObject()->Show();
	
	int objType = obj->getObjectType();
	Building* building = catan.catan_ai->game_state->buildings->getBuilding(point);

	if (((objType == BoardObjects::city) && (building != nullptr) && (building->type == settelment) && (building->id == catan.catan_ai->getCurrentPlayer()))
		|| ((objType == BoardObjects::settelment) && (building == nullptr))
		|| ((objType == BoardObjects::cityHooks)))
	{
		if (((!catan.catan_ai->game_state->buildings->IsThereBuildingsAround(point))
			&& (catan.catan_ai->game_state->roads->IsRoadPointExists(point)))
			|| (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))) {

			if (objType == BoardObjects::cityHooks) {

				cityHooks* dropObjCityHook = dynamic_cast<cityHooks*>(obj);

				int dropObjPoint = dropObjCityHook->point;
				Building* building = catan.catan_ai->game_state->buildings->getBuilding(dropObjPoint);
				int owner = building->id;
				building_types type = building->type;

				catan.catan_ai->game_state->buildings->DeleteSettelement(point);
				catan.catan_ai->game_state->buildings->DeleteSettelement(dropObjPoint);
				catan.catan_ai->game_state->buildings->AddSettelement(point, owner);

				if (type == city)
					catan.catan_ai->game_state->buildings->UpgradeBuilding(point);				
			}
			else {
				catan.catan_ai->game_state->buildings->DeleteSettelement(point);
				catan.catan_ai->game_state->buildings->AddSettelement(point, catan.catan_ai->getCurrentPlayer());
				if (objType == BoardObjects::city)
					catan.catan_ai->game_state->buildings->UpgradeBuilding(point);
			}
			
			return true;
		}
	}
	
	return false;
}

void cityHooks::OnDragOver(Object* obj)
{
	if (catan.drag->IsDraggring()) {		
		int objType = obj->getObjectType();
		Building* building = catan.catan_ai->game_state->buildings->getBuilding(point);

		if (((objType == BoardObjects::city) && (building != nullptr) && (building->type == settelment) && (building->id == catan.catan_ai->getCurrentPlayer()))
			|| ((objType == BoardObjects::settelment) && (building == nullptr))
			|| ((objType == BoardObjects::cityHooks)))
		{
			if (((!catan.catan_ai->game_state->buildings->IsThereBuildingsAround(point))				
				&& (catan.catan_ai->game_state->roads->IsRoadPointExists(point)))
				|| (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))) {	

				setSpriteID(obj->getSpriteID());
				catan.drag->GetObject()->Hide();
				setFillColor(sf::Color(255, 255, 255, 255));

			}
		}
	}
}

void cityHooks::OnMouseLeave()
{
	if (catan.drag->IsDraggring()){
		setSpriteID(old_sprite_id);		
		catan.drag->GetObject()->Show();
		
		if (old_sprite_id == Sprites::none) {
			setFillColor(sf::Color(0, 0, 0, 0));
		}
	}	
}

bool cityHooks::OnStartDrag()
{
	bool result = false;
	if ((getSpriteID() != Sprites::ID::none) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))) {	
		result = true;
	}
	return (result);
}

void cityHooks::OnEndDrag(bool accepted)
{
	//TODO DELETE!
	if (catan.mouse_x > 1100) {
		catan.catan_ai->game_state->buildings->DeleteSettelement(point);
	}
	else {
		if (accepted) {
			catan.catan_ai->game_state->buildings->DeleteSettelement(point);
		}
	}
	catan.drag->ReturnBack(accepted);
}

void cityHooks::Update()
{
	if (!catan.drag->IsDraggring()) {
		Building * building = catan.catan_ai->getBuilding(point);
		if (building != nullptr) {						
			setFillColor(sf::Color(255, 255, 255, 255));
			if (building->type == settelment) {
				setSpriteID(static_cast<Sprites::ID>(Sprites::ID::redSet + building->id));
			}
			else if (building->type == city) {
				setSpriteID(static_cast<Sprites::ID>(Sprites::ID::redCity + building->id));
			}			
		}
		else {
			setSpriteID(Sprites::ID::none);
			setFillColor(sf::Color(0, 0, 0, 0));
		}
		old_sprite_id = getSpriteID();
	}
}

unsigned int roadHooks::road_hook_id = 0;

roadHooks::roadHooks(CatanGUI & _catan, float x, float y, double angle) :
	RectangleObject(_catan, BoardObjects::roadHooks, sf::Color(), 0,
		sf::Color(0, 0, 0, 0), x, y, kRoadWidth, kRoadHeight, angle)
{
	sf::Vector2f orig = getSize();
	setOrigin(orig.x / 2, orig.y / 2);

	road_id = road_hook_id++;
}

bool roadHooks::IsDragObjectAcceptable(Object* obj)
{
	bool result = false;

	if (obj != nullptr) {
		const Sprites::ID _id = obj->getSpriteID();
		if ((_id >= Sprites::redRoad) && (_id <= Sprites::brownRoad))
			result = true;
	}

	return (result);
}

bool roadHooks::OnDragDrop(Object* obj)
{	
	catan.drag->GetObject()->Show();
	int objType = obj->getObjectType();

	if ((objType == BoardObjects::road) ||
		((objType == BoardObjects::roadHooks)))
	{
		DFSTracePathPoints AllPathPoints(*catan.catan_ai->game_state.get());
		if ((AllPathPoints.IsItPossibleToBuildRoad(road_id_to_from_to[road_id][0], road_id_to_from_to[road_id][1]))
			|| (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))) {

			if (objType == BoardObjects::roadHooks) {

				roadHooks* dropObjId = dynamic_cast<roadHooks*>(obj);
				unsigned int rId = dropObjId->getRoadId();
				int newRoadId = catan.catan_ai->game_state->roads->getRoad(road_id_to_from_to[rId][0], road_id_to_from_to[rId][1])->id;

				catan.catan_ai->game_state->roads->DeleteRoad(road_id_to_from_to[road_id][0], road_id_to_from_to[road_id][1]);
				catan.catan_ai->game_state->roads->DeleteRoad(road_id_to_from_to[rId][0], road_id_to_from_to[rId][1]);
				catan.catan_ai->game_state->roads->AddRoad(road_id_to_from_to[road_id][0], road_id_to_from_to[road_id][1], newRoadId);
			}
			else {
				catan.catan_ai->game_state->roads->DeleteRoad(road_id_to_from_to[road_id][0], road_id_to_from_to[road_id][1]);
				catan.catan_ai->game_state->roads->AddRoad(road_id_to_from_to[road_id][0], road_id_to_from_to[road_id][1], catan.catan_ai->getCurrentPlayer());
			}

			return true;
		}
	}	
	return false;
}

void roadHooks::OnDragOver(Object* obj)
{
	if (catan.drag->IsDraggring()) {
		int objType = obj->getObjectType();

		if ((objType == BoardObjects::road) ||
			((objType == BoardObjects::roadHooks)))
		{			
			DFSTracePathPoints AllPathPoints(*catan.catan_ai->game_state.get());			
			if ((AllPathPoints.IsItPossibleToBuildRoad(road_id_to_from_to[road_id][0], road_id_to_from_to[road_id][1]))
				|| (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))) {

				AllPathPoints.PrintAllPathPoints();
				setSpriteID(obj->getSpriteID());
				catan.drag->GetObject()->Hide();
				setFillColor(sf::Color(255, 255, 255, 255));

			}
		}
	}
}

void roadHooks::OnMouseLeave()
{
	if (catan.drag->IsDraggring()) {
		setSpriteID(old_sprite_id);
		catan.drag->GetObject()->Show();

		if (old_sprite_id == Sprites::none) {
			setFillColor(sf::Color(0, 0, 0, 0));
		}
	}
}

bool roadHooks::OnStartDrag()
{
	bool result = false;
	if ((getSpriteID() != Sprites::ID::none) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))) {
		result = true;
	}
	return (result);
}

void roadHooks::OnEndDrag(bool accepted)
{
	//TODO DELETE!
	if (catan.mouse_x > 1100) {
		catan.catan_ai->game_state->roads->DeleteRoad(road_id_to_from_to[road_id][0], road_id_to_from_to[road_id][1]);
	}
	else {
		if (accepted) {
			catan.catan_ai->game_state->roads->DeleteRoad(road_id_to_from_to[road_id][0], road_id_to_from_to[road_id][1]);
		}
	}
	catan.drag->ReturnBack(accepted);
}

void roadHooks::Update()
{
	if (!catan.drag->IsDraggring()) {
		Road* road = catan.catan_ai->game_state->roads->getRoad(road_id_to_from_to[road_id][0], road_id_to_from_to[road_id][1]);
		if (road != nullptr) {
			setFillColor(sf::Color(255, 255, 255, 255));			
			setSpriteID(static_cast<Sprites::ID>(Sprites::ID::redRoad + road->id));
		}
		else {
			setSpriteID(Sprites::ID::none);
			setFillColor(sf::Color(0, 0, 0, 0));
		}
		old_sprite_id = getSpriteID();
	}
}

City::City(CatanGUI & _catan, Sprites::ID spriteId, float x, float y):
	RectangleObject(_catan, BoardObjects::city, spriteId, 56, 56, x, y, 0)
{
	sf::Vector2f orig = getSize();
	setOrigin(orig.x/2, orig.y/2);
}

void City::Update()
{
	setSpriteID(static_cast<Sprites::ID>(Sprites::ID::redCity + catan.catan_ai->getCurrentPlayer()));
}

Settelment::Settelment(CatanGUI& _catan, Sprites::ID spriteId, float x, float y):
	RectangleObject(_catan, BoardObjects::settelment, spriteId, 56, 56, x, y, 0)
{
	sf::Vector2f orig = getSize();
	setOrigin(orig.x / 2, orig.y / 2);
}

void Settelment::Update()
{
	setSpriteID(static_cast<Sprites::ID>(Sprites::ID::redSet + catan.catan_ai->getCurrentPlayer()));
}

BoardRoad::BoardRoad(CatanGUI& _catan, Sprites::ID spriteId, float x, float y) :
	RectangleObject(_catan, BoardObjects::road, spriteId, 16, 102, x, y, 0)
{
	sf::Vector2f orig = getSize();
	setOrigin(orig.x / 2, orig.y / 2);
}

void BoardRoad::Update()
{
	setSpriteID(static_cast<Sprites::ID>(Sprites::ID::redRoad + catan.catan_ai->getCurrentPlayer()));
}

Label::Label(CatanGUI& _catan, float x, float y, double angle, const sf::Color& textColor, const std::string& text, int textSize, objButtonEvents event)
	: Object(_catan, BoardObjects::label)
{
	font.loadFromFile(kFont);
	setFont(font);
	setString(text);
	setCharacterSize(textSize);
	setFillColor(textColor);
	sf::Text::setPosition(x, y);
	setRotation(angle);
}

void Label::OnDraw()
{
	catan.GetWindow().draw(*this);
}
