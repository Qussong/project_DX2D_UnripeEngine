#include "pch.h"
#include "CKeyMgr.h"

int g_keySync[(int)KEY::KEY_END]
{
	'0', '1', '2', '3', '4',
	'5', '6', '7', '8', '9',

	VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4,
	VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9,

	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
	'Z', 'X', 'C', 'V', 'B', 'N', 'M',

	VK_TAB, VK_LSHIFT, VK_LMENU, VK_LCONTROL, VK_SPACE,
	VK_ESCAPE, VK_RETURN, VK_BACK,
	VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,

	VK_LBUTTON, VK_RBUTTON,
};

CKeyMgr::CKeyMgr()
	: m_vMousePos(0.f, 0.f)
{
}

CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::Init()
{
	// reserve vs resize
	m_vecKeyData.reserve((int)KEY::KEY_END);

	for (UINT i = 0; i < (int)KEY::KEY_END; ++i)
	{
		m_vecKeyData.push_back(KeyData{ (KEY)i, KEY_STATE::NONE, false });
	}
}

void CKeyMgr::Tick()
{
	if (nullptr == GetFocus())
	{
		KEY_STATE curKeyState = KEY_STATE::NONE; 
		KEY_STATE nextKeState = KEY_STATE::NONE;

		for (size_t i = 0; i < m_vecKeyData.size(); ++i)
		{
			curKeyState = m_vecKeyData[i].eState;
			nextKeState = KEY_STATE::NONE;

			if (KEY_STATE::TAP == curKeyState)
			{
				nextKeState = KEY_STATE::PRESSED;
			}
			else if (KEY_STATE::PRESSED == curKeyState)
			{
				nextKeState = KEY_STATE::RELEASED;
			}

			m_vecKeyData[i].eState = nextKeState;
		}	
	}
	else
	{
		SHORT keyState = 0;
		SHORT pressed = static_cast<SHORT>(0x8001);

		for (size_t i = 0; i < m_vecKeyData.size(); ++i)
		{
			keyState = GetAsyncKeyState(g_keySync[(int)m_vecKeyData[i].eKey]);

			// 현재 프레임에 눌려짐
			if (keyState & pressed)
			{
				if (true == m_vecKeyData[i].bPressed)
					m_vecKeyData[i].eState = KEY_STATE::PRESSED;
				else
					m_vecKeyData[i].eState = KEY_STATE::TAP;

				m_vecKeyData[i].bPressed = true;
			}
			// 현재 프레임에 안 눌려짐
			else
			{
				if (true == m_vecKeyData[i].bPressed)
					m_vecKeyData[i].eState = KEY_STATE::RELEASED;
				else
					m_vecKeyData[i].eState = KEY_STATE::NONE;

				m_vecKeyData[i].bPressed = false;
			}
		}

		// 마우스 좌표 계산
		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(CEngine::GetInst()->GetWindowHandle(), &pt);
		m_vMousePos = Vec2((float)pt.x, (float)pt.y);
	}
}