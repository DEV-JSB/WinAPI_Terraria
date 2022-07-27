#pragma once
class CScene
{
protected:
	CScene();
	virtual ~CScene();
public:
	virtual int Render(const HDC _hdc) = 0;
	virtual int Update()			   = 0;
};

