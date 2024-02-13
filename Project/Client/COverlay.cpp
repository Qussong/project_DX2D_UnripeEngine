#include "pch_client.h"
#include "COverlay.h"

COverlay::COverlay()
	: Super("Overlay", "##Overlay")
{
    ImGuiWindowFlags flag = ImGuiWindowFlags_NoDecoration
        | ImGuiWindowFlags_NoDocking
        | ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoSavedSettings
        | ImGuiWindowFlags_NoFocusOnAppearing
        | ImGuiWindowFlags_NoNav;

    SetWindowFlag(flag);
}

COverlay::~COverlay()
{
}

void COverlay::SetWindowOption()
{
    ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
}

void COverlay::Render_Update()
{
    ImGui::Text("Simple overlay\n" "(right-click to change position)");
    ImGui::Separator();
    ImGui::Text("Delta Time: %.3f (ms/frame)", M_TIME->DeltaTime() * 1000);
    ImGui::Text("FPS: %d", M_TIME->FPS());
    ImGui::Text("Mouse Pos: (%.1f, %.1f)", M_KEY->GetMouseCurPos().x, M_KEY->GetMouseCurPos().y);
}

