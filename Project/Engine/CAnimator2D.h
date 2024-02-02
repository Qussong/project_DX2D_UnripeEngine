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
	// 애니메이션 생성
	void Create(const wstring& _aniName, 
				Ptr<CTexture> _atlas, 
				int32 _frameCnt, 
				Vec2 _leftTop, 
				Vec2 _sliceSize, 
				Vec2 _offset, 
				float _fps);
	// 저장된 애니메이션 탐색
	CAnimation* FindAnimation(const wstring& _aniName);	

public:
	virtual void Begin() override {};
	virtual void Tick() override {};
	virtual void FinalTick() override;
	virtual void UpdateData() override {};
};