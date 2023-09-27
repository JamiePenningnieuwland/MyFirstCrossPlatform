#include "MathUtils.h"

#include <Core/Application.h>

glm::vec2 MathUtils::RandomVec2()
{
	return glm::vec2(Randomf(), Randomf());
}

unsigned int MathUtils::GetSeed()
{
	unsigned int seed = Application::Get()->getTime();
	return seed;
}
float MathUtils::RandomRangedFloat(float v)
{
	float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / v));
	return r2;
}
std::string MathUtils::GenerateRandomName()
{
	std::string name;
	std::string prefix;
	std::string stem;
	std::string suffix;

	prefix = Letters::NamePrefix[Random() % 7];
	stem = Letters::nameStems[Random() & 6];
	suffix = GenerateRandomSuffix();

	name = prefix + " " +  stem + suffix;
	return name;
}
std::string MathUtils:: GenerateRandomSuffix()
{
	std::string name;
	unsigned int rand = Random() % 2;
	unsigned int length = 3;
	int count = 0;

	for (unsigned int i = 0; i < length; i++)
	{
		if (rand < 2 && count < 2)
		{
			std::string letter =  Letters::consonents[Random() % 19];
			name = name + letter;
			count++;
		}
		else
		{
			name = name + Letters::vowels[Random() % 5];
			count = 0;
		}
		rand = Random() % 2;
		
	}
	return name;
}