#pragma once
class CComponent
{

public:// CComponent Logic
	virtual int Render(const HDC _hdc) = 0;
	virtual int Update(const HDC _hdc) = 0;
	virtual int FinalUpdate(const HDC _hdc) = 0;

protected:
	bool m_bRender;
protected: // construction Nedd Acces SubClass
	CComponent(bool _wiilRender);
public:
	virtual ~CComponent();
};

