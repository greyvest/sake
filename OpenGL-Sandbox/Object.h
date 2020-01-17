#pragma once
#include "OBJ_Loader.h"

class Object
{
public:
	//Default consructor
	Object();
	//Destructor
	~Object();

private:
	objl::Mesh* objectMesh;
	std::string objectName;
	objl::Vector3 position;
	objl::Vector3 rotation;
	
};

