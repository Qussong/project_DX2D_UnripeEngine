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
		// 충돌체가 없는 경우
		if (nullptr == vecLeft[idxL]->Collider2D())
			continue;

		// 이중검사 방지
		size_t idxR = 0;
		// _left, _right 동일 레이어인경우
		if (_left == _right)
			idxR = idxL + 1;
		for (; idxR < rightObjCnt; ++idxR)
		{
			// 충돌체를 보유하고 있지 않은 경우
			if (nullptr == vecRight[idxR]->Collider2D())
				continue;

			// 두 충돌체의 아이디 조합
			CollisionID tID = {};
			tID.iLeftID = vecLeft[idxL]->Collider2D()->GetID();
			tID.iRightID = vecRight[idxR]->Collider2D()->GetID();

			// 이전 프레임 충돌여부 확인
			map<UINT_PTR, bool>::iterator iter = m_mapCollsionRecord.find(tID.iID);
			// 충돌내역이 없는 경우
			if (iter == m_mapCollsionRecord.end())
			{
				m_mapCollsionRecord.insert(make_pair(tID.iID, false));
				iter = m_mapCollsionRecord.find(tID.iID);
			}

			// Dead 상태 확인
			bool bDead = vecLeft[idxL]->IsDead() || vecRight[idxR]->IsDead();	// 둘 중 하나라도 Dead 이면 true

			// 해당 프렘이에 충돌해있는 경우
			if (CollisionBtwCollider(vecLeft[idxL]->Collider2D(), vecRight[idxR]->Collider2D()))
			{
				// 이전 프레임에 충돌한 내역이 있는 경우
				if (iter->second)
				{
					// 두 충돌체중 한 객체라도 Dead 상태인 경우
					if (bDead)
					{
						// 충돌 종료
						vecLeft[idxL]->Collider2D()->EndOverlap(vecRight[idxR]->Collider2D());
						vecRight[idxR]->Collider2D()->EndOverlap(vecLeft[idxL]->Collider2D());
					}
					// 두 충돌체 모두 !Dead 상태인 경우
					else
					{
						// 충돌 유지
						vecLeft[idxL]->Collider2D()->Overlap(vecRight[idxR]->Collider2D());
						vecRight[idxR]->Collider2D()->Overlap(vecLeft[idxL]->Collider2D());
					}
				}
				// 이전 프레임에 충돌한 내역이 없는 경우
				else
				{
					// 두 충돌체중 한 객체라도 Dead 상태인 경우 -> 충돌 무효
					// 두 충돌체 모두 !Dead 상태인 경우
					if (!bDead)
					{
						// 충돌 시작
						vecLeft[idxL]->Collider2D()->BeginOverlap(vecRight[idxR]->Collider2D());
						vecRight[idxR]->Collider2D()->BeginOverlap(vecLeft[idxL]->Collider2D());
						iter->second = true;
					}
				}
			}
			// 해당 프레임에 충돌해있지 않은 경우
			else
			{
				// 이전 프레임에 충돌한 내역이 있는 경우
				if (iter->second)
				{
					// 충돌 종료
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

	// 충돌테스트

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
	// 0 -→ 1
	// ↓    |
	// 3 -- 2
	arrProj[0] = XMVector3TransformCoord(arrRect[1], _matRect1) - XMVector3TransformCoord(arrRect[0], _matRect1);
	arrProj[1] = XMVector3TransformCoord(arrRect[3], _matRect1) - XMVector3TransformCoord(arrRect[0], _matRect1);

	arrProj[2] = XMVector3TransformCoord(arrRect[1], _matRect2) - XMVector3TransformCoord(arrRect[0], _matRect2);
	arrProj[3] = XMVector3TransformCoord(arrRect[3], _matRect2) - XMVector3TransformCoord(arrRect[0], _matRect2);

	Vec3 vCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _matRect2) - XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _matRect1);

	// i 번째 투영축으로 4개의 표면벡터를 투영시킨다.
	for (int i = 0; i < 4; ++i)
	{
		// i 번째 표면백터를 투영축으로 삼는다
		Vec3 vProj = arrProj[i];

		// 단위벡터로 만들어서 내적할 경우 투영된 길이를 구할 수 있게 한다.
		vProj.Normalize();

		// 투영된 길이를 누적시킬 변수
		float ProjAcc = 0.f;

		// 반복문 돌면서 4개의 표면벡터를 지정된 투영축으로 투영시켜서 길이를 누적받는다.
		for (int j = 0; j < 4; ++j)
		{
			ProjAcc += abs(vProj.Dot(arrProj[j]));
		}

		// 투영된 길이의 절반씩 합친 길이가 필요하기 때문에 전체 합친길이를 2 로 나눈다
		ProjAcc /= 2.f;

		// 두 충돌체의 중심을 이은 벡터도 투영시킨다.
		float fCenterDist = abs(vProj.Dot(vCenter));

		// 중심을 이은 벡터를 투영시킨 길이가, 표면을 투영시킨 길이의 절반보다 크다면 
		// 둘을 분리시킬 수 있다.
		if (ProjAcc < fCenterDist)
		{
			return false;	// 비 충돌 상태
		}
	}

	return true;	// 충돌 상태
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
		return false;	// 비 충돌 상태
	}

	return true;	// 충돌 상태
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

	// 투영벡터
	Vec3 arrProj[3] = {};
	arrProj[0] = XMVector3TransformCoord(arrRect[1], _matRect) - XMVector3TransformCoord(arrRect[0], _matRect);
	arrProj[1] = XMVector3TransformCoord(arrRect[3], _matRect) - XMVector3TransformCoord(arrRect[0], _matRect);

	Vec3 vCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _matCircle) - XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _matRect);
	arrProj[2] = vCenter;

	// i 번째 투영축으로 2개의 표면벡터를 투영시킨다.
	for (int i = 0; i < 3; ++i)
	{
		// i 번째 표면백터를 투영축으로 삼는다
		Vec3 vProj = arrProj[i];

		// 단위벡터로 만들어서 내적할 경우 투영된 길이를 구할 수 있게 한다.
		vProj.Normalize();

		// 투영된 길이를 누적시킬 변수
		float ProjAcc = 0.f;

		// 원의 지름을 투영된 길이에 누적
		ProjAcc += (1.f * scale.x);

		// 반복문 돌면서 Rect의 2개의 표면벡터를 지정된 투영축으로 투영시켜서 길이를 누적받는다.
		for (int j = 0; j < 2; ++j)
		{
			ProjAcc += abs(vProj.Dot(arrProj[j]));
		}

		// 투영된 길이의 절반씩 합친 길이가 필요하기 때문에 전체 합친길이를 2 로 나눈다
		ProjAcc /= 2.f;

		// 두 충돌체의 중심을 이은 벡터도 투영시킨다.
		float fCenterDist = abs(vProj.Dot(vCenter));

		// 중심을 이은 벡터를 투영시킨 길이가, 표면을 투영시킨 길이의 절반보다 크다면 
		// 둘을 분리시킬 수 있다.
		if (ProjAcc < fCenterDist)
		{
			return false; // 비 충돌 상태
		}
	}

	return true;	// 충돌 상태
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

	// right/left layer 가 nullptr 인 경우
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
			// left, right 레이어의 충돌 설정이 false인 경우
			if (false == m_arr2LayerCollisionConfig[left][right])
				continue;

			// left, right 레이어의 충돌 설정이 true인 경우
			CollisionBtwLayer((UINT)left, (UINT)right);
		}
	}
}
