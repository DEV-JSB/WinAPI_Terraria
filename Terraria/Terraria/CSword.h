#pragma once
#include "CTool.h"
#include "CFactory2.h"

class CCollider;
class CAnimator;

class CSword : public CTool
{
public: // Logic
	virtual int Render(const HDC _dc)		override;
	virtual int Update()					override;
	virtual int SetOwner(CPlayer* _pPlayer)	override;
	virtual int FinalUpdate() 				override;


private:
	int UpdateTransform();
	int CreateAnimator();
	int UpdateCollider();
	// Use In Animator Create Because Collider Will make through Bit Information
	int CreateCollider(CAnimator* _pAni, const wstring& _strAniname);
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

