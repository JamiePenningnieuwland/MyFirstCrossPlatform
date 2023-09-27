#pragma once
#include "gl.h"
#include <Engine/Rendering/Shaders/Shader.h>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

class BulletDebugDraw : public btIDebugDraw
{
public:
	BulletDebugDraw() = default;
	BulletDebugDraw(Shader* shader)
		: debugShader(shader)
	{
	}
	virtual ~BulletDebugDraw() {};
	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override {};
	void reportErrorWarning(const char* warningString) override {};
	void draw3dText(const btVector3& location, const char* textString) override {};
	void setDebugMode(int debugMode) override
	{
		m_DebugMode = debugMode;
	}
	int getDebugMode() const override
	{
		return m_DebugMode;
	}
private:
	int m_DebugMode = btIDebugDraw::DBG_DrawFrames;
	Shader* debugShader = nullptr;

};
