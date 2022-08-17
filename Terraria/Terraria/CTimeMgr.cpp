#include "pch.h"
#include "CTimeMgr.h"
#include"CEngine.h"
CTimeMgr::CTimeMgr()
	:m_llCurCount({})
	, m_llFrequency({})
	, m_dDT(0.f)
	, m_dAccumulate(0.f)
	, m_llPrevCount({})
	, m_iFps(0)
	, m_iCallCount(0)
{
}


int CTimeMgr::Update()
{
	m_dDT = 0.;
	float m_fVsync = 1.f / 60.f;
	while (0.f < m_fVsync)
	{
		QueryPerformanceCounter(&m_llCurCount);

		// Cululate Delta Time
		double m_dAcc = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)m_llFrequency.QuadPart;

		// ResetPrevTime
		m_llPrevCount = m_llCurCount;
		// Add DT Accum
		m_dAccumulate += m_dDT;

		// Vsync
		m_fVsync -= (float)m_dDT;
		m_dDT += m_dAcc;
	}
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

int CTimeMgr::Render()
{
	++m_iCallCount;
	// if DT Accum over then 1 second
	if (m_dAccumulate >= 1)
	{
		m_dAccumulate = 0;
		m_iFps = m_iCallCount;
		PrintTimeState();
		m_iCallCount = 0;
	}
	return 0;
}

int CTimeMgr::PrintTimeState()
{
	wchar_t szBuffer[255] = {};
	swprintf_s(szBuffer, L"FPS : %d ,  DT : %f", m_iFps, m_dDT);
	SetWindowText(CEngine::GetInstance()->GetMainHWND(), szBuffer);

	return 0;
}


CTimeMgr::~CTimeMgr()
{

}
