#pragma once

#include "CatanGUI.h"

class Board {
private:	
	std::map<unsigned int, std::unique_ptr<Object>> Objects;
	
	Object* objUnderCursor = nullptr;
	Object* lastobjUnderCursor = nullptr;
	Object* objPressed = nullptr;	

public:
	Board();
	~Board() = default;

	static std::unique_ptr<Drag> drag;

	template<typename T,typename ...Types>
		void addObject(Types&& ...args);

	Object* GetObject(int x, int y);

	void Init();
	void Draw();
	void Update();

	void handleMouseEvent(sf::Event);	
};
