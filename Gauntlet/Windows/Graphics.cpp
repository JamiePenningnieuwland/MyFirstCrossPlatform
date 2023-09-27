#include "Engine/Rendering/Graphics.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "input.h"
#include <iostream>
#include "../ExternalFiles/IamGUI/imgui_impl_glfw.h"
#include "../ExternalFiles/IamGUI/imgui_impl_opengl3.h"
#include <Core/Application.h>


//global for multiple functions
GLFWwindow* window;
Graphics::Graphics(std::string name, uint32_t width, uint32_t height)
    : m_Width(width)
    , m_Height(height)

{
    
    ///* Initialize the library */
    if (!glfwInit())
    {
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
    }



    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
    }
    Input::Init(window);

    std::cout << "OpenGL Renderer:" << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer:" << glGetString(GL_RENDERER) << std::endl;
    std::cout << "version:" << glGetString(GL_VERSION) << std::endl;


    glfwSetWindowSizeCallback(window, [](GLFWwindow* a_window, int width, int height)
    {
        Application::Get()->ResizeWindow(width, height);
        glViewport(0, 0, width, height);
    });


    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends

    glfwSetKeyCallback(window, [](GLFWwindow* a_window, int key, int scancode, int action, int mods) 
    {
        if (action == GLFW_PRESS)
            Application::Get()->KeyPressEventCallBack(key);
    });
    glfwSetMouseButtonCallback(window, [](GLFWwindow* a_window, int button, int action, int mods)
    {
        if (action == GLFW_PRESS)
            Application::Get()->ButtonPressEventCallBack(button);
    });
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 100");
    imGUI_initalize();

}

bool Graphics::ShouldClose()
{
    return glfwWindowShouldClose(window);
}

void Graphics::SwapBuffers()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}
void Graphics::BeginImGuiFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}
void Graphics::RenderImGUI() 
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Graphics::Shutdown()
{
    glfwTerminate();
}
