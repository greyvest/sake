#include "glpch.h"
#include "Application.h"

#include "Log.h"

#include "Input.h"

#include <glfw/glfw3.h>

namespace GLCore {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	//Self reference to current application instance
	Application* Application::s_Instance = nullptr;

	//Constructor for application
	Application::Application(const std::string& name, uint32_t width, uint32_t height)
	{
		if (!s_Instance)
		{
			// Initialize core
			Log::Init();
		}

		GLCORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		//Create a window with name, width, and height from constructor
		m_Window = std::unique_ptr<Window>(Window::Create({ name, width, height }));
		//Bind event callback to the application OnEvent handler
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		// Renderer::Init();
		//Create an ImGui layer by default
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}
	//Pushes layer into the stack at the current layer iterator
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}
	//Pushes an overlay layer to the stack, which means it's last on the stack of layers to get processed (Does not iterate layer iterator)
	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}
	
	//Event handler function
	//This takes an event from the application layer, and sends it to each layer in the layer stack till it returns as handled
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		//For each layer in the stack (moving from the end to the beginning)
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		//While running bool is true (which it is by default on program startup)
		while (m_Running)
		{ 
			//Timestep since last frame
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			//Run the update function for each present layer
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			//Start up ImGui and run the ImGui render for each present layer
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();
			//Poll for events and swap image buffers
			m_Window->OnUpdate();
		}
	}

	//Kill it dead
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}