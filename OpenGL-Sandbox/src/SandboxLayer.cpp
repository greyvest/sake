#include "SandboxLayer.h"
#include "../../OpenGL-Sandbox/Renderer.h"
#include "../../OpenGL-Sandbox/fileOperations.h"
using namespace GLCore;
using namespace GLCore::Utils;

//Constructor
SandboxLayer::SandboxLayer() : m_CameraController(16.0f / 9.0f)
{
	fileOperations::loadModelsFromFile();
	
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

	//Create our default shader
	m_Shader = Shader::FromGLSLTextFiles("shaders/test.vert.glsl", "shaders/test.frag.glsl");

	//create vertex array for test square TODO: Remove this once you're importing 3d models
	glCreateVertexArrays(1, &m_QuadVA);
	glBindVertexArray(m_QuadVA);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	glCreateBuffers(1, &m_QuadVB);
	glBindBuffer(GL_ARRAY_BUFFER, m_QuadVB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
	glCreateBuffers(1, &m_QuadIB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_QuadIB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
}

//Runs once when layer is removed from layer stack
void SandboxLayer::OnDetach()
{
	// Shutdown here
	glDeleteVertexArrays(1, &m_QuadVA);
	glDeleteBuffers(1, &m_QuadVB);
	glDeleteBuffers(1, &m_QuadIB);
}

//When application recieves events, they're passed into this function as well as every other layer to be processed till the event.handled flag is set to true
void SandboxLayer::OnEvent(Event& event)
{
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
}
//Every render cycle in the application runs this function, with the time from the last render cycle passed in as ts
void SandboxLayer::OnUpdate(Timestep ts)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_Shader->GetRendererID());
	
	int location = glGetUniformLocation(m_Shader->GetRendererID(), "u_ViewProjection");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m_CameraController.GetCamera().GetViewProjectionMatrix()));

	location = glGetUniformLocation(m_Shader->GetRendererID(), "u_Color");

	glUniform4fv(location, 1, glm::value_ptr(m_SquareColor));

	glBindVertexArray(m_QuadVA);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	// Render all objects in scene here
	Renderer::RenderObjectList(objectList);
	
}
//IMGUI objects are handled here
void SandboxLayer::OnImGuiRender()
{
	// ImGui here
	ImGui::Begin("Controls");
	if (ImGui::ColorEdit4("Square Base Color", glm::value_ptr(m_SquareBaseColor)))
		m_SquareColor = m_SquareBaseColor;
	ImGui::ColorEdit4("Square Alternate Color", glm::value_ptr(m_SquareAlternateColor));
	ImGui::End();
}
