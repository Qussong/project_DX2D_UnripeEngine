#include "pch.h"
#include "CTransform.h"

CTransform::CTransform()
	: Super(COMPONENT_TYPE::TRANSFORM)
	, m_v3LocalPostion(Vec3(0.f, 0.f, 0.f))
	, m_v3LocalScale(Vec3(1.0f, 1.0f, 1.0f))
	, m_v3LocalRotation(Vec3(0.f, 0.f, 0.f))
	, m_arrLocalDir{}
	, m_matWorld {}
	, m_isAffectScale(false)
{
	SetName(L"Transform");
}

CTransform::~CTransform()
{
}

void CTransform::FinalTick()
{
	// S,R,T Ÿ�� ��ȯ (Vec3 -> Matrix)
	Matrix matScale = XMMatrixScaling(m_v3LocalScale.x, m_v3LocalScale.y, m_v3LocalScale.z);
	Matrix matRotX = XMMatrixRotationX(m_v3LocalRotation.x);
	Matrix matRotY = XMMatrixRotationY(m_v3LocalRotation.y);
	Matrix matRotZ = XMMatrixRotationZ(m_v3LocalRotation.z);
	Matrix matTrans = XMMatrixTranslation(m_v3LocalPostion.x, m_v3LocalPostion.y, m_v3LocalPostion.z);

	// World ���
	m_matWorld = XMMatrixIdentity();
	m_matWorld = m_matWorld * matScale * (matRotX * matRotY * matRotZ) * matTrans;

	// ��������
	Vec3 arrDefaultDir[(UINT)DIR_TYPE::END] = {};
	arrDefaultDir[(UINT)DIR_TYPE::RIGHT]	= Vec3(1.f, 0.f, 0.f);
	arrDefaultDir[(UINT)DIR_TYPE::UP]		= Vec3(0.f, 1.f, 0.f);
	arrDefaultDir[(UINT)DIR_TYPE::FRONT]	= Vec3(0.f, 0.f, 1.f);

	// �� �࿡ ���� ���� ���Ϳ� ���� ����� ���Ѵ�.
	// ��� ���� Normalize �����ν� ���� �ٶ󺸰� �ִ� ���� ���͸� ���Ѵ�.
	for (size_t i = 0; i < (UINT)DIR_TYPE::END; ++i)
	{
		m_arrLocalDir[i] = XMVector3TransformNormal(arrDefaultDir[i], m_matWorld);
		m_arrLocalDir[i].Normalize();

		// �θ�ü�� ���� ��� LocalDir == WorldDir
		m_arrWorldDir[i] = m_arrLocalDir[i];
	}

	CGameObject* pParent = GetOwner()->GetParent();
	// �θ� ��ü�� �����ϴ� ���
	if (nullptr != pParent)
	{
		// �θ� ��ü�� TransformComp
		CTransform* pParentTransComp = pParent->Transform();
		// �θ� ��ü�� World ��ȯ ���(SRT)
		const Matrix& matParentSRT = pParentTransComp->GetWorldMatrix();

		// WorldMatrix
		// �θ� ��ü�κ��� Scale ������ �������
		if (m_isAffectScale)
		{
			m_matWorld *= matParentSRT;
		}
		// �θ� ��ü�κ��� Scale ������ ���� �������
		else
		{
			Vec3 v3ParentScale = pParentTransComp->GetLocalScale();
			Vec3 v3ParentScaleInv = Vec3(1.f / v3ParentScale.x, 1.f / v3ParentScale.y, 1.f / v3ParentScale.z);
			Matrix matParnetScaleInv = XMMatrixScaling(v3ParentScaleInv.x, v3ParentScaleInv.y, v3ParentScaleInv.z);

			Matrix matParentRT = matParnetScaleInv * matParentSRT;
			m_matWorld *= matParentRT;
		}

		// Direction
		for (size_t i = 0; i < (UINT)DIR_TYPE::END; ++i)
		{
			m_arrWorldDir[i] = XMVector3TransformNormal(arrDefaultDir[i], m_matWorld);
			m_arrWorldDir[i].Normalize();
		}
	}
}

void CTransform::UpdateData()
{
	g_tTransform.matWorld = m_matWorld;

	// 0�� Register �� ���ε�
	CConstantBuffer* pCB = GRAPHICS->GetCB(CB_TYPE::TRANSFORM);
	pCB->SetData(&g_tTransform);
	pCB->UpdateData();
}

Vec3 CTransform::WorldSRT(SRT_TYPE _type)
{
	Vec3 result = { 0.f, 0.f, 0.f };

	Vec3 v3WorldScale = {};
	Vec3 v3WorldRot = {};
	Vec3 v3WorldPos = {};
	Quaternion quatRot = {};
	m_matWorld.Decompose(v3WorldScale, quatRot, v3WorldPos);
	v3WorldRot = ToEulerAngles(quatRot);

	switch (_type)
	{
	case SRT_TYPE::SCALE:
		result = v3WorldScale;
		break;
	case SRT_TYPE::ROTATE:
		result = v3WorldRot;
		break;
	case SRT_TYPE::POS:
		result = v3WorldPos;
		break;
	default:
		// error
		break;
	}

	return result;
}

Vec3 CTransform::GetWorldScale()
{
	return WorldSRT(SRT_TYPE::SCALE);
}

Vec3 CTransform::GetWorldRotation()
{
	return WorldSRT(SRT_TYPE::ROTATE);
}

Vec3 CTransform::GetWorldPos()
{
	return WorldSRT(SRT_TYPE::POS);
}

Vec3 CTransform::ToEulerAngles(Quaternion q)
{
	Vec3 angles;

	// roll (x-axis rotation)
	double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	angles.x = std::atan2((float)sinr_cosp, (float)cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = std::sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
	double cosp = std::sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
	angles.y = 2 * std::atan2((float)sinp, (float)cosp) - 3.14159f / 2;

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	angles.z = std::atan2((float)siny_cosp, (float)cosy_cosp);

	return angles;
}
