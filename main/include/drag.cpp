#include "stdafx.h"
#include "CatanGUI.h"

Drag::Drag(CatanGUI & _catan) : catan(_catan) {};

void Drag::SetObject(Object * obj)
{
	source_object = obj;
	back_position = source_object->getPosition();	

	//old_scale = source_object->getScale();
	//source_object->setScale(1.0f, 1.0f);
}

void Drag::ReturnBack(bool accepted)
{
	if (accepted) {
		source_object->setPosition(back_position.x, back_position.y);
		source_object = nullptr;
	}
	else {
		going_back = true;
	}	
}

void Drag::Start()
{
	dragging = true;
}

void Drag::Stop(bool accepted)
{	
	dragging = false;	
	source_object->OnEndDrag(accepted);	
}

void Drag::Update()
{
	if (dragging) {
		sf::Vector2f pos;		
		source_object->setPosition(catan.mouse_x, catan.mouse_y);
	}

	if (going_back) {

		float current_X = source_object->getPosition().x;
		float current_Y = source_object->getPosition().y;

		if (abs(current_X - back_position.x) <= speed) {		
			source_object->setPosition(back_position.x, back_position.y);
			going_back = false;
			source_object = nullptr;
		}
		else {

			float dX{}, dY;
			float k = abs(speed / (current_X - back_position.x));

			if (current_X > back_position.x) {
				dX = current_X - speed;
			}
			else {
				if (current_X < back_position.x) {
					dX = current_X + speed;
				}
			}
			dY = current_Y - k * (current_Y - back_position.y);

			source_object->setPosition(dX, dY);
		}
	}
}

