#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);
public: // Logic
	int Update();
	int Render(HDC _hdc);
	int Enter();
	int Init();
	int Release();
public:
	int SetCurScene(CScene* _pScene) { m_pCurScene = _pScene; }
	CScene* GetCurScene()const { return m_pCurScene; }
private:
	CScene* m_pCurScene;
};

