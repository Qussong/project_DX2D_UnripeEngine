#include "pch.h"
#include "CAnimation.h"

CAnimation::CAnimation()
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Create(CAnimator2D* _animator, Ptr<CTexture> _atlas, uint32 _frameCnt, tAnimFrame _aniInfo)
{
	m_pAnimator = _animator;
	m_AtlasTex = _atlas;
	
	for (size_t i = 0; i < _frameCnt; ++i)
	{
		m_vecFrameInfo.push_back(_aniInfo);
	}
}
