#pragma once

#define		SINGLETON(classType)	private:\
										classType();\
										~classType();\
										friend class CSingleton<classType>;

#define		GRAPHICS	CGraphics::GetInst()
#define		DEVICE		CGraphics::GetInst()->GetDevice()
#define		CONTEXT		CGraphics::GetInst()->GetContext()
#define		SWAPCHAIN	CGraphics::GetInst()->GetSwapChain()

#define		DT			CTimeMgr::GetInst()->DeltaTime()