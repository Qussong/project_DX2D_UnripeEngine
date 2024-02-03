#include "pch.h"
#include "CCollisionMgr.h"

CCollisionMgr::CCollisionMgr()
	: m_arr2LayerCollisionConfig{}
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::CollisionBtwLayer(UINT _left, UINT _right)
{
	CLevel* pCurLevel = M_LEVEL->GetCurrentLevel();

	LAYER_TYPE leftType = (LAYER_TYPE)_left;
	LAYER_TYPE rightType = (LAYER_TYPE)_right;
	CLayer* pLeftLayer = pCurLevel->GetLayer(leftType);
	CLayer* pRightLayer = pCurLevel->GetLayer(rightType);

	const vector<CGameObject*>& vecLeft = pLeftLayer->GetLayerObjects();
	const vector<CGameObject*>& vecRight = pRightLayer->GetLayerObjects();
	size_t leftObjCnt = vecLeft.size();
	size_t rightObjCnt = vecRight.size();
	for (size_t idxL = 0; idxL < leftObjCnt; ++idxL)
	{
		// �浹ü�� ���� ���
		if (nullptr == vecLeft[idxL]->Collider2D())
			continue;

		// ���߰˻� ����
		size_t idxR = 0;
		// _left, _right ���� ���̾��ΰ��
		if (_left == _right)
			idxR = idxL + 1;
		for (; idxR < rightObjCnt; ++idxR)
		{
			// �浹ü�� �����ϰ� ���� ���� ���
			if (nullptr == vecRight[idxR]->Collider2D())
				continue;

			// �� �浹ü�� ���̵� ����
			CollisionID tID = {};
			tID.iLeftID = vecLeft[idxL]->Collider2D()->GetID();
			tID.iRightID = vecRight[idxR]->Collider2D()->GetID();

			// ���� ������ �浹���� Ȯ��
			map<UINT_PTR, bool>::iterator iter = m_mapCollsionRecord.find(tID.iID);
			// �浹������ ���� ���
			if (iter == m_mapCollsionRecord.end())
			{
				m_mapCollsionRecord.insert(make_pair(tID.iID, false));
				iter = m_mapCollsionRecord.find(tID.iID);
			}

			// Dead ���� Ȯ��
			bool bDead = vecLeft[idxL]->IsDead() || vecRight[idxR]->IsDead();	// �� �� �ϳ��� Dead �̸� true

			// �ش� �����̿� �浹���ִ� ���
			if (CollisionBtwCollider(vecLeft[idxL]->Collider2D(), vecRight[idxR]->Collider2D()))
			{
				// ���� �����ӿ� �浹�� ������ �ִ� ���
				if (iter->second)
				{
					// �� �浹ü�� �� ��ü�� Dead ������ ���
					if (bDead)
					{
						// �浹 ����
						vecLeft[idxL]->Collider2D()->EndOverlap(vecRight[idxR]->Collider2D());
						vecRight[idxR]->Collider2D()->EndOverlap(vecLeft[idxL]->Collider2D());
					}
					// �� �浹ü ��� !Dead ������ ���
					else
					{
						// �浹 ����
						vecLeft[idxL]->Collider2D()->Overlap(vecRight[idxR]->Collider2D());
						vecRight[idxR]->Collider2D()->Overlap(vecLeft[idxL]->Collider2D());
					}
				}
				// ���� �����ӿ� �浹�� ������ ���� ���
				else
				{
					// �� �浹ü�� �� ��ü�� Dead ������ ��� -> �浹 ��ȿ
					// �� �浹ü ��� !Dead ������ ���
					if (!bDead)
					{
						// �浹 ����
						vecLeft[idxL]->Collider2D()->BeginOverlap(vecRight[idxR]->Collider2D());
						vecRight[idxR]->Collider2D()->BeginOverlap(vecLeft[idxL]->Collider2D());
						iter->second = true;
					}
				}
			}
			// �ش� �����ӿ� �浹������ ���� ���
			else
			{
				// ���� �����ӿ� �浹�� ������ �ִ� ���
				if (iter->second)
				{
					// �浹 ����
					vecLeft[idxL]->Collider2D()->EndOverlap(vecRight[idxR]->Collider2D());
					vecRight[idxR]->Collider2D()->EndOverlap(vecLeft[idxL]->Collider2D());
					iter->second = false;
				}
			}
		}
	}
}

bool CCollisionMgr::CollisionBtwCollider(CCollider2D* _left, CCollider2D* _right)
{
	bool result = true;

	const Matrix& matLeft = _left->GetColliderWorldMat();
	const Matrix& matRight = _right->GetColliderWorldMat();

	COLLIDER2D_TYPE leftType = _left->GetColliderType();
	COLLIDER2D_TYPE rightType = _right->GetColliderType();

	// �浹�׽�Ʈ

	// RECT-RECT
	if (leftType == COLLIDER2D_TYPE::RECT
		&& rightType == COLLIDER2D_TYPE::RECT)
	{
		result = ObbRectRect(matLeft, matRight);
	}

	// CIRCLE-CIRCLE
	if (leftType == COLLIDER2D_TYPE::CIRCLE
		&& rightType == COLLIDER2D_TYPE::CIRCLE)
	{
		result = ObbCircleCircle(matLeft, matRight);
	}

	// RECT-CIRCLE
	if (leftType == COLLIDER2D_TYPE::RECT
		&& rightType == COLLIDER2D_TYPE::CIRCLE)
	{
		result = ObbRectCircle(matLeft, matRight);
	}

	// CIRCLE-RECT
	if (leftType == COLLIDER2D_TYPE::CIRCLE
		&& rightType == COLLIDER2D_TYPE::RECT)
	{
		result = ObbRectCircle(matRight, matLeft);
	}
	
	return result;
}

bool CCollisionMgr::ObbRectRect(const Matrix& _matRect1, const Matrix& _matRect2)
{
	// Rect Local
	// 0 -- 1
	// |    |
	// 3 -- 2
	static Vec3 arrRect[4] = { Vec3(-0.5f, 0.5f, 0.f)
								, Vec3(0.5f, 0.5f, 0.f)
								, Vec3(0.5f, -0.5f, 0.f)
								, Vec3(-0.5f, -0.5f, 0.f) };
	Vec3 arrProj[4] = {};
	// 0 -�� 1
	// ��    |
	// 3 -- 2
	arrProj[0] = XMVector3TransformCoord(arrRect[1], _matRect1) - XMVector3TransformCoord(arrRect[0], _matRect1);
	arrProj[1] = XMVector3TransformCoord(arrRect[3], _matRect1) - XMVector3TransformCoord(arrRect[0], _matRect1);

	arrProj[2] = XMVector3TransformCoord(arrRect[1], _matRect2) - XMVector3TransformCoord(arrRect[0], _matRect2);
	arrProj[3] = XMVector3TransformCoord(arrRect[3], _matRect2) - XMVector3TransformCoord(arrRect[0], _matRect2);

	Vec3 vCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _matRect2) - XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _matRect1);

	// i ��° ���������� 4���� ǥ�麤�͸� ������Ų��.
	for (int i = 0; i < 4; ++i)
	{
		// i ��° ǥ����͸� ���������� ��´�
		Vec3 vProj = arrProj[i];

		// �������ͷ� ���� ������ ��� ������ ���̸� ���� �� �ְ� �Ѵ�.
		vProj.Normalize();

		// ������ ���̸� ������ų ����
		float ProjAcc = 0.f;

		// �ݺ��� ���鼭 4���� ǥ�麤�͸� ������ ���������� �������Ѽ� ���̸� �����޴´�.
		for (int j = 0; j < 4; ++j)
		{
			ProjAcc += abs(vProj.Dot(arrProj[j]));
		}

		// ������ ������ ���ݾ� ��ģ ���̰� �ʿ��ϱ� ������ ��ü ��ģ���̸� 2 �� ������
		ProjAcc /= 2.f;

		// �� �浹ü�� �߽��� ���� ���͵� ������Ų��.
		float fCenterDist = abs(vProj.Dot(vCenter));

		// �߽��� ���� ���͸� ������Ų ���̰�, ǥ���� ������Ų ������ ���ݺ��� ũ�ٸ� 
		// ���� �и���ų �� �ִ�.
		if (ProjAcc < fCenterDist)
		{
			return false;	// �� �浹 ����
		}
	}

	return true;	// �浹 ����
}

bool CCollisionMgr::ObbCircleCircle(const Matrix& _matCircle1, const Matrix& _matCircle2)
{
	Matrix		left = _matCircle1;
	Matrix		right = _matCircle2;

	Vec3		scaleL;
	Quaternion	rotL;
	Vec3		posL;

	Vec3		scaleR;
	Quaternion	rotR;
	Vec3		posR;

	left.Decompose(scaleL, rotL, posL);
	right.Decompose(scaleR, rotR, posR);

	float fCenter = (float)sqrt(pow((posR.x - posL.x), 2) + pow((posR.y - posL.y), 2));
	float fLeftRadius = 0.5f * scaleL.x;
	float fRightRadius = 0.5f * scaleR.x;

	if (fCenter > fLeftRadius + fRightRadius)
	{
		return false;	// �� �浹 ����
	}

	return true;	// �浹 ����
}

bool CCollisionMgr::ObbRectCircle(const Matrix& _matRect, const Matrix& _matCircle)
{
	// Circle World
	Matrix		mCircle = _matCircle;
	Vec3		scale;
	Quaternion	rot;
	Vec3		pos;
	mCircle.Decompose(scale, rot, pos);

	// Rect Local
	static Vec3 arrRect[4] = { Vec3(-0.5f, 0.5f, 0.f)
								, Vec3(0.5f, 0.5f, 0.f)
								, Vec3(0.5f, -0.5f, 0.f)
								, Vec3(-0.5f, -0.5f, 0.f) };

	// ��������
	Vec3 arrProj[3] = {};
	arrProj[0] = XMVector3TransformCoord(arrRect[1], _matRect) - XMVector3TransformCoord(arrRect[0], _matRect);
	arrProj[1] = XMVector3TransformCoord(arrRect[3], _matRect) - XMVector3TransformCoord(arrRect[0], _matRect);

	Vec3 vCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _matCircle) - XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _matRect);
	arrProj[2] = vCenter;

	// i ��° ���������� 2���� ǥ�麤�͸� ������Ų��.
	for (int i = 0; i < 3; ++i)
	{
		// i ��° ǥ����͸� ���������� ��´�
		Vec3 vProj = arrProj[i];

		// �������ͷ� ���� ������ ��� ������ ���̸� ���� �� �ְ� �Ѵ�.
		vProj.Normalize();

		// ������ ���̸� ������ų ����
		float ProjAcc = 0.f;

		// ���� ������ ������ ���̿� ����
		ProjAcc += (1.f * scale.x);

		// �ݺ��� ���鼭 Rect�� 2���� ǥ�麤�͸� ������ ���������� �������Ѽ� ���̸� �����޴´�.
		for (int j = 0; j < 2; ++j)
		{
			ProjAcc += abs(vProj.Dot(arrProj[j]));
		}

		// ������ ������ ���ݾ� ��ģ ���̰� �ʿ��ϱ� ������ ��ü ��ģ���̸� 2 �� ������
		ProjAcc /= 2.f;

		// �� �浹ü�� �߽��� ���� ���͵� ������Ų��.
		float fCenterDist = abs(vProj.Dot(vCenter));

		// �߽��� ���� ���͸� ������Ų ���̰�, ǥ���� ������Ų ������ ���ݺ��� ũ�ٸ� 
		// ���� �и���ų �� �ִ�.
		if (ProjAcc < fCenterDist)
		{
			return false; // �� �浹 ����
		}
	}

	return true;	// �浹 ����
}

void CCollisionMgr::LayerCheck(LAYER_TYPE _left, LAYER_TYPE _right)
{
	int32 iLeftLayer = (int32)_left;
	int32 iRightLayer = (int32)_right;

	if (iLeftLayer > iRightLayer)
		m_arr2LayerCollisionConfig[iRightLayer][iLeftLayer] = true;
	else
		m_arr2LayerCollisionConfig[iLeftLayer][iRightLayer] = true;
}

void CCollisionMgr::LayerCheck(const wstring& _leftLayerName, const wstring& _rightLayerName)
{
	CLevel* pCurLevel = M_LEVEL->GetCurrentLevel();
	CLayer* pLeftLayer = pCurLevel->GetLayer(_leftLayerName);
	CLayer* pRightLayer = pCurLevel->GetLayer(_rightLayerName);

	// right/left layer �� nullptr �� ���
	if (nullptr == pLeftLayer || nullptr == pRightLayer)
	{
		MessageBoxA(nullptr, "Invalid Layer Name", "CCollisionMgr Error", MB_OK);
		_exit(EXIT_FAILURE);
	}

	LayerCheck(pLeftLayer->GetLayerType(), pRightLayer->GetLayerType());
}

void CCollisionMgr::Clear()
{
	for (size_t left = 0; left < LAYER_MAX; ++left)
	{
		for (size_t right = left; right < LAYER_MAX; ++right)
			m_arr2LayerCollisionConfig[left][right] = false;
	}
}

void CCollisionMgr::Tick()
{
	for (size_t left = 0; left < LAYER_MAX; ++left)
	{
		for (size_t right = left; right < LAYER_MAX; ++right)
		{
			// left, right ���̾��� �浹 ������ false�� ���
			if (false == m_arr2LayerCollisionConfig[left][right])
				continue;

			// left, right ���̾��� �浹 ������ true�� ���
			CollisionBtwLayer((UINT)left, (UINT)right);
		}
	}
}
