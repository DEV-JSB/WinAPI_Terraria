#pragma once
class CTimeMgr
{

public:

	// GetDelaTime
	double GetDT() { return m_dDT; }

public:
	int Update();
	int Init();
private:
	// Union Current Time
	LARGE_INTEGER m_llCurCount;
	// Union Prev Time
	LARGE_INTEGER m_llPrevCount;
	// Union CPU Frequency
	LARGE_INTEGER m_llFrequency;

	// Delta time 
	double m_dDT;
private:
	SINGLE(CTimeMgr);
};

