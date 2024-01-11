#pragma once

#define		SINGLETON(classType)	private:\
										classType();\
										~classType();\
										friend class CSingleton<classType>;

#define		DEVICE		CGraphics::GetInst()->GetDevice()
#define		CONTEXT		CGraphics::GetInst()->GetContext()
#define		SWAPCHAIN	CGraphics::GetInst()->GetSwapChain()
