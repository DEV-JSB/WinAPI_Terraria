#pragma once
#include "CTool.h"
#include "CFactory2.h"

class CCollider;

class CSword : public CTool
{
public: // Logic
	virtual int Render(const HDC _dc)	override;
	virtual int Update()				override;
private:
	int CreateAnimator();
	int UpdateCollider();
	int CreateCollider();
private:
	int m_iFrameMaxCount;
	int m_iColliderIndex;
	vector<CCollider*> m_vecCollider;

private:
	friend class CFactory2;
	CSword();
public:
	virtual ~CSword();
};

