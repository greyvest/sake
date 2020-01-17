#include "SandboxLayer.h"

using namespace GLCore;
using namespace GLCore::Utils;

SandboxLayer::SandboxLayer()
{
}

SandboxLayer::~SandboxLayer()
{
}

//Runs once when layer is added to layer stack
void SandboxLayer::OnAttach()
{
	//Enable debugging cause it's good
	EnableGLDebugging();
	//Set clear color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
}

//Runs once when layer is removed from layer stack
void SandboxLayer::OnDetach()
{
	// Shutdown here
}

//When application recieves events, they're passed into this function as well as every other layer to be processed till the event.handled flag is set to true
void SandboxLayer::OnEvent(Event& event)
{
	// Events here
}
//Every render cycle in the application runs this function, with the time from the last render cycle passed in as ts
void SandboxLayer::OnUpdate(Timestep ts)
{
	glClear(GL_COLOR_BUFFER_BIT);
	// Render here
}
//IMGUI objects are handled here
void SandboxLayer::OnImGuiRender()
{
	// ImGui here
}
