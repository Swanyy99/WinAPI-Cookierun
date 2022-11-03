#include "framework.h"
#include "CImageObject.h"

#include "CRenderManager.h"

#include "CImage.h"

CImageObject::CImageObject()
{
	m_pImage = nullptr;
}

CImageObject::~CImageObject()
{
}

CImage* CImageObject::GetIamge()
{
    return m_pImage;
}

void CImageObject::SetImage(CImage* pImage)
{
	m_pImage = pImage;
}

void CImageObject::Init()
{
}

void CImageObject::Update()
{
}

void CImageObject::Render()
{
	if (nullptr != m_pImage)
	{
		RENDER->Image(
			m_pImage,
			0,
			0,
			(float)m_pImage->GetWidth(),
			(float)m_pImage->GetHeight()
		);
	}
}

void CImageObject::Release()
{
}
