#pragma once

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);
public:
	int SetCurScene(CScene* _pScene) { m_pCurScene = _pScene; }

private:
	CScene* m_pCurScene;
};

