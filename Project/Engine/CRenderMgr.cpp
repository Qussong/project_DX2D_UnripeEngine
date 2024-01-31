#include "pch.h"
#include "CRenderMgr.h"

CRenderMgr::CRenderMgr()
{
}

CRenderMgr::~CRenderMgr()
{
}

void CRenderMgr::RegisterCamera(CCamera* _cam, int32 _idx)
{
	int32 iCamCnt = m_vecCamera.size();
	int32 iPriority = _idx + 1;

	// 등록된 카메라들보다 우선순위가 뒤에 있을 경우 카메라 컨테이너의 수용공간을 늘린다.
	if (iCamCnt <= iPriority)
	{
		m_vecCamera.resize(iPriority);
	}

	// 동일한 우선순위의 카메라가 이미 존재할경우 종료
	if (nullptr != m_vecCamera[_idx])
	{
		MessageBoxA(nullptr, "Already Exist Another Camera", "Priority Error", MB_OK);
		_exit(EXIT_FAILURE);
	}

	// _idx 위치에 _cam 위치시키기
	m_vecCamera[_idx] = _cam;
}

void CRenderMgr::Init()
{
}

void CRenderMgr::Tick()
{
	Vec4 v4Color = { 0.75f, 0.72f, 0.7f, 1.f };
	GRAPHICS->ClearRenderTarget(v4Color);

	Render();
	Render_Debug();

	//GRAPHICS->RenderEnd();	// ImGui::Progress 뒤에 위치
}

void CRenderMgr::Render()
{
	size_t camCnt = m_vecCamera.size();
	for (size_t i = 0; i < camCnt; ++i)
	{
		//m_vecCamera[i].Render();
	}
}

void CRenderMgr::Render_Debug()
{
}
