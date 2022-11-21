#pragma once
#include "CGameObject.h"

class CUIManager;

class CUI : public CGameObject
{
	friend CUIManager;
public:
	CUI();
	virtual ~CUI();

protected:
	list<CUI*>	m_listChildUI;		// 자식 UI들을 보관할 자료구조
	CUI*		m_pParentUI;		// 부모 UI

	// Vector	m_vecPos;			// 부모를 기준으로한 상대 위치
	Vector		m_vecAbsolutePos;	// 게임에서의 절대 위치
	Vector		m_vecRenderPos;		// 게임에서의 그려질 위치
	bool		m_bScreenFixed;		// 화면 고정 여부

	bool		m_bPrevMouseOn;		// UI가 이전 프레임에 마우스가 올려진 여부
	bool		m_bCurMouseOn;		// UI가 현재 프레임에 마우스가 올려진 여부
	bool		m_bPrevDown;		// UI가 이전 프레임에 눌렸는지 여부
	bool		m_bCurDown;			// UI가 현재 프레임에 눌렸는지 여부

public:
	CUI* GetParentUI();
	void AddChildUI(CUI* pChildUI);

	bool GetScreenFixed();
	void SetScreenFixed(bool fixed);

protected:
	void MouseOnCheck();

protected:
	// UI 부모 전용 함수들 :
	// UI에 있는 모든 자식 UI를 갱신
	void GameObjectInit() override;
	void GameObjectUpdate() override;
	void GameObjectRender() override;
	void GameObjectRelease() override;

	// UI의 마우스 이벤트 재정의하여 기능 구현
	virtual void OnMouseEnter() = 0;
	virtual void OnMouseOver() = 0;
	virtual void OnMouseExit() = 0;
	virtual void OnMouseUp() = 0;
	virtual void OnMouseDown() = 0;
	virtual void OnMouseClicked() = 0;
};

