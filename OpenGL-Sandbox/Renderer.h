#pragma once
#include "gameObject.h"
#include <vector>

static class Renderer
{
public:
	static void RenderObjectList(std::vector<gameObject*> objectList);

	static void RenderObject(gameObject* objectToRender);

   
};