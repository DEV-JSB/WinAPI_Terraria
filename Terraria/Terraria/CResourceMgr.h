#pragma once

class CResource;
class CTexture;

class CResourceMgr
{
public:
	BITMAP GetTextureSize(const wstring& _strKey);
	CTexture* LoadTexture(const wstring& _strKey,const wstring& _strRelativePath);
	CTexture* FindTexture(const wstring& _strKey);
public:
	int Release();
private:
	SINGLE(CResourceMgr);
private:
	map<wstring, CResource*> m_mapResource;
};

