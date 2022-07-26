#include "pch.h"
#include "CInputMgr.h"

#define MOUSE_LEFT 0
#define MOUSE_RIGHT 1

int KeyInfo[(int)KEY::KEY_LAST] = {
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	'Q',
	'W',
	'E',
	'R',
	'A',
	'S',
	'D',
	'F',

	VK_CONTROL,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE
};

int CInputMgr::Update()
{
	for (size_t i = 0; i < m_vecstKeyInfo.size(); ++i)
	{
		// Key Pressed State
		if (GetAsyncKeyState(m_vecstKeyInfo[i].iKey) & 0x8000)
		{
			// Is Not prev Pressed
			if (m_vecstKeyInfo[i].bIsPressed == false)
			{
				m_vecstKeyInfo[i].bIsPressed = true;
				m_vecstKeyInfo[i].eState = INPUTSTATE::INPUTSTATE_TAP;
			}// Is prev Pressed
			else if (m_vecstKeyInfo[i].bIsPressed == true)
			{
				m_vecstKeyInfo[i].bIsPressed = true;
				m_vecstKeyInfo[i].eState = INPUTSTATE::INPUTSTATE_TAP;
				m_vecstKeyInfo[i].eState = INPUTSTATE::INPUTSTATE_HOLD;
			}
		} // Not Key Pressed
		else
		{
			if (m_vecstKeyInfo[i].bIsPressed == true)
			{
				m_vecstKeyInfo[i].bIsPressed = false;
				m_vecstKeyInfo[i].eState = INPUTSTATE::INPUTSTATE_AWAY;
			}
			else
			{
				m_vecstKeyInfo[i].bIsPressed = false;
				m_vecstKeyInfo[i].eState = INPUTSTATE::INPUTSTATE_NONE;
			}
		}
	}

	return 0;
}

int CInputMgr::Init()
{
	m_stMousePos = { 0,0 };

	// resize Key vector
	m_vecstKeyInfo.resize((size_t)KEY::KEY_LAST);
	// Reset Setting KeyInfo
	for (size_t i = 0; i < m_vecstKeyInfo.size(); ++i)
	{
		m_vecstKeyInfo[i].iKey = KeyInfo[i];
		m_vecstKeyInfo[i].eState = INPUTSTATE::INPUTSTATE_NONE;
		m_vecstKeyInfo[i].bIsPressed = false;
	}


	m_vecstMouseInfo[MOUSE_LEFT].iKey = VK_LBUTTON;
	m_vecstMouseInfo[MOUSE_RIGHT].iKey = VK_RBUTTON;

	m_vecstMouseInfo[MOUSE_LEFT].eState = INPUTSTATE::INPUTSTATE_NONE;
	m_vecstMouseInfo[MOUSE_RIGHT].eState = INPUTSTATE::INPUTSTATE_NONE;
	m_vecstKeyInfo[MOUSE_RIGHT].bIsPressed = false;
	m_vecstKeyInfo[MOUSE_LEFT].bIsPressed = false;
	return 0;
}
