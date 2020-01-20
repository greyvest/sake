#pragma once
#include "OBJ_Loader.h"
#include <map>
#include <GLCoreUtils.h>
#include <filesystem>

namespace fileOperations
{
	static std::map<std::string, objl::Mesh*> meshDict;

    static void setModelDirectory(std::string newDirectory);

    static objl::Loader modelLoader;

    static std::string modelDirectory = "models/";

	static void loadModelsFromFile()
    {
        using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

        for (const auto& dirEntry : recursive_directory_iterator(fileOperations::modelDirectory))
        {
            LOG_INFO("Here's our current file:");
            LOG_INFO( dirEntry.path().string());

            if (modelLoader.LoadFile(dirEntry.path().string())) {
                //Hella, it loaded
            }
            else {
                //Uh oh didn't load
            }


        }

        //Place references to all the loaded models in the meshDict
        for each (objl::Mesh currentMesh in modelLoader.LoadedMeshes)
        {
            meshDict.insert(std::pair(currentMesh.MeshName, &currentMesh));
            LOG_INFO("Here's a mesh we loaded:");
            LOG_INFO(currentMesh.MeshName);
        }

    }
	
};

