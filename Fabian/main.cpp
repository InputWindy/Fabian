#include "Fabian.h"
#include "BulkDataSystem.h"
void main()
{
	FBulkDataSystem System;

	FModelBulkData ModelBulkData;
	{
		FModelBulkData::LoadDesc ModelDesc;
		ModelDesc.FileName = "Content/Model/Gun.fbx";
		ModelDesc.ImportFlags = aiProcess_CalcTangentSpace
			| aiProcess_GenSmoothNormals
			| aiProcess_JoinIdenticalVertices
			| aiProcess_ImproveCacheLocality
			| aiProcess_LimitBoneWeights
			| aiProcess_RemoveRedundantMaterials
			| aiProcess_SplitLargeMeshes
			| aiProcess_Triangulate
			| aiProcess_GenUVCoords
			| aiProcess_SortByPType;

		assert(System.LoadFromFile(ModelDesc, ModelBulkData));
	}
	System.ReleaseData(ModelBulkData);
	assert(System.ReloadFile(ModelBulkData));
	assert(System.IsEmpty(ModelBulkData));
	System.Register(&ModelBulkData);

	//==================================//

	FImageBulkData ImageData;
	{
		FImageBulkData::LoadDesc Desc;
		Desc.Channels = 4;
		Desc.FileName = "Content/Image/test.png";
		assert(System.LoadFromFile(Desc, ImageData));
	}
	System.ReleaseData(ImageData);
	assert(System.ReloadFile(ImageData));
	assert(System.IsEmpty(ImageData));
	System.Register(&ImageData);
	//==================================//

	/*System.ForEach([](class IBulkData* InData)
		{
			cout << InData->GetTypeString() << endl;
		});*/
	System.ForEach(move(ImageData));
	System.ReleaseAll();

	

	FWindow& Window = GetMainWindow();
	Window.NativeWindowDesc.Width      = 1280;
	Window.NativeWindowDesc.Height     = 720;
	Window.NativeWindowDesc.WindowName = "Fabian";

	Window.GuiBackendDesc.Config     |= ImGuiConfigFlags_NavEnableKeyboard;
	Window.GuiBackendDesc.Config     |= ImGuiConfigFlags_DockingEnable;
	Window.GuiBackendDesc.GlslVersion = "#version 330 core";

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