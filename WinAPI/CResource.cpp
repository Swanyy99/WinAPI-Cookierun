#include "framework.h"
#include "CResource.h"

CResource::CResource()
{
}

CResource::~CResource()
{
}

const wstring& CResource::GetKey()
{
	return m_strKey;
}

void CResource::SetKey(const wstring& key)
{
	m_strKey = key;
}

const wstring& CResource::GetPath()
{
	return m_strPath;
}

void CResource::SetPath(const wstring& path)
{
	m_strPath = path;
}