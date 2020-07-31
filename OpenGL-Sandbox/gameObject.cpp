#include "gameObject.h"
#include <GLCore\Util\OrthographicCameraController.h>
#include <GLCore.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//base game object (other game objects inherit from)
#pragma region baseGameObject
void baseGameObject::setName(std::string input)
{
	objectName = input;
}

#pragma endregion

//Regular (3d) game object
#pragma region gameObject
gameObject::gameObject()
{
}

gameObject::gameObject(objl::Mesh* newMesh)
{
	objectMesh = newMesh;
    shader = GLCore::Utils::Shader::FromGLSLTextFiles("shaders/test2.vert.glsl", "shaders/test2.frag.glsl");


	//TODO: this should happen on mesh load in if you can't find a way to pass just the list of Vertice positions to glBufferData
	
	objectMesh->VertexPositions = new float[sizeof(objectMesh->Vertices)];

	int z = 0;
	for (int i = 0; i < sizeof(objectMesh->Vertices); i++) {
		objectMesh->VertexPositions[z] = objectMesh->Vertices[i].Position.X;
		z++;
		objectMesh->VertexPositions[z] = objectMesh->Vertices[i].Position.Y;
		z++;
		objectMesh->VertexPositions[z] = objectMesh->Vertices[i].Position.Z;
		z++;
	}

	//LOG_INFO(objectMesh->VertexPositions);

	//Populate VBO
	glCreateBuffers(1, &objectMesh->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, objectMesh->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(objectMesh->Vertices), &objectMesh->VertexPositions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	glCreateBuffers(1, &objectMesh->IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objectMesh->IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(objectMesh->Indices), &objectMesh->VertexPositions, GL_STATIC_DRAW);

}

gameObject::~gameObject()
{
}

objl::Mesh* gameObject::getMesh()
{
	return nullptr;
}

objl::Vector3 gameObject::getPos()
{
	return pos;
}

void gameObject::renderObject()
{

	//glActiveTexture(objectMesh->MeshMaterial.map_d)

}

void gameObject::renderObject(GLCore::Utils::OrthographicCameraController inputPM, glm::vec4 inputColor)
{
	//Select shaders
	glUseProgram(shader->GetRendererID());
	//the next two lines set the view projection matrix
	int location = glGetUniformLocation(shader->GetRendererID(), "u_ViewProjection");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(inputPM.GetCamera().GetViewProjectionMatrix()));
	//Get model
	location = glGetUniformLocation(shader->GetRendererID(), "model");
	//FOR TESTING: ROTATE MODEL SO I CAN SEE IT
	glm::mat4 model(1.0f);
	rotation.Y += 0.3f;
	model = glm::rotate(model, rotation.Y * (3.14f / 180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(model));
	//Sets the color in the shader
	location = glGetUniformLocation(shader->GetRendererID(), "u_Color");
	glUniform4fv(location, 1, glm::value_ptr(inputColor));
	//Bind vertex array
	glBindVertexArray(objectMesh->VAO);
	///first paramater is mode, second parameter is count,third parameters id type ,fourth parameter is element array buffer offset
	glDrawElements(GL_TRIANGLES, objectMesh->indexCount, GL_UNSIGNED_INT, nullptr);
	//unbind vertex array		
	glBindVertexArray(0);
	//Reset shader program
	glUseProgram(0);
}

#pragma endregion

//2d Game Object
#pragma region gameObject2D
gameObject2D::gameObject2D()
{
}

gameObject2D::gameObject2D(float* inVertices, int inputVertexCount, uint32_t* inIndices, int inputIndiceCount, GLCore::Utils::Shader* inputShader)
{

	vertexCount = inputVertexCount;
	indiceCount = inputIndiceCount;

	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	int i = 0;
	for (int z = 0; z < inputVertexCount; z++)
	{
		vertices[i] = inVertices[z];
		i++;
	}

	i = 0;
	for (int z = 0; z < inputIndiceCount; z++)
	{
		indices[i] = inIndices[z];
		i++;
	}

	//Populate VBO
	glCreateBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glCreateBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//Todo: Compile these shaders here instead?
	shader = inputShader;

}

gameObject2D::~gameObject2D()
{
}

void gameObject2D::renderObject(GLCore::Utils::OrthographicCameraController inputPM, glm::vec4 inputColor)
{
	//Select shaders
	glUseProgram(shader->GetRendererID());
	//the next two lines set the view projection matrix
	int location = glGetUniformLocation(shader->GetRendererID(), "u_ViewProjection");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(inputPM.GetCamera().GetViewProjectionMatrix()));
	//Get model
	location = glGetUniformLocation(shader->GetRendererID(), "model");
	//FOR TESTING: ROTATE MODEL SO I CAN SEE IT
	glm::mat4 model(1.0f);
	rotation.Y += 0.3f;
	model = glm::rotate(model, rotation.Y * (3.14f / 180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(model));
	//Sets the color in the shader
	location = glGetUniformLocation(shader->GetRendererID(), "u_Color");
	glUniform4fv(location, 1, glm::value_ptr(inputColor));
	//Bind vertex array
	glBindVertexArray(VAO);
	///first paramater is mode, second parameter is count,third parameters id type ,fourth parameter is element array buffer offset
	glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, nullptr);
	//unbind vertex array		
	glBindVertexArray(0);
	//Reset shader program
	glUseProgram(0);
}
#pragma endregion



