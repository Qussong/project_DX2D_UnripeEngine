#pragma once

class CTexture;

class CAnimation
	: public CEntity
{
	using Super = CEntity;

public:
	CAnimation();
	virtual ~CAnimation();

private:
	CAnimator2D*		m_pAnimator;
	vector<tAnimFrame>	m_vecFrameInfo;

	int32				m_iCurFrameIdx;
	bool				m_bFinish;
	Ptr<CTexture>		m_AtlasTex;

public:
	void Create(CAnimator2D* _animator, 
				Ptr<CTexture> _atlas,
				uint32 _frameCnt,
				tAnimFrame _aniInfo);
};

