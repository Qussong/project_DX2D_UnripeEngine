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
	CAnimator2D*		m_pAnimator;		// �ش� �ִϸ��̼��� ����Ǿ��ִ� Animator
	vector<tAniFrmInfo>	m_vecFrmInfo;		// �ִϸ��̼��� �����ϴ� �� �����ӿ� ���� ����
	int32				m_iCurFrmIdx;		// ����ǰ� �ִ� �ִϸ��̼��� ���� ����� �ε���(������)
	bool				m_bFinish;			// �ִϸ��̼� ��� �Ϸ� ����
	Ptr<CTexture>		m_AtlasTex;			// �ִϸ��̼ǿ� ���Ǵ� ��Ʋ�� �̹���

	float				m_fCurFrmPlayTime;	// ���� ������ �÷��� �����ð�

public:
	// �ִϸ��̼� ����
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

