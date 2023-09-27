#pragma once
#include <map>
#include <string>

class Animation;
class Model;
class Texture;


class ResourceManager
{
public:
	static void AddAnimation(Animation* animation, std::string name);
	static Animation* GetAnimation(std::string name);

	static  const std::map<std::string, Animation*>& GetAnimationMap();
	//--------------------------------------------------------------
	static void AddModel(bool generated, std::string name);
	static Model* GetModel(std::string name);
	//--------------------------------------------------------------
	static void clear();
private:
	
	static std::map<std::string, Animation*> s_Animations;
	static std::map<std::string, Model*> s_Models;
};