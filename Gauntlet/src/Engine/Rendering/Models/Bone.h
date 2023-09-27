#pragma once
#include <vector>
#include <string>

#include <map>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>


struct TranslationKey
{
	TranslationKey()
		:Translation(0.f)
		, TimeFrame(0.f)
	{}
	glm::vec3 Translation;
	float TimeFrame = 0.f;
};
struct RotationKey
{
	RotationKey()
		:Rotation(glm::vec3(0.f))
		, TimeFrame(0.f)
	{}
	glm::quat Rotation;
	float TimeFrame = 0.f;
};
struct ScaleKey
{
	ScaleKey()
		:Scale(0.f)
		, TimeFrame(0.f)
	{}
	glm::vec3 Scale;
	float TimeFrame = 0.f;
};

struct BoneKey
{
	std::vector<TranslationKey> TranslationKeys;
	std::vector<RotationKey> RotationKeys;
	std::vector<ScaleKey> ScaleKeys;
	std::string BoneName;
};


struct Bone
{
	Bone();
	glm::mat4 GetMatrix();
	
	int Parent;
	glm::vec3 Translation;
	glm::quat Rotation;
	glm::vec3 Scale;

	glm::mat4 Offset;
};

