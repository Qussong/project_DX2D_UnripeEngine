#include "pch.h"
#include "CAnimator2D.h"

CAnimator2D::CAnimator2D()
	: Super(COMPONENT_TYPE::ANIMATOR2D)
	, m_pCurAnimation(nullptr)
	, m_bRepeat(true)
{
	SetName(L"Animator2D");
}

CAnimator2D::~CAnimator2D()
{
	Lazy::DelMap(m_mapAnimation);
}

void CAnimator2D::Create(const wstring& _aniName, Ptr<CTexture> _atlas, int32 _frameCnt
						, Vec2 _leftTop, Vec2 _sliceSize, Vec2 _offset, Vec2 _background, float _fps)
{
	CAnimation* pAni = FindAnimation(_aniName);
	if (nullptr != pAni)
	{
		MessageBoxA(nullptr, "Already Created Animation Name", "CAnimator2D Error", MB_OK);
		return;
	}

	pAni = new CAnimation;
	pAni->SetName(_aniName);
	pAni->Create(this, _atlas, _frameCnt, _leftTop, _sliceSize, _offset, _background, _fps);
	m_mapAnimation.insert(make_pair(_aniName, pAni));
}

CAnimation* CAnimator2D::FindAnimation(const wstring& _aniName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnimation.find(_aniName);

	if (iter == m_mapAnimation.end())
		return nullptr;

	return iter->second;
}

void CAnimator2D::Clear()
{
	// b2 레지스터에 바인딩된 애니메이션의 현재 프레임에 대한 정보를 초기화
	CAnimation::Clear();
}

void CAnimator2D::Play(const wstring& _aniName, bool _repeat)
{
	CAnimation* pAni = FindAnimation(_aniName);

	if (nullptr == pAni)
	{
		MessageBoxA(nullptr, "Invalid Animation", "CAnimator2D Error", MB_OK);
		return;
	}

	m_pCurAnimation = pAni;
	m_bRepeat = _repeat;
	m_pCurAnimation->Reset();	// 애니메이션 초기화(프레임 = 0, 완료여부 = false, 프레임누적시간 = 0)
}

void CAnimator2D::FinalTick()
{
	// 지정된 애니메이션이 없다면 함수 종료
	if (nullptr == m_pCurAnimation)
		return;

	// 애니메이션이 재생완료되었고, 반복재생해야하는 경우
	if (m_pCurAnimation->IsFinish() && m_bRepeat)
	{
		m_pCurAnimation->Reset();
	}

	m_pCurAnimation->FinalTick();	// 애니메이션 프레임 진행(재생)
}

void CAnimator2D::UpdateData()
{
	// 지정된 현재 애니메이션(m_pCurAnimation)이 없으면 함수 종료
	if (nullptr == m_pCurAnimation)
	{
		MessageBoxA(nullptr, "Current Animation NOT DEFINED", "CAnimator2D Error", MB_OK);
		return;
	}

	// 애니메이션의 현재 프레임에 대한 정보를 상수버퍼로 옮기고 b2 레지스터(CB_TYPE::ANI_2D)에 바인딩
	// 애니메이션이 사용하는 아틀라스 이미지를 t10에 바인딩
	m_pCurAnimation->UpdateData();
}
