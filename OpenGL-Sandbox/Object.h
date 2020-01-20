#ifndef OBJECT
#define OBJECT

#include "OBJ_Loader.h"

class gameObject
{
public:
	//Default consructor
	gameObject();
	//Destructor
	~gameObject();

	objl::Mesh* getMesh();
	
private:
	objl::Mesh* objectMesh;
	std::string objectName;
	objl::Vector3 position;
	objl::Vector3 rotation;
	
};


#endif
