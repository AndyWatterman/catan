#pragma once

#include "stdafx.h"
#include "header.h"

class CatanGUI {
private:
	sf::RenderWindow Window;
	sf::Font font;

	ResourceHolder<sf::Image, Resources::ID> images;
	ResourceHolder<sf::Texture, Resources::ID> textures;
	Holder<sf::Sprite, Sprites::ID> sprites;

private:
	void processEvents();
	void update();
	void render();

	void LoadImages();
	void LoadFonts();
	void LoadSprites();
	void LoadTextures();
	void SetWindowOptions();

public:
	CatanGUI();
	~CatanGUI() = default;

	void start();

	std::unique_ptr<Board> board;
	std::unique_ptr<CatanAi> catan_ai;

	const sf::Sprite& GetSprite(Sprites::ID id) { return (sprites.get(id)); };
	const sf::Texture& GetTexture(Resources::ID id) { return (textures.get(id)); };
	const sf::Image& GetMainImage() { return (images.get(Resources::ID::all)); };
	sf::RenderWindow& GetWindow() { return (Window); };	
	
	const sf::Font& getFont();

	sf::Vector2f mouse;		//current mouse position
};

#include "catan_ai.h"
#include "objects.h"
#include "board.h"
#include "drag.h"

