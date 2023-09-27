#pragma once
#include "Rendering/Objects/Mesh.h"
#include "Rendering/Shaders/Shader.h"
#include "Rendering/Objects/PhysicsObject.h"
#include"gl.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Texture.h"



class Object
{
public:
	Object() = default;
	Object(Model* model, Texture* texture, btScalar mass, btVector3 halfscaleCollideBox, glm::vec3 pos = { 0.f, 0.f, 0.f }, btVector3 centerOffset = { 0, 0, 0 }, glm::vec3 rot = { 0.f,0.f,0.f }, glm::vec3 scale = { 1.f, 1.f, 1.f })
		: m_Model(model)
		, m_Texture(texture)
		, m_Position(pos)
		, m_Scale(scale)
		, m_Rotation(rot)
		,m_Offset(glm::vec3(centerOffset.x(), centerOffset.y(), centerOffset.z()))
	{
		//m_Offset = glm::vec3(0., 0.75f, 0.f);
		m_PhysicsObj.ObjectShape = new btBoxShape(halfscaleCollideBox);
		m_PhysicsObj.Scale = glm::vec3(halfscaleCollideBox.x(), halfscaleCollideBox.y(), halfscaleCollideBox.z()) * 2.f;

		btTransform ObjectTransform;
		ObjectTransform.setIdentity();
		ObjectTransform.setOrigin(btVector3(m_Position.x,m_Position.y, m_Position.z));

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			m_PhysicsObj.ObjectShape->calculateLocalInertia(mass, localInertia);

		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(ObjectTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, m_PhysicsObj.ObjectShape, localInertia);
		m_PhysicsObj.Objectbody = new btRigidBody(rbInfo);
		
	};
	Object(Model* model, Texture* texture, glm::vec3 pos = {0.f, 0.f, 0.f}, glm::vec3 rot = {0.f,0.f,0.f}, glm::vec3 scale = {1.f, 1.f, 1.f})
		: m_Model(model)
		, m_Texture(texture)
		, m_Position(pos)
		, m_Scale(scale)
		, m_Rotation(rot)
	{
	};
	
	void Init(btDiscreteDynamicsWorld*& dynamicWorld)
	{
		//add the body to the dynamics world
		dynamicWorld->addRigidBody(m_PhysicsObj.Objectbody);
	}
	void ProcessInput(float deltaTime);
	void Update(float deltaTime);
	void Draw(Shader&);
	void DebugDraw(Shader&, Model*);
	void UpdateMatrix();

	glm::mat4 GetModelMatrix();

	glm::vec3 GetPosition() { return m_Position; }
	void SetPosition(glm::vec3 p) { m_Position = p; }
	
	glm::quat& GetRotation() { return m_Rotation; }
	void SetRotation(glm::quat r) { m_Rotation = r; }

	glm::vec3& GetScale() { return m_Scale; }
	void SetScale(glm::vec3 s) { m_Scale = s; }

	const Texture* GetTexture() { return m_Texture; }
	//TODO add scale and rotation
	const PhysicsObject& GetPhysicsOBJ() { return m_PhysicsObj; }

private:
	PhysicsObject m_PhysicsObj;
	Model* m_Model = nullptr;
	Texture* m_Texture = nullptr;

	glm::vec3 m_Offset;
	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	glm::quat m_Rotation;

};

