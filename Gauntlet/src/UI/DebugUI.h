#pragma once
#include <vector>

class GameObject;
class btDiscreteDynamicsWorld;
class btCollisionDispatcher;
class Scene;
class DebugUI
{
public:
	void DebugControlWindow(Scene& scene, float deltaTime);

private:

	char Objectname[128] = "";
	char ModelFileName[128] = "";
	char aModelFileName[128] = "";
	char saveSceneFile[128] = "";
	char loadSceneFile[128] = "";
	bool isDynamic = false;
	bool generated = false;


	void DebugUiTransform(GameObject* gameObject);

	bool DebugUiRender(GameObject* gameObject);
	void addDebugUiRender(GameObject* gameObject);

	bool DebugUiCamera(GameObject* gameObject);
	void addDebugUiCamera(GameObject* gameObject);

	bool DebugUiCameraControl(GameObject* gameObject);
	void addDebugUiCameraControl(GameObject* gameObject);

	bool DebugUiAnimatedRender(GameObject* gameObject);
	void addDebugUiAnimatedRender(GameObject* gameObject);

	bool DebugUiPhysics(GameObject* gameObject);
	void addDebugUiPhysics(GameObject* gameObject, Scene& scene);

	bool DebugUiControls(GameObject* gameObject);
	void addDebugUiControls(GameObject* gameObject);
};