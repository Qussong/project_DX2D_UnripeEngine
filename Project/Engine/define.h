#pragma once

#define		SINGLETON(classType)	private:\
										classType();\
										~classType();\
										friend class CSingleton<classType>;

#define		GRAPHICS		CGraphics::GetInst()
#define		DEVICE			CGraphics::GetInst()->GetDevice()
#define		CONTEXT			CGraphics::GetInst()->GetContext()
#define		SWAPCHAIN		CGraphics::GetInst()->GetSwapChain()

#define		M_TIME			CTimeMgr::GetInst()
#define		M_PATH			CPathMgr::GetInst()
#define		M_KEY			CKeyMgr::GetInst()
#define		M_ASSET			CAssetMgr::GetInst()
#define		M_LEVEL			CLevelMgr::GetInst()
#define		M_TASK			CTaskMgr::GetInst()
#define		M_GC			CGarbageCollector::GetInst()
#define		M_RENDER		CRenderMgr::GetInst()
#define		M_COLLISION		CCollisionMgr::GetInst()

#define		DT				M_TIME->DeltaTime()

#define		LIGHT_MAX_CNT	10

// Layer의 Z축 위치 값
#define		DEFAULT_LAYER_Z		0
#define		BACKGROUND_LAYER_Z	0
#define		TILE_LAYER_Z		0
#define		PLAYER_LAYER_Z		0
#define		MONSTER_LAYER_Z		0
#define		LIGHT2D_LAYER_Z		0
#define		UI_LAYER_Z			0

// 상수버퍼 Register 번호
#define		TEX_ANIM_2D			10
#define		LIGHT_2D			11
#define		TEX_POSTPROCESS		13