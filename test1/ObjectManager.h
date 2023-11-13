#pragma once
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

class GameObject;

class ObjectManager
{
public:
	static ObjectManager* GetInstance();

	void UpdateObjects();
	void RenderObjects();
	GameObject* SpawnObject(GameObject* object);
	void RemoveDeadObjects();
	void CheckCollision();
	bool CheckForGameOver();
	int ObjectAmount();

private:
	ObjectManager();
	~ObjectManager();
	static ObjectManager* Instance;
	std::vector<std::unique_ptr<GameObject>> Objects;
	std::unordered_map< GameObject*, GameObject*> AlreadyCollidedWith;
	//I'm using vector cus I'm going to add/remove elemnts (so no array) but not hashset since it's more important to iterate throught every object 
};
