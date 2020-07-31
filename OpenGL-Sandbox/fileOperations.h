#pragma once
#include "OBJ_Loader.h"
#include <map>
#include <GLCoreUtils.h>
#include <filesystem>w
#include <GLCore\Core\Layer.h>
#include <GLCore.h>
#include "src/SandboxLayer.h"

static class fileOperations
{
private:
    fileOperations();
    ~fileOperations();

	static std::map<std::string, objl::Mesh*> meshDict;

    static void loadModelsIntoGameObjects() {
        //std::for_each(meshDict.begin(), meshDict.end(), loadModelToGameobject);
    }

    static void loadModelToGameobject(objl::Mesh * mesh, std::string objectName, std::vector<baseGameObject *> * objectList) {
        LOG_INFO("Loading in " + mesh->MeshName + "to game object" );
        gameObject* newGameObject = new gameObject(mesh);
        newGameObject->setName(objectName);
        objectList->push_back(newGameObject);
    }
public:
    ///This function loads models from obj files into game objects
    static void loadModelsFromFile(std::string inputDirectory, std::vector<baseGameObject*> *objectList)
    {
        using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

        objl::Loader modelLoader;
		
        for (const auto& dirEntry : recursive_directory_iterator(inputDirectory))
        {
			if (modelLoader.LoadFile(dirEntry.path().string())) {
                //If it loaded with a name "default", change it's name to be not that. TODO: Make this just the file name instead of the path (probably parse it out)
                if (modelLoader.LoadedMeshes.back().MeshName == "default")
                    modelLoader.LoadedMeshes.back().MeshName = dirEntry.path().string();

                LOG_INFO(modelLoader.LoadedMeshes.back().MeshName);
            }
            else {
                //Uh oh didn't load
            }
		}
                
        //Load all the meshes into a game object and place it in our objectlist
        for each (objl::Mesh currentMesh in modelLoader.LoadedMeshes)
        {
            loadModelToGameobject(&currentMesh, currentMesh.MeshName, objectList);
        }
        
    }
	
};

