#pragma once
#include <string>
#include <glm/vec3.hpp>
#include <glm/common.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>



class GameObject;
class Component
{
public:
	friend class GameObject;

	Component() = default;
	virtual ~Component() {};
	virtual void Init() = 0;
	virtual void Update(float DeltaTime) {};
	virtual void Destroy() = 0;

protected:
	GameObject* m_Parent = nullptr;
private:
	void SetParent(GameObject* parent) { m_Parent = parent; };
};

#define GET_ID_FUNCTION(name) static std::string GetID() { return #name; }

class TransformComponent :public Component
{
public:
	GET_ID_FUNCTION(TransformComponent)
	
	TransformComponent(const TransformComponent&) = default;
	TransformComponent(glm::vec3 p = { 0.f,0.f,0.f }, glm::quat r = glm::quat(glm::vec3(0.f)), glm::vec3 scale = { 1.f,1.f,1.f })
		: Position(p)
		, Rotation(r)
		, Scale(scale)

	{}
	virtual void Init() {};
	virtual void Destroy() {};
	glm::mat4 GetTransform()
	{
		glm::mat4 translation = glm::translate(glm::mat4(1.f), Position);
		glm::mat4 scale = glm::scale(glm::mat4(1.f), Scale);
		glm::mat4 rotation = glm::toMat4(Rotation);

		//order important
		return translation * rotation * scale;
		
	}
	glm::vec3 Position;
	glm::vec3 Scale;
	glm::quat Rotation;
private:

};

class TagComponent :public Component
{
public:

	GET_ID_FUNCTION(TagComponent)

		TagComponent(const TagComponent&) = default;
	TagComponent()
		:Tag("NONE")
	{};
	TagComponent(std::string name)
		:Tag(name)
	{};

	virtual void Init() {};
	virtual void Destroy() {};
	std::string Tag;
private:

};
