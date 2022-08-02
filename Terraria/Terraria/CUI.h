#pragma once
#include "CObject.h"

class CUI : public CObject
{
public:
    
    //SetFocus
    int SetFocus(const bool _b) { m_bIsFocus = _b; return 0; };

    CUI* GetParent()const { return m_pParent; }
    // Add Chid UI and Set Parent Point
    int AddChild(CUI* _pChild);
    // Get UI Type
    virtual UI_TYPE GetType() { return m_eType; };
    
    // Get UI Group
    const vector<CUI*>& GetUIGroup(const UI_TYPE _type)
    {
        return m_vecChildUI[(int)_type]; 
    };

public:

    virtual int Update()        override;
    virtual int Render(const HDC _dc) override;
    virtual int FinalUpdate() override;
    // Child Function
    virtual int MouseButtonClicked() { return 0; };
public:
    int Release();
private: // Child Update Logic

    int Update_Child();
    int Render_Child(const HDC _dc);
    int FinalUpdate_Child();

protected:
    // IsFocusing
    bool m_bIsFocus;
    // Parent UI
    CUI* m_pParent;
    // Culculate relative Position
    Vector3 m_vOffsetPos;
    //Is Affected Camera?
    bool m_bCamAffected;
    // UI Type
    UI_TYPE m_eType;
private:
    // Have Many Child UI  
    vector<CUI*> m_vecChildUI[(int)UI_TYPE::UI_END];
protected: //Construct
    friend class CFactory<CUI>;
    CUI(const Vector3 _pos, const Vector3 _rot, const Vector2 _scale, bool _bAffected);
    CUI(const bool _bAffected);
public:
    virtual ~CUI();
};

