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
	CAnimator2D*		m_pAnimator;		// 해당 애니메이션이 저장되어있는 Animator
	vector<tAniFrmInfo>	m_vecFrmInfo;		// 애니메이션을 구성하는 각 프레임에 대한 정보
	int32				m_iCurFrmIdx;		// 재생되고 있는 애니메이션의 현재 장면의 인덱스(프레임)
	bool				m_bFinish;			// 애니메이션 재생 완료 여부
	Ptr<CTexture>		m_AtlasTex;			// 애니메이션에 사용되는 아틀라스 이미지

	float				m_fCurFrmPlayTime;	// 현재 프레임 플레이 누적시간

public:
	// 애니메이션 생성
	void FrameSet(CAnimator2D* _animator, 
				Ptr<CTexture> _atlas,
				uint32 _frameCnt,
				Vec2 _leftTop,	
				Vec2 _sliceSize,
				Vec2 _offset,
				Vec2 _background,
				float _fps);

public:
	void FinalTick();
	void UpdateData();
	static void Clear();
};

