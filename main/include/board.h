#pragma once

#include "CatanGUI.h"

class Board {
private:
	CatanGUI & catan;
	std::map<unsigned int, std::unique_ptr<Object>> Objects;
	
	//template <typename T, typename... Types>
	//friend void addObject(T objType, Types... args);

	void CreateStandartObjects();	

public:
	Board(CatanGUI & _catan);

	template<typename T,typename ...Types>
		void addObject(Types&& ...args);

	Object* GetObject(int x, int y);
	void Draw();
	void Update();
	void UpdateHexesAndDices();
};
