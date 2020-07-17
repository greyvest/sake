#pragma once
#include <string>
#include "OBJ_Loader.h"
#include <GLCore\Util\OrthographicCameraController.h>
#include <GLCore/Util/Shader.h>
class baseGameObject {
public:
	virtual void renderObject(GLCore::Utils::OrthographicCameraController inputPM, glm::vec4 inputColor) = 0;
	std::string objectName;
	objl::Vector3 pos;
public:
	virtual void setName(std::string);
};

class gameObject : public baseGameObject
{
public:
	gameObject();
	gameObject(objl::Mesh *);
	~gameObject();

	objl::Mesh * getMesh();
	objl::Vector3 getPos();

	void renderObject();
	void renderObject(GLCore::Utils::OrthographicCameraController inputPM, glm::vec4 inputColor);
private:
	//TODO: Do I want to allow multiple meshes per object?
	objl::Mesh* objectMesh;
};



class gameObject2D : public baseGameObject
{
public:
	//Constructors/Destructors
	gameObject2D();
	gameObject2D(float* inVertices, int inputVertexCount, uint32_t* inIndices, int inputIndiceCount, GLCore::Utils::Shader* inputShader);
	~gameObject2D();
	//Render Object function
	void renderObject(GLCore::Utils::OrthographicCameraController inputPM, glm::vec4 inputColor);

private:
	float vertices[21];
	uint32_t indices[12];

	int vertexCount;
	int indiceCount;

	GLuint VAO, VBO, IBO;

	GLCore::Utils::Shader* shader;
	
};