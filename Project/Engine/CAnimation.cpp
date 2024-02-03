#include "pch.h"
#include "CAnimation.h"

CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_iCurFrmIdx(0)
	, m_bFinish(false)
	, m_fCurFrmPlayTime(0.f)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::FrameSet(CAnimator2D* _animator, Ptr<CTexture> _atlas, uint32 _frameCnt, Vec2 _leftTop, Vec2 _sliceSize, Vec2 _offset, Vec2 _background, float _fps)
{
	m_pAnimator = _animator;
	m_AtlasTex = _atlas;

	for (size_t i = 0; i < _frameCnt; ++i)
	{
		Vec2 v2CurFrmSliceSize = Vec2(_sliceSize.x / (float)_atlas->GetWidth(),
										_sliceSize.y / (float)_atlas->GetHeight());
		Vec2 v2CurFrmLefTop = Vec2(_leftTop.x / (float)_atlas->GetWidth() + v2CurFrmSliceSize.x * i,
									_leftTop.y / (float)_atlas->GetHeight());
		Vec2 v2CurFrmOffset = Vec2(_offset.x / (float)_atlas->GetWidth(),
									_offset.y / (float)_atlas->GetHeight());
		Vec2 v2CurFrmBackground = Vec2(_background.x / (float)_atlas->GetWidth(),
										_background.y / (float)_atlas->GetHeight());

		tAniFrmInfo frameInfo = {};
		{
			frameInfo.v2LeftTop = v2CurFrmLefTop;
			frameInfo.v2SliceSize = v2CurFrmSliceSize;
			frameInfo.v2Offset = v2CurFrmOffset;
			frameInfo.v2Background = v2CurFrmBackground;
			frameInfo.fDuration = 1.f / _fps;
		}

		m_vecFrmInfo.push_back(frameInfo);
	}
}

void CAnimation::FinalTick()
{
	m_fCurFrmPlayTime += DT;
	//  ���� �������� ������ �÷���Ÿ���� �Ѿ ���
	if (m_vecFrmInfo[m_iCurFrmIdx].fDuration < m_fCurFrmPlayTime)
	{
		++m_iCurFrmIdx;
		m_fCurFrmPlayTime = 0.f;

		// ���� �������� �ִϸ��̼� �����Ӱ����� ������� ù ���������� ���ư���
		int32 iFrameCnt = m_vecFrmInfo.size();
		if (iFrameCnt <= m_iCurFrmIdx)
			m_iCurFrmIdx = 0;
	}
}

void CAnimation::UpdateData()
{
	// ���� �����ӿ� ���� ������ ������۷� �ű�� b2 �������ͷ�(CB_TYPE::ANI_2D) ���ε�
	static CConstantBuffer* pCB = GRAPHICS->GetCB(CB_TYPE::ANI_2D);
	tAnimation2D data = {};
	{
		data.v2LeftTop = m_vecFrmInfo[m_iCurFrmIdx].v2LeftTop;
		data.v2SliceSize = m_vecFrmInfo[m_iCurFrmIdx].v2SliceSize;
		data.v2Offset = m_vecFrmInfo[m_iCurFrmIdx].v2Offset;
		data.v2Background = m_vecFrmInfo[m_iCurFrmIdx].v2Background;
		data.iUseAni2D = 1;	
		data.iDebugCheck = M_RENDER->IsDebugCheck();	// 1 = true, 0 = false
	}
	pCB->SetData(&data);
	pCB->UpdateData();

	// �ִϸ��̼��� ����ϴ� ��Ʋ�� �̹����� t10�� ���ε�
	m_AtlasTex->UpdateData(10);
}

void CAnimation::Clear()
{
	static CConstantBuffer* pCB = GRAPHICS->GetCB(CB_TYPE::ANI_2D);
	tAnimation2D data = {};

	pCB->SetData(&data);
	pCB->UpdateData();
}
