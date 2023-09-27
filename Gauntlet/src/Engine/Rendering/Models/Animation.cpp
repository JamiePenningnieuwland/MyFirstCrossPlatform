#include "Animation.h"

Bone Animation::GetBoneAtTime(size_t index, float time)
{
	BoneKey& key = Keys[index];
	float localTime = fmod(time * TicksPerSecond, Duration);

	size_t TranslationKeyIndex = 0;
	for (size_t i = 0; i < key.TranslationKeys.size() - 1; i++)
	{
		TranslationKey transkey = key.TranslationKeys[i + 1];
		if (localTime < transkey.TimeFrame)
		{
			TranslationKeyIndex = i + 1;
			break;
		}
	}

	size_t RotationKeyIndex = 0;
	for (size_t i = 0; i < key.RotationKeys.size() - 1; i++)
	{
		RotationKey rotkey = key.RotationKeys[i + 1];
		if (localTime < rotkey.TimeFrame)
		{
			RotationKeyIndex = i + 1;
			break;
		}
	}

	size_t ScaleKeyIndex = 0;
	for (size_t i = 0; i < key.ScaleKeys.size() - 1; i++)
	{
		ScaleKey scalekey = key.ScaleKeys[i + 1];
		if (localTime < scalekey.TimeFrame)
		{
			ScaleKeyIndex = i + 1;
			break;
		}
	}

	//interpolations values
	if(TranslationKeyIndex > 0)
	{
		TranslationKey transFrame = key.TranslationKeys[TranslationKeyIndex - 1];
		TranslationKey nextTransFrame = key.TranslationKeys[TranslationKeyIndex];
		float TransInterpolation = glm::smoothstep((float)transFrame.TimeFrame, (float)nextTransFrame.TimeFrame, localTime);

		RotationKey rotFrame = key.RotationKeys[RotationKeyIndex - 1];
		RotationKey nextRotFrame = key.RotationKeys[RotationKeyIndex];
		float rotInterpolation = glm::smoothstep((float)rotFrame.TimeFrame, (float)nextRotFrame.TimeFrame, localTime);

		ScaleKey scaleFrame = key.ScaleKeys[ScaleKeyIndex - 1];
		ScaleKey nextScaleFrame = key.ScaleKeys[ScaleKeyIndex];
		float scaleInterpolation = glm::smoothstep((float)scaleFrame.TimeFrame, (float)nextScaleFrame.TimeFrame, localTime);

		//bone
		Bone bone;
		bone.Translation = glm::mix(transFrame.Translation, nextTransFrame.Translation, TransInterpolation);
		bone.Rotation = glm::mix(rotFrame.Rotation, nextRotFrame.Rotation, rotInterpolation);
		bone.Scale = glm::mix(scaleFrame.Scale, nextScaleFrame.Scale, scaleInterpolation);

		return bone;
	}
	else 
	{
		Bone bone;
		bone.Translation = key.TranslationKeys[0].Translation;
		bone.Rotation = key.RotationKeys[0].Rotation;
		bone.Scale = key.ScaleKeys[0].Scale;

		return bone;
	
	}
}