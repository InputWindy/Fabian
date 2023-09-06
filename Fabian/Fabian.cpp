#include "Fabian.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"assimp-vc142-mtd.lib")

GLFWwindow* InitNativeWindow(FNativeWindowDesc& InDesc)
{
	GLFWwindow* OutWindow = nullptr;
	glfwInit();
	glfwDefaultWindowHints();

	OutWindow = glfwCreateWindow(InDesc.Width, InDesc.Height, InDesc.WindowName.c_str(), NULL, NULL);
	glfwMakeContextCurrent(OutWindow);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	return OutWindow;
};
ImGuiContext* InitGuiBackend(FGuiBackendDesc& InDesc, GLFWwindow* InNativeWindow)
{
	ImGuiContext* GCtx = nullptr;
	IMGUI_CHECKVERSION();
	GCtx = ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(InNativeWindow, true);
	ImGui_ImplOpenGL3_Init(InDesc.GlslVersion.c_str());

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags  = InDesc.Config;
	io.BackendFlags = InDesc.BackendFlag;

	return GCtx;
	
}
void InitWindow(FWindow& InWindow)
{
	if (GetWindowState(InWindow) & EWindowState::UnInit)
	{
		InWindow.NativeWindow = InitNativeWindow(InWindow.NativeWindowDesc);
		InWindow.GuiBackend = InitGuiBackend(InWindow.GuiBackendDesc, InWindow.NativeWindow);
		InWindow.State = EWindowState::Initialized;
	}
}
;

void TerminateGuiBackend()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
};
void TerminateNativeWindow(GLFWwindow* InNativeWindow)
{
	glfwDestroyWindow(InNativeWindow);
	glfwTerminate();
}
void TeminateWindow(FWindow& InWindow)
{
	TerminateGuiBackend();
	TerminateNativeWindow(InWindow.NativeWindow);
	InWindow.State = EWindowState::UnInit;
}
EWindowState GetWindowState(const FWindow& InWindow)
{
	return InWindow.State;
}
void UpdateWindowState(FWindow& InWindow)
{
	if (InWindow.State & EWindowState::Initialized)
	{
		InWindow.State = 
			glfwWindowShouldClose(InWindow.NativeWindow) ? EWindowState::ShouldClose: 
			EWindowState::Initialized;
	}
}
void SwapBuffers(FWindow& InWindow)
{
	glfwSwapBuffers(InWindow.NativeWindow);
}
void PollEvents()
{
	glfwPollEvents();
}
void BeginGui()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}
void EndGui()
{
	ImGui::Render();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void WindowEndFrame(FWindow& InWindow)
{
	SwapBuffers(InWindow);
	UpdateWindowState(InWindow);
}
void MaximizeViewport(FWindow& InWindow)
{
	int display_w, display_h;
	glfwGetFramebufferSize(InWindow.NativeWindow, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
}
;