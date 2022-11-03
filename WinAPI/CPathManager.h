#pragma once

class CCore;

class CPathManager : public SingleTon<CPathManager>
{
	friend SingleTon<CPathManager>;
	friend CCore;
private:
	wstring m_strPath;

	CPathManager();
	virtual ~CPathManager();

	void Init();
	void Release();

public:
	const wstring& GetPath();
};

#define PATH	CPathManager::GetInstance()
#define GETPATH	CPathManager::GetInstance()->GetPath()