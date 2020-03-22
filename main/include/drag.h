#pragma once

//#include "CatanGUI.h"

class Drag {
private:
	CatanGUI & catan;

	bool dragging = false;
	bool going_back = false;

	sf::Vector2f back_position;
	Object* source_object = nullptr;

	const int speed = 60;

public:
	Drag(CatanGUI & _catan);
	Drag() = delete;	

	Object* GetObject() { return (source_object); };
	void SetObject(Object* obj);
	bool IsDraggring() { return (dragging); };

	void ReturnBack(bool accepted = false);
	void Start();
	void Stop(bool accepted = false);
	void Update();
};


