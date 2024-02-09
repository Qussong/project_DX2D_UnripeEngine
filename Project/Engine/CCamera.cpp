#include "pch.h"
#include "CCamera.h"

CCamera::CCamera()
	: Super(COMPONENT_TYPE::CAMERA)
	, m_eProjType(PROJ_TYPE::ORTHOGRAPHIC)
	, m_fFOV(XM_PI / 2.f)	// 90��
	, m_fScale(1.f)
	, m_v2Resolution(Vec2(0.f, 0.f))
	, m_fAspectRatio(1.f)
	, m_fNear(1.f)
	, m_fFar(1000.f)
	, m_iPriority(0)
	, m_arrLayerCheck{}
{
	m_matView = XMMatrixIdentity();
	m_matProj = XMMatrixIdentity();
	m_v2Resolution = GRAPHICS->GetResolution();
	m_fAspectRatio = m_v2Resolution.x / m_v2Resolution.y;
}

CCamera::~CCamera()
{
}

void CCamera::ViewMatrix()
{
	// ī�޶� ������Ʈ�� ������ GameObject ��ü�� ���û󿡼��� ��ġ��
	Vec3 v3CamPos = GetOwner()->Transform()->GetLocalPos();

	// View ��ȯ���� "��ġ��ȯ"�� ī�޶� �̵��Ѹ�ŭ �ݴ�� ���ư���ȴ�.
	// ������ ī�޶� ��ġ ��ǥ�� -1 �� ������ �Ÿ���ŭ �̵���ȯ ���ָ� �ȴ�.
	Matrix matRevTrans = XMMatrixTranslation(-v3CamPos.x, -v3CamPos.y, -v3CamPos.z);

	// ī�޶� ������Ʈ�� ������ GameObject ��ü�� ���û󿡼��� ȸ����
	Vec3 v3RotX = GetOwner()->Transform()->GetLocalDirection(DIR_TYPE::RIGHT);
	Vec3 v3RotY = GetOwner()->Transform()->GetLocalDirection(DIR_TYPE::UP);
	Vec3 v3RotZ = GetOwner()->Transform()->GetLocalDirection(DIR_TYPE::FRONT);

	// View ��ȯ�� "ȸ����ȯ"�� ī�޶� ȭ���Ѹ�ŭ �ݴ�� ���ư���ȴ�.
	// ������ ī�޶��� ȸ����ȯ����� ������� ���ؼ� �����ָ�ȴ�.
	// ȸ����ȯ ����� ��ġ��� == �����
	//////////////////////////////////////////////////////////////////////////
	// ȸ����ȯ���� ��ġ��� == ����� ���� ������ ��
	//////////////////////////////////////////////////////////////////////////
	Matrix matRevRot = XMMatrixIdentity();
	matRevRot._11 = v3RotX.x; matRevRot._12 = v3RotY.x; matRevRot._13 = v3RotZ.x;
	matRevRot._21 = v3RotX.y; matRevRot._22 = v3RotY.y; matRevRot._23 = v3RotZ.y;
	matRevRot._31 = v3RotX.z; matRevRot._32 = v3RotY.z; matRevRot._33 = v3RotZ.z;

	// View ��� �ϼ� (��ġ��ȯ, ȸ����ȯ ����)
	// ������� �����ִ°��̱⿡ ������ ������ �ݴ� ������ �������ش�.
	// ������ : SRT -> ������ : TRS
	m_matView = matRevTrans * matRevRot;
}

void CCamera::ProjectionMatrix()
{
	// �������� (Orthographic)
	if (PROJ_TYPE::ORTHOGRAPHIC == m_eProjType)
	{
		float fViewWidth = m_v2Resolution.x * m_fScale;
		float fViewHeight = m_v2Resolution.y * m_fScale;
		m_matProj = XMMatrixOrthographicLH(fViewWidth, fViewHeight, m_fNear, m_fFar);
	}
	// �������� (Perspective)
	if (PROJ_TYPE::PERSPECTIVE == m_eProjType)
	{
		m_matProj = XMMatrixPerspectiveFovLH(m_fFOV, m_fAspectRatio, m_fNear, m_fFar);
	}
}

void CCamera::SetPriority(int32 _priority)
{
	// �켱���� ����
	m_iPriority = _priority;
	// Render Manger�� ī�޶� ���
	M_RENDER->RegisterCamera(this, _priority);
}

void CCamera::LayerCheck(LAYER_TYPE _layer, bool _bCheck)
{
	m_arrLayerCheck[(int32)_layer] = _bCheck;
}

void CCamera::LayerCheck(const wstring& _layerName, bool _bCheck)
{
	CLevel* pCurLevel = M_LEVEL->GetCurrentLevel();
	CLayer* pLayer = pCurLevel->GetLayer(_layerName);
	
	if (nullptr == pLayer)
		return;

	LAYER_TYPE layerType = pLayer->GetLayerType();
	LayerCheck(layerType, _bCheck);
}

void CCamera::LayerCheckAll(bool _bCheck)
{
	// ���̾� �޾Ƽ� ���� _bCheck �� ����
	for (size_t i = 0; i < LAYER_MAX; ++i)
	{
		LayerCheck((LAYER_TYPE)i, _bCheck);
	}
}

void CCamera::FinalTick()
{
	ViewMatrix();
	ProjectionMatrix();
}

void CCamera::SortObject()
{
	CLevel* pCurLevel = M_LEVEL->GetCurrentLevel();
	for (size_t i = 0; i < LAYER_MAX; i++)
	{
		// ī�޶� �ν��ϵ��� ������ Layer�� �ƴϸ� ����
		if (false == m_arrLayerCheck[i])
			continue;

		// ���̾� 
		CLayer* pLayer = pCurLevel->GetLayer((LAYER_TYPE)i);
		// ���̾ ���� ��ü
		const vector<CGameObject*>& vecObjects = pLayer->GetLayerObjects();
		// ��ü ����
		size_t objCnt = vecObjects.size();
		for (size_t k = 0; k < objCnt; ++k)
		{
			CGameObject* pTarget = vecObjects[k];
			// Mesh, Material, Shader ���� Ȯ�� -> �ϳ��� ����ִ� ��� Render ����
			if (!(pTarget->RenderComp()
				  && pTarget->RenderComp()->GetMesh().Get()
				  && pTarget->RenderComp()->GetMaterial().Get()
				  && pTarget->RenderComp()->GetMaterial()->GetShader().Get()))
			{
				continue;
			}

			// Domain �������� �����Ͽ� �����̳ʿ� �־��ֱ�
			SHADER_DOMAIN eDomain = pTarget->RenderComp()->GetMaterial()->GetShader()->GetDomain();
			switch (eDomain)
			{
			case SHADER_DOMAIN::DOMAIN_OPAQUE:
				m_DomainObj[(uint32)SHADER_DOMAIN::DOMAIN_OPAQUE].push_back(pTarget);
				break;
			case SHADER_DOMAIN::DOMAIN_MASK:
				m_DomainObj[(uint32)SHADER_DOMAIN::DOMAIN_MASK].push_back(pTarget);
				break;
			case SHADER_DOMAIN::DOMAIN_TRANSPARENT:
				m_DomainObj[(uint32)SHADER_DOMAIN::DOMAIN_TRANSPARENT].push_back(pTarget);
				break;
			case SHADER_DOMAIN::DOMAIN_POSTPROCESS:
				m_DomainObj[(uint32)SHADER_DOMAIN::DOMAIN_POSTPROCESS].push_back(pTarget);
				break;
			case SHADER_DOMAIN::DOMAIN_DEBUG:
				// nothing
				break;
			}
		}
	}
}

void CCamera::Render()
{
	// Transform ������� ���� ����ü �� ����
	g_tTransformConst.matView = m_matView;
	g_tTransformConst.matProj = m_matProj;

	Render(m_DomainObj[(int32)SHADER_DOMAIN::DOMAIN_OPAQUE]);
	Render(m_DomainObj[(int32)SHADER_DOMAIN::DOMAIN_MASK]);
	Render(m_DomainObj[(int32)SHADER_DOMAIN::DOMAIN_TRANSPARENT]);
	Render_PostProcess();
}

void CCamera::Render(vector<CGameObject*>& _vecObj)
{
	size_t iObjCnt = _vecObj.size();
	for (size_t i = 0; i < iObjCnt; ++i)
	{
		_vecObj[i]->Render();
	}
	_vecObj.clear();
}

void CCamera::Render_PostProcess()
{
	vector<CGameObject*> &vecPPObj = m_DomainObj[(uint32)SHADER_DOMAIN::DOMAIN_POSTPROCESS];
	for (size_t i = 0; i < vecPPObj.size(); ++i)
	{
		// ���� ������ �̹����� ��ó�� Ÿ�ٿ� ����
		CRenderMgr::GetInst()->CopyRenderTargetToPostProcessTarget();

		// ������� ��ó�� �ؽ��ĸ� t13 �������Ϳ� ���ε�
		Ptr<CTexture> pPostProcessTex = CRenderMgr::GetInst()->GetPostProcessTex();
		pPostProcessTex->UpdateData(13);

		// ��ó�� ������Ʈ ������
		vecPPObj[i]->Render();
	}

	vecPPObj.clear();
}