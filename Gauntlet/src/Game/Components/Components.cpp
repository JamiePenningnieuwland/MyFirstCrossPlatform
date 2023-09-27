//#include "Components.h"
//#include "Engine/Rendering/Shaders/Shader.h"
//#include "Engine/Rendering/Models/Texture.h"
//
//#include "Engine/PhysicsDebug/BulletDebug.h"
//#include "Input.h"
//
//template<typename T>
//T Lerp(T min, T max, float t)
//{
//	return (max - min) * t + min; 
//}
//
//void RenderComponent::Render(Shader& shader)
//{
//	auto transform = m_Parent->GetComponent<TransformComponent>();
//	shader.UploadUniform("Model", transform->GetTransform());
//	model->Draw(shader);
//}
//
//void CollisionComponent::Init()
//{
//	//auto Transform = m_Parent->GetComponent<TransformComponent>();
//	switch (Shape)
//	{
//	case Geometry::Box:
//		
//		CollisionShape = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));
//		break;
//	case Geometry::Sphere:
//		CollisionShape = new btSphereShape(1.f);
//		break;
//	case Geometry::Capsule:
//		CollisionShape = new btCapsuleShape(1.f, 1.f);
//		break;
//	default:
//		CollisionShape = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));
//		break;
//	}
//	btTransform ObjectTransform;
//	ObjectTransform.setIdentity();
//	btVector3 localInertia(0, 0, 0);
//	if(Dynamic)
//	{
//		
//		CollisionShape->calculateLocalInertia(1.f, localInertia);
//	}
//	//btDefaultMotionState* myMotionState = new btDefaultMotionState(ObjectTransform);
//	object = new btCollisionObject();
//	CopyTransform();
//	object->setCollisionShape(CollisionShape);
//	dynamicWorld->addCollisionObject(object);
//}
//void CollisionComponent::CopyTransform()
//{
//	auto transform = m_Parent->GetComponent<TransformComponent>();
//	glm::vec3 newScale = transform->Scale * Scale;
//
//	btVector3 scale = btVector3(newScale.x, newScale.y, newScale.z);
//	CollisionShape->setLocalScaling(scale);
//
//	glm::vec3 transOffset;
//	{
//		glm::mat3 transScale = glm::scale(glm::mat4(1.f), transform->Scale);
//		glm::mat3 transRot = glm::inverse(glm::toMat3(transform->Rotation));
//		transOffset = Offset * transRot * transScale;
//	}
//
//
//	btTransform btransform;
//	btransform.setIdentity();
//	glm::vec3 transpos = transform->Position + transOffset;
//	btVector3 pos = btVector3
//	(
//		transpos.x,
//		transpos.y,
//		transpos.z
//	);
//	btQuaternion rot = btQuaternion
//	(
//		transform->Rotation.x,
//		transform->Rotation.y,
//		transform->Rotation.z,
//		transform->Rotation.w
//	);
//	btransform.setOrigin(pos);
//	btransform.setRotation(rot);
//	object->setWorldTransform(btransform);
//}
//void CollisionComponent::Update(float deltaTime)
//{
//	//object->setAngularFactor(btVector3(btScalar(!LockXRotation), btScalar(!LockYRotation), btScalar(!LockZRotation)));
//	glm::vec3 transOffset;
//	{
//		auto transform = m_Parent->GetComponent<TransformComponent>();
//		glm::mat3 transScale = glm::scale(glm::mat4(1.f), transform->Scale);
//		glm::mat3 transRot = glm::inverse(glm::toMat3(transform->Rotation));
//		transOffset = Offset * transRot * transScale;
//	}
//
//	btTransform transform;
//	transform = object->getWorldTransform();
//	m_Parent->GetComponent<TransformComponent>()->Rotation = (glm::quat((float)transform.getRotation().w(), (float)transform.getRotation().x(), (float)transform.getRotation().y(), (float)transform.getRotation().z()));
//	m_Parent->GetComponent<TransformComponent>()->Position = (glm::vec3(transform.getOrigin().x(), transform.getOrigin().y(), transform.getOrigin().z()) - transOffset);
//}
//void PhysicsComponent::CopyTransform()
//{
//	auto transform = m_Parent->GetComponent<TransformComponent>();
//	glm::vec3 newScale = transform->Scale * Scale;
//
//	btVector3 scale = btVector3(newScale.x, newScale.y, newScale.z);
//	ObjectShape->setLocalScaling(scale) ;
//
//	glm::vec3 transOffset;
//	{
//		glm::mat3 transScale = glm::scale(glm::mat4(1.f), transform->Scale);
//		glm::mat3 transRot = glm::inverse(glm::toMat3(transform->Rotation));
//		transOffset = Offset * transRot * transScale;
//	}
//
//
//	btTransform btransform;
//	btransform.setIdentity();
//	glm::vec3 transpos = transform->Position + transOffset;
//	btVector3 pos = btVector3
//	(
//		transpos.x,
//		transpos.y,
//		transpos.z
//	);
//	btQuaternion rot = btQuaternion
//	(
//		transform->Rotation.x,
//		transform->Rotation.y,
//		transform->Rotation.z,
//		transform->Rotation.w
//	);
//	btransform.setOrigin(pos);
//	btransform.setRotation(rot);
//	Objectbody->setWorldTransform(btransform);
//}
//void PhysicsComponent::Init()
//{	
//	//auto Transform = m_Parent->GetComponent<TransformComponent>();
//	switch (Shape)
//	{
//	case Geometry::Box:
//		ObjectShape = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));
//		break;
//	case Geometry::Sphere:
//		ObjectShape = new btSphereShape(1.f);
//		break;
//	case Geometry::Capsule:
//		ObjectShape = new btCapsuleShape(1.f, 1.f);
//		break;
//	default:
//		ObjectShape = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));
//		break;
//	}
//	//ObjectShape = new btBoxShape(btVector3(0.5f, 0.5f,0.5f));
//	
//	btTransform ObjectTransform;
//	ObjectTransform.setIdentity();
//
//	//rigidbody is dynamic if and only if mass is non zero, otherwise static
//	bool isDynamic = (mass != 0.f);
//
//	btVector3 localInertia(0, 0, 0);
//	if (isDynamic)
//		ObjectShape->calculateLocalInertia(mass, localInertia);
//
//	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
//	btDefaultMotionState* myMotionState = new btDefaultMotionState(ObjectTransform);
//	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, ObjectShape, localInertia);
//	Objectbody = new btRigidBody(rbInfo);
//	CopyTransform();
//	AttachToPhysicsWorld();
//}
//
//void PhysicsComponent::CopyTransformFromPhysicsWorld()
//{
//	//Objectbody->setAngularVelocity(btVector3(btScalar(!LockXRotation), btScalar(!LockYRotation), btScalar(!LockZRotation)) * Objectbody->getAngularVelocity());
//	//Objectbody->setAngularFactor(btVector3(btScalar(!LockXRotation), btScalar(!LockYRotation), btScalar(!LockZRotation)));
//	//Objectbody->setFriction(0.f);
//	//Objectbody->setDamping(btVector3(1.f,1.f,1.f),btVector3(btScalar(LockXRotation), btScalar(LockYRotation), btScalar(LockZRotation)));
//
//	glm::vec3 transOffset;
//	{
//		auto transform = m_Parent->GetComponent<TransformComponent>();
//		glm::mat3 transScale = glm::scale(glm::mat4(1.f), transform->Scale);
//		glm::mat3 transRot = glm::inverse(glm::toMat3(transform->Rotation));
//		transOffset = Offset * transRot * transScale;
//	}
//
//	btTransform transform;
//	transform = Objectbody->getWorldTransform();
//	m_Parent->GetComponent<TransformComponent>()->Rotation = (glm::quat((float)transform.getRotation().w(), (float)transform.getRotation().x(), (float)transform.getRotation().y(), (float)transform.getRotation().z()));
//	m_Parent->GetComponent<TransformComponent>()->Position = (glm::vec3(transform.getOrigin().x(), transform.getOrigin().y(), transform.getOrigin().z()) - transOffset);
//}
//
//void PhysicsComponent::AttachToPhysicsWorld()
//{
//	dynamicWorld->addRigidBody(Objectbody);
//
//}
//void PhysicsComponent::Destroy()
//{
//	//looked at github example https://github.com/bulletphysics/bullet3/blob/master/examples/HelloWorld/HelloWorld.cpp
//	
//	btCollisionObject* obj = Objectbody;
//	btRigidBody* body = btRigidBody::upcast(obj);
//	if (body && body->getMotionState())
//	{
//		delete body->getMotionState();
//	}
//	dynamicWorld->removeCollisionObject(obj);
//	delete obj;
//
//	//delete collision shapes
//	btCollisionShape* shape = ObjectShape;
//	delete shape;
//		
//	// dynamicWorld;
//}
//btCollisionWorld::ClosestRayResultCallback PhysicsComponent::RayCollisionTest(btVector3 From, btVector3 To)
//{
//	btCollisionWorld::ClosestRayResultCallback closestResults(From, To);
//	dynamicWorld->rayTest(From, To, closestResults);
//	return closestResults;
//}
//
//
//void PlayerControllerComponent::Update(float deltaTime)
//{
//	if (!IsActive)
//		return;
//
//	m_Parent->GetComponent<PhysicsComponent>()->Objectbody->setAngularVelocity(btVector3(0.f, 0.f, 0.f));
//
//	glm::vec3 newPosition(0.f,0.f,0.f);
//	glm::vec3 direction(0.f,0.f,0.f);
//	glm::vec2 inputChange(0.f);
//
//	//input
//	if (Input::GetKey(KEY_D))
//	{
//		inputChange.x -= 1.f;
//	}
//	
//	if (Input::GetKey(KEY_A))
//	{
//		inputChange.x += 1.f;
//	}
//	
//	if (Input::GetKey(KEY_W))
//	{
//		inputChange.y += 1.f;
//	}
//	
//	if (Input::GetKey(KEY_S))
//	{
//		inputChange.y -= 1.f;
//	}
//	auto physicobj = m_Parent->GetComponent<PhysicsComponent>();
//	auto transform = m_Parent->GetComponent<TransformComponent>();
//	
//
//	if (Input::GetKey(KEY_SPACE))
//	{
//		// took example from  https://gamedev.stackexchange.com/questions/58012/detect-when-a-bullet-rigidbody-is-on-ground
//		int numManifolds = physicobj->Dispatcher->getNumManifolds();
//		for (int i = 0; i < numManifolds; i++)
//		{
//			btPersistentManifold* contactManifold = physicobj->dynamicWorld->getDispatcher()->getManifoldByIndexInternal(i);
//			btCollisionObject* obA = const_cast<btCollisionObject*>(contactManifold->getBody0());
//			btCollisionObject* obB = const_cast<btCollisionObject*>(contactManifold->getBody1());
//
//			if (obA == physicobj->Objectbody || obB == physicobj->Objectbody ) {
//				int numContacts = contactManifold->getNumContacts();
//				for (int j = 0; j < numContacts; j++)
//				{
//					btManifoldPoint& pt = contactManifold->getContactPoint(j);
//					if (pt.getDistance() < 0.f)
//					{
//
//						btVector3 normal;
//
//
//						if (obB == physicobj->Objectbody) 
//							normal = -pt.m_normalWorldOnB;
//						else
//							normal = pt.m_normalWorldOnB;
//
//
//						if (normal.y() > 0.4f /*put the threshold here */) 
//						{
//							float jump = 0;
//							jump = 3.f;
//							//m_Parent->GetComponent<TransformComponent>()->Position.y = Lerp(jump,m_Parent->GetComponent<TransformComponent>()->Position.y, 10 * deltaTime);
//						}
//					}
//				} 
//			}
//		}
//	}
//	
//	if (glm::length2(inputChange) > 0.1f)
//	{
//		
//		glm::vec3 oldpos = m_Parent->GetComponent<TransformComponent>()->Position;
//		direction = glm::vec3(inputChange.x, 0.f, inputChange.y) * glm::inverse(glm::toMat3(transform->Rotation));
//		newPosition = oldpos + (glm::normalize(direction) * Strength);
//		m_Parent->GetComponent<TransformComponent>()->Position =  Lerp(oldpos, newPosition, deltaTime);
//		if (m_Parent->HasComponent<AnimationRenderComponent>())
//			m_Parent->GetComponent<AnimationRenderComponent>()->isPlaying = true;
//	}
//	else
//	{
//		if (m_Parent->HasComponent<AnimationRenderComponent>())
//			m_Parent->GetComponent<AnimationRenderComponent>()->isPlaying = false;
//	}
//
//}
//
//glm::mat4 CameraComponent::GetView()
//{
//	auto transform = m_Parent->GetComponent<TransformComponent>();
//	glm::vec3 Position = transform->Position + ObjectPositionOffset;
//
//	glm::mat4 translation = glm::translate(glm::mat4(1.f), Position);
//	glm::mat4 OffsetMatrix = glm::translate(glm::mat4(1.f), Offset);
//	glm::mat4 rotation = glm::toMat4(transform->Rotation);
//	glm::mat4 Lookat = glm::lookAt(glm::vec3(0.f), -Offset, { 0.f,1.f,0.f });
//	//order important
//	return translation * rotation * OffsetMatrix * glm::inverse(Lookat);
//}
//void CameraControlComponent::Update(float deltaTime)
//{
//	if(m_CameraComponent->IsMain == true)
//	{
//	
//		float xoffset = Input::GetMouseDelta().x;
//		float yoffset = Input::GetMouseDelta().y;
//
//		float sensitivity = 0.1f * deltaTime;
//		xoffset *= sensitivity;
//		yoffset *= sensitivity;
//
//		Rotation.x += yoffset;
//		Rotation.y += xoffset;
//
//		Rotation.x = glm::clamp(Rotation.x, glm::radians(-65.f), glm::radians(0.f));
//		m_CameraComponent->Offset = glm::vec3( 0.f, 0., -Distance) *  
//			glm::mat3(glm::rotate(glm::mat4(1.f), Rotation.x, glm::vec3(1.f, 0.f, 0.f)));
//
//		m_Parent->GetComponent<TransformComponent>()->Rotation = glm::vec3(0.f, Rotation.y, 0.f);
//	}
//
//}
//void AnimationRenderComponent::Render(Shader& shader)
//{
//	if(model->Animated)
//	{
//		std::vector<glm::mat4> transforms(skeleton.bones.size());
//		std::vector<glm::mat4> localTransforms(skeleton.bones.size());
//		std::vector<glm::mat4> modelTransforms(skeleton.bones.size());
//
//		for (size_t i = 0; i < skeleton.bones.size(); i++)
//		{
//			localTransforms[i] = skeleton.bones[i].GetMatrix();
//		}
//		modelTransforms[0] = localTransforms[0];
//
//		for (size_t i = 1; i < skeleton.bones.size(); i++)
//		{
//			int parent = skeleton.bones[i].Parent;
//			modelTransforms[i] = modelTransforms[parent] * localTransforms[i];
//		}
//		for (size_t i = 0; i < skeleton.bones.size(); i++)
//		{
//			transforms[i] = modelTransforms[i] * skeleton.bones[i].Offset;
//		}
//		for (size_t i = 0; i < skeleton.bones.size(); i++)
//		{
//			shader.UploadUniform("BoneMatrices[" + std::to_string(i) + "]", transforms[i]);
//		}
//
//	}
//	auto transform = m_Parent->GetComponent<TransformComponent>();
//	shader.UploadUniform("Model", transform->GetTransform());
//	model->Draw(shader);
//}
