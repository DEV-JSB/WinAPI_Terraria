#pragma once

class CResource;
class CTexture;

class CResourceMgr
{
public:
	CTexture* LoadTexture(const wstring& _strKey,const wstring& _strRelativePath);
	CTexture* FindTexture(const wstring& _strKey);
private:
	SINGLE(CResourceMgr);
private:
	map<wstring, CResource*> m_mapResource;
};

