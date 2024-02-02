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
	Vec2		m_v2Resolution;

private:
	vector<CGameObject*>	m_vecObj;

private:
	void	DebugRenderCheck();	// Debug °´Ã¼ Render ½ºÀ§Ä¡(Key : O)

public:
	HWND	GetWindowHandle() { return m_hWnd; }

public:
	int		Init(HWND _hWnd, uint32 _width, uint32 _height);
	void	Progress();
};
