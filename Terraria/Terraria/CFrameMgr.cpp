#include "pch.h"
#include "CFrameMgr.h"
#include "CTimeMgr.h"
#include "CEngine.h"

CFrameMgr::CFrameMgr()
    :m_iFps(60)
	,m_dAccumDelta(0)
	, m_iCallCount(0)
	, m_dTime(1.)
	, m_dAccumTime(1.)
	, m_dOneFrameDelta(1.)
{

}


int CFrameMgr::PrintTimeState()
{
	wchar_t szBuffer[255] = {};
	swprintf_s(szBuffer, L"FPS : %d ,  DT : %f", m_iCallCount, m_dOneFrameDelta);
	SetWindowText(CEngine::GetInstance()->GetMainHWND(), szBuffer);
	m_iCallCount = 0;
	return 0;
}


bool CFrameMgr::Update()
{
	CTimeMgr::GetInstance()->Update();
	double dDT = CTimeMgr::GetInstance()->GetDT();
	m_dAccumDelta += dDT;
	m_dAccumTime += dDT;
	if (m_dAccumDelta >= (1. / (double)m_iFps))
	{
		++m_iCallCount;
		if (m_dAccumTime >= m_dTime)
		{
			PrintTimeState();
			m_dAccumTime = 0.;
		}
		m_dOneFrameDelta = m_dAccumDelta;
		m_dAccumDelta = 0.;

		return true;
	}
    return false;
}


int CFrameMgr::Init()
{
	CTimeMgr::GetInstance()->Init();
	return 0;
}

CFrameMgr::~CFrameMgr()
{

}
