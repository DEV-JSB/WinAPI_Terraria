#pragma once
#include "CObject.h"

class CPlayer;

class CItem : public CObject
{
public: // SetFunction
	int SetAnimatorFlip(const bool _b);
	virtual int SetOwner(CPlayer* _pPlayer); 
	int SetCoolTime(const float _fTime) { m_fCoolTime = _fTime; return 0; }
public: // GetFunction
	const wstring GetTextureName()const { return m_strItemTexture; }
	const float GetCoolTime()const { return m_fCoolTime; }
	const ITEM_NAME GetItemCategory()const { return m_eItemCategory; }
public: // Logic
	virtual int Render(const HDC _dc)	 = 0;
	virtual int Update()				 override;
	virtual int FinalUpdate()			override;
public:
	// Setting Texture
	virtual int SetTexture(const wstring& _str);
protected:
	// Flip Item -> Flip Player
	bool m_bIsFilp;



	CPlayer* m_pOwner;
	// Item CoolTime
	float m_fCoolTime;
	float m_fAccumTime;
	// Item Texture
	wstring m_strItemTexture;
	// Item Animation Name
	wstring m_strItemAnimation;
	// Item Type
	ITEM_NAME m_eItemCategory;
protected:
	CItem(const ITEM_NAME _eType);
public:
	virtual ~CItem();
};

