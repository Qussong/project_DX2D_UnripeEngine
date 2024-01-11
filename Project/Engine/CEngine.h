#pragma once

class CEngine
	: public CSingleton<CEngine>
{
	SINGLETON(CEngine);

private:
	HWND		m_hWnd;

	// Resolution
	int32		 m_width;
	int32		 m_height;

public:
	HWND GetWindowHandle() { return m_hWnd; }

public:
	int Init(HWND _hWnd, uint32 _width, uint32 _height);
	void Progress();
	void Tick();
	void Render();
};

