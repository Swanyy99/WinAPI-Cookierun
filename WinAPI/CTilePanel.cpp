#include "framework.h"
#include "CTilePanel.h"

#include "CResourceManager.h"
#include "CRenderManager.h"
#include "CSceneManager.h"

#include "CSceneTileTool.h"
#include "CTileButton.h"
#include "CImage.h"
#include "CTile.h"

CTilePanel::CTilePanel()
{
	m_pImage = nullptr;
	m_uiTilePage = 0;
	m_uiPaletteX = 0;
	m_uiPaletteY = 0;
	m_uiTileCountX = 0;
	m_uiTileCountY = 0;

	m_uiMenuHeight = 200;
}

CTilePanel::~CTilePanel()
{
}

void CTilePanel::CreateTilePalette()
{
	m_pImage = RESOURCE->LoadImg(L"Time", L"Image\\Tile.png");
	m_uiTileCountX = m_pImage->GetWidth() / CTile::TILESIZE;
	m_uiTileCountY = m_pImage->GetHeight() / CTile::TILESIZE;

	m_uiPaletteX = (int)(m_vecScale.x / CTile::TILESIZE);
	m_uiPaletteY = (int)((m_vecScale.y - m_uiMenuHeight) / CTile::TILESIZE);
	int marginX = ((int)m_vecScale.x % CTile::TILESIZE) / 2;
	int marginY = ((int)m_vecScale.y % CTile::TILESIZE) / 2;

	for (UINT y = 0; y < m_uiPaletteY; y++)
	{
		for (UINT x = 0; x < m_uiPaletteX; x++)
		{
			CTileButton* pTileButton = new CTileButton;
			pTileButton->SetImage(m_pImage);
			pTileButton->SetPos(Vector((float)x * CTile::TILESIZE, (float)y * CTile::TILESIZE));
			pTileButton->SetPos(Vector(pTileButton->GetPos() + Vector((float)marginX, (float)marginY)));
			AddChildUI(pTileButton);
			m_vecTileButton.push_back(pTileButton);
		}
	}
}

void CTilePanel::CreatePageButton()
{
	auto prevClick = [](DWORD_PTR tilePanel, DWORD_PTR)
	{
		CTilePanel* pTilePanel = (CTilePanel*)tilePanel;
		pTilePanel->SetPrevPage();
	};

	CButton* pPrevButton = new CButton;
	pPrevButton->SetScale(50.f, 30);
	pPrevButton->SetPos(Vector(10.f,
		(float)(m_vecScale.y - m_uiMenuHeight)));
	pPrevButton->SetText(L"<-");
	pPrevButton->SetClickedCallback(prevClick, (DWORD_PTR)this, (DWORD_PTR)0);
	AddChildUI(pPrevButton);

	auto nextClick = [](DWORD_PTR tilePanel, DWORD_PTR)
	{
		CTilePanel* pTilePanel = (CTilePanel*)tilePanel;
		pTilePanel->SetNextPage();
	};
	CButton* pNextButton = new CButton;
	pNextButton->SetScale(50.f, 30);
	pNextButton->SetPos(Vector((float)(m_vecScale.x - 60.f),
		(float)(m_vecScale.y - m_uiMenuHeight)));
	pPrevButton->SetText(L"->");
	pNextButton->SetClickedCallback(nextClick, (DWORD_PTR)this, (DWORD_PTR)0);
	AddChildUI(pNextButton);
}

void CTilePanel::CreateTileTypeButton()
{
	auto click = [](DWORD_PTR tileTool, DWORD_PTR tileType)
	{
		CSceneTileTool* pTileTool = (CSceneTileTool*)tileTool;
		pTileTool->ClickTileType((TypeTile)tileType);
	};

	CScene* pScene = SCENE->GetCurScene();
	CSceneTileTool* pTileToolScene = (CSceneTileTool*)pScene;

	CButton* pNoneTypeButton = new CButton;
	pNoneTypeButton->SetScale(100.f, 50.f);
	pNoneTypeButton->SetPos(Vector(10.f, m_vecScale.y - 100.f));
	pNoneTypeButton->SetText(L"None");
	pNoneTypeButton->SetClickedCallback(click, (DWORD_PTR)pTileToolScene, (DWORD_PTR)TypeTile::None);
	AddChildUI(pNoneTypeButton);

	CButton* pGroundTypeButton = new CButton;
	pGroundTypeButton->SetScale(100.f, 50.f);
	pGroundTypeButton->SetPos(Vector(150.f, m_vecScale.y - 100.f));
	pGroundTypeButton->SetText(L"Ground");
	pGroundTypeButton->SetClickedCallback(click, (DWORD_PTR)pTileToolScene, (DWORD_PTR)TypeTile::Ground);
	AddChildUI(pGroundTypeButton);
} 

void CTilePanel::SetPage(UINT page)
{
	for (UINT i = 0; i < m_vecTileButton.size(); i++)
	{
		auto clicked = [](DWORD_PTR tilePanel, DWORD_PTR index)
		{
			CScene* pScene = SCENE->GetCurScene();
			CSceneTileTool* pTileToolScene = (CSceneTileTool*)pScene;
			UINT tileIndex = (UINT)index;

			pTileToolScene->ClickTileButton(tileIndex);
		};

		UINT tileIndex = i + m_uiTilePage * (UINT)m_vecTileButton.size();
		m_vecTileButton[i]->SetTileIndex(tileIndex);
		m_vecTileButton[i]->SetClickedCallback(clicked, (DWORD_PTR)this, (DWORD_PTR)tileIndex);
	}
}

void CTilePanel::SetPrevPage()
{
	if (m_uiTilePage <= 0)
		return;
	SetPage(--m_uiTilePage);
}

void CTilePanel::SetNextPage()
{
	UINT tileCount = m_uiTileCountX * m_uiTileCountY;
	if (m_uiTilePage >= tileCount / m_vecTileButton.size())
		return;
	SetPage(++m_uiTilePage);
}

void CTilePanel::Init()
{
	CreateTilePalette();
	CreatePageButton();
	CreateTileTypeButton();
	SetPage(0);
}

void CTilePanel::Update()
{
}

void CTilePanel::Render()
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

void CTilePanel::Release()
{
}
