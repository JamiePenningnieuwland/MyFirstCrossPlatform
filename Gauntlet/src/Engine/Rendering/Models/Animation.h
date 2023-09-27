#pragma once
#include "Engine/Managers/ResourceManager.h"
#include <vector>
#include "Bone.h"

class Animation
{
public:
	Animation()
		: Duration(0.f)
		, TicksPerSecond(0.f)
	{}
	Bone GetBoneAtTime(size_t i, float time);
	float Duration;
	float TicksPerSecond;
	std::vector<BoneKey> Keys;
};

class SkeletalMesh
{
public:
	void SetPose(std::string nameAnimation, float time)
	{
		Animation* anim = ResourceManager::GetAnimation(nameAnimation);
		if (anim != nullptr)
		{
			for (size_t i = 0; i < anim->Keys.size(); i++)
			{
				Bone& bone = bones[boneInfoMap[anim->Keys[i].BoneName]];
				Bone animatedBone = anim->GetBoneAtTime(static_cast<int>(i), time);
				bone.Translation = animatedBone.Translation;
				bone.Rotation = animatedBone.Rotation;
				bone.Scale = animatedBone.Scale;
			}
		}
	}
	//std::map<std::string, Animation*> Animations;
	std::vector<Bone> bones;
	std::map<std::string, int> boneInfoMap;
};