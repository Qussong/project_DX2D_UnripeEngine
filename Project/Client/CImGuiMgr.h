#pragma once

class CImGuiMgr
	: public CSingleton<CImGuiMgr>
{
	SINGLETON(CImGuiMgr);

private:
	void Tick();
	void Render();

	void Test();

public:
	void Init(HWND _hMainWnd);
	void Progress();
};

