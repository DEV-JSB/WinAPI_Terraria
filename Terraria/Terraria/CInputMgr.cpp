#include "pch.h"
#include "CEngine.h"
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

CInputMgr::CInputMgr()
	:m_stMousePos({0,0})
	,m_arrMouseInfo()
{

}
CInputMgr::~CInputMgr()
{

}


bool CInputMgr::IsLBTDown()
{
	switch (m_arrMouseInfo[MOUSE_LEFT].eState)
	{
	case INPUTSTATE::INPUTSTATE_TAP:
		return true;
	case INPUTSTATE::INPUTSTATE_HOLD:
		return false;
	default:
		return false;
	}
}

bool CInputMgr::IsLBTUp()
{
	switch (m_arrMouseInfo[MOUSE_LEFT].eState)
	{
	case INPUTSTATE::INPUTSTATE_AWAY:
		return true;
	default:
		return false;
	}
}

bool CInputMgr::IsLBTPressed()
{

	return false;
}

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


	for (int i = 0; i < (int)MOUSE::MOUSE_END; ++i)
	{
		// Mouse Pressed State
		if (GetAsyncKeyState(m_arrMouseInfo[i].iKey) & 0x8000)
		{
			// Is Not prev Pressed
			if (m_arrMouseInfo[i].bIsPressed == false)
			{
				m_arrMouseInfo[i].bIsPressed = true;
				m_arrMouseInfo[i].eState = INPUTSTATE::INPUTSTATE_TAP;
			}// Is prev Pressed
			else if (m_arrMouseInfo[i].bIsPressed == true)
			{
				m_arrMouseInfo[i].bIsPressed = true;
				m_arrMouseInfo[i].eState = INPUTSTATE::INPUTSTATE_TAP;
				m_arrMouseInfo[i].eState = INPUTSTATE::INPUTSTATE_HOLD;
			}
		} // Not Key Pressed
		else
		{
			if (m_arrMouseInfo[i].bIsPressed == true)
			{
				m_arrMouseInfo[i].bIsPressed = false;
				m_arrMouseInfo[i].eState = INPUTSTATE::INPUTSTATE_AWAY;
			}
			else
			{
				m_arrMouseInfo[i].bIsPressed = false;
				m_arrMouseInfo[i].eState = INPUTSTATE::INPUTSTATE_NONE;
			}
		}
	}


	GetCursorPos(&m_stMousePos);
	ScreenToClient(CEngine::GetInstance()->GetMainHWND(), &m_stMousePos);


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


	m_arrMouseInfo[MOUSE_LEFT].iKey = VK_LBUTTON;
	m_arrMouseInfo[MOUSE_RIGHT].iKey = VK_RBUTTON;

	m_arrMouseInfo[MOUSE_LEFT].eState = INPUTSTATE::INPUTSTATE_NONE;
	m_arrMouseInfo[MOUSE_RIGHT].eState = INPUTSTATE::INPUTSTATE_NONE;
	m_vecstKeyInfo[MOUSE_RIGHT].bIsPressed = false;
	m_vecstKeyInfo[MOUSE_LEFT].bIsPressed = false;
	return 0;
}
