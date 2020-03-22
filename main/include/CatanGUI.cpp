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

	//catan_ai = std::unique_ptr<CatanAi>(new CatanAi(_board));
	catan_ai = std::unique_ptr<CatanAi>(new CatanAi(_board));

	board = std::unique_ptr<Board>(new Board(*this));
	drag = std::unique_ptr<Drag>(new Drag(*this));	

	board->UpdateHexesAndDices();
}

void CatanGUI::processEvents()
{
	sf::Event event;
	while (Window.pollEvent(event))
	{
		if ((event.type == sf::Event::MouseButtonPressed) ||
			(event.type == sf::Event::MouseButtonReleased))
		{
			SetMouseXY(event.mouseButton.x, event.mouseButton.y);	//save mouse coordinates			

			handleMouseEvent(event.mouseButton.x, event.mouseButton.y,
				event.mouseButton.button, event.type);
		}

		if (event.type == sf::Event::MouseMoved)
		{
			SetMouseXY(event.mouseMove.x, event.mouseMove.y);	//save mouse coordinates			

			handleMouseEvent(event.mouseMove.x, event.mouseMove.y,
				event.mouseButton.button, event.type);
		}

		if (event.type == sf::Event::MouseLeft) {
			handleMouseEvent(NULL, NULL, event.mouseButton.button, event.type);
		}

		if (event.type == sf::Event::Closed)
			Window.close();
	}
}

void CatanGUI::handleMouseEvent(int x, int y, sf::Mouse::Button button, sf::Event::EventType event)
{
	objUnderCursor = board->GetObject(x, y);

	if (event == sf::Event::MouseButtonPressed) {
		//if (button == sf::Mouse::Left) {
			if (objUnderCursor != nullptr) {
				objPressed = objUnderCursor;
				objPressed->OnMouseDown(x, y, button);
			}
		//}
	}

	if (event == sf::Event::MouseButtonReleased) {
		if (objPressed != nullptr) {	//
			if (drag->IsDraggring()) {
				bool acceptedDrag = false;

				if (objUnderCursor != nullptr) {
					acceptedDrag = objUnderCursor->OnDragDrop(drag->GetObject());
				}

				drag->Stop(acceptedDrag);
			}
			else {
				objPressed->OnMouseUp(button);
			}
			objPressed = nullptr;
		}
	}

	if (event == sf::Event::MouseMoved) {

		if (objPressed != nullptr) {
			if (!drag->IsDraggring()) {
				if (objPressed->OnStartDrag()) {	//true if object draggable
					drag->SetObject(objPressed);
					drag->Start();
				}
				else {
					if (objUnderCursor != nullptr) {
						objUnderCursor->OnMouseMove(x, y);
					}
				}
			}
			else {
				if (objUnderCursor != nullptr) {
					objUnderCursor->OnDragOver(drag->GetObject());
				}
				objPressed->OnDrag();
			}
		}
		else {
			if (objUnderCursor != nullptr) {
				objUnderCursor->OnMouseMove(x, y);
			}
		}

		if ((lastobjUnderCursor != objUnderCursor) && (lastobjUnderCursor != nullptr)) {
			lastobjUnderCursor->OnMouseLeave();
		}
	}

	if (event == sf::Event::MouseLeft) {
		if (objPressed != nullptr) {
			if (drag->IsDraggring()) {
				drag->Stop();
			}
			else {
				objPressed->OnMouseUp(button);
			}
			objPressed = nullptr;
		}
	}

	lastobjUnderCursor = objUnderCursor;
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

	images.LoadFromFile(Resources::all, ALL_SPRITES_FILENAME);
	images.LoadFromFile(Resources::background, BG_TEXTURE_FILENAME);

}

void CatanGUI::LoadTextures()
{
	//loading textures

	textures.LoadFromFile(Resources::all, ALL_SPRITES_FILENAME);
	textures.LoadFromFile(Resources::background, BG_TEXTURE_FILENAME);
	textures.get(Resources::all).setSmooth(true);
}

void CatanGUI::SetWindowOptions()
{
	Window.setPosition(sf::Vector2i(0, 0));
	Window.setFramerateLimit(60);
	Window.setVerticalSyncEnabled(true);
}


void CatanGUI::start()
{
	while (Window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void CatanGUI::render()
{
	Window.clear();

	//draw a background
	Window.draw(sprites.get(Sprites::background));

	board->Draw();

	Window.display();
}

void CatanGUI::update()
{
	drag->Update();
	board->Update();
}
