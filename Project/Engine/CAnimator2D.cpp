#include "pch.h"
#include "CAnimator2D.h"

CAnimator2D::CAnimator2D()
	: Super(COMPONENT_TYPE::ANIMATOR2D)
{
}

CAnimator2D::~CAnimator2D()
{
}

void CAnimator2D::Create(const wstring& _aniName, Ptr<CTexture> _atlas, int32 _frameCnt, Vec2 _leftTop, Vec2 _sliceSize, Vec2 _offset,  float _fps)
{
	CAnimation* pAni = FindAnimation(_aniName);
	if (nullptr != pAni)
	{
		MessageBoxA(nullptr, "Already Created Animation Name", "CAnimator2D Error", MB_OK);
		return;
	}

	tAnimFrame frameInfo = {};
	{
		frameInfo.v2LeftTop = _leftTop;
		frameInfo.v2SliceSize = _sliceSize;
		frameInfo.v2Offset = _offset;
		frameInfo.fDuration = _fps;
	}

	pAni = new CAnimation;
	pAni->Create(this, _atlas, _frameCnt, frameInfo);
	m_mapAnimation.insert(make_pair(_aniName, pAni));
}

CAnimation* CAnimator2D::FindAnimation(const wstring& _aniName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnimation.find(_aniName);

	if (iter == m_mapAnimation.end())
		return nullptr;

	return iter->second;
}

void CAnimator2D::FinalTick()
{
}
