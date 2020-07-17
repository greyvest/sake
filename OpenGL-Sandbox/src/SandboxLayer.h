#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>

class SandboxLayer : public GLCore::Layer
{
public:
	//Constructor
	SandboxLayer();
	//Destructor
	virtual ~SandboxLayer();
	//On Layer Startup
	virtual void OnAttach() override;
	//On layer destroy
	virtual void OnDetach() override;
	//Handling events from GLFW
	virtual void OnEvent(GLCore::Event& event) override;
	//Time based main update loop
	virtual void OnUpdate(GLCore::Timestep ts) override;
	//IMGUI renndering loop
	virtual void OnImGuiRender() override;
	//Object adding function
	static void addObjectToList(baseGameObject*);


	//This function will dissapear once I load meshes
	void createTestShape();
private:
	//Start binding them to game objects. Maybe use this as default;
	GLCore::Utils::Shader* m_Shader;

	GLCore::Utils::OrthographicCameraController m_CameraController;

	glm::vec4 m_SquareBaseColor = { 0.8f, 0.2f, 0.3f, 1.0f };
	glm::vec4 m_SquareAlternateColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec4 m_SquareAlternateColor2 = { 0.9f, 0.3f, 0.8f, 1.0f };
	glm::vec4 m_SquareColor = m_SquareBaseColor;
};