#include "framework.h"
#include "CUI.h"

#include "CCameraManager.h"
#include "CInputManager.h"

CUI::CUI()
{
	m_layer = Layer::Ui;
	m_pParentUI = nullptr;

	m_vecAbsolutePos = Vector(0, 0);
	m_vecRenderPos = Vector(0, 0);
	m_bScreenFixed = true;

	m_bPrevMouseOn	= false;
	m_bCurMouseOn	= false;
	m_bPrevDown		= false;
	m_bCurDown		= false;
}

CUI::~CUI()
{
}

CUI* CUI::GetParentUI()
{
	return m_pParentUI;
}

void CUI::AddChildUI(CUI* pChildUI)
{
	m_listChildUI.push_back(pChildUI);
	pChildUI->m_pParentUI = this;
	pChildUI->SetScreenFixed(m_bScreenFixed);
}

bool CUI::GetScreenFixed()
{
	return m_bScreenFixed;
}

void CUI::SetScreenFixed(bool fixed)
{
	m_bScreenFixed = fixed;
}

void CUI::MouseOnCheck()
{
	Vector mousePos = MOUSESCREENPOS;
	Vector uiPos = CAMERA->WorldToScreenPoint(m_vecRenderPos);

	if (uiPos.x <= mousePos.x && mousePos.x <= uiPos.x + m_vecScale.x
		&& uiPos.y <= mousePos.y && mousePos.y <= uiPos.y + m_vecScale.y)
	{
		m_bCurMouseOn = true;
	}
	else
	{
		m_bCurMouseOn = false;
	}
}

void CUI::GameObjectInit()
{
	Init();

	for (CUI* pUI : m_listChildUI)
	{
		pUI->GameObjectInit();
	}
}

void CUI::GameObjectUpdate()
{
	Update();

	// 자식 UI의 위치는 부모를 기준으로 설정
	// 부모 UI가 위치 이동이 있을 경우 자식도 같이 이동
	m_vecAbsolutePos = m_vecPos;

	if (nullptr != GetParentUI())
		m_vecAbsolutePos += GetParentUI()->m_vecAbsolutePos;

	if (m_bScreenFixed)
		m_vecRenderPos = CAMERA->ScreenToWorldPoint(m_vecAbsolutePos);
	else
		m_vecRenderPos = m_vecAbsolutePos;

	for (CUI* pUI : m_listChildUI)
	{
		pUI->GameObjectUpdate();
	}

	MouseOnCheck();
}

void CUI::GameObjectRender()
{
	Render();

	for (CUI* pUI : m_listChildUI)
	{
		pUI->GameObjectRender();
	}
}

void CUI::GameObjectRelease()
{
	for (CUI* pUI : m_listChildUI)
	{
		pUI->GameObjectRelease();
		delete pUI;
	}

	Release();
}
