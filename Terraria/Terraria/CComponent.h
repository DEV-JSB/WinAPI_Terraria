#pragma once
class CComponent
{

public:// CComponent Logic
	virtual int Render(const HDC _dc)const = 0;
	virtual int Update()					= 0;
	virtual int FinalUpdate()				= 0;
protected:
	bool m_bRender;
protected: // construction Nedd Acces SubClass
	CComponent(bool _wiilRender);
public:
	virtual ~CComponent();
};

