#pragma once

class CObject;

class CObjectMgr
{
	SINGLE(CObjectMgr);
private:
	// ObjectVector
	vector<CObject*> m_vecObject[(UINT)OBJECT::OBJECT_END];
};
