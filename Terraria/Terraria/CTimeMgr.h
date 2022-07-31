#pragma once
class CTimeMgr
{



public:
	int Update();
	int Init();
	int Render();
	int PrintTimeState();
private:
	// Union Current Time
	LARGE_INTEGER m_llCurCount;
	// Union Prev Time
	LARGE_INTEGER m_llPrevCount;
	// Union CPU Frequency
	LARGE_INTEGER m_llFrequency;

	// CallCount -> using Know FPS
	int m_iCallCount;
	// Delta time 
	double m_dDT;
	// Accumulate Time
	double m_dAccumulate;
	// Frame
	UINT   m_iFps;
private:
	SINGLE(CTimeMgr);
};

