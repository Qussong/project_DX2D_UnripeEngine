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

void CAnimator2D::Create(const wstring& _aniName, Ptr<CTexture> _atlas, int32 _frameCnt, Vec2 _leftTop, Vec2 _sliceSize, Vec2 _offset,  float _fps)
{
	CAnimation* pAni = FindAnimation(_aniName);
	if (nullptr != pAni)
	{
		MessageBoxA(nullptr, "Already Created Animation Name", "CAnimator2D Error", MB_OK);
		return;
	}

	pAni = new CAnimation;
	pAni->SetName(_aniName);
	pAni->FrameSet(this, _atlas, _frameCnt, _leftTop, _sliceSize, _offset, _fps);
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
	// b2 �������Ϳ� ���ε��� �ִϸ��̼��� ���� �����ӿ� ���� ������ �ʱ�ȭ
	CAnimation::Clear();
}

void CAnimator2D::Play(const wstring& _aniName)
{
	CAnimation* pAni = FindAnimation(_aniName);

	if (nullptr == pAni)
	{
		MessageBoxA(nullptr, "Invalid Animation", "CAnimator2D Error", MB_OK);
		return;
	}

	m_pCurAnimation = pAni;
}

void CAnimator2D::FinalTick()
{
	m_pCurAnimation->FinalTick();	// �ִϸ��̼� ������ ����(���)
}

void CAnimator2D::UpdateData()
{
	// ������ ���� �ִϸ��̼�(m_pCurAnimation)�� ������ �Լ� ����
	if (nullptr == m_pCurAnimation)
	{
		MessageBoxA(nullptr, "Current Animation NOT DEFINED", "CAnimator2D Error", MB_OK);
		return;
	}

	// �ִϸ��̼��� ���� �����ӿ� ���� ������ ������۷� �ű�� b2 ��������(CB_TYPE::ANI_2D)�� ���ε�
	// �ִϸ��̼��� ����ϴ� ��Ʋ�� �̹����� t10�� ���ε�
	m_pCurAnimation->UpdateData();
}
