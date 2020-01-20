#pragma once
#include <string>
#include "OBJ_Loader.h"

class gameObject
{
public:
	gameObject();
	~gameObject();

	objl::Mesh * getMesh();
	objl::Vector3 getPos();
private:
	std::string objectName;	
	//TODO: Do I want to allow multiple meshes per object?
	objl::Mesh* objectMesh;
	objl::Vector3 pos;
};

