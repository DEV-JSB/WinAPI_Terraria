#pragma once

class CScene;

class CSceneMgr
{
public://Get
	SCENE GetType()const;
	// Return ObjectGroup in CurrentScene
	const vector<CObject*> GetObjectGroup(const OBJECT _eType);
public: // Logic
	int FinalUpdate();
	int Update();
	int Render(HDC _dc);
	int Init();
	int Release();
public:
	int SetCurScene(CScene* _pScene) { m_pCurScene = _pScene; }
	CScene* GetCurScene()const { return m_pCurScene; }
private:
	CScene* m_pCurScene;
private:
	SINGLE(CSceneMgr);

};

