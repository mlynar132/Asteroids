#include "ObjectManager.h"

#include "Asteroid.h"
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
    Objects.emplace_back(object/*new ObjectBall{250,400, "Assets/dude.png"}*/);
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
            // Ship* s = dynamic_cast<Ship*>(Objects[i].get());
            // Asteroid* a = dynamic_cast<Asteroid*>(Objects[j].get());
            // if (s && a)
            // {
            //     std::cout<<Objects[i]->Location.DistanceTo(Objects[j]->Location) << "\n";
            // }
            if (static_cast<float>(Objects[i]->Radius + Objects[j]->Radius) >=
                Objects[i]->Location.DistanceTo(Objects[j]->Location))
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
    for (int i = 0; i < Objects.size(); i++)
    {
        if (typeid(Objects[i]) == typeid(Ship))
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
