#pragma once
#include "CUI.h"
#include "CFactory2.h"
#include "CInventoryUI.h"
class CItemPocketUI : public CUI
{
public:// Get
    int GetIndex()const { return m_iIndex; }
public:// Set
    int SetIndex(const int _i) { m_iIndex = _i; return 0; }
public: // Logic
    virtual int Update()                override;
    virtual int Render(const HDC _dc)   override;
    virtual int FinalUpdate()           override;
private:
    BITMAP CreateSkinComponent();
    int m_iIndex;
private:// Constructor
    friend class CInventoryUI;
    CItemPocketUI();
    int Setting(const int _x,const int _y);
public:
    virtual ~CItemPocketUI();
};

