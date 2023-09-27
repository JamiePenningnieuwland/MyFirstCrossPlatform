#pragma once
#include <map>
#include <string>
#include <glm/common.hpp>
#include <glm/vec3.hpp>
#include "Game/Components/BaseComponent.h"

class GameObject
{
public:

	GameObject();
	GameObject(std::string name);
	GameObject(std::string name, glm::vec3 position);
	~GameObject()
	{
		for (auto& component : m_Components)
		{
			component.second->Destroy();
			delete component.second;
		}
	}

	void Update(float deltaTime)
	{
		for (auto& component : m_Components)
		{
			component.second->Update(deltaTime);
		}
	}
	
	template<typename T, typename... Args>
	T* AddComponent(Args&&... args);

	template<typename T>
	T* GetComponent();
	template<typename T>
	bool HasComponent();

private:
	std::map<std::string, Component*> m_Components;
};

template<typename T, typename... Args>
T* GameObject::AddComponent(Args&&... args)
{
	std::string id = T::GetID();
	//check if a component of this type does not exist already 
	if (m_Components.find(id) == m_Components.end())
	{
		m_Components[id] = (Component*) new T(std::forward<Args>(args)...);
		m_Components[id]->SetParent(this);
		m_Components[id]->Init();
	}
	else
	{
		printf("Trying to add a component that already has been added!");
	}
	return(T*)m_Components[id];
}

template<typename T>
bool GameObject::HasComponent()
{
	std::string id = T::GetID();
	return (m_Components.find(id) != m_Components.end());
}

template<typename T>
T* GameObject::GetComponent()
{
	std::string id = T::GetID();
	if (m_Components.find(id) != m_Components.end())
	{
		return (T*)m_Components[id];
	}
	return nullptr;
}


