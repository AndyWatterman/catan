#include "stdafx.h"
#include "CatanGUI.h"

void Drag::ReturnBack(bool accepted)
{
	if (accepted) {
		transformable->setPosition(back_position);
		source_object = nullptr;
	}
	else {
		going_back = true;
	}	
}

void Drag::Start(Object* obj)
{	
	source_object = obj;	
	
	transformable = dynamic_cast<sf::Transformable*>(obj);
	if (transformable != nullptr) {
		back_position = transformable->getPosition();
		dragging = true;
		source_object->OnStartDrag();
	};
}

void Drag::Stop(bool accepted)
{	
	dragging = false;
	ReturnBack(source_object->OnEndDrag(accepted));
}

void Drag::Update()
{
	if (dragging) {
		transformable->setPosition(catan->mouse);
	}

	if (going_back) {

		sf::Vector2f pos = transformable->getPosition();

		if (abs(pos.x - back_position.x) <= speed) {		
			transformable->setPosition(back_position);
			going_back = false;
			source_object = nullptr;
		}
		else {			
			sf::Vector2f newPos;
			float k = abs(speed / (pos.x - back_position.x));

			if (pos.x > back_position.x) {
				newPos.x = pos.x - speed;
			}
			else {
				if (pos.x < back_position.x) {
					newPos.x = pos.x + speed;
				}
			}
			newPos.y = pos.y - k * (pos.y - back_position.y);

			transformable->setPosition(newPos.x, newPos.y);
		}
	}
}