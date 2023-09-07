#pragma once
#include "pch.h"

enum EWindowState
{
	UnInit		= 1 << 0,
	Initialized	= 1 << 1,

	ShouldClose = 1 << 2,
};

struct FNativeWindowDesc
{
	string WindowName = "Default";

	int Width = 1280;
	int Height = 720;
};

struct FGuiBackendDesc
{
	string GlslVersion = "#version 330 core";
	ImGuiConfigFlags  Config = 0;
	ImGuiBackendFlags BackendFlag = 0;
};

struct FWindow
{
	GLFWwindow*   NativeWindow = nullptr;
	ImGuiContext* GuiBackend = nullptr;

	FNativeWindowDesc NativeWindowDesc;
	FGuiBackendDesc   GuiBackendDesc;

	EWindowState State = EWindowState::UnInit;
};

GLFWwindow* InitNativeWindow(FNativeWindowDesc& InDesc);
ImGuiContext* InitGuiBackend(FGuiBackendDesc& InDesc, GLFWwindow* InNativeWindow);
void InitWindow(FWindow& InWindow);

void TerminateGuiBackend();
void TerminateNativeWindow(GLFWwindow* InNativeWindow);
void TeminateWindow(FWindow& InWindow);

EWindowState GetWindowState(const FWindow& InWindow);
void UpdateWindowState(FWindow& InWindow);

void SwapBuffers(FWindow& InWindow);
void PollEvents();

void BeginGui();
void EndGui();
void WindowEndFrame(FWindow& InWindow);

void MaximizeViewport(FWindow& InWindow);

FWindow& GetMainWindow();