#include "Renderer.h"
void Renderer::RenderObjectList(std::vector<gameObject*> objectList)
{
	for each (gameObject* obj in objectList)
	{
		RenderObject(obj);
		
	}
}

void Renderer::RenderObject(gameObject* objectToRender)
{
	//TODO: Render the object by pulling out the mesh
	auto objectMesh = objectToRender->getMesh();
	glBindVertexArray(objectMesh->VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objectMesh->IBO);
	glDrawElements(GL_TRIANGLES, objectMesh->indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
