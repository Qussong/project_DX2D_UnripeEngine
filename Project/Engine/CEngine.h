#pragma once

class CEngine
	: public CSingleton<CEngine>
{
	SINGLETON(CEngine);

private:
	HWND				m_hWnd;

public:
	int Init(HWND _hWnd);
	void Update();
	void Render();
};

