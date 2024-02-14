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

    // Custom UI
    Lazy::DelMap(m_mapUI);
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

    // Create Custom UI
    Create_UI();

    // test
    CLevel* pCurLevel = M_LEVEL->GetCurrentLevel();
    CGameObject* pTarget = pCurLevel->FindObjectByName(L"PlayerObj");
    CInspector* pInspector = (CInspector*)FindUI("##Inspector");
    pInspector->SetTargetObject(pTarget);
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

    ImGuizmo::BeginFrame();

    // Custom UI Update
    for (const auto& pair : m_mapUI)
        pair.second->Tick();

    // Sample
    DemoWindow();
    //CustomWindow();
};

void CImGuiMgr::Render()
{
    ImGuiIO& io = ImGui::GetIO();

    // Custom UI Rendering
    for (const auto& pair : m_mapUI)
        pair.second->Render();

    // ImGui::Rendering
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // ImGui : Update and Render additional Platform Windows
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

void CImGuiMgr::Create_UI()
{
    CUI* pUI = nullptr;

    // Inspector
    {
        pUI = new CInspector;
        AddUI(pUI->GetID(), pUI);
    }

    // Content
    {
        pUI = new CContent;
        AddUI(pUI->GetID(), pUI);
    }

    // Outliner
    {
        pUI = new COutliner;
        AddUI(pUI->GetID(), pUI);
    }

    // Overlay
    {
        pUI = new COverlay;
        AddUI(pUI->GetID(), pUI);
    }

    // View
    {
        pUI = new CViewUI;
        AddUI(pUI->GetID(), pUI);
    }
}

CUI* CImGuiMgr::FindUI(const string& _name)
{
    map<string, CUI*>::iterator iter = m_mapUI.find(_name);

    // 해당하는 이름을 가진 UI가 없는 경우
    if (m_mapUI.end() == iter)
        return nullptr;

    // 해당하는 이름을 가진 UI가 존재하는 경우
    return iter->second;
}

void CImGuiMgr::AddUI(const string& _key, CUI* _ui)
{
    CUI* pUI = FindUI(_key);

    // 인자로 주어진 이름(key) 값을 가진 UI가 존재하지 않는 경우
    if (nullptr == pUI)
    {
        m_mapUI.insert(make_pair(_key, _ui));
    }
    // 인자로 주어진 이름(key) 값을 가진 UI가 존재하는 경우
    else
    {
        m_mapUI.insert(make_pair(_key, pUI));
    }

}

void CImGuiMgr::DemoWindow()
{
    if (show_demo_window)
    {
        ImGui::ShowDemoWindow(&show_demo_window);
    }
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