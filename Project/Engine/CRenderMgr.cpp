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

	// ��ϵ� ī�޶�麸�� �켱������ �ڿ� ���� ��� ī�޶� �����̳��� ��������� �ø���.
	if (iCamCnt <= iPriority)
	{
		m_vecCamera.resize(iPriority);
	}

	// ������ �켱������ ī�޶� �̹� �����Ұ�� ����
	if (nullptr != m_vecCamera[_idx])
	{
		MessageBoxA(nullptr, "Already Exist Another Camera", "Priority Error", MB_OK);
		_exit(EXIT_FAILURE);
	}

	// _idx ��ġ�� _cam ��ġ��Ű��
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

	//GRAPHICS->RenderEnd();	// ImGui::Progress �ڿ� ��ġ
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
