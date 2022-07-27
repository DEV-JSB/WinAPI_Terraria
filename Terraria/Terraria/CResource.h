#pragma once


class CResource
{
public:
	// SetKey and Path
	int SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	int SetPath(const wstring& _strPath) { m_strRelativePath = _strPath; }

	// Get Key and Path
	const wstring& GetKey()const { return m_strKey; }
	const wstring& GetPath()const { return m_strRelativePath; }

private:
	// Resource Key
	wstring m_strKey;
	// Resource Path
	wstring m_strRelativePath;
};

