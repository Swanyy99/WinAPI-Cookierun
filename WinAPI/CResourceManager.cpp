#include "framework.h"
#include "CResourceManager.h"

#include "CPathManager.h"
#include "CImage.h"
#include "CSound.h"

CResourceManager::CResourceManager()
{
}

CResourceManager::~CResourceManager()
{
}

CImage* CResourceManager::FindImg(const wstring& key)
{
	auto iter = m_umapImage.find(key);
	if (iter == m_umapImage.end())
		return nullptr;
	else
		return m_umapImage[key];
}

CImage* CResourceManager::LoadImg(const wstring& key, const wstring& fileName)
{
	CImage* pImage = FindImg(key);
	if (nullptr != pImage)
		return pImage;

	wstring filePath = GETPATH + fileName;
	pImage = new CImage;
	pImage->Load(filePath);
	pImage->SetKey(key);
	pImage->SetPath(filePath);
	m_umapImage.insert(make_pair(key, pImage));

	return pImage;
}

CImage* CResourceManager::LoadImgWithPath(const wstring& key, const wstring& path)
{
	CImage* pImage = FindImg(key);
	if (nullptr != pImage)
		return pImage;

	wstring filePath = path;
	pImage = new CImage;
	pImage->Load(filePath);
	pImage->SetKey(key);
	pImage->SetPath(filePath);
	m_umapImage.insert(make_pair(key, pImage));

	return pImage;
}

CSound* CResourceManager::FindSound(const wstring& key)
{
	auto iter = m_umapSound.find(key);
	if (iter == m_umapSound.end())
		return nullptr;
	else
		return m_umapSound[key];
}

CSound* CResourceManager::LoadSound(const wstring& key, const wstring& fileName)
{
	CSound* pSound = FindSound(key);
	if (nullptr != pSound)
		return pSound;

	wstring filePath = GETPATH + fileName;
	pSound = new CSound;
	pSound->Load(filePath);
	pSound->SetKey(key);
	pSound->SetPath(filePath);
	m_umapSound.insert(make_pair(key, pSound));

	return pSound;
}

void CResourceManager::Init()
{
}

void CResourceManager::Release()
{
	for (pair<wstring, CImage*> image : m_umapImage)
	{
		delete image.second;
	}
	m_umapImage.clear();

	for (pair<wstring, CSound*> sound : m_umapSound)
	{
		delete sound.second;
	}
	m_umapSound.clear();
}
