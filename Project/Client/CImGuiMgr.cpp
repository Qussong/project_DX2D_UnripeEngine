#include "pch_client.h"
#include "CImGuiMgr.h"

CImGuiMgr::CImGuiMgr()
{
}

CImGuiMgr::~CImGuiMgr()
{
    // Clear the Dear ImGui
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void CImGuiMgr::Init(HWND _hMainWnd)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(_hMainWnd);
    ImGui_ImplDX11_Init(DEVICE, CONTEXT);
}

void CImGuiMgr::Progress()
{
    // Start the Dear ImGui frame
    Tick();

    // Render the Dear ImGui
    Render();
}

void CImGuiMgr::Tick()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // test
    Test();
}

void CImGuiMgr::Render()
{
    ImGuiIO& io = ImGui::GetIO();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // ImGui : Update and Render additional Platform Windows
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

void CImGuiMgr::Test()
{
    DemoWindow();
    //CustomWindow();
    MyScene();
    Overlay();
}

void CImGuiMgr::DemoWindow()
{
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);
}

void CImGuiMgr::CustomWindow()
{
    ImGuiIO& io = ImGui::GetIO();

    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();

    // 3. Show another simple window.
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }
}

void CImGuiMgr::MyScene()
{
    ImGuiIO& io = ImGui::GetIO();

    ImGui::Begin("My Scene");
    {
        //ImGui::Image();
    }
    ImGui::End();
}

void CImGuiMgr::Overlay()
{
    ImGuiIO& io = ImGui::GetIO();
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration 
                                    | ImGuiWindowFlags_NoDocking 
                                    | ImGuiWindowFlags_AlwaysAutoResize 
                                    | ImGuiWindowFlags_NoSavedSettings 
                                    | ImGuiWindowFlags_NoFocusOnAppearing 
                                    | ImGuiWindowFlags_NoNav;

    ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
    ImGui::Begin("Example: Simple overlay", &show_overlay_window, window_flags);
    {
        ImGui::Text("Simple overlay\n" "(right-click to change position)");
        ImGui::Separator();
        ImGui::Text("Delta Time: %.3f (ms/frame)", M_TIME->DeltaTime() * 1000);
        ImGui::Text("FPS: %d", M_TIME->FPS());
        ImGui::Text("Mouse Pos: (%.1f, %.1f)", M_KEY->GetMouseCurPos().x, M_KEY->GetMouseCurPos().y);
    }
    ImGui::End();
}

