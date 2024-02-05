#pragma once

class CAnimation;
class CTexture;

class CAnimator2D
	: public CComponent
{
	using Super = CComponent;

public:
	CAnimator2D();
	virtual ~CAnimator2D();

private:
	map<wstring, CAnimation*>	m_mapAnimation;
	CAnimation*					m_pCurAnimation;
	bool						m_bRepeat;

public:
	// CAnimation->Create() 호출로 애니메이션 생성후 m_mapAnimation에 저장
	void Create(const wstring& _aniName, 
				Ptr<CTexture> _atlas, 
				int32 _frameCnt, 
				Vec2 _leftTop,	// Texture 상에서 애니메이션이 시작될 LeftTop
				Vec2 _sliceSize, 
				Vec2 _offset, 
				Vec2 _background,
				float _fps);
	// 저장된 애니메이션 탐색
	CAnimation* FindAnimation(const wstring& _aniName);	
	// b2 레지스터에 바인딩된 재생중인 애니메이션의 현재 프레임에대한 정보 초기화
	void Clear();
	// m_pCurAnimation(현재 재생중인 애니메이션) 지정
	void Play(const wstring& _aniName, bool _repeat = true);	

public:
	virtual void Begin() override {};
	virtual void Tick() override {};
	virtual void FinalTick() override;
	virtual void UpdateData() override;
};