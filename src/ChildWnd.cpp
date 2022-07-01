#include <stdio.h>
#include <vector>
#include "imgui.h"
#include "ChildWnd.hpp"
#include "AnimTimer.hpp"

namespace {
	std::vector<float> bounceTable = {0, 1, 1, 1, 1, 2 ,2, 3, 4, 5 ,4 ,3, 2, 2, 1, 1, 1, 1, 0 };
	AnimTimer<float> bounceTimer_(bounceTable, std::chrono::milliseconds(300));
}

static void ShowExampleMenuFile()
{
    // IMGUI_DEMO_MARKER("Examples/Menu");
    ImGui::MenuItem("(demo menu)", NULL, false, false);
    if (ImGui::MenuItem("New")) {}
    if (ImGui::MenuItem("Open", "Ctrl+O")) {}
    if (ImGui::BeginMenu("Open Recent"))
    {
        ImGui::MenuItem("fish_hat.c");
        ImGui::MenuItem("fish_hat.inl");
        ImGui::MenuItem("fish_hat.h");
        if (ImGui::BeginMenu("More.."))
        {
            ImGui::MenuItem("Hello");
            ImGui::MenuItem("Sailor");
            if (ImGui::BeginMenu("Recurse.."))
            {
                ShowExampleMenuFile();
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }
    // if (ImGui::MenuItem("Save", "Ctrl+S")) {}
    // if (ImGui::MenuItem("Save As..")) {}

    // ImGui::Separator();
    // // IMGUI_DEMO_MARKER("Examples/Menu/Options");
    // if (ImGui::BeginMenu("Options"))
    // {
    //     static bool enabled = true;
    //     ImGui::MenuItem("Enabled", "", &enabled);
    //     ImGui::BeginChild("child", ImVec2(0, 60), true);
    //     for (int i = 0; i < 10; i++)
    //         ImGui::Text("Scrolling Text %d", i);
    //     ImGui::EndChild();
    //     static float f = 0.5f;
    //     static int n = 0;
    //     ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
    //     ImGui::InputFloat("Input", &f, 0.1f);
    //     ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
    //     ImGui::EndMenu();
    // }

    // // IMGUI_DEMO_MARKER("Examples/Menu/Colors");
    // if (ImGui::BeginMenu("Colors"))
    // {
    //     float sz = ImGui::GetTextLineHeight();
    //     for (int i = 0; i < ImGuiCol_COUNT; i++)
    //     {
    //         const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
    //         ImVec2 p = ImGui::GetCursorScreenPos();
    //         ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
    //         ImGui::Dummy(ImVec2(sz, sz));
    //         ImGui::SameLine();
    //         ImGui::MenuItem(name);
    //     }
    //     ImGui::EndMenu();
    // }

    // // Here we demonstrate appending again to the "Options" menu (which we already created above)
    // // Of course in this demo it is a little bit silly that this function calls BeginMenu("Options") twice.
    // // In a real code-base using it would make senses to use this feature from very different code locations.
    // if (ImGui::BeginMenu("Options")) // <-- Append!
    // {
    //     // IMGUI_DEMO_MARKER("Examples/Menu/Append to an existing menu");
    //     static bool b = true;
    //     ImGui::Checkbox("SomeOption", &b);
    //     ImGui::EndMenu();
    // }

    // if (ImGui::BeginMenu("Disabled", false)) // Disabled
    // {
    //     IM_ASSERT(0);
    // }
    // if (ImGui::MenuItem("Checked", NULL, true)) {}
    // if (ImGui::MenuItem("Quit", "Alt+F4")) {}
}

void ChildWnd::show(float xpos, float ypos,  float xwidth, float yheight) {
	ImGui::SetCursorPosX(xpos);
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
	static int childHovered = 0;
	static int menuOpen = 0;
	static int childClicked = 0;
	int animY = 0;
	if (childHovered || menuOpen) {
		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(150, 255, 150, 100));
		bounceTimer_.reset();
	}
	else {
		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 255, 0, 100));
		animY = bounceTimer_.getNextTableEntry();
	}
	ImGui::SetCursorPosY(ypos + animY);
	ImGui::BeginChild("ChildR", ImVec2(xwidth, yheight), true, ImGuiWindowFlags_None | ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar()) {
		menuOpen = ImGui::BeginMenu("Menu");
		if (menuOpen) {
			ShowExampleMenuFile();
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	ImGui::Text("Status: OK");
	ImGui::EndChild();
	childHovered = ImGui::IsItemHovered();
	childClicked = ImGui::IsItemClicked(ImGuiMouseButton_Left);
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();

	ImGui::End();
}
