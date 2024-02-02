#include "pch.h"
#include "CRenderMgr.h"

CRenderMgr::CRenderMgr()
	: m_pDebugObj(nullptr)
	, m_bDebugCheck(false)
{
}

CRenderMgr::~CRenderMgr()
{
	if (nullptr != m_pDebugObj)
		delete m_pDebugObj;
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
	m_pDebugObj = new CGameObject;
	m_pDebugObj->AddComponent(new CTransform);
	m_pDebugObj->AddComponent(new CMeshRender);
}

void CRenderMgr::Tick()
{
	GRAPHICS->RenderBegin();
	Vec4 v4Color = { 0.75f, 0.72f, 0.7f, 1.f };
	GRAPHICS->ClearRenderTarget(v4Color);

	Render();					// 카메라 기준 일반 객체 Render
	Render_Debug();				// 카메라 기준 Debug 객체 Render

	//GRAPHICS->RenderEnd();	// ImGui::Progress 뒤에 위치
}

void CRenderMgr::Render()
{
	size_t camCnt = m_vecCamera.size();
	for (size_t i = 0; i < camCnt; ++i)
	{
		m_vecCamera[i]->Render();
	}
}

void CRenderMgr::Render_Debug()
{
	g_tTransformConst.matView = m_vecCamera[0]->GetViewMatrix();
	g_tTransformConst.matProj = m_vecCamera[0]->GetProjMatrix();

	list<tDebugShapeInfo>::iterator iter = m_listDebugShapeInfo.begin();
	for (; iter != m_listDebugShapeInfo.end(); )
	{
		tDebugShapeInfo info = *iter;

		// Transform 설정
		m_pDebugObj->Transform()->SetWorldMatrix(info.matWorld);
		m_pDebugObj->Transform()->UpdateData();

		// Mesh 설정
		switch (info.eShape)
		{
		case DEBUG_SHAPE::RECT:
			m_pDebugObj->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"RectMesh_Debug"));
			break;
		case DEBUG_SHAPE::CIRCLE:
			m_pDebugObj->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"CircleMesh_Debug"));
			break;
		case DEBUG_SHAPE::CROSS:
			m_pDebugObj->MeshRender()->SetMesh(M_ASSET->FindAsset<CMesh>(L"CrossMesh_Debug"));
			break;
		default:
			break;
		}

		// Material 설정
		m_pDebugObj->MeshRender()->SetMaterial(M_ASSET->FindAsset<CMaterial>(L"DebugMaterial"));
		Vec4 v4DebugColor = { info.v3Color, 1.f };
		m_pDebugObj->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::VEC4_0, v4DebugColor);

		// DEBUG_SHAPE::CROSS 인 경우 Topology 변경
		Ptr<CGraphicShader> shader = m_pDebugObj->MeshRender()->GetMaterial()->GetShader();
		D3D11_PRIMITIVE_TOPOLOGY prevTopology  = shader->GetTopology();
		if (DEBUG_SHAPE::CROSS == info.eShape)
			shader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINELIST);

		// Render
		m_pDebugObj->Render();

		// DEBUG_SHAPE::CROSS 인 경우 Render가 끝났기에 변경되었던 Topology 복구
		if (DEBUG_SHAPE::CROSS == info.eShape)
			shader->SetTopology(prevTopology);

		// 유지 시간 체크 (보완 필요함)
		// 현재 수명 0 때문에 1프레임 출력후 바로 사라짐, 또한 매 프레임마다 하나씩 추가됨
		info.fLifeTime += DT;
		// 수명이 지난 경우 
		if (info.fDuration <= info.fLifeTime)
			iter = m_listDebugShapeInfo.erase(iter);
		// 수명이 남은 경우
		else
			++iter;
	}
}
