#include "framework.h"
#include "CPathManager.h"

CPathManager::CPathManager()
{
}

CPathManager::~CPathManager()
{
}

void CPathManager::Init()
{
	WCHAR path[255] = {};				// 경로를 받기 위한 문자열
	GetCurrentDirectory(255, path);		// 현재 경로를 확인
	m_strPath = wstring(path);			// 문자열을 wstring 으로 변환
	m_strPath += L"\\Resource\\";		// 경로뒤에 리소스 폴더를 추가

	Logger::Debug(L"현재 경로");
	Logger::Debug(m_strPath);
}

void CPathManager::Release()
{
}

const wstring& CPathManager::GetPath()
{
	return m_strPath;
}
