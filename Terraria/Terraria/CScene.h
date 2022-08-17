#pragma once

class CObject;
class CPlayer;

class CScene
{
public: // Get
	// Return Type
	SCENE GetSceneType()const { return m_eType; }
	// Return ObjectGroup
	const vector<CObject*> GetObjectGroup(const OBJECT _type) { return m_arrObjectVec[(int)_type]; }
	CPlayer* GetPlayer()const;
public:
	virtual int FinalUpdate()			= 0;
	virtual int Release()				= 0;
	virtual int Render(const HDC _dc)	= 0;
	virtual int Update()				= 0;
	virtual int Enter()					= 0;
protected:
	// ObjectVector
	std::vector<CObject*> m_arrObjectVec[(int)OBJECT::OBJECT_END];
protected:
	CScene();
protected:
	SCENE m_eType;
public:
	virtual ~CScene();
};

