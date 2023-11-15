#include "Fabian.h"
#include "BulkDataSystem.h"
#include "RHI.h"

void main()
{
	FWindow& Window = GetMainWindow();
	{
		Window.NativeWindowDesc.Width = 1280;
		Window.NativeWindowDesc.Height = 720;
		Window.NativeWindowDesc.WindowName = "Fabian";

		Window.GuiBackendDesc.Config |= ImGuiConfigFlags_NavEnableKeyboard;
		Window.GuiBackendDesc.Config |= ImGuiConfigFlags_DockingEnable;
		Window.GuiBackendDesc.GlslVersion = "#version 330 core";
	}
	
	FModelBulkData Sponza;
	{
		FModelBulkData::LoadDesc Desc;
		Desc.FileName = "Content/Model/Sponza/glTF/Sponza.gltf";
		Desc.ImportFlags;

		FBulkDataSystem::Get().LoadFromFile(Desc, Sponza);
	}

	FRHI::Generic(E_RHI_T_OpenglES)->GetRHIType();

	InitWindow(Window);
	do
	{
		PollEvents();

		//render gui
		{
			BeginGui();

			ImGui::ShowDemoWindow();

			MaximizeViewport(Window);
			EndGui();
		}

		WindowEndFrame(Window);
	} while (!(GetWindowState(Window) & EWindowState::ShouldClose));

	TeminateWindow(Window);
}