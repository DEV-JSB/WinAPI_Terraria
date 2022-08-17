#include "pch.h"
#include "CTimeMgr.h"
#include"CEngine.h"
CTimeMgr::CTimeMgr()
	:m_llCurCount({})
	, m_llFrequency({})
	, m_llPrevCount({})
	, m_dDT(0.f)
{
}


int CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);
	// Cululate Delta Time
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;
	m_llPrevCount = m_llCurCount;
	return 0;
}

int CTimeMgr::Init()
{
	// Get CPU Frequency Count
	QueryPerformanceFrequency(&m_llFrequency);
	// Init PrevTime
	QueryPerformanceCounter(&m_llPrevCount);

	return 0;
}


CTimeMgr::~CTimeMgr()
{

}
