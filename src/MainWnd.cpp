#include <stdio.h>
#include <vector>
#include "imgui.h"
#include "ChildWnd.hpp"
#include "MainWnd.hpp"

namespace {
	ChildWnd childWnd;
}

void MainWnd::show(bool* p_open) {
#ifdef IMGUI_HAS_VIEWPORT
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->GetWorkPos());
	ImGui::SetNextWindowSize(viewport->GetWorkSize());
	ImGui::SetNextWindowViewport(viewport->ID);
#else
	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
#endif
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::Begin("main", p_open, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize);

	static int offsetX = 0;
	// ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
	ImGui::DragInt("Offset X", &offsetX, 1.0f, 0, 1000);
	static int offsetY = 0;
	ImGui::DragInt("Offset Y", &offsetY, 1.0f, 0, 1000);
	static int widthX = 200;
	ImGui::DragInt("Width X", &widthX, 1.0f, 0, 1000);
	static int heightY = 100;
	ImGui::DragInt("Height", &heightY, 1.0f, 0, 1000);

	childWnd.show(
			ImGui::GetCursorPosX() + (float)offsetX,
			ImGui::GetCursorPosY() + (float)offsetY,
			widthX,
			heightY
			);
	ImGui::PopStyleVar(1);
}
