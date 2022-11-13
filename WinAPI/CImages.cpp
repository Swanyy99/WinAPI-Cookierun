#include "framework.h"
#include "CImages.h"


CImages::CImages()
{
	m_layer = Layer::UnderUi;
	m_strName = L"Ui";
	PauseImage = nullptr;
	FailImage = nullptr;
}

CImages::~CImages()
{
}

void CImages::Init()
{
	PauseImage = RESOURCE->LoadImg(L"PauseImage", L"Image\\Pause.png");
	FailImage = RESOURCE->LoadImg(L"PauseImage", L"Image\\Fail.png");


}

void CImages::Update()
{
}

void CImages::Render()
{
	RENDER->Image(
		Image,
		m_vecPos.x, m_vecPos.y, m_vecScale.x, m_vecScale.y);
}

void CImages::Release()
{
}

CImage CImages::GetPauseImage()
{
	return *PauseImage;
}

void CImages::SetPauseImage(CImage* target)
{
	target = PauseImage;
}

void CImages::SetImageName(const wstring& name)
{
	ImageName = name;
	Image = RESOURCE->LoadImg(ImageName, L"Image\\" + ImageName);
}
