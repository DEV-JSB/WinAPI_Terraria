#pragma once

class CObject;


class CScene
{
public:
	const vector<CObject*> GetObjectGroup(const OBJECT _type) { return m_arrObjectVec[(int)_type]; }
public:
	virtual int Release()              = 0;
	virtual int Render(const HDC _hdc) = 0;
	virtual int Update()			   = 0;
	virtual int Enter()				   = 0;
protected:
	// ObjectVector
	std::vector<CObject*> m_arrObjectVec[(int)OBJECT::OBJECT_END];
protected:
	CScene();
	virtual ~CScene();
};

