#pragma once

class CUI;

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
	map<string, CUI*> m_mapUI;

public:
	void	Init(HWND _hMainWnd);
	void	Progress();

private:
	void	Tick();
	void	Render();
	void	Create_UI();

public:
	CUI*	FindUI(const string& _id);
	void	AddUI(const string& _key, CUI* _ui);	// key = id

private:
	void	CustomWindow(bool* isOpen);
	void	DockSpace(bool* isOpen);
};

