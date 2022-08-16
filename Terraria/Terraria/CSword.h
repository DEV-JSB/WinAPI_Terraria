#pragma once
#include "CTool.h"
#include "CFactory2.h"
class CSword : public CTool
{
public: // Logic
	virtual int Render(const HDC _dc)	override;
	virtual int Update()				override;
private:
	friend class CFactory2;
	CSword();
public:
	virtual ~CSword();
};

