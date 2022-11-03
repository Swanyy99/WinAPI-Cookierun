#include "framework.h"
#include "CPanel.h"

#include "CRenderManager.h"
#include "CInputManager.h"

CPanel::CPanel()
{
	m_vecDragStartPos = Vector(0, 0);
	m_bIsDragging = false;
	m_bDraggable = true;
}

CPanel::~CPanel()
{
}

bool CPanel::GetDraggable()
{
    return m_bDraggable;
}

void CPanel::SetDraggable(bool draggable)
{
	m_bDraggable = draggable;
}

void CPanel::Init()
{
}

void CPanel::Render()
{
	RENDER->FillRect(
		m_vecRenderPos.x,
		m_vecRenderPos.y,
		m_vecRenderPos.x + m_vecScale.x,
		m_vecRenderPos.y + m_vecScale.y,
		Color(255, 255, 255, 1)
	);

	RENDER->FrameRect(
		m_vecRenderPos.x,
		m_vecRenderPos.y,
		m_vecRenderPos.x + m_vecScale.x,
		m_vecRenderPos.y + m_vecScale.y,
		Color(0, 0, 0, 1)
	);
}

void CPanel::Update()
{
}

void CPanel::Release()
{
}

void CPanel::OnMouseEnter()
{
}

void CPanel::OnMouseOver()
{
	if (m_bIsDragging)
	{
		Vector vecDiff = MOUSESCREENPOS - m_vecDragStartPos;
		m_vecPos += vecDiff;
		m_vecDragStartPos = MOUSESCREENPOS;

		// 부모 UI가 있는 경우 부모 UI를 벗어나지 못하도록 위치이동 제한
		if (m_pParentUI != nullptr)
		{
			if (m_vecPos.x < 0)
				m_vecPos.x = 0;
			else if (m_vecPos.x + m_vecScale.x > m_pParentUI->GetScale().x)
				m_vecPos.x = m_pParentUI->GetScale().x - m_vecScale.x;

			if (m_vecPos.y < 0)
				m_vecPos.y = 0;
			else if (m_vecPos.y + m_vecScale.y > m_pParentUI->GetScale().y)
				m_vecPos.y = m_pParentUI->GetScale().y - m_vecScale.y;
		}
	}
}

void CPanel::OnMouseExit()
{
	m_bIsDragging = false;
}

void CPanel::OnMouseUp()
{
	m_bIsDragging = false;
}

void CPanel::OnMouseDown()
{
	m_vecDragStartPos = MOUSESCREENPOS;
	m_bIsDragging = m_bDraggable;
}

void CPanel::OnMouseClicked()
{
}
