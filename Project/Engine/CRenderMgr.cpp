#include "pch.h"
#include "CRenderMgr.h"

CRenderMgr::CRenderMgr()
	: m_pDebugObj(nullptr)
	, m_bDebugCheck(false)
	, m_pLight2DBuffer(nullptr)
{
}

CRenderMgr::~CRenderMgr()
{
	if (nullptr != m_pDebugObj)
		delete m_pDebugObj;

	if (nullptr != m_pLight2DBuffer)
		delete m_pLight2DBuffer;
}

void CRenderMgr::RegisterCamera(CCamera* _cam, int32 _idx)
{
	int32 iCamCnt = (int32)m_vecCamera.size();
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

void CRenderMgr::CopyRenderTargetToPostProcessTarget()
{
	Ptr<CTexture> pRTTex = M_ASSET->FindAsset<CTexture>(L"RenderTargetTex");
	CONTEXT->CopyResource(m_PostProcessTex->GetTex2D().Get(), pRTTex->GetTex2D().Get());
}

void CRenderMgr::CopyRenderTargetToViewUITarget()
{
	Ptr<CTexture> pRTTex = M_ASSET->FindAsset<CTexture>(L"RenderTargetTex");
	CONTEXT->CopyResource(m_ViewUITex->GetTex2D().Get(), pRTTex->GetTex2D().Get());
}

void CRenderMgr::UpdateData()
{
	// 전역 데이터 업데이트
	{
		g_tGlobalConst.iLight2DCnt = (int32)m_vecLight2D.size();
		static CConstantBuffer* pCB = GRAPHICS->GetCB(CB_TYPE::GLOBAL);
		pCB->SetData(&g_tGlobalConst);
		pCB->UpdateData();
	}

	// 2D 광원 정보(tLightInfo) 업데이트
	{
		// 갱신된 광원에 대한 정보를 컨테이너에 추가
		static vector<tLight2D> vecLight2DInfo;
		for (size_t i = 0; i < m_vecLight2D.size(); ++i)
		{
			const tLight2D& info = m_vecLight2D[i]->GetLightInfo();
			vecLight2DInfo.push_back(info);
		}

		if (!vecLight2DInfo.empty())
		{
			// 컨테이너에 들어욌는 광원 데이터들을 구조화 버퍼에 복사
			m_pLight2DBuffer->SetData(vecLight2DInfo.data(), (UINT)vecLight2DInfo.size());
		}
		// 구조화 버퍼를 파이프라인에 세팅
		m_pLight2DBuffer->UpdateData(LIGHT_2D);
		// 데이터를 다 넘겨줬기에 비워준다.
		vecLight2DInfo.clear();
	}
}

void CRenderMgr::Tick()
{
	GRAPHICS->RenderBegin();
	Vec4 v4ClearColor = { 0.3f, 0.3f, 0.3f, 1.f };
	GRAPHICS->ClearRenderTarget(v4ClearColor);

	UpdateData();		// 리소스 바인딩

	Render();			// 카메라 기준 일반 객체 Render
	Render_Debug();		// 카메라 기준 Debug 객체 Render

	Clear();			// 리소스 클리어

	//GRAPHICS->RenderEnd();	// 렌더링 결과 출력 -> ImGui::Progress 뒤에 위치
}

void CRenderMgr::Render()
{
	size_t camCnt = m_vecCamera.size();
	for (size_t i = 0; i < camCnt; ++i)
	{
		m_vecCamera[i]->SortObject();
		m_vecCamera[i]->Render();
	}
}

void CRenderMgr::Render_Debug()
{
	// Main 카메라의 View, Projection 변환 행렬을 가져와, Transform 상수버퍼 대응 구조체 값 세팅
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
		m_pDebugObj->MeshRender()->SetMaterial(M_ASSET->FindAsset<CMaterial>(L"DebugMtrl"));
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

	// 최종 렌더링 이미지를 ViewUI 타겟에 복사
	CopyRenderTargetToViewUITarget();
}

void CRenderMgr::Clear()
{
	m_vecLight2D.clear();
}
