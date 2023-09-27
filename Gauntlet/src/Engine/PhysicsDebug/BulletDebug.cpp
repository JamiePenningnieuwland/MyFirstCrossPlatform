#include "BulletDebug.h"


void BulletDebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{

	/*float lineVertex[9]
	{
		from.x(), from.y(), from.z(),
		to.x(), to.y(), to.z(),
		color.x(), color.y(), color.z()
	};*/
	debugShader->Bind();
	debugShader->UploadUniform("uPosition[0]", glm::vec3(from.x(), from.y(), from.z()));
	debugShader->UploadUniform("uPosition[1]", glm::vec3(to.x(), to.y(), to.z()));
	debugShader->UploadUniform("uColor", glm::vec3(color.x(), color.y(), color.z()));

	/// baddddd 
	//glVertexPointer(9, GL_FLOAT, 0, lineVertex);
	glDrawArrays(GL_LINES, 0, 2);
}
