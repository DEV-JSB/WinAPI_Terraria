#pragma once
#include "CObject.h"
#include"CFactory.h"

class CUI :
    public CObject
{
public:

    CUI* GetParent()const { return m_pParent; }
    // Add Chid UI and Set Parent Point
    int AddChild(CUI* _pChild);
   

public:

    virtual int Update()        override;
    virtual int Render(const HDC _dc) override;
    virtual int FinalUpdate() override;

public: // Child Update Logic

    int Update_Child();
    int Render_Child(const HDC _dc);
    int FinalUpdate_Child();
    
private: 
    
    // Have Many Child UI  
    vector<CUI*> m_vecChildUI;
    // Parent UI
    CUI* m_pParent;
    // Culculate relative Position
    Vector3 m_vOffsetPos;

private: //Factory
    friend class CFactory<CUI>;
private: //Construct
    CUI(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale);
    CUI();
public:
    virtual ~CUI();
};

