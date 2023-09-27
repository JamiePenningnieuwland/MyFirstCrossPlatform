#include "Bone.h"


Bone::Bone() 
	:Parent(-1)
	, Translation(0.f)
	, Rotation(glm::vec3(0.f))
	, Scale(1.f)
	, Offset(1.f)

{

};
glm::mat4 Bone::GetMatrix()
{
	return glm::translate(glm::mat4(1.), Translation) * glm::toMat4(Rotation) * glm::scale(glm::mat4(1.), Scale);
}