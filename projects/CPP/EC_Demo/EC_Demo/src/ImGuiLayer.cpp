//internal code
#include "ImGuiLayer.hpp"

// external libraries
#include <imgui/imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

ImGuiLayer::ImGuiLayer()
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

	ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::OnUpdate(float deltaTime)
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2((float)1840, (float)1035);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	bool show = true;
	ShowFPSAndEntityCount(&show);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseButtonPressedEvent));
	dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseButtonReleasedEvent));
	dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseMovedEvent));
}

bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[event.GetMouseButton()] = true;
	return false;
}

bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[event.GetMouseButton()] = false;
	return false;
}

bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& event)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2(event.GetX(), event.GetY());
	return false;
}

// Demonstrate creating a simple static window with no decoration + a context-menu to choose which corner of the screen to use.
void ImGuiLayer::ShowFPSAndEntityCount(bool* p_open)
{
	const float DISTANCE = 10.0f;
	static int corner = 1;
	ImVec2 window_pos = ImVec2((corner & 1) ? ImGui::GetIO().DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? ImGui::GetIO().DisplaySize.y - DISTANCE : DISTANCE);
	ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
	if (corner != -1)
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	ImGui::SetNextWindowBgAlpha(0.3f); // Transparent background
	if (ImGui::Begin("Demo Display", p_open, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
	{
		ImGui::Text("FPS: %d", m_FPS);
		ImGui::Separator();
		ImGui::Text("Objects: %d", m_Objects);
	}
	ImGui::End();
}
