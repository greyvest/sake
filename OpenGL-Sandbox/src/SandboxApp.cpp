#include "GLCore.h"
#include "SandboxLayer.h"

using namespace GLCore;

class Sandbox : public Application
{
public:
	Sandbox()
	{
		//Add base layer of functionality to be executed by application
		PushLayer(new SandboxLayer());
	}
};

int main()
{
	//std::unique_ptr is a smart pointer that owns and manages another object through a pointer and disposes of that object when the unique_ptr goes out of scope.
	std::unique_ptr<Sandbox> app = std::make_unique<Sandbox>();
	//Because the sandbox class inherits from Application, it runs the Appliction Run function to startup
	app->Run();
}