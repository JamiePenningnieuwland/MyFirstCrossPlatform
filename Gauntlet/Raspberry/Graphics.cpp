#include "Engine/Rendering/Graphics.h"

#include <iostream>
#include <fstream>
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <Input.h>
#include "InputData.h"

#pragma GCC diagnostic push 

#pragma GCC diagnostic ignored "-Wconversion"    
#include "../ExternalFiles/IamGUI/imgui.h"
#include "../ExternalFiles/IamGUI/imgui_impl_opengl3.h"
#include "../ExternalFiles/IamGUI/imgui_impl_x11.h"
#pragma GCC diagnostic pop

#include <Core/Application.h>
extern IMGUI_IMPL_API int ImGui_ImplX11_EventHandler(XEvent& event);


// Too lazy to do this the proper way
namespace Internal
{
	Window win;
	Display* display;
	EGLDisplay eglDisplay;
	EGLSurface eglSurface;
	EGLContext eglContext;
	Atom wmDeleteMessage;
	bool running{ false };
	InputData inputData;
}

void InitializeWindow(uint32_t w, uint32_t h, std::string name)
{
	/// Create Display
	Internal::display = XOpenDisplay(NULL);
	if (Internal::display == NULL)
	{
		std::cout << "Error creating X display!" << std::endl;
		exit(1);
	}

	//get information about out display
	int screen_num = DefaultScreen(Internal::display);

	//now lets create the window
	int win_width = w;
	int win_height = h;

	int win_x = 0;
	int win_y = 0;
	Internal::win = XCreateSimpleWindow(
		Internal::display,
		RootWindow(Internal::display, screen_num),
		win_x,
		win_y,
		win_width,
		win_height,
		0,
		BlackPixel(Internal::display, screen_num),
		WhitePixel(Internal::display, screen_num)
	);

	//Window name
	XStoreName(Internal::display, Internal::win, name.c_str());

	//register for events
	XSelectInput(Internal::display, Internal::win, ExposureMask| KeyPressMask | KeyReleaseMask 
		| ButtonPressMask | ButtonReleaseMask | PointerMotionMask /*| ResizeRedirectMask */ | StructureNotifyMask);

	//make the window visable
	XMapWindow(Internal::display, Internal::win);

	Internal::wmDeleteMessage = XInternAtom(Internal::display, "WM_DELETE_WINDOW", false);
	XSetWMProtocols(Internal::display, Internal::win, &Internal::wmDeleteMessage, 1);


	//XSelectInput(Internal::display, Internal::win,
	//	KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask /*| ResizeRedirectMask */| StructureNotifyMask);

	Input::Init(&Internal::inputData);

	Internal::running = true;


}

void InitializeEGL()
{
	Internal::eglDisplay = eglGetDisplay((EGLNativeDisplayType)Internal::display);
	if (Internal::eglDisplay == EGL_NO_DISPLAY)
	{
		printf("ERROR: \"Failed to get Display\"\n"); exit(2);
	}

	// Initialising EGL (can replace NULL with major/minor version variables)
	if (eglInitialize(Internal::eglDisplay, NULL, NULL) != EGL_TRUE)
	{
		printf("ERROR: \"Failed to Initialize EGL\"\n"); return exit(3);
	}

	//Create an EGL config for what we want
	EGLConfig config;
	EGLint numConfigs;
	EGLint configs[] =
	{
		EGL_BUFFER_SIZE, 32,
		EGL_RENDERABLE_TYPE,
		EGL_OPENGL_ES3_BIT,
		EGL_DEPTH_SIZE, 8,
		EGL_NONE
	};

	// Choosing which config to use
	if (eglChooseConfig(Internal::eglDisplay, configs, &config, 1, &numConfigs) == EGL_FALSE)
	{
		printf("ERROR: \"Failed to choose config\"\n"); exit(4);
	}

	// Creating the window surface
	Internal::eglSurface = eglCreateWindowSurface(Internal::eglDisplay, config, Internal::win, NULL);
	if (Internal::eglSurface == EGL_NO_SURFACE)
	{
		printf("ERROR: \"Failed to create Window Surface\"\n"); exit(5);
	}

	// Context Attributes
	EGLint contextAttribs[] =
	{
		EGL_CONTEXT_MAJOR_VERSION, 3,
		EGL_CONTEXT_MINOR_VERSION, 1,
		EGL_NONE
	};

	// Create rendering context
	Internal::eglContext = eglCreateContext(Internal::eglDisplay, config, EGL_NO_CONTEXT, contextAttribs);
	if (Internal::eglContext == EGL_NO_CONTEXT)
	{
		printf("ERROR: \"Failed to create Context\"\n"); exit(6);
	}

	// Set context as current
	if (eglMakeCurrent(Internal::eglDisplay, Internal::eglSurface, Internal::eglSurface, Internal::eglContext) != EGL_TRUE)
	{
		printf("ERROR: \"Failed to make context current\"\n"); exit(7);
	}
}

Graphics::Graphics(std::string name, uint32_t width, uint32_t height)
{
	m_Width = width;
	m_Height = height;
	InitializeWindow(m_Width, m_Height, name);
	InitializeEGL();
	eglSwapInterval(Internal::eglDisplay, 0);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	
	io.DisplaySize.x = m_Width;
	io.DisplaySize.y = m_Height;

	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplX11_Init(Internal::display, (void*)Internal::win);
	ImGui_ImplOpenGL3_Init("#version 100");
	imGUI_initalize();
}

bool Graphics::ShouldClose()
{
	return !Internal::running;
}
void Resize(float height, float width)
{
	glViewport(0.0f, 0.0f, width, height);
	//eglDestroySurface(Internal::eglDisplay, Internal::eglSurface);
	//eglDestroyContext(Internal::eglDisplay, Internal::eglContext);
	//eglTerminate(Internal::eglDisplay);
	//Internal::eglDisplay = nullptr;
	//Internal::eglSurface = nullptr;
	//Internal::eglContext = nullptr;

	//InitializeEGL();
	//eglSwapInterval(Internal::eglDisplay, 0);
	
}
void Graphics::SwapBuffers()
{
	eglSwapBuffers(Internal::eglDisplay, Internal::eglSurface);

	//key event check
	while (XPending(Internal::display))
	{
		XEvent e;
		XNextEvent(Internal::display, &e);
		
		ImGui_ImplX11_EventHandler(e);

		switch (e.type)
		{

		case KeyPress:
		{
			//TO GET KEYCODES
			Application::Get()->KeyPressEventCallBack(e.xkey.keycode);
			Internal::inputData.Keys[e.xkey.keycode] = true;
			break;
		}
		case KeyRelease:
		{
   			Internal::inputData.Keys[e.xkey.keycode] = false;
			break;
		}
		//mouse input
		case ButtonPress:
		{
			Application::Get()->ButtonPressEventCallBack(e.xkey.keycode);
			Internal::inputData.MouseButtons[e.xbutton.button] = true;
			break;
		}
		case ButtonRelease:
		{
			Internal::inputData.MouseButtons[e.xbutton.button] = false;
			break;
		}
		case MotionNotify:
		{
			//glm::vec2 previousMousePos = Internal::inputData.MousePosition;
			Internal::inputData.MousePosition.x = static_cast<float>(e.xmotion.x);
			Internal::inputData.MousePosition.y = static_cast<float>(e.xmotion.y);
		
			break;
		}
		case ClientMessage:
		{
			if (static_cast<Atom>(e.xclient.data.l[0]) == Internal::wmDeleteMessage)
			{
				Internal::running = false;
			}
			break;
		}
		case ConfigureNotify:
		{
			m_Width = e.xconfigure.width;
			m_Height = e.xconfigure.height;

			Application::Get()->ResizeWindow(e.xconfigure.width, e.xconfigure.height);
			Resize(m_Height, m_Width);
			break;
		}
	
		default:
			break;
		}
	}
}
void Graphics::BeginImGuiFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplX11_NewFrame();
	ImGui::NewFrame();
}
void Graphics::RenderImGUI()
{
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void Graphics::Shutdown()
{
	//ImGui_ImplX11_Shutdown();
	eglDestroySurface(Internal::eglDisplay, Internal::eglSurface);
	eglDestroyContext(Internal::eglDisplay, Internal::eglContext);
	eglTerminate(Internal::eglDisplay);
	XDestroyWindow(Internal::display, Internal::win);
	XCloseDisplay(Internal::display);

}
