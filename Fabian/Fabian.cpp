#include "pch.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"assimp-vc142-mtd.lib")

int Width  = 1280;
int Height = 720;

GLFWwindow* Window = nullptr;

uint32_t SceneColor0 = 0;

void main()
{
	//init window & load opengl functions
	{
		glfwInit();
		glfwDefaultWindowHints();

		Window = glfwCreateWindow(Width, Height, "Fabian", NULL, NULL);
		glfwMakeContextCurrent(Window);

		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}

	//init imgui
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(Window, true);
		ImGui_ImplOpenGL3_Init("#version 330 core");

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	}
	
	while (!glfwWindowShouldClose(Window))
	{
		glfwPollEvents();

		//render scene to scenecolor0
		{
			SceneColor0;
		}

		//render gui
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGui::ShowDemoWindow();

			ImGui::Render();
			int display_w, display_h;
			glfwGetFramebufferSize(Window, &display_w, &display_h);
			glViewport(0, 0, display_w, display_h);
			glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}
		
		glfwSwapBuffers(Window);
		
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(Window);

	glfwTerminate();
}