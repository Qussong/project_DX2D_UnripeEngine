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

void CAnimation::FrameSet(CAnimator2D* _animator, Ptr<CTexture> _atlas, uint32 _frameCnt, Vec2 _leftTop, Vec2 _sliceSize, Vec2 _offset, float _fps)
{
	m_pAnimator = _animator;
	m_AtlasTex = _atlas;

	for (size_t i = 0; i < _frameCnt; ++i)
	{
		Vec2 v2CurFrmLefTop = Vec2();

		// �� ä���
		tAniFrmInfo info = {};
		{
			info.v2LeftTop;
			info.v2SliceSize = _sliceSize;
			info.v2Offset = _offset;
			info.fDuration = 1.f / _fps;
		}

		m_vecFrmInfo.push_back(info);
	}
}

void CAnimation::FinalTick()
{
	m_fCurFrmPlayTime += DT;
	//  ���� �������� ������ �÷���Ÿ���� �Ѿ ���
	if (m_vecFrmInfo[m_iCurFrmIdx].fDuration < m_fCurFrmPlayTime)
	{
		++m_iCurFrmIdx;
		m_fCurFrmPlayTime = 0;

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
		data.iUseAni2D = 1;
		//data.iPadding;
	}
	pCB->SetData(&data);
	pCB->UpdateData();

	// �ִϸ��̼ǿ� ����ϴ� ��Ʋ�� �̹����� t10�� ���ε�
	m_AtlasTex->UpdateData(10);
}

void CAnimation::Clear()
{
	static CConstantBuffer* pCB = GRAPHICS->GetCB(CB_TYPE::ANI_2D);
	tAnimation2D data = {};
	//data.iUseAni2D = 0;

	pCB->SetData(&data);
	pCB->UpdateData();
}
