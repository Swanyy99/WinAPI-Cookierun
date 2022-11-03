#pragma once
#include "CResource.h"

class CRenderManager;
class CResourceManager;
struct ID2D1Bitmap;

class CImage : public CResource
{
	friend CRenderManager;
	friend CResourceManager;
private:
	ID2D1Bitmap* m_pBitmap;

public:
	CImage();
	virtual ~CImage();

	int GetWidth();
	int GetHeight();

public:
	ID2D1Bitmap* GetImage();
	void Load(const wstring& filePath);
};

