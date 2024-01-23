#pragma once

#define		SINGLETON(classType)	private:\
										classType();\
										~classType();\
										friend class CSingleton<classType>;

#define		GRAPHICS	CGraphics::GetInst()
#define		DEVICE		CGraphics::GetInst()->GetDevice()
#define		CONTEXT		CGraphics::GetInst()->GetContext()
#define		SWAPCHAIN	CGraphics::GetInst()->GetSwapChain()

#define		M_TIME		CTimeMgr::GetInst()
#define		M_PATH		CPathMgr::GetInst()
#define		M_KEY		CKeyMgr::GetInst()
#define		M_ASSET		CAssetMgr::GetInst()
#define		M_LEVEL		CLevelMgr::GetInst()
#define		M_TASK		CTaskMgr::GetInst()

#define		DT			M_TIME->DeltaTime()