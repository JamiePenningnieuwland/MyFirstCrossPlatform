#pragma once
#include "BaseComponent.h"
#include "Game/GameObjects/GameObject.h"
#include "Engine/Rendering//Models/Model.h"
#include <string>


class Shader;
enum class AnimationState
{
	Walking = 0,
	Idle = 1,
	turning = 2
};

class RenderComponent : public Component
{
public:
	GET_ID_FUNCTION(RenderComponent)

		RenderComponent(const RenderComponent&) = default;
	RenderComponent(Model* m)
		: model(m)
	{};
	virtual void Init() {};
	virtual void Destroy() {};
	virtual void Update(float deltaTime) {};
	void Render(Shader&);

	Model* model;

};

class MeshRenderComponent : public Component
{
public:
	GET_ID_FUNCTION(RenderComponent)

		MeshRenderComponent(const MeshRenderComponent&) = default;
	MeshRenderComponent(Mesh* m, Texture* t)
		: mesh(m)
		, texture(t)
	{};
	virtual void Init() {};
	virtual void Destroy() {};
	virtual void Update(float deltaTime) {};
	void Render(Shader& shader)
	{
		auto transform = m_Parent->GetComponent<TransformComponent>();
		shader.UploadUniform("Model", transform->GetTransform());
		mesh->Draw(shader);
	}

	Mesh* mesh;
	Texture* texture;

};

class AnimationRenderComponent :public Component
{
public:
	GET_ID_FUNCTION(AnimationRenderComponent)

		AnimationRenderComponent(const AnimationRenderComponent&) = default;
	AnimationRenderComponent(Model* m)
		: model(m)
		, isPlaying(false)
		, AnimationTime(0.)
	{
		if (model->Animated)
			skeleton = model->CopySkeleton();
	};
	virtual void Init() {};
	virtual void Destroy() {};
	virtual void Update(float deltaTime)
	{
		if (isPlaying)
		{
			AnimationTime += deltaTime;
			skeleton.SetPose(activeAnimation, AnimationTime);
		}
	};
	void Render(Shader&);

	Model* model;
	SkeletalMesh skeleton;
	float AnimationTime;
	bool isPlaying;
	std::string activeAnimation;
};
class CharacterAnimationComponent :public Component
{
public:
	GET_ID_FUNCTION(CharacterAnimationComponent)
		CharacterAnimationComponent(const CharacterAnimationComponent&) = default;
	virtual void Init() {};
	virtual void Update(float deltaTime)
	{
		AnimationTime += deltaTime;
		switch (State)
		{
		case AnimationState::Walking:
		{

			break;
		}
		case AnimationState::Idle:
		{
			break;
		}
		case AnimationState::turning:
		{
			break;
		}
		default:
			break;
		}
	};
	virtual void Destroy() {};
	void SetState(AnimationState state)
	{
		State = state;
		AnimationTime = 0.f;
	}
	float AnimationTime;
	AnimationState State = AnimationState::Idle;

};
