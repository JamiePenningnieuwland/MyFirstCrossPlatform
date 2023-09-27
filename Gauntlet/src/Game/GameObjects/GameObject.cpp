#include "GameObject.h"
#include "Game/Components/Components.h"


GameObject::GameObject()
{
	AddComponent<TagComponent>("Unnamed");
	AddComponent<TransformComponent>();
};
GameObject::GameObject(std::string name)
{
	AddComponent<TagComponent>(name);
	AddComponent<TransformComponent>();
};
GameObject::GameObject(std::string name, glm::vec3 position)
{
	AddComponent<TagComponent>(name);
	AddComponent<TransformComponent>(position);

};