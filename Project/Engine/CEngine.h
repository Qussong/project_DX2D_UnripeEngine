#pragma once

class CMesh;
class CGraphicShader;
class CConstantBuffer;
class CGameObject;

class CEngine
	: public CSingleton<CEngine>
{
	SINGLETON(CEngine);

private:
	HWND		m_hWnd;

	// Resolution
	int32		 m_iWidth;
	int32		 m_iHeight;

private:
	vector<CGameObject*>	m_vecObj;

public:
	HWND	GetWindowHandle() { return m_hWnd; }

public:
	int		Init(HWND _hWnd, uint32 _width, uint32 _height);
	void	Progress();
	void	Tick();
	void	Render();
};
