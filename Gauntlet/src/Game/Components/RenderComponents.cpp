#include "RenderComponents.h"

#include "Engine/Rendering/Shaders/Shader.h"
#include "Engine/Rendering/Models/Texture.h"



void AnimationRenderComponent::Render(Shader& shader)
{
	if (model->Animated)
	{
		std::vector<glm::mat4> transforms(skeleton.bones.size());
		std::vector<glm::mat4> localTransforms(skeleton.bones.size());
		std::vector<glm::mat4> modelTransforms(skeleton.bones.size());

		for (size_t i = 0; i < skeleton.bones.size(); i++)
		{
			localTransforms[i] = skeleton.bones[i].GetMatrix();
		}
		modelTransforms[0] = localTransforms[0];

		for (size_t i = 1; i < skeleton.bones.size(); i++)
		{
			int parent = skeleton.bones[i].Parent;
			modelTransforms[i] = modelTransforms[parent] * localTransforms[i];
		}
		for (size_t i = 0; i < skeleton.bones.size(); i++)
		{
			transforms[i] = modelTransforms[i] * skeleton.bones[i].Offset;
		}
		for (size_t i = 0; i < skeleton.bones.size(); i++)
		{
			shader.UploadUniform("BoneMatrices[" + std::to_string(i) + "]", transforms[i]);
		}

	}
	auto transform = m_Parent->GetComponent<TransformComponent>();
	shader.UploadUniform("Model", transform->GetTransform());
	model->Draw(shader);
}

void RenderComponent::Render(Shader& shader)
{
	auto transform = m_Parent->GetComponent<TransformComponent>();
	shader.UploadUniform("Model", transform->GetTransform());
	model->Draw(shader);
}