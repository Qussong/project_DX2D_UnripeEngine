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
	// CAnimation->Create() ȣ��� �ִϸ��̼� ������ m_mapAnimation�� ����
	void Create(const wstring& _aniName, 
				Ptr<CTexture> _atlas, 
				int32 _frameCnt, 
				Vec2 _leftTop,	// Texture �󿡼� �ִϸ��̼��� ���۵� LeftTop
				Vec2 _sliceSize, 
				Vec2 _offset, 
				Vec2 _background,
				float _fps);
	// ����� �ִϸ��̼� Ž��
	CAnimation* FindAnimation(const wstring& _aniName);	
	// b2 �������Ϳ� ���ε��� ������� �ִϸ��̼��� ���� �����ӿ����� ���� �ʱ�ȭ
	void Clear();
	// m_pCurAnimation(���� ������� �ִϸ��̼�) ����
	void Play(const wstring& _aniName, bool _repeat = true);	

public:
	virtual void Begin() override {};
	virtual void Tick() override {};
	virtual void FinalTick() override;
	virtual void UpdateData() override;
};