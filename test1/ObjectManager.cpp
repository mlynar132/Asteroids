#include "ObjectManager.h"

#include "Asteroid.h"
#include "Game.h"
#include "GameObject.h"
#include "Ship.h"

ObjectManager* ObjectManager::Instance = nullptr;

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

ObjectManager* ObjectManager::GetInstance()
{
    if (Instance == nullptr)
    {
        Instance = new ObjectManager;
    }
    return Instance;
}

void ObjectManager::UpdateObjects()
{
    CheckCollision();
    RemoveDeadObjects();
    for (int i = 0; i < Objects.size(); i++)
    {
        Objects[i]->Update();
    }
}

void ObjectManager::RenderObjects()
{
    for (int i = 0; i < Objects.size(); i++)
    {
        Objects[i]->Render();
    }
}

GameObject* ObjectManager::SpawnObject(GameObject* object)
{
    Objects.emplace_back(object);
    return object;
}

void ObjectManager::RemoveDeadObjects()
{
    Objects.erase(std::remove_if(Objects.begin(), Objects.end(), [](const std::unique_ptr<GameObject>& object)
    {
        return object->bIsDead;
    }), Objects.end());
}

void ObjectManager::CheckCollision()
{
    for (int i = 0; i < Objects.size() - 1; i++)
    {
        for (int j = i + 1; j < Objects.size(); j++)
        {
            float distance = Objects[i]->Location.DistanceToSqrtLess(Objects[j]->Location);//Without sqrt cuz it's quicker to multiply the radius than do sqrt

            if (static_cast<float>((Objects[i]->Radius + Objects[j]->Radius) * (Objects[i]->Radius + Objects[j]->Radius)) >= distance)
            {
                Objects[i]->OnCollision(Objects[j].get());
                Objects[j]->OnCollision(Objects[i].get());

                //AlreadyCollidedWith.insert(std::make_pair(Objects[j].get(), Objects[i].get()));
                //no need to add i,j cuz that already was checked;
            }
        }
    }
    if (!AlreadyCollidedWith.empty())
    {
        AlreadyCollidedWith.clear();
    }
}

bool ObjectManager::CheckForGameOver()
{
    if (Game::StressTestingMode)
    {
        if (Game::CloseGame)
        {
            return true;
        }
        return false;
    }
    for (int i = 0; i < Objects.size(); i++)
    {
        if (Ship* ship = dynamic_cast<Ship*>(Objects[i].get()))
        {
            return false;
        }
    }
    return true;
}

int ObjectManager::ObjectAmount()
{
    return Objects.size();
}
