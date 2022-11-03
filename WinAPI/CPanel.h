#pragma once
#include "CUI.h"
class CPanel : public CUI
{
public:
	CPanel();
	virtual ~CPanel();

private:
	Vector	m_vecDragStartPos;
	bool	m_bIsDragging;
	bool	m_bDraggable;

public:
	bool GetDraggable();
	void SetDraggable(bool draggable);

private:
	void Init() override;
	void Render() override;
	void Update() override;
	void Release() override;

	void OnMouseEnter() final;
	void OnMouseOver() final;
	void OnMouseExit() final;
	void OnMouseUp() final;
	void OnMouseDown() final;
	void OnMouseClicked() final;
};

