#pragma once
#include <string>
#include <glm/common.hpp>
#include <glm/vec2.hpp>

namespace Letters
{
	const std::string NamePrefix[8]
	{
		"The good",
		"The evil",
		"The praised",
		"The loved",
		"The godless",
		"The motherless",
		"The mindless",
		"The fearless"

	};
	const std::string nameStems[7]
	{
		"adur",
		"arya",
		"eva",
		"ara",
		"eba",
		"ulo",
		"orbis",

	};
	const std::string vowels[6] =
	{
		"a","e","i","o","u","y"
	};
	const std::string consonents[21] =
	{
		"b","c","d","f","g","j","k","l","m","n","p","q","r","s","t","v","x","z","h","w"
	};
}

class MathUtils
{
public:
	static glm::vec2 RandomVec2();
	static unsigned int GetSeed();
	static float RandomRangedFloat(float v);
	static unsigned int RandomUInt(unsigned int& seed)
	{
		seed ^= seed << 13, seed ^= seed >> 17; seed ^= seed << 5; return seed;
	}
	static unsigned int Random()
	{
		unsigned int S = GetSeed();
		return RandomUInt(S);

	}
	static float Randomf()
	{
		unsigned int S = GetSeed();
		return RandomFloat(S);

	}
	static float RandomFloat(unsigned int& seed)
	{
		return RandomUInt(seed) * 2.3283064365387e-10f;
	}
	static std::string GenerateRandomName();
	static std::string GenerateRandomSuffix();

};