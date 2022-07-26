#pragma once



class CInputMgr
{
	SINGLE(CInputMgr);
public:
	int Update();
	int Init();
private:
	// SaveKeyState vector
	std::vector<stKeyInfo> m_vecstKeyInfo;
	// SaveMouseState vector
	std::vector<stMouseInfo> m_vecstMouseInfo;
	// MousePoint
	POINT m_stMousePos;
};

