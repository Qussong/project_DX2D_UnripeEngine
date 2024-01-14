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

public:
	HWND	GetWindowHandle() { return m_hWnd; }

public:
	int		Init(HWND _hWnd, uint32 _width, uint32 _height);
	void	Progress();
	void	Tick();
	void	Render();

private:
	CMesh*					m_pRectMesh = nullptr;
	CMesh*					m_pCircleMesh = nullptr;
	CGraphicShader*			m_pShader = nullptr;
	vector<CGameObject*>	m_vecObj;

public:
	void RectMesh();
	void CircleMesh();
	void Test_tick();
	void Test_render();
	void Test_GameObject();
};
