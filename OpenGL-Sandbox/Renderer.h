#pragma once
#include "gameObject.h"
#include <vector>

static class Renderer
{
public:
	
	static void RenderObjectList(std::vector<baseGameObject*>  *objectList, GLCore::Utils::OrthographicCameraController inputPM, glm::vec4 inputColor);

	static void RenderObject(gameObject* objectToRender);

	void RenderSprite(gameObject2D* objectToRender);

   
};