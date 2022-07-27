#include "pch.h"
#include "CPathMgr.h"

CPathMgr::CPathMgr()
	:m_szContentPath{}
{}
CPathMgr::~CPathMgr()
{

}
void CPathMgr::Init()
{
	GetCurrentDirectory(255, m_szContentPath);

}
