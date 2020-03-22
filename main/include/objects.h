#pragma once

#include "CatanGUI.h"
#include "drag.h"

class Object {

	static unsigned int ObjectIDs;

private:
	unsigned int objectId;
	BoardObjects::ID objectType;

protected:
	CatanGUI & catan;

	bool hidden = false,
		active = true,
		selected = false,
		useTextureForDragNDrop = true;

public:
	explicit Object(CatanGUI & _catan, BoardObjects::ID _type);
	Object() = delete;

	virtual ~Object() = default;

	const bool IsHidden() { return (hidden); }
	const bool IsActive() { return (active); }
	const bool IsSelected() { return (selected); }

	void Disable() { active = false; };
	void Enable() { active = true; };
	void Hide() { hidden = true; };
	void Show() { hidden = false; };

	const int getObjectId() { return (objectId); }
	const int getObjectType() { return (objectType); }	

public:

	virtual void OnMouseDown(int x, int y, sf::Mouse::Button button) {};
	virtual void OnMouseMove(float x, float y) {};
	virtual void OnMouseUp(sf::Mouse::Button button) {};
	virtual void OnMouseLeave() {};

	virtual bool OnDragDrop(Object* obj) { return (false); };
	virtual void OnDrag() {};
	virtual void OnDragOver(Object* obj) {};
	virtual bool OnStartDrag() { return (false); };
	virtual void OnEndDrag(bool accepted) { catan.drag->ReturnBack(accepted); };

	virtual void OnDraw() = 0;
	virtual void Update() {};

	virtual bool IsDragObjectAcceptable(Object* obj) { return (false); };
	virtual const bool IsTextureUsedForDrop() { return (useTextureForDragNDrop); } ;
	void setDragRectangle(bool enable) { if (enable) { useTextureForDragNDrop = !enable; } };	//using global bounds instead of image

	virtual sf::FloatRect getGlobalBounds() = 0;
	virtual sf::FloatRect getLocalBounds() = 0;
	virtual const sf::IntRect & getTextureRect() const = 0;
	virtual float getRotation() const = 0;
	virtual const sf::Vector2f & getScale() const = 0;
	virtual const sf::Vector2f& getSize() const = 0;
	virtual const sf::Vector2f& getOrigin() const = 0;
	virtual const sf::Vector2f & getPosition() const = 0;
	virtual const sf::Texture* getTexture() const = 0;
	virtual const sf::Transform& getTransform() const = 0;
	
	virtual void setPosition(float x, float y) = 0;
	virtual void setPosition(const sf::Vector2f& position) = 0;
	virtual void setOrigin(float x, float y) = 0;
	virtual void setOrigin(const sf::Vector2f& origin) = 0;

	virtual const Sprites::ID getSpriteID() const { return (Sprites::none); };
};

class RectangleObject : public Object, public sf::RectangleShape {
private:
	Sprites::ID sprite_id = Sprites::ID::none;

public:
	//Rectangle with outline
	RectangleObject(CatanGUI & _catan, BoardObjects::ID _type,
		sf::Color OutlineColor, float OutlineThickness, sf::Color FillColor,
		float x, float y, int width, int height, float angle);

	//Only sprite
	RectangleObject(CatanGUI & _catan, BoardObjects::ID _type, Sprites::ID spriteId,
		int width, int height, float x, float y, float angle);

	~RectangleObject() = default;
	RectangleObject() = delete;

	virtual bool IsDragObjectAcceptable(Object* obj) { return (false); };

	operator sf::RectangleShape() { return ((sf::RectangleShape&)*this); }

	sf::FloatRect getGlobalBounds() { return (sf::RectangleShape::getGlobalBounds()); };
	sf::FloatRect getLocalBounds() { return (sf::RectangleShape::getLocalBounds()); };
	const Sprites::ID getSpriteID() const { return (sprite_id); };

	const sf::IntRect & getTextureRect() const { return (sf::RectangleShape::getTextureRect()); };
	float getRotation() const { return (sf::RectangleShape::getRotation()); };
	const sf::Vector2f & getScale() const { return (sf::RectangleShape::getScale()); };
	const sf::Vector2f& getSize() const { return (sf::RectangleShape::getSize()); };
	const sf::Vector2f& getOrigin() const { return (sf::RectangleShape::getOrigin()); };
	const sf::Vector2f & getPosition() const { return (sf::RectangleShape::getPosition()); };
	const sf::Texture* getTexture() const { return(sf::RectangleShape::getTexture()); };
	const sf::Transform& getTransform() const { return (sf::RectangleShape::getTransform()); };

	void setPosition(float x, float y) { sf::RectangleShape::setPosition(x, y); };
	void setPosition(const sf::Vector2f& position) { sf::RectangleShape::setPosition(position); };
	void setOrigin(float x, float y) { sf::RectangleShape::setOrigin(x, y); };
	void setOrigin(const sf::Vector2f& origin) { sf::RectangleShape::setOrigin(origin); };
	void setSpriteID(Sprites::ID sp);

	virtual void OnDraw() { catan.GetWindow().draw((sf::RectangleShape&)*this); };
};

class BoardBorder : public RectangleObject {

	static unsigned int border_id;

private:
	
	unsigned int current_border_id;
	int harbor_type = 0;
	bool isPressed = false;

public:
	BoardBorder(CatanGUI & _catan, Sprites::ID spriteId, float x, float y, double angle);

	const unsigned int getCurrentBorderId();
	
	void OnMouseUp(sf::Mouse::Button button) override;
	void OnMouseDown(int x, int y, sf::Mouse::Button button) override;
	void OnMouseLeave() override;	

	void setHarbor(int h);
};

class BoardHex : public RectangleObject {

	static unsigned int hex_id;

private:
	unsigned int current_hex_id;	
	sf::Sprite diceSprite;
	int dice = 0;
	bool isPressed = false;

public:
	BoardHex(CatanGUI & _catan, float x, float y, float angle);
	
	const unsigned int getCurrentHexId();
	const int getDice();
	
	void OnMouseDown(int x, int y, sf::Mouse::Button button) override;
	void OnMouseMove(float x, float y) override;
	void OnMouseLeave() override;	
	void OnMouseUp(sf::Mouse::Button button) override;
	void OnDraw() override;

	void setDice(int _dice);
};

class Btn : public RectangleObject {
private:
	bool isPressed = false;
	sf::Sprite pressed;
	objButtonEvents event;

	sf::Font font;
	sf::Text caption;

	sf::Color OutlineColor, FillColor, HoverFillColor, HoverOutlineColor, PressedFillColor,
		PressedOutlineColor;
	std::string text;

public:
	Btn(CatanGUI & _catan, float x, float y,
		Sprites::ID normal, Sprites::ID pressed, objButtonEvents event);

	Btn(CatanGUI & _catan, float x, float y, int width, int height, float angle,
		const sf::Color& OutlineColor, float OutlineThickness, const sf::Color& FillColor,
		const sf::Color& HoverFillColor, const sf::Color& HoverOutlineColor,
		const sf::Color& PressedFillColor, const sf::Color& PressedOutlineColor,
		const sf::Color &textColor, const std::string& text, int textSize,
		objButtonEvents event);

	void setBtnState(btnStates state);

	void OnMouseDown(int x, int y, sf::Mouse::Button button) override;	
	void OnMouseLeave() override;
	void OnMouseMove(float x, float y) override;
	void OnMouseUp(sf::Mouse::Button button) override;

	void OnDraw() override;

	static void processBtnEvent(CatanGUI & catan, objButtonEvents event);
};

class City : public RectangleObject {
private:
public:
	City(CatanGUI& _catan, Sprites::ID spriteId, float x, float y);
	City() = delete;
	~City() = default;

	bool OnStartDrag() override { return (true); };
	void Update() override;
};

class Settelment : public RectangleObject {
private:
public:
	Settelment(CatanGUI& _catan, Sprites::ID spriteId, float x, float y);
	Settelment() = delete;
	~Settelment() = default;

	bool OnStartDrag() override { return (true); };
	void Update() override;
};

class BoardRoad : public RectangleObject {
private:
public:
	BoardRoad(CatanGUI& _catan, Sprites::ID spriteId, float x, float y);
	BoardRoad() = delete;
	~BoardRoad() = default;

	bool OnStartDrag() override { return (true); };
	void Update() override;
};

class cityHooks : public RectangleObject {
	static unsigned int city_hook_id;

private:
	mutable unsigned int point;	//=building.point
	Sprites::ID old_sprite_id = Sprites::ID::none;

public:
	explicit cityHooks(CatanGUI & _catan, float x, float y);
	~cityHooks() = default;
	cityHooks() = delete;

	bool IsDragObjectAcceptable(Object* obj) override;

	bool OnDragDrop(Object* obj);
	void OnDragOver(Object* obj) override;
	void OnMouseLeave() override;	
	bool OnStartDrag() override;
	void OnEndDrag(bool accepted);
	void Update();
};

class roadHooks : public RectangleObject {
	static unsigned int road_hook_id;

private:
	mutable unsigned int road_id;	//=building.point
	Sprites::ID old_sprite_id = Sprites::ID::none;

public:
	explicit roadHooks(CatanGUI & _catan, float x, float y, double angle);
	~roadHooks() = default;
	roadHooks() = delete;
	
	bool IsDragObjectAcceptable(Object* obj) override;
	unsigned int getRoadId() const { return (road_id); }

	bool OnDragDrop(Object* obj);
	void OnDragOver(Object* obj) override;
	void OnMouseLeave() override;
	bool OnStartDrag() override;
	void OnEndDrag(bool accepted);
	void Update();
};

class PlayerContainer : public RectangleObject {
private:

public:
	explicit PlayerContainer(CatanGUI & _catan, BoardObjects::ID _type,
		int player_id, float x, float y);
	~PlayerContainer() = default;
	PlayerContainer() = delete;	

	void Update() override;
};

class Label : public Object, public sf::Text {
private:
	sf::Font font;

public:
	Label(CatanGUI& _catan, float x, float y, double angle, const sf::Color& textColor, const std::string& text, int textSize, objButtonEvents event);

	sf::FloatRect getGlobalBounds() { return (sf::Text::getGlobalBounds()); };
	sf::FloatRect getLocalBounds() { return (sf::Text::getLocalBounds()); };

	const sf::IntRect& getTextureRect() const { return (sf::IntRect()); };
	float getRotation() const { return (sf::Text::getRotation()); };
	const sf::Vector2f& getScale() const { return (sf::Text::getScale()); };
	const sf::Vector2f& getSize() const { return (sf::Vector2f()); };
	const sf::Vector2f& getOrigin() const { return (sf::Text::getOrigin()); };
	const sf::Vector2f& getPosition() const { return (sf::Text::getPosition()); };
	const sf::Texture* getTexture() const { return(&sf::Texture()); };
	const sf::Transform& getTransform() const { return (sf::Text::getTransform()); };

	void setPosition(float x, float y) { sf::Text::setPosition(x, y); };
	void setPosition(const sf::Vector2f& position) { sf::Text::setPosition(position); };
	void setOrigin(float x, float y) { sf::Text::setOrigin(x, y); };
	void setOrigin(const sf::Vector2f& origin) { sf::Text::setOrigin(origin); };	

	operator sf::Text() { return ((sf::Text&) * this); }

	void OnDraw() override;
};