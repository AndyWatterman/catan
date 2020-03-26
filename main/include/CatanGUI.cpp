#include "stdafx.h"
#include "CatanGUI.h"
#include "sample.h"

CatanGUI::CatanGUI() : Window(sf::VideoMode(1900, 1000), "Catan GUI v0.2a", sf::Style::Default, sf::ContextSettings(0, 0, 8, 1, 1, 0, 0))
//CatanGUI::CatanGUI() : Window(sf::VideoMode(1000, 600), "Catan GUI v0.1a", sf::Style::Default, sf::ContextSettings(0, 0, 8, 1, 1, 0, 0))
{
	SetWindowOptions();

	LoadImages();
	LoadTextures();
	LoadSprites();
	LoadFonts();
	
	catan_ai = std::unique_ptr<CatanAi>(new CatanAi(_board));
	board = std::unique_ptr<Board>(new Board());
}

void CatanGUI::processEvents()
{
	sf::Event event;
	while (Window.pollEvent(event))
	{
		if ((event.type == sf::Event::MouseButtonPressed) ||
			(event.type == sf::Event::MouseButtonReleased))
		{
			mouse.x = event.mouseButton.x;
			mouse.y = event.mouseButton.y;
		}

		if (event.type == sf::Event::MouseMoved)
		{
			mouse.x = event.mouseMove.x;
			mouse.y = event.mouseMove.y;
		}		

		board->handleMouseEvent(event);		//process events

		if (event.type == sf::Event::Closed)
			Window.close();
	}
}

void CatanGUI::LoadSprites()
{
	sf::Sprite sprite;

	for (size_t i = 0; i < Sprites::sprite_table.size(); i++)
	{
		sprite.setTexture(textures.get(Sprites::sprite_table[i].rId));
		sprite.setTextureRect(sf::IntRect(
			Sprites::sprite_table[i].left,
			Sprites::sprite_table[i].top,
			Sprites::sprite_table[i].width,
			Sprites::sprite_table[i].height
		));
		sprites.load(Sprites::sprite_table[i].id, sprite);
	};
};

void CatanGUI::LoadImages()
{
	//loading main images to get access to specific pixels

	images.LoadFromFile(Resources::ID::all, ALL_SPRITES_FILENAME);
	images.LoadFromFile(Resources::ID::background, BG_TEXTURE_FILENAME);

}

void CatanGUI::LoadFonts()
{
	WCHAR path[MAX_PATH * 2];
	DWORD size = GetModuleFileNameW(NULL, path, MAX_PATH * 2);
	
	std::filesystem::path p(path);
	p.remove_filename();
	p.append(kFont);
	font.loadFromFile(p.string());	
}

void CatanGUI::LoadTextures()
{
	//loading textures

	textures.LoadFromFile(Resources::ID::all, ALL_SPRITES_FILENAME);
	textures.LoadFromFile(Resources::ID::background, BG_TEXTURE_FILENAME);
	textures.get(Resources::ID::all).setSmooth(true);
}

void CatanGUI::SetWindowOptions()
{
	Window.setPosition(sf::Vector2i(0, 0));
	Window.setFramerateLimit(60);
	Window.setVerticalSyncEnabled(true);
}


void CatanGUI::start()
{
	board->Init();

	while (Window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

const sf::Font& CatanGUI::getFont()
{
	return (font);
}

void CatanGUI::render()
{
	Window.clear();	
	Window.draw(sprites.get(Sprites::ID::background));	//draw a background
	board->Draw();
	Window.display();
}

void CatanGUI::update()
{	
	board->Update();
}
