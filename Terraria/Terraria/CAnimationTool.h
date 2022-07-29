#pragma once
#include"CScene.h"
#include"CFactory.h"

class CAnimation;
class CTexture;

class CAnimationTool : public CScene
{
public:
	// Setting FileName
	int SetOpenFileName(const wstring& _Key) { m_strFileName = _Key; return 0; };
public:
	// Delete Object
	virtual int Release()			   override;
	// Rendering
	virtual int Render(const HDC _hdc) override;
	// Update Scene
	virtual int Update()			   override;
	virtual int Enter()				   override;

private:// Member
	wstring m_strFileName;
	
	// Will MakeAnimation
	CAnimation* m_pWillMake;

	// Will Load Texture
	CTexture* m_pTexture;

private: // Constructor
	friend class CFactory<CAnimationTool>;
	CAnimationTool();
public:
	virtual ~CAnimationTool();
};

