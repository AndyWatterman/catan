#pragma once

#include "stdafx.h"
#include "header.h"

class CatanGUI {
private:
	sf::RenderWindow Window;	

	Object* objUnderCursor = nullptr;
	Object* lastobjUnderCursor = nullptr;
	Object* objPressed = nullptr;

	ResourceHolder<sf::Image, Resources::ID> images;
	ResourceHolder<sf::Texture, Resources::ID> textures;
	Holder<sf::Sprite, Sprites::ID> sprites;

private:
	void processEvents();
	void update();
	void render();

	void handleMouseEvent(int x, int y, sf::Mouse::Button button, sf::Event::EventType event);

	void LoadImages();
	void LoadSprites();
	void LoadTextures();
	void SetWindowOptions();

public:
	CatanGUI();
	void start();

	std::unique_ptr<Board> board;
	std::unique_ptr<CatanAi> catan_ai;
	std::unique_ptr<Drag> drag;	

	mutable int mouse_x, mouse_y;	//current mouse position

	const sf::Sprite& GetSprite(Sprites::ID id) { return (sprites.get(id)); };
	const sf::Texture& GetTexture(Resources::ID id) { return (textures.get(id)); };
	const sf::Image& GetMainImage() { return (images.get(Resources::all)); };
	sf::RenderWindow& GetWindow() { return (Window); };

	const void SetMouseXY(int x, int y) { mouse_x = x; mouse_y = y; };
};

#include "catan_ai.h"
#include "objects.h"
#include "board.h"
#include "drag.h"

