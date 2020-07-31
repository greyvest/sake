#include <GLCore/Core/Layer.h>
#include "Renderer.h"
#include <GLCore\Util\OrthographicCameraController.h>

void Renderer::RenderObjectList(std::vector<baseGameObject*> * objectList, GLCore::Utils::OrthographicCameraController inputPM, glm::vec4 inputColor)
{
	for each (baseGameObject* obj in *objectList)
	{
		obj->renderObject(inputPM, inputColor);
	}
}

void Renderer::RenderObject(gameObject* objectToRender)
{
	//TODO: Render the object by pulling out the mesh
	auto objectMesh = objectToRender->getMesh();
//	LOG_INFO("RENDERING MESH:  " + objectMesh->MeshName);
	//Bind vertex array to mesh vertexs
	glBindVertexArray(objectMesh->VAO);
	//Bind GL_ELEMENT_ARRAY_BUFFER to object mesh 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objectMesh->IBO);
	//DRAW
	glDrawElements(GL_TRIANGLES, objectMesh->indexCount, GL_UNSIGNED_INT, 0);
	//Clearing this
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void Renderer::RenderSprite(gameObject2D* objectToRender) {


}