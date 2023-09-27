#include "Application.h"
#include "gl.h"
#include "Input.h"

Application* Application::app = nullptr;

void Application::Run()
{
	game.Init();
	OpenGLSetUp();

	//	deltaTime
	timer.reset();

	while (!WindowOpen)
	{
		WindowOpen = window.ShouldClose();
		window.BeginImGuiFrame();

		//creating deltatime
		CalculateDeltaTime();
	
		//clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		game.Update(deltaTime);

		ImGui::Render();
		window.RenderImGUI();

		//swapping the buffers
		window.SwapBuffers();


	}
	window.Shutdown();
}
Application* Application::Get()
{
	if(!app)
	{
		app = new Application();
	}
	return app;
}
void Application::KeyPressEventCallBack(int key)
{
	//if(ImGui::GetIO().WantCaptureKeyboard)
		game.KeyPressEvent(key);
}
void Application::ButtonPressEventCallBack(int button)
{
	if (!ImGui::GetIO().WantCaptureMouse)
		game.ButtonPressEvent(button);
}
void Application::CalculateDeltaTime()
{
	deltaTime = timer.elapsed();
	timer.reset();
	Input::Update();
}
void Application::OpenGLSetUp()
{
	// depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//tells open gl to not render the faces pointing away
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//set the clear color
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}
