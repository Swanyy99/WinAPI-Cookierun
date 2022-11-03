#pragma once

// 리소스 : 게임에 필요한 코드 외의 자원
// ex) 이미지, 사운드, 등
class CResource
{
public:
	CResource();
	virtual ~CResource();

protected:
	wstring m_strKey;		// 리소스의 탐색용 키
	wstring m_strPath;		// 리소스의 경로

public:
	void SetKey(const wstring& key);
	void SetPath(const wstring& path);

public:
	const wstring& GetKey();
	const wstring& GetPath();
};
