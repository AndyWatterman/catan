#pragma once

class Drag {
private:
	bool dragging = false;
	bool going_back = false;

	sf::Vector2f back_position;
	Object* source_object = nullptr;
	sf::Transformable* transformable = nullptr;

	const int speed = 60;

public:
	Drag() = default;
	~Drag() = default;

	Object* get() { return (source_object); };	
	bool IsDraggring() { return (dragging); };

	void ReturnBack(bool accepted = false);
	void Start(Object* obj);
	void Stop(bool accepted = false);
	void Update();
};


