#include "SandboxLayer.h"
#include "../../OpenGL-Sandbox/Renderer.h"
#include "../../OpenGL-Sandbox/fileOperations.h"
#include <GLCore\Core\KeyCodes.h>

using namespace GLCore;
using namespace GLCore::Utils;



//Constructor
SandboxLayer::SandboxLayer() : m_CameraController(16.0f / 9.0f)
{
	//load all models from file 
	fileOperations::loadModelsFromFile("models/");
	//fileOperations::loadModelsIntoGameObjects();
	
}

//Destructor
SandboxLayer::~SandboxLayer()
{
}

//Runs once when layer is added to layer stack
void SandboxLayer::OnAttach()
{
	
	//Enable debugging cause it's good
	EnableGLDebugging();
	//Set clear color (probably default to black in future)
	glClearColor(.44f, .73f, .81f, 1.0f);
	//Enabling render functionality from opengl TODO: Figure out what these do
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	createTestShape();
}


//This is just to make sure I'm rendering until I can import meshes
void SandboxLayer::createTestShape()
{
	float vertices3[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
		-0.5f, 0.7f, 0.0f,
		0.0f, 0.7f, 0.0f,
		0.0f, 0.5f, 0.0f,
	};

	uint32_t indices3[] = { 0, 1, 2, 2, 3, 0, 3, 4, 5, 3, 5, 6 };

	uint32_t indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};


	float vertices[] = {
		-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};
	
	//Create our default shader
	Shader* x = Shader::FromGLSLTextFiles("shaders/test.vert.glsl", "shaders/test.frag.glsl");
	Shader* y = Shader::FromGLSLTextFiles("shaders/test2.vert.glsl", "shaders/test2.frag.glsl");
	gameObject2D* g3 = new gameObject2D(vertices3, 21, indices3, 12, x);

	gameObject2D* g2 = new gameObject2D(vertices, 12, indices, 12, y);

	//objectList.push_back(g3);
	objectList.push_back(g2);
}

//Runs once when layer is removed from layer stack
void SandboxLayer::OnDetach()
{

}

//When application recieves events, they're passed into this function as well as every other layer to be processed till the event.handled flag is set to true
void SandboxLayer::OnEvent(Event& event)
{

	LOG_INFO(event);
	// Events here
	m_CameraController.OnEvent(event);

	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<MouseButtonPressedEvent>(
		[&](MouseButtonPressedEvent& e)
		{
			m_SquareColor = m_SquareAlternateColor;
			return false;
		});
	dispatcher.Dispatch<MouseButtonReleasedEvent>(
		[&](MouseButtonReleasedEvent& e)
		{
			m_SquareColor = m_SquareBaseColor;
			return false;
		});
	dispatcher.Dispatch<KeyPressedEvent>(
		[&](KeyPressedEvent& e)
		{

			if (e.GetKeyCode() == HZ_KEY_H)
			{
				m_SquareColor = m_SquareAlternateColor;
			}

			if (e.GetKeyCode() == HZ_KEY_J)
			{
				m_SquareColor = m_SquareAlternateColor2;
			}

			return false;
		});

	dispatcher.Dispatch<KeyReleasedEvent>(
		[&](KeyReleasedEvent& e)
		{
			m_SquareColor = m_SquareBaseColor;
			return false;
		});

}
//Every render cycle in the application runs this function, with the time from the last render cycle passed in as ts
void SandboxLayer::OnUpdate(Timestep ts)
{
	//Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	m_CameraController.OnUpdate(ts);

	// Render all objects in scene here

	Renderer::RenderObjectList(objectList, m_CameraController, m_SquareColor);
	
	//Reset shader program in use
	glUseProgram(0);
}

//IMGUI objects are handled here
void SandboxLayer::OnImGuiRender()
{
	// ImGui here
	ImGui::Begin("Controls");
	if (ImGui::ColorEdit4("Square Base Color", glm::value_ptr(m_SquareBaseColor)))
		m_SquareColor = m_SquareBaseColor;
	ImGui::ColorEdit4("Square Alternate Color", glm::value_ptr(m_SquareAlternateColor));
	ImGui::ColorEdit4("Square Alternate Color 2", glm::value_ptr(m_SquareAlternateColor2));
	ImGui::End();
}

void SandboxLayer::addObjectToList(baseGameObject* x)
{
	//objectList.push_back(x);
}
