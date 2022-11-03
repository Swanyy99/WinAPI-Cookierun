#pragma once
#include "CPanel.h"

class CTileButton;
class CImage;

class CTilePanel : public CPanel
{
public:
	CTilePanel();
	virtual ~CTilePanel();

private:
	CImage* m_pImage;
	vector<CTileButton*> m_vecTileButton;

	UINT m_uiMenuHeight;

	UINT m_uiTilePage;
	UINT m_uiPaletteX;
	UINT m_uiPaletteY;
	UINT m_uiTileCountX;
	UINT m_uiTileCountY;

private:
	void CreateTilePalette();
	void CreatePageButton();
	void CreateTileTypeButton();
	void SetPage(UINT page);
	void SetPrevPage();
	void SetNextPage();

private:
	void Init();
	void Update();
	void Render();
	void Release();
};

