#pragma once
#include "CObject.h"

class CPlayer;

class CItem : public CObject
{
public: // SetFunction
	int SetAnimatorFlip(const bool _b);
	int SetOwner(CPlayer* _pPlayer); 
	int SetCoolTime(const float _fTime) { m_fCoolTime = _fTime; return 0; }
public: // GetFunction
	const wstring GetTextureName()const { return m_strItemTexture; }
	const float GetCoolTime()const { return m_fCoolTime; }
public: // Logic
	virtual int Render(const HDC _dc)	 = 0;
	virtual int Update()				 override;
	virtual int FinalUpdate()			override;
public:
	// Setting Texture
	virtual int SetTexture(const wstring& _str);
protected:

	CPlayer* m_pOwner;
	// Item CoolTime
	float m_fCoolTime;
	float m_fAccumTime;
	// ItemIndex
	int m_iItemIndex;
	// Making through this Menber variable
	static int m_iIdxKey;
	// Item Texture
	wstring m_strItemTexture;
	// Item Animation Name
	wstring m_strItemAnimation;
protected:
	CItem();
public:
	virtual ~CItem();
};

