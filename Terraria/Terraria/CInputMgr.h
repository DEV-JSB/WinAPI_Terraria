#pragma once



class CInputMgr
{
public:
	bool IsLBTDown();
	bool IsLBTUp();
	bool IsLBTPressed();

	POINT GetMousePos()const { return m_stMousePos; }
	INPUTSTATE GetKeyState(KEY _eType) { return m_vecstKeyInfo[(int)_eType].eState; }
public:// Logic
	int Update();
	int Init();
private:
	// SaveKeyState vector
	std::vector<stKeyInfo> m_vecstKeyInfo;
	// SaveMouseState vector
	stMouseInfo m_arrMouseInfo[2];
	// MousePoint
	POINT m_stMousePos;
private:
	SINGLE(CInputMgr);
};

