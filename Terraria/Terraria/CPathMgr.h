#pragma once



class CPathMgr
{
	SINGLE(CPathMgr);
public:
	void Init();
	// GetFilePath
	const wchar_t* GetContentPath() { return m_szContentPath; }
private:
	// File Path wchar_t
	wchar_t m_szContentPath[255];
};

