#include "framework.h"
#include "CUnderUI.h"


CUnderUI::CUnderUI()
{
	m_layer = Layer::UnderUi;
	m_strName = L"Ui";
	PauseImage = nullptr;
	FailImage = nullptr;
}

CUnderUI::~CUnderUI()
{
}

void CUnderUI::Init()
{
	PauseImage = RESOURCE->LoadImg(L"PauseImage", L"Image\\Pause.png");

	Loading = RESOURCE->LoadImg(L"Loading", L"Image\\Loading.png");

	FailImage = RESOURCE->LoadImg(L"PauseImage", L"Image\\Fail.png");

	CookierunTitle = RESOURCE->LoadImg(L"CookierunTitle", L"Image\\CookierunTitle.png");

	PrepareScene = RESOURCE->LoadImg(L"PrepareScenePetChoice", L"Image\\PrepareScenePetChoice.png");

	slideImage = RESOURCE->LoadImg(L"SlideButton1", L"Image\\Idle_Slide.png");

	jumpImage = RESOURCE->LoadImg(L"JumpButton1", L"Image\\Idle_Jump.png");

	HPIcon = RESOURCE->LoadImg(L"HpIcon", L"Image\\Hp_Icon.png");

	HPEffect = RESOURCE->LoadImg(L"HpEffect", L"Image\\Hp_Effect.png");

	HPBar = RESOURCE->LoadImg(L"HpBar", L"Image\\Hp_Bar.png");

	HPBackBar = RESOURCE->LoadImg(L"HpBackBar", L"Image\\Hp_BackBar.png");

	HPProgressBar = RESOURCE->LoadImg(L"HpProgressBar", L"Image\\Hp_ProgressBar.png");

}

void CUnderUI::Update()
{
}

void CUnderUI::Render()
{
	RENDER->Image(
		Image,
		m_vecPos.x, m_vecPos.y, m_vecScale.x, m_vecScale.y);
}

void CUnderUI::Release()
{
}

void CUnderUI::OnMouseEnter()
{
}

void CUnderUI::OnMouseOver()
{
}

void CUnderUI::OnMouseExit()
{
}

void CUnderUI::OnMouseUp()
{
}

void CUnderUI::OnMouseDown()
{
}

void CUnderUI::OnMouseClicked()
{
}

CImage CUnderUI::GetPauseImage()
{
	return *PauseImage;
}

void CUnderUI::SetPauseImage(CImage* target)
{
	target = PauseImage;
}

void CUnderUI::SetImageName(const wstring& name)
{
	ImageName = name;
	Image = RESOURCE->LoadImg(ImageName, L"Image\\" + ImageName);
}

void CUnderUI::SetUI()
{
	
}
