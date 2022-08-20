#include "pch.h"
#include "CTool.h"
#include "CFrameMgr.h"

CTool::CTool(const ITEM_NAME _eItemType)
	:CItem(_eItemType)
	,m_iAttackDamage(0)
{
}
int CTool::Update()
{
	return 0;
}


int CTool::CreateCollider()
{
	return 0;
}



CTool::~CTool()
{
}
