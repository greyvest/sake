#include "fileOperations.h"



//
//void fileOperations::loadModelsFromFile()
//{
//    using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
//    
//    for (const auto& dirEntry : recursive_directory_iterator(fileOperations::modelDirectory))
//    {
//        LOG_INFO("Here's our current file:  %s", dirEntry.path().string());
//        if (modelLoader.LoadFile(dirEntry.path().string())) {
//            //Hella, it loaded
//        }
//        else {
//            //Uh oh didn't load
//        }
//		
//		
//    }
//
//    //Place references to all the loaded models in the meshDict
//    for each (objl::Mesh currentMesh in modelLoader.LoadedMeshes)
//    {
//        meshDict.insert(std::pair(currentMesh.MeshName, &currentMesh));
//        LOG_INFO("Here's a mesh we loaded: %s", currentMesh.MeshName);
//    }
//
//}

void fileOperations::setModelDirectory(std::string newDirectory)
{
    fileOperations::modelDirectory = newDirectory;
}
