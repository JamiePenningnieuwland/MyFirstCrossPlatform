#pragma once
#include "BaseComponent.h"


class GameObject;
class PlayerControllerComponent :public Component
{
public:
	GET_ID_FUNCTION(PlayerControllerComponent);
	PlayerControllerComponent(const PlayerControllerComponent&) = default;
	PlayerControllerComponent(float strength)
		: Strength(strength)
	{

	}

	virtual void Init();
	virtual void Destroy() {};
	virtual void Update(float deltaTime);

	float Strength;
	bool IsActive = false;
};
