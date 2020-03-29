#pragma once

#include "CatanGUI.h"

struct Key {
	unsigned int id;
	std::string name;

	Key(unsigned int id, const std::string& _name) : id(id), name(_name) {};
	Key() = delete;
	~Key() = default;
};

struct KeyCmp {
	bool operator()(const Key& lhs, const Key& rhs) const
	{
		return (lhs.id < rhs.id);
	}
};

class Board {
private:	
	std::map<Key, std::unique_ptr<Object>, KeyCmp> Objects;
	
	Object* objUnderCursor = nullptr;
	Object* lastobjUnderCursor = nullptr;
	Object* objPressed = nullptr;	

public:
	Board();
	~Board() = default;

	static std::unique_ptr<Drag> drag;

	template<typename T1, typename ...Types>
		void addObject(const std::string& name, Types&& ...args);

	Object* GetObject(int x, int y);
	Object* GetObjectByName(const std::string& name);

	void Init();
	void Draw();
	void Update();

	void handleMouseEvent(sf::Event);	
};
