#include "stdafx.h"
#include "objects.h"

unsigned int Object::ObjectIDs = 0;
unsigned int BoardHex::hex_id = 0;
unsigned int BoardBorder::border_id = 0;
unsigned int roadHooks::road_hook_id = 0;

Object::Object(BoardObjects _type) :
	objectType(_type), objectId(ObjectIDs)
{
	ObjectIDs++;
}

bool Object::IsHidden() const
{
	return hidden;
}

bool Object::IsActive() const
{
	return active;
}

bool Object::IsDraggable() const
{
	return draggable;
}

void Object::Disable()
{
	active = false;
}

void Object::Enable()
{
	active = true;
}

void Object::Hide()
{
	hidden = true;
}

void Object::Show()
{
	hidden = false;
}

void Object::TurnDragOn()
{
	draggable = true;
}

void Object::TurnDragOff()
{
	draggable = false;
}

unsigned int Object::getObjectId() const
{
	return objectId;
}

BoardObjects Object::getObjectType() const
{
	 return (objectType);
}

void Object::OnMouseDown(int x, int y, sf::Mouse::Button button)
{
}

void Object::OnMouseMove()
{
}

bool Object::OnMouseOver(float x, float y)
{
	return false;
}

void Object::OnMouseUp(sf::Mouse::Button button)
{
}

void Object::OnMouseLeave()
{
}

bool Object::OnDragDrop(Object* obj)
{
	return false;
}

void Object::OnDrag()
{
}

void Object::OnDragOver(Object* obj)
{
}

void Object::OnStartDrag()
{
}

bool Object::OnEndDrag(bool accepted)
{
	return false;
}

bool Object::IsDragObjectAcceptable(Object* obj)
{
	return false;
}

void Object::Update()
{
}

BoardHex::BoardHex(float x, float y):
	Rectangle(BoardObjects::hex, Sprites::ID::hex_free, x, y, 176, 200, 0)
{
	current_hex_id = hex_id++;
		
	diceSprite = catan->GetSprite(Sprites::ID::n10);	//only to calculate position
	sf::FloatRect fr = getGlobalBounds();
	diceSprite.setPosition(fr.left + fr.width / 2 - 56 / 2, fr.top + fr.height / 2 - 56 / 2);

	UseTextureForDrop(true);
}


unsigned int BoardHex::getCurrentHexId() const
{
	return (current_hex_id);
}

int BoardHex::getDice() const
{
	return (dice);
}

void BoardHex::OnMouseDown(int x, int y, sf::Mouse::Button button)
{
	isPressed = true;
}

void BoardHex::OnMouseMove()
{
	if (getSpriteId() == Sprites::ID::hex_free) {
		setTextureRect(catan->GetSprite(Sprites::ID::hex_hover).getTextureRect());
	}
}

void BoardHex::OnMouseLeave()
{	
	setTextureRect(catan->GetSprite(getSpriteId()).getTextureRect());
	isPressed = false;
}


void BoardHex::OnMouseUp(sf::Mouse::Button button)
{
	if (isPressed) {
		isPressed = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
			if (getSpriteId() >= Sprites::ID::desert) {
				setSpriteID(Sprites::ID::stone);
			}
			else {
				setSpriteID(static_cast<Sprites::ID>(static_cast<int>(getSpriteId()) + 1));
			}

			catan->catan_ai->setHexResource(getCurrentHexId(), static_cast<resource>(getSpriteId()));
		}
	}
}

void BoardHex::OnDraw()
{
	catan->GetWindow().draw(*this);
	if (getDice() > 0) {
		catan->GetWindow().draw(diceSprite);
	}
}

void BoardHex::Update()
{
	setSpriteID(static_cast<Sprites::ID>(catan->catan_ai->getResourcesRef()[current_hex_id]));

	auto _dice = catan->catan_ai->getDicesRef()[current_hex_id];
	if (_dice > 0) {
		(_dice < 7) ? (_dice += 32) : (_dice += 31);
		setDice(_dice);
	}
	else {
		setDice(0);
	}
}


void BoardHex::setDice(int _dice)
{
	if ((dice = _dice) > 0) {
		diceSprite.setTextureRect(catan->GetSprite(static_cast<Sprites::ID>(dice)).getTextureRect());
	}
}

Btn::Btn(float x, float y, int width, int height, float angle,
	const sf::Color& OutlineColor, float OutlineThickness, const sf::Color& FillColor,
	const sf::Color& HoverFillColor, const sf::Color& HoverOutlineColor, const sf::Color& HoverTextColor,
	const sf::Color& PressedFillColor, const sf::Color& PressedOutlineColor, const sf::Color& PressedTextColor,
	const sf::Color& textColor, const std::string& text, int textSize, objButtonEvents event) :
	Rectangle(BoardObjects::button, OutlineColor, OutlineThickness, FillColor,x, y, width, height, angle),

	OutlineColor(OutlineColor), FillColor(FillColor), textColor(textColor), 
	HoverFillColor(HoverFillColor), HoverOutlineColor(HoverOutlineColor), HoverTextColor(HoverTextColor),
	PressedFillColor(PressedFillColor), PressedOutlineColor(PressedOutlineColor), PressedTextColor(PressedTextColor),
	text(text),	event(event)
{	
	caption.setFont(catan->getFont());
	caption.setString(text);
	caption.setCharacterSize(textSize);
	caption.setFillColor(textColor);

	/*const sf::FloatRect bounds(caption.getLocalBounds());
	const sf::Vector2f box(Rectangle::getSize());	
	caption.setRotation(angle);	
	caption.setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);
	caption.setPosition(x, y);*/

	const sf::FloatRect bounds(caption.getLocalBounds());
	caption.setOrigin(bounds.width / 2, bounds.height / 2 + bounds.top);
	caption.setPosition(x, y);
}

void Btn::setBtnState(btnStates state)
{
	switch (state) {
		case btnStates::normal:
			setOutlineColor(OutlineColor);
			setFillColor(FillColor);
			caption.setFillColor(textColor);
			break;

		case btnStates::hover:
			setOutlineColor(HoverOutlineColor);
			setFillColor(HoverFillColor);
			caption.setFillColor(HoverTextColor);
			break;

		case btnStates::pressed:
			setOutlineColor(PressedOutlineColor);
			setFillColor(PressedFillColor);
			caption.setFillColor(PressedTextColor);
	}
}


void Btn::OnMouseDown(int x, int y, sf::Mouse::Button button)
{
	isPressed = true;
	setBtnState(btnStates::pressed);	
}

void Btn::OnMouseLeave()
{
	isPressed = false;
	setBtnState(btnStates::normal);
}

void Btn::OnMouseMove()
{
	setBtnState(btnStates::hover);
}

void Btn::OnMouseUp(sf::Mouse::Button button)
{
	if (isPressed) {
		isPressed = false;		
		setBtnState(btnStates::hover);
		processBtnEvent(event);
	}
}

void Btn::OnDraw()
{
	catan->GetWindow().draw(*this);
	catan->GetWindow().draw(caption);
}

void Btn::processBtnEvent(objButtonEvents event)
{
	switch (event) {
		case objButtonEvents::genHexes:
			std::cout << "genHexesPressed" << std::endl;
			catan->catan_ai->genNewHexes();			
			break;

        case objButtonEvents::nextTurn:
			std::cout << "nextTurnPressed" << std::endl;
			catan->catan_ai->nextTurn();
			break;
    }
}

BoardBorder::BoardBorder(float x, float y, double angle):
	Rectangle(BoardObjects::borders, Sprites::ID::none, x, y, 153, 547, angle)
{	
	current_border_id = border_id++;
	setOrigin(0, 0);
	UseTextureForDrop(true);
}


unsigned int BoardBorder::getCurrentBorderId() const
{
	return (current_border_id);
}


void BoardBorder::OnMouseUp(sf::Mouse::Button button)
{
	if (isPressed) {
		isPressed = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
			if (getSpriteId() >= Sprites::ID::harbor_wood) {
				setSpriteID(Sprites::ID::harbor_stone);
			}
			else {
				setSpriteID(static_cast<Sprites::ID>(static_cast<int>(getSpriteId()) + 1));
			}

			catan->catan_ai->setBorderType(getCurrentBorderId(), 
				static_cast<resource>(static_cast<int>(getSpriteId()) - static_cast<int>(Sprites::ID::harbor_stone)));
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
	Sprites::ID sId = Sprites::ID::none;

	switch (h) {
		case 0: sId = Sprites::ID::harbor_stone;
			break;
		case 1: sId = Sprites::ID::harbor_3_brick;
			break;
		case 2: sId = Sprites::ID::harbor_3_sheep;
			break;
		case 3: sId = Sprites::ID::harbor_3;
			break;
		case 4: sId = Sprites::ID::harbor_3_weat;
			break;
		case 5: sId = Sprites::ID::harbor_wood;
			break;

	default:
		break;
	}

	setSpriteID(sId);
}

void BoardBorder::Update()
{
	std::vector<resource>& harbors = catan->catan_ai->getHarborsRef();
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
			setHarbor(rowHRes / 5);
			break;
		}
	}
}

Rectangle::Rectangle(BoardObjects _type,
	sf::Color OutlineColor, float OutlineThickness, sf::Color FillColor,
	float x, float y, int width, int height, float angle)
	:Object(_type)
{
	setSize(sf::Vector2f(width, height));
	setRotation(angle);
	setOutlineColor(OutlineColor);
	setOutlineThickness(OutlineThickness);
	RectangleShape::setPosition(x, y);
	setFillColor(FillColor);	

	sf::Vector2f orig = getSize();
	setOrigin(orig.x / 2, orig.y / 2);
}

Rectangle::Rectangle(BoardObjects _type, Sprites::ID sprite, float x, float y, int width, int height, float angle)
	:Object(_type)
{
	setSize(sf::Vector2f(width, height));
	setRotation(angle);
	setPosition(x, y);	
	setSpriteID(sprite);

	sf::Vector2f orig = getSize();
	setOrigin(orig.x / 2, orig.y / 2);
}

Sprites::ID Rectangle::getSpriteId() const
{
	return (sprite_id);
}

void Rectangle::setSpriteID(Sprites::ID sprite)
{
	if (sprite != sprite_id) {
		if (sprite != Sprites::ID::none) {
			setTexture(&catan->GetTexture(Resources::ID::all), true);
			setTextureRect(catan->GetSprite(sprite).getTextureRect());
		}
		else {
			setTexture(nullptr, true);
		};
		sprite_id = sprite;
	}	
}

PlayerContainer::PlayerContainer(float x, float y) :
	Rectangle(BoardObjects::rectangle, sf::Color(85, 85, 85, 255), 3,
		kPlayerColors[catan->catan_ai->getCurrentPlayer()], x, y,
		kPlayerContainerWidth, kPlayerContainerHeight, 0)
{
	
}

bool Rectangle::IsTextureUsedForDrop() const
{
	return useTextureForDragNDrop;
}

void Rectangle::UseTextureForDrop(bool enable)
{
	useTextureForDragNDrop = enable;
}

bool Rectangle::OnMouseOver(float x, float y)
{
	if (!IsHidden()) {
		if (getGlobalBounds().contains(x, y)) {
			sf::Vector2f vec = getTransform().getInverse().transformPoint(x, y);
			
			bool mouseOnObject = false;
			sf::FloatRect lBounds = getLocalBounds();
			if ((vec.x < lBounds.width) && (vec.x >= 0)
				&& (vec.y < lBounds.height) && (vec.y >= 0)) {		

				if (!getTexture() || !IsTextureUsedForDrop()) {	//no texture, only shape					
					return (true);					
				}
				else {
					sf::IntRect rect = getTextureRect();
					const sf::Image& image = catan->GetMainImage();
					sf::Color pColor = image.getPixel(static_cast<unsigned int>(vec.x + rect.left),
						static_cast<unsigned int>(vec.y + rect.top));
					if (pColor.a) {						
						return (true);
					}
				}
			}			
		}
	}
	
	return (false);
}

void Rectangle::OnDraw()
{
	catan->GetWindow().draw(*this);
}

void PlayerContainer::Update()
{
	setFillColor(kPlayerColors[catan->catan_ai->getCurrentPlayer()]);
}

Label::Label(float x, float y, double angle, const sf::Color& textColor, const std::string& text, unsigned int textSize)
	: Object(BoardObjects::label)
{	
	setFont(catan->getFont());
	setString(text);
	setCharacterSize(textSize);
	_textColor = textColor;
	setFillColor(textColor);
	sf::Text::setPosition(x, y);
	setRotation(angle);	
}

void Label::OnDraw()
{
	catan->GetWindow().draw(*this);
}

BoardBuilding::BoardBuilding(Sprites::ID spriteId, float x, float y)
	: Rectangle(BoardObjects::building, spriteId, x, y, 56, 56, 0)
{
	if ((spriteId >= Sprites::ID::redSet) && (spriteId <= Sprites::ID::brownSet)) {
		type = building_types::settelment;
	}
	else {
		type = building_types::city;
	}

	TurnDragOn();
}

bool BoardBuilding::OnEndDrag(bool accepted)
{
	if (accepted) {
		return true;	//need to return dragging object back
	}
	return false;
}

void BoardBuilding::Update()
{
	Sprites::ID sp;
	if (type == building_types::settelment) {
		sp = Sprites::ID::redSet;
	}
	else {
		sp = Sprites::ID::redCity;
	}
	setSpriteID(static_cast<Sprites::ID>(static_cast<unsigned int>(sp) + catan->catan_ai->getCurrentPlayer()));
}

unsigned int buildingHooks::building_hook_id = 0;

buildingHooks::buildingHooks(float x, float y)	
	: Rectangle(BoardObjects::buildingHooks, sf::Color(), 0, sf::Color(0, 0, 0, 0), x, y,	56, 56, 0)
{
	point = building_hook_id++;
}

bool buildingHooks::IsDragObjectAcceptable(Object* obj)
{
	if (obj != nullptr) {
		if ((obj->getObjectType() == BoardObjects::buildingHooks) || (obj->getObjectType() == BoardObjects::building)) {
			return (true);
		}
	}
	return (false);
}

bool buildingHooks::IsDraggable() const
{	
	bool result = false;
	//if ((getSpriteId() != Sprites::ID::none) && 
	if ((type != building_types::none) &&
		((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)))) {
		result = true;
	}
	return (result);
}

bool buildingHooks::OnDragDrop(Object* obj)
{
	obj->Show();

	BoardObjects objType = obj->getObjectType();
	int oldPoint = -1;
	int owner = catan->catan_ai->getCurrentPlayer();
	building_types bType = building_types::none;

	if (objType == BoardObjects::building) {
		BoardBuilding* b = dynamic_cast<BoardBuilding*>(obj);
		bType = b->type;
	}
	else {
		if (objType == BoardObjects::buildingHooks) {
			buildingHooks* b = dynamic_cast<buildingHooks*>(obj);
			oldPoint = b->point;			
			Building* building = catan->catan_ai->game_state->buildings->getBuilding(oldPoint);
			bType = building->type;
			owner = building->id;
		}
		else {
			return false;
		}
	}

	Building* building = catan->catan_ai->game_state->buildings->getBuilding(point);

	if (((bType == building_types::city) && (building != nullptr) && (building->type == building_types::settelment) && (building->id == catan->catan_ai->getCurrentPlayer()))
		|| ((bType == building_types::settelment) && (building == nullptr) && (!catan->catan_ai->game_state->buildings->IsThereBuildingsAround(point)) && (catan->catan_ai->game_state->roads->IsRoadPointExists(point)))
		|| (objType == BoardObjects::buildingHooks)
		|| ((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)))) {
			{
				catan->catan_ai->game_state->buildings->DeleteSettelement(point);
				catan->catan_ai->game_state->buildings->AddSettelement(point, owner);

				if (bType == building_types::city)
					catan->catan_ai->game_state->buildings->UpgradeBuilding(point);

				return (true);
			}
	}

	return false;
}

void buildingHooks::OnDragOver(Object* obj)
{		
	BoardObjects objType = obj->getObjectType();
	building_types bType = building_types::none;
	Sprites::ID sp = Sprites::ID::none;

	if (objType == BoardObjects::building) {
		BoardBuilding* b = dynamic_cast<BoardBuilding*>(obj);
		bType = b->type;
		sp = b->getSpriteId();
	}
	else {
		if (objType == BoardObjects::buildingHooks) {
			buildingHooks* b = dynamic_cast<buildingHooks*>(obj);
			bType = b->type;
			sp = b->getSpriteId();
		}
		else {
			return;
		}
	}	
	
	Building* building = catan->catan_ai->game_state->buildings->getBuilding(point);

	if (((bType == building_types::city) && (building != nullptr) && (building->type == building_types::settelment) && (building->id == catan->catan_ai->getCurrentPlayer()))
		|| ((bType == building_types::settelment) && (building == nullptr) && (!catan->catan_ai->game_state->buildings->IsThereBuildingsAround(point)) && (catan->catan_ai->game_state->roads->IsRoadPointExists(point)))
		|| (objType == BoardObjects::buildingHooks)
		|| ((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)))) {
		{
				//Rectangle* rect = dynamic_cast<Rectangle*>(obj);
				setSpriteID(sp);
				setFillColor(sf::Color(255, 255, 255, 255));
				obj->Hide();
		}	
	}
}

void buildingHooks::OnMouseLeave()
{
	if (Board::drag->IsDraggring()) {
		setSpriteID(old_sprite_id);
		Board::drag->get()->Show();

		if (old_sprite_id == Sprites::ID::none) {
			setFillColor(sf::Color(0, 0, 0, 0));
		}
	}
}

bool buildingHooks::OnEndDrag(bool accepted)
{
	if (catan->mouse.x > 1100) {
		catan->catan_ai->game_state->buildings->DeleteSettelement(point);
	}
	else {
		if (accepted) {
			catan->catan_ai->game_state->buildings->DeleteSettelement(point);
			return false;
		}
	}
	return true;
	//Board::drag->ReturnBack(accepted);
}

void buildingHooks::Update()
{
	if (!Board::drag->IsDraggring()) {
		Building* building = catan->catan_ai->game_state->buildings->getBuilding(point);
		if (building != nullptr) {
			setFillColor(sf::Color(255, 255, 255, 255));
			type = building->type;
			if (type == building_types::settelment) {
				setSpriteID(static_cast<Sprites::ID>(static_cast<int>(Sprites::ID::redSet) + building->id));				
			}
			else if (type == building_types::city) {
				setSpriteID(static_cast<Sprites::ID>(static_cast<int>(Sprites::ID::redCity) + building->id));
			}
		}
		else {
			setSpriteID(Sprites::ID::none);
			setFillColor(sf::Color(0, 0, 0, 0));
			type = building_types::none;
		}
		old_sprite_id = getSpriteId();
	}
}

BoardRoad::BoardRoad(Sprites::ID spriteId, float x, float y)
	: Rectangle(BoardObjects::road, spriteId, x, y, kRoadWidth, kRoadHeight, 0)
{
	TurnDragOn();
}

bool BoardRoad::OnEndDrag(bool accepted)
{
	if (accepted) {
		return true;	//need to return dragging object back
	}
	return false;
}

void BoardRoad::Update()
{
	setSpriteID(static_cast<Sprites::ID>(static_cast<int>(Sprites::ID::redRoad) + catan->catan_ai->getCurrentPlayer()));
}

roadHooks::roadHooks(float x, float y, double angle)
	: Rectangle(BoardObjects::roadHooks, sf::Color(), 0, sf::Color(0, 0, 0, 0), x, y, kRoadWidth, kRoadHeight, angle)
{
	road_id = road_hook_id++;
}

bool roadHooks::IsDragObjectAcceptable(Object* obj)
{
	if (obj != nullptr) {
		if ((obj->getObjectType() == BoardObjects::roadHooks) || (obj->getObjectType() == BoardObjects::road)) {
			return (true);
		}
	}
	return (false);
}

bool roadHooks::IsDraggable() const
{
	bool result = false;
	if ((getSpriteId() != Sprites::ID::none) && 	
		((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)))) {
		result = true;
	}
	return (result);
}

bool roadHooks::OnDragDrop(Object* obj)
{
	obj->Show();
	BoardObjects objType = obj->getObjectType();
	Roads* _roads = catan->catan_ai->game_state->roads.get();

	int newRoadPlayerId;
	int OldRoadId = -1;	

	switch (objType)
	{
	case BoardObjects::road: {
		newRoadPlayerId = catan->catan_ai->getCurrentPlayer();
		break;
	}

	case BoardObjects::roadHooks: {
		roadHooks* dropObj = dynamic_cast<roadHooks*>(obj);
		OldRoadId = dropObj->road_id;
		Road* rd = _roads->getRoad(road_id_to_from_to[dropObj->road_id][0], road_id_to_from_to[dropObj->road_id][1]);
		newRoadPlayerId = rd->id;
		break;
	}

	default:
		return false;
	}

	DFSTracePathPoints AllPathPoints(*catan->catan_ai->game_state.get(), newRoadPlayerId);
	if ((AllPathPoints.IsItPossibleToBuildRoad(road_id_to_from_to[road_id][0], road_id_to_from_to[road_id][1]))
		|| (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))) {

		if (OldRoadId >= 0)
			_roads->DeleteRoad(road_id_to_from_to[OldRoadId][0], road_id_to_from_to[OldRoadId][1]);
		_roads->DeleteRoad(road_id_to_from_to[road_id][0], road_id_to_from_to[road_id][1]);
		_roads->AddRoad(road_id_to_from_to[road_id][0], road_id_to_from_to[road_id][1], newRoadPlayerId);

		return true;
	}	

	return false;
}

void roadHooks::OnDragOver(Object* obj)
{	
	BoardObjects objType = obj->getObjectType();	
	int newRoadPlayerId = -1;

	switch (objType)
	{
	case BoardObjects::road: {
		newRoadPlayerId = catan->catan_ai->getCurrentPlayer();
		break;
	}

	case BoardObjects::roadHooks: {
		roadHooks* dropObj = dynamic_cast<roadHooks*>(obj);				
		newRoadPlayerId = catan->catan_ai->game_state->roads->getRoad(road_id_to_from_to[dropObj->road_id][0], road_id_to_from_to[dropObj->road_id][1])->id;
		break;
	}

	default:
		return;
	}

	DFSTracePathPoints AllPathPoints(*catan->catan_ai->game_state.get(), newRoadPlayerId);
	if ((AllPathPoints.IsItPossibleToBuildRoad(road_id_to_from_to[road_id][0], road_id_to_from_to[road_id][1]))
		|| (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))) {
		
		Rectangle* rect = dynamic_cast<Rectangle*>(obj);
		setSpriteID(rect->getSpriteId());
		obj->Hide();
		setFillColor(sf::Color(255, 255, 255, 255));
	}
}

void roadHooks::OnMouseLeave()
{
	if (Board::drag->IsDraggring()) {
		setSpriteID(old_sprite_id);
		Board::drag->get()->Show();

		if (old_sprite_id == Sprites::ID::none) {
			setFillColor(sf::Color(0, 0, 0, 0));
		}
	}
}

bool roadHooks::OnEndDrag(bool accepted)
{
	if (catan->mouse.x > 1100) {
		catan->catan_ai->game_state->roads->DeleteRoad(road_id_to_from_to[road_id][0], road_id_to_from_to[road_id][1]);
	}
	else {
		if (accepted) {
			catan->catan_ai->game_state->roads->DeleteRoad(road_id_to_from_to[road_id][0], road_id_to_from_to[road_id][1]);
			return false;
		}
	}
	return true;
}

void roadHooks::Update()
{
	if (!Board::drag->IsDraggring()) {
		Road* road = catan->catan_ai->game_state->roads->getRoad(road_id_to_from_to[road_id][0], road_id_to_from_to[road_id][1]);
		if (road != nullptr) {
			setFillColor(sf::Color(255, 255, 255, 255));
			setSpriteID(static_cast<Sprites::ID>(static_cast<int>(Sprites::ID::redRoad) + road->id));
		}
		else {
			setSpriteID(Sprites::ID::none);
			setFillColor(sf::Color(0, 0, 0, 0));
		}
		old_sprite_id = getSpriteId();
	}
}

lRoadLabel::lRoadLabel(float x, float y, double angle, const sf::Color& textColor, const std::string& text, unsigned int textSize, int _playerId)
	:Label(x, y, angle,textColor, text, textSize), playerId(_playerId)
{}

void lRoadLabel::Update()
{
	std::ostringstream o;
	Players* players = catan->catan_ai->game_state->players.get();
	//(*players)[road.id].AddRoad();
	//o << "L. Road (" << (*players)[players->GetLargestRoadId()].GetMaxRoadLength() <<")";
	int pId;
	if (playerId == -1) {
		pId = catan->catan_ai->getCurrentPlayer();
	}
	else {
		pId = playerId;
	}
	o << "L. Road (" << ((catan->catan_ai->getPlayersCount()) ? ((*players)[pId].GetMaxRoadLength()) : 0) <<")";
	setString(o.str());
	if (pId == (*players).GetLargestRoadId()) {
		setFillColor(sf::Color(228, 255, 0, 255));
	}
	else {
		setFillColor(_textColor);
	}
}
