#pragma once



class CInputMgr
{
public:
	bool IsLBTDown();
	bool IsLBTUp();

	INPUTSTATE GetKeyState();

	POINT GetMousePos()const { return m_stMousePos; }
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

