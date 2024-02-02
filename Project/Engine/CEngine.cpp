#include "pch.h"
#include "CEngine.h"

CEngine::CEngine()
	: m_hWnd(nullptr)
	, m_v2Resolution{}

{
}

CEngine::~CEngine()
{
	size_t size = m_vecObj.size();
	for (size_t i = 0; i < size; i++)
	{
		if (nullptr != m_vecObj[i])
		{
			delete m_vecObj[i];
			m_vecObj[i] = nullptr;
		}
	}
}

void CEngine::DebugRenderCheck()
{
	if (KEY_STATE::TAP == M_KEY->GetKeyState(KEY::O))
	{
		M_RENDER->IsDebugCheck() ? M_RENDER->SetDebugCheck(false) : M_RENDER->SetDebugCheck(true);
	}
}

int CEngine::Init(HWND _hWnd, uint32 _width, uint32 _height)
{
	// member init
	m_hWnd = _hWnd;
	m_v2Resolution.x = static_cast<float>(_width);
	m_v2Resolution.y = static_cast<float>(_height);

	// Device, Context, SwapChain init
	CGraphics::GetInst()->Init(m_hWnd, m_v2Resolution.x, m_v2Resolution.y);

	// Manager init
	M_TIME->Init();
	M_PATH->Init();
	M_KEY->Init();

	M_ASSET->Init();	// Mesh, Shader, Material, Texture 积己
	M_RENDER->Init();	// 叼滚弊 按眉 积己
	M_LEVEL->Init();	// 阿辆 按眉 积己

	return S_OK;
}

void CEngine::Progress()
{
	// Manger Update
	M_TIME->Tick();		
	M_KEY->Tick();	

	// Level Update
	M_LEVEL->Tick();
	M_COLLISION->Tick();

	// Render
	M_RENDER->Tick();	

	// GC
	M_GC->Tick();

	// Task
	M_TASK->Tick();		

	// Debug
	DebugRenderCheck();
}