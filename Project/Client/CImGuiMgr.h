#pragma once

class CImGuiMgr
	: public CSingleton<CImGuiMgr>
{
	SINGLETON(CImGuiMgr);

private:
	bool show_demo_window = true;
	bool show_another_window = false;
	bool show_docking_window = true;
	bool show_overlay_window = true;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

private:
	void Tick();
	void Render();
	void Test();

private:
	// test windowes
	void DemoWindow();
	void CustomWindow();
	void MyScene();
	void Overlay();

public:
	void Init(HWND _hMainWnd);
	void Progress();
};

