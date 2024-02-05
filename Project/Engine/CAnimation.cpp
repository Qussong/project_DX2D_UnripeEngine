#include "pch.h"
#include "CAnimation.h"

CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_iCurFrmIdx(0)
	, m_bFinish(false)
	, m_fAccTime(0.f)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Create(CAnimator2D* _animator, Ptr<CTexture> _atlas, uint32 _frameCnt, Vec2 _leftTop, Vec2 _sliceSize, Vec2 _offset, Vec2 _background, float _fps)
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

void CAnimation::Reset()
{
	m_bFinish = false;
	m_iCurFrmIdx = 0;
	m_fAccTime = 0.f;
}

void CAnimation::FinalTick()
{
	// 프레임 재생 누적시간 갱신
	m_fAccTime += DT;

	// 현재 프레임이 정해진 재생시간을 넘어선 경우
	if (m_vecFrmInfo[m_iCurFrmIdx].fDuration < m_fAccTime)
	{
		++m_iCurFrmIdx;
		m_fAccTime = 0.f;

		// 애니메이션의 모든 프레임이 재생 완료된 경우
		int32 iFrameCnt = (int32)m_vecFrmInfo.size();
		if (iFrameCnt <= m_iCurFrmIdx)
		{
			// 마지막 프레임에 머무른다.
			m_iCurFrmIdx = iFrameCnt - 1;
			// 애니메이션 재생 완료 플래그 true
			m_bFinish = true;
		}
	}
}

void CAnimation::UpdateData()
{
	// 현재 프레임에 대한 정보를 상수버퍼로 옮기고 b2 레지스터로(CB_TYPE::ANI_2D) 바인딩
	static CConstantBuffer* pCB = GRAPHICS->GetCB(CB_TYPE::ANI2D);
	tAnimation2D data = {};
	{
		data.v2LeftTop = m_vecFrmInfo[m_iCurFrmIdx].v2LeftTop;
		data.v2SliceSize = m_vecFrmInfo[m_iCurFrmIdx].v2SliceSize;
		data.v2Offset = m_vecFrmInfo[m_iCurFrmIdx].v2Offset;
		data.v2Background = m_vecFrmInfo[m_iCurFrmIdx].v2Background;
		data.iUseAni2D = 1;	
		//data.iDebugCheck = M_RENDER->IsDebugCheck();	// 1 = true, 0 = false
	}
	pCB->SetData(&data);
	pCB->UpdateData();

	// 애니메이션이 사용하는 아틀라스 이미지를 t10에 바인딩
	m_AtlasTex->UpdateData(10);
}

void CAnimation::Clear()
{
	static CConstantBuffer* pCB = GRAPHICS->GetCB(CB_TYPE::ANI2D);
	tAnimation2D data = {};

	pCB->SetData(&data);
	pCB->UpdateData();
}
