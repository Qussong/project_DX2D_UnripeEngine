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
	// DebugObj
	m_pDebugObj = new CGameObject;
	m_pDebugObj->AddComponent(new CTransform);
	m_pDebugObj->AddComponent(new CMeshRender);

	// Light
	Vec4 arr[3] =
	{
		Vec4(1.f, 0.f, 0.f, 1.f),
		Vec4(0.f, 1.f, 0.f, 1.f),
		Vec4(0.f, 0.f, 1.f, 1.f),
	};

	m_pLight2DBuffer = new CStructuredBuffer;
	m_pLight2DBuffer->Create(sizeof(Vec4), 2, SB_TYPE::READ_ONLY, true);
	m_pLight2DBuffer->SetData(arr, 3);
	m_pLight2DBuffer->UpdateData(14);

	// test
	Vec4 arrTest[3] = {};
	m_pLight2DBuffer->GetData(arrTest, 3);
}

void CRenderMgr::Tick()
{
	GRAPHICS->RenderBegin();
	Vec4 v4Color = { 0.75f, 0.72f, 0.7f, 1.f };
	GRAPHICS->ClearRenderTarget(v4Color);

	Render();					// ī�޶� ���� �Ϲ� ��ü Render
	Render_Debug();				// ī�޶� ���� Debug ��ü Render

	//GRAPHICS->RenderEnd();	// ImGui::Progress �ڿ� ��ġ
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

		// Transform ����
		m_pDebugObj->Transform()->SetWorldMatrix(info.matWorld);
		m_pDebugObj->Transform()->UpdateData();

		// Mesh ����
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

		// Material ����
		m_pDebugObj->MeshRender()->SetMaterial(M_ASSET->FindAsset<CMaterial>(L"DebugMaterial"));
		Vec4 v4DebugColor = { info.v3Color, 1.f };
		m_pDebugObj->MeshRender()->GetMaterial()->SetScalarParam(SCALAR_PARAM::VEC4_0, v4DebugColor);

		// DEBUG_SHAPE::CROSS �� ��� Topology ����
		Ptr<CGraphicShader> shader = m_pDebugObj->MeshRender()->GetMaterial()->GetShader();
		D3D11_PRIMITIVE_TOPOLOGY prevTopology  = shader->GetTopology();
		if (DEBUG_SHAPE::CROSS == info.eShape)
			shader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINELIST);

		// Render
		m_pDebugObj->Render();

		// DEBUG_SHAPE::CROSS �� ��� Render�� �����⿡ ����Ǿ��� Topology ����
		if (DEBUG_SHAPE::CROSS == info.eShape)
			shader->SetTopology(prevTopology);

		// ���� �ð� üũ (���� �ʿ���)
		// ���� ���� 0 ������ 1������ ����� �ٷ� �����, ���� �� �����Ӹ��� �ϳ��� �߰���
		info.fLifeTime += DT;
		// ������ ���� ��� 
		if (info.fDuration <= info.fLifeTime)
			iter = m_listDebugShapeInfo.erase(iter);
		// ������ ���� ���
		else
			++iter;
	}
}
