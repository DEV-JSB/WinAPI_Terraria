#pragma once
class CFrameMgr
{
public:
	float GetFrameDelta()const { return (float)m_dOneFrameDelta; }
public:
	bool Update();
	int Init();
private:
	int PrintTimeState();
private:
	double m_dAccumDelta;
	int m_iCallCount;
	int m_iFps;
	double m_dTime;
	double m_dAccumTime;
	double m_dOneFrameDelta;
private:
	SINGLE(CFrameMgr);
};

