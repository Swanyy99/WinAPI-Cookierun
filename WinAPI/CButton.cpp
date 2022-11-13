#include "framework.h"
#include "CButton.h"

#include "CRenderManager.h"

extern bool pause;
extern bool inTitle;
extern bool isDead;


CButton::CButton()
{
	m_pCallback = nullptr;
	m_pParam1 = 0;
	m_pParam2 = 0;

	m_strText = L"";
	m_iSizeText = 12;
	m_colorText = Color(0, 0, 0, 1);

	isMouseOver = false;

	m_buttonImage = RESOURCE->LoadImg(L"ButtonImage", L"Image\\ButtonImage.png");
	m_buttonImageMouseOver = RESOURCE->LoadImg(L"ButtonImageMouseOver", L"Image\\ButtonImageMouseOver.png");

}

CButton::~CButton()
{
}

void CButton::SetClickedCallback(CallbackFunc pCallback, DWORD_PTR pParam1, DWORD_PTR pParam2)
{
	
	m_pCallback = pCallback;
	m_pParam1 = pParam1;
	m_pParam2 = pParam2;
	
}

void CButton::SetText(const wstring& text, float fontSize, Color color)
{
	m_strText = text;
	m_iSizeText = fontSize;
	m_colorText = color;
}

void CButton::SetImage(const wstring& image, const wstring& mouseOverImage)
{
	m_strImageName = image;
	m_buttonImage = RESOURCE->LoadImg(m_strImageName, L"Image\\" + m_strImageName);
	m_buttonImageMouseOver = RESOURCE->LoadImg(m_strImageName, L"Image\\" + m_strImageName);
}

void CButton::Init()
{
}

void CButton::Update()
{
	//SetClickedCallback(m_pCallback, m_pParam1, m_pParam2);
}

void CButton::Render()
{
	if (pause == true || inTitle == true || isDead == true)
	{
		if (isMouseOver == false)
		{
			RENDER->Image(
				m_buttonImage,
				m_vecRenderPos.x,
				m_vecRenderPos.y,
				m_vecRenderPos.x + m_vecScale.x,
				m_vecRenderPos.y + m_vecScale.y);
		}

		else if (isMouseOver == true)
		{
			RENDER->Image(
				m_buttonImageMouseOver,
				m_vecRenderPos.x,
				m_vecRenderPos.y,
				m_vecRenderPos.x + m_vecScale.x,
				m_vecRenderPos.y + m_vecScale.y);
		}

		RENDER->Text(
			m_strText,
			m_vecRenderPos.x,
			m_vecRenderPos.y,
			m_vecRenderPos.x + m_vecScale.x,
			m_vecRenderPos.y + m_vecScale.y,
			m_colorText,
			m_iSizeText
		);

	}
		
}

void CButton::Release()
{
}

void CButton::OnMouseEnter()
{
}

void CButton::OnMouseOver()
{
	isMouseOver = true;
}

void CButton::OnMouseExit()
{
	isMouseOver = false;
}

void CButton::OnMouseUp()
{
}

void CButton::OnMouseDown()
{
	
	if (nullptr != m_pCallback)
		m_pCallback(m_pParam1, m_pParam2);
	
}

void CButton::OnMouseClicked()
{
}
