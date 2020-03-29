#pragma once

#include "CatanGUI.h"
#include "drag.h"

class Object {
	static unsigned int ObjectIDs;

private:
	unsigned int objectId;
	BoardObjects objectType;
	
//protected:
	bool hidden = false,
		active = true,
		draggable = false;

public:
	explicit Object(BoardObjects _type);
	Object() = delete;
	virtual ~Object() = default;

	bool IsHidden() const;
	bool IsActive() const;	
	virtual bool IsDraggable() const;

	void Disable();
	void Enable();
	void Hide();
	void Show();
	void TurnDragOn();
	void TurnDragOff();

	unsigned int getObjectId() const;
	BoardObjects getObjectType() const;	

public:

	//standart events
	virtual void OnMouseDown(int x, int y, sf::Mouse::Button button);
	virtual void OnMouseLeave();
	virtual void OnMouseMove();
	virtual bool OnMouseOver(float x, float y);	//check if mouse is on the object
	virtual void OnMouseUp(sf::Mouse::Button button);	

	virtual bool OnDragDrop(Object* obj);
	virtual void OnDrag();
	virtual void OnDragOver(Object* obj);
	virtual void OnStartDrag();
	virtual bool OnEndDrag(bool accepted);	
	virtual bool IsDragObjectAcceptable(Object* obj);
	
	virtual void Update();
	virtual void OnDraw() = 0;
};

class Rectangle : public Object, public sf::RectangleShape {
private:
	Sprites::ID sprite_id = Sprites::ID::none;
	bool useTextureForDragNDrop = false;	

public:
	//Rectangle with outline, buttons, etc..
	Rectangle(BoardObjects _type, sf::Color OutlineColor, float OutlineThickness, sf::Color FillColor,
		float x, float y, int width, int height, float angle);

	//Only sprite
	Rectangle(BoardObjects _type, Sprites::ID spriteId,
		float x, float y, int width, int height, float angle);

	virtual ~Rectangle() = default;
	Rectangle() = delete;		

	Sprites::ID getSpriteId() const;
	void setSpriteID(Sprites::ID sprite);

	void UseTextureForDrop(bool enable);	//using global bounds or texture
	virtual bool IsTextureUsedForDrop() const;

	virtual bool OnMouseOver(float x, float y) override;	//if mouse on the object
	virtual void OnDraw() override;
};

class BoardHex : public Rectangle {
	static unsigned int hex_id;

private:
	unsigned int current_hex_id;
	unsigned int dice = 0;
	sf::Sprite diceSprite;
	
	bool isPressed = false;

public:
	BoardHex(float x, float y);

	unsigned int getCurrentHexId() const;

	int getDice() const;
	void setDice(int _dice);

	void OnMouseDown(int x, int y, sf::Mouse::Button button) override;
	void OnMouseMove() override;
	void OnMouseLeave() override;
	void OnMouseUp(sf::Mouse::Button button) override;
	void OnDraw() override;

	void Update() override;
};

class PlayerContainer : public Rectangle {
private:

public:
	explicit PlayerContainer(float x, float y);
	~PlayerContainer() = default;
	PlayerContainer() = delete;
	
	void Update() override;
};

class BoardBorder : public Rectangle {
	static unsigned int border_id;

private:	
	unsigned int current_border_id;
	int harbor_type = 0;
	bool isPressed = false;

public:
	BoardBorder(float x, float y, double angle);

	unsigned int getCurrentBorderId() const;
	
	void OnMouseUp(sf::Mouse::Button button) override;
	void OnMouseDown(int x, int y, sf::Mouse::Button button) override;
	void OnMouseLeave() override;	

	void setHarbor(int h);
	void Update();
};

class Btn : public Rectangle {
private:
	bool isPressed = false;	
	objButtonEvents event;

	sf::Font font;
	sf::Text caption;

	sf::Color OutlineColor, FillColor, textColor, HoverFillColor, HoverOutlineColor, HoverTextColor, PressedFillColor,
		PressedOutlineColor, PressedTextColor;
	std::string text;

public:
	Btn(float x, float y, int width, int height, float angle,
		const sf::Color& OutlineColor, float OutlineThickness, const sf::Color& FillColor,
		const sf::Color& HoverFillColor, const sf::Color& HoverOutlineColor, const sf::Color& HoverTextColor,
		const sf::Color& PressedFillColor, const sf::Color& PressedOutlineColor, const sf::Color& PressedTextColor,
		const sf::Color &textColor, const std::string& text, int textSize, objButtonEvents event);

	void setBtnState(btnStates state);

	void OnMouseDown(int x, int y, sf::Mouse::Button button) override;	
	void OnMouseLeave() override;
	void OnMouseMove() override;
	void OnMouseUp(sf::Mouse::Button button) override;

	void OnDraw() override;

	static void processBtnEvent(objButtonEvents event);
};

class Label : public Object, public sf::Text {
protected:
	sf::Color _textColor;

public:
	Label(float x, float y, double angle, const sf::Color& textColor, const std::string& text, unsigned int textSize);
	virtual ~Label() = default;

	virtual void OnDraw() override;
};

class lRoadLabel : public Label {
private:
	int playerId = -1;
public:
	using Label::Label;
	lRoadLabel(float x, float y, double angle, const sf::Color& textColor, const std::string& text, unsigned int textSize, int playerId);

	void Update() override;
};

class BoardBuilding : public Rectangle {
public:
	BoardBuilding(Sprites::ID spriteId, float x, float y);
	BoardBuilding() = delete;
	~BoardBuilding() = default;
	
	building_types type = building_types::none;	//settelment or city

	bool OnEndDrag(bool accepted) override;
	void Update() override;
};

class buildingHooks : public Rectangle {
	static unsigned int building_hook_id;

private:	
	Sprites::ID old_sprite_id = Sprites::ID::none;	

public:
	buildingHooks(float x, float y);
	~buildingHooks() = default;
	buildingHooks() = delete;

	building_types type = building_types::none;	//settelment or city
	unsigned int point;	//=building.point

	bool IsDragObjectAcceptable(Object* obj) override;
	bool IsDraggable() const override;

	bool OnDragDrop(Object* obj);
	void OnDragOver(Object* obj) override;
	void OnMouseLeave() override;	
	bool OnEndDrag(bool accepted) override;
	void Update() override;
};


class BoardRoad : public Rectangle {
private:
public:
	BoardRoad(Sprites::ID spriteId, float x, float y);
	BoardRoad() = delete;
	~BoardRoad() = default;

	bool OnEndDrag(bool accepted) override;
	void Update() override;
};

class roadHooks : public Rectangle {
	static unsigned int road_hook_id;

private:	
	Sprites::ID old_sprite_id = Sprites::ID::none;

public:
	roadHooks(float x, float y, double angle);
	~roadHooks() = default;
	roadHooks() = delete;
	
	unsigned int road_id;	//=road.point

	bool IsDragObjectAcceptable(Object* obj) override;
	bool IsDraggable() const override;

	bool OnDragDrop(Object* obj);
	void OnDragOver(Object* obj) override;
	void OnMouseLeave() override;
	bool OnEndDrag(bool accepted) override;
	void Update() override;
};
