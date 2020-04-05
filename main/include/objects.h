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
	Object(const std::string& name, BoardObjects _type);
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

	const std::string name;

public:

	//standart events
	virtual void OnMouseDown(int x, int y, sf::Mouse::Button button);
	virtual void OnMouseLeave();
	virtual void OnMouseMove();
	virtual Object* OnMouseOver(float x, float y);	//check if mouse is on the object
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

class Rectangl : public Object, public sf::RectangleShape {
private:
	Sprites::ID sprite_id = Sprites::ID::none;
	bool useTextureForDragNDrop = false;	

public:
	//Rectangl with outline, buttons, etc..
	Rectangl(const std::string& name, BoardObjects _type, sf::Color OutlineColor, float OutlineThickness, sf::Color FillColor,
		float x, float y, int width, int height, float angle);

	//Only sprite
	Rectangl(const std::string& name, BoardObjects _type, Sprites::ID spriteId,
		float x, float y, int width, int height, float angle);

	Rectangl() = delete;
	virtual ~Rectangl() = default;	

	Sprites::ID getSpriteId() const;
	void setSpriteID(Sprites::ID sprite);

	void UseTextureForDrop(bool enable);	//using global bounds or texture
	virtual bool IsTextureUsedForDrop() const;

	virtual Object* OnMouseOver(float x, float y) override;	//if mouse on the object
	virtual void OnDraw() override;
};

class CheckBox : public Rectangl {
public:
	CheckBox(const std::string& name, sf::Color OutlineColor, sf::Color FillColor, float x, float y);
	CheckBox() = delete;

	mutable bool isChecked = true;
	void setCheckState(bool state = true) const;	

	void OnMouseDown(int x, int y, sf::Mouse::Button button) override;
	void OnMouseLeave() override;
	void OnMouseUp(sf::Mouse::Button button) override;

	void OnDraw() override;

private:
	bool isPressed = false;
	sf::Sprite checkSprite = catan->GetSprite(Sprites::ID::check);

};

class BoardHex : public Rectangl {
private:
	unsigned int current_hex_id;
	unsigned int dice = 0;
	sf::Sprite diceSprite;
	
	bool isPressed = false;

public:
	BoardHex(const std::string& name, float x, float y);

	static unsigned int hex_id;
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

class PlayerContainer : public Rectangl {
private:

public:
	PlayerContainer(const std::string& name, float x, float y, int width, int height);
	~PlayerContainer() = default;
	PlayerContainer() = delete;
	
	//void Update() override;
};

class UpdateAbstractClass : public Object {
private:

public:
	UpdateAbstractClass(const std::string& name);
	~UpdateAbstractClass() = default;
	UpdateAbstractClass() = delete;

	void OnDraw() override;
	void Update() override;
};

class BoardBorder : public Rectangl {
	static unsigned int border_id;

private:	
	unsigned int current_border_id;
	int harbor_type = 0;
	bool isPressed = false;

public:
	BoardBorder(const std::string& name, float x, float y, double angle);

	unsigned int getCurrentBorderId() const;
	
	void OnMouseUp(sf::Mouse::Button button) override;
	void OnMouseDown(int x, int y, sf::Mouse::Button button) override;
	void OnMouseLeave() override;	

	void setHarbor(int h);
	void Update();
};

class Btn : public Rectangl {
private:
	bool isPressed = false;	
	objButtonEvents event;

	sf::Font font;
	sf::Text caption;

	sf::Color OutlineColor, FillColor, textColor, HoverFillColor, HoverOutlineColor, HoverTextColor, PressedFillColor,
		PressedOutlineColor, PressedTextColor;
	std::string text;

	std::vector <std::any> params;

public:
	template <typename ...Args>
	Btn(const std::string& name, float x, float y, int width, int height, float angle,
		const sf::Color& OutlineColor, float OutlineThickness, const sf::Color& FillColor,
		const sf::Color& HoverFillColor, const sf::Color& HoverOutlineColor, const sf::Color& HoverTextColor,
		const sf::Color& PressedFillColor, const sf::Color& PressedOutlineColor, const sf::Color& PressedTextColor,
		const sf::Color& textColor, const std::string& text, int textSize, objButtonEvents event, Args&& ...args)

		: Rectangl(name, BoardObjects::button, OutlineColor, OutlineThickness, FillColor, x, y, width, height, angle),
		OutlineColor(OutlineColor), FillColor(FillColor), textColor(textColor),
		HoverFillColor(HoverFillColor), HoverOutlineColor(HoverOutlineColor), HoverTextColor(HoverTextColor),
		PressedFillColor(PressedFillColor), PressedOutlineColor(PressedOutlineColor), PressedTextColor(PressedTextColor),
		text(text), event(event)
	
		{
			params = std::vector<std::any>({ args... });


			caption.setFont(catan->getFont());
			caption.setString(text);
			caption.setCharacterSize(textSize);
			caption.setFillColor(textColor);

			const sf::FloatRect bounds(caption.getLocalBounds());
			caption.setOrigin(bounds.width / 2, bounds.height / 2 + bounds.top);
			caption.setPosition(x, y);
		};

	void setBtnState(btnStates state);

	void OnMouseDown(int x, int y, sf::Mouse::Button button) override;
	void OnMouseLeave() override;
	void OnMouseMove() override;
	void OnMouseUp(sf::Mouse::Button button) override;

	void OnDraw() override;

	static void processBtnEvent(objButtonEvents event, const std::vector<std::any>& params);
};

class Label : public Object, public sf::Text {
protected:
public:
	Label(const std::string& name, float x, float y, double angle, const sf::Color& textColor, const std::string& text, unsigned int textSize);
	virtual ~Label() = default;

	sf::Color _textColor;

	virtual void OnDraw() override;
};

class ControlTradeResource : public Rectangl {
public:
	ControlTradeResource(const std::string& name, Sprites::ID spriteId, resource resType, float x, float y);

	void Reset();
	
	void OnMouseDown(int x, int y, sf::Mouse::Button button) override;
	void OnMouseLeave() override;
	void OnMouseUp(sf::Mouse::Button button) override;
	Object* OnMouseOver(float x, float y) override;
	virtual void OnDraw() override;

	ControlTradeResource operator++(int);
	operator int();

	bool isSelectedForTrade = false;

private:
	bool isSelected = false;

	//which resources for trading has bee selected	
	unsigned resourceCount = 0;
	Label lFromTo, lResourceCount;
	Btn addButton;
	resource tradeResource;
};


class BoardBuilding : public Rectangl {
public:
	BoardBuilding(const std::string& name, Sprites::ID spriteId, float x, float y);
	BoardBuilding() = delete;
	~BoardBuilding() = default;
	
	building_types type = building_types::none;	//settelment or city

	bool OnEndDrag(bool accepted) override;
	void Update() override;
};

class buildingHooks : public Rectangl {
private:	
	Sprites::ID old_sprite_id = Sprites::ID::none;	

public:
	buildingHooks(const std::string& name, float x, float y);
	~buildingHooks() = default;
	buildingHooks() = delete;

	static unsigned int building_hook_id;
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


class BoardRoad : public Rectangl {
private:
public:
	BoardRoad(const std::string& name, Sprites::ID spriteId, float x, float y);
	BoardRoad() = delete;
	~BoardRoad() = default;

	bool OnEndDrag(bool accepted) override;
	void Update() override;
};

class roadHooks : public Rectangl {
private:	
	Sprites::ID old_sprite_id = Sprites::ID::none;

public:
	roadHooks(const std::string& name, float x, float y, double angle);
	~roadHooks() = default;
	roadHooks() = delete;	
	
	unsigned int road_id;	//=road.point
	static unsigned int road_hook_id;

	bool IsDragObjectAcceptable(Object* obj) override;
	bool IsDraggable() const override;

	bool OnDragDrop(Object* obj);
	void OnDragOver(Object* obj) override;
	void OnMouseLeave() override;
	bool OnEndDrag(bool accepted) override;
	void Update() override;
};
