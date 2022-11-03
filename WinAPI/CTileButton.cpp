#include "framework.h"
#include "CTileButton.h"

#include "CRenderManager.h"

#include "CImage.h"
#include "CTile.h"

CTileButton::CTileButton()
{
	m_vecScale = Vector(CTile::TILESIZE, CTile::TILESIZE);

	m_pImage = nullptr;
	m_uiTileIndex = 0;

	m_imageWidth = 0;
	m_imageHeight = 0;
	m_iCountX = 0;
	m_iCountY = 0;
	m_iTileX = 0;
	m_iTileY = 0;
}

CTileButton::~CTileButton()
{
}

CImage* CTileButton::GetImage()
{
	return m_pImage;
}

void CTileButton::SetImage(CImage* pImage)
{
	m_pImage = pImage;

	m_imageWidth = m_pImage->GetWidth();
	m_imageHeight = m_pImage->GetHeight();

	m_iCountX = m_imageWidth / CTile::TILESIZE;
	m_iCountY = m_imageHeight / CTile::TILESIZE;

	m_iTileX = m_uiTileIndex % m_iCountY;
	m_iTileY = m_uiTileIndex / m_iCountY;
}

UINT CTileButton::GetTileIndex()
{
    return m_uiTileIndex;
}

void CTileButton::SetTileIndex(UINT index)
{
	m_uiTileIndex = index;

	m_imageWidth = m_pImage->GetWidth();
	m_imageHeight = m_pImage->GetHeight();

	m_iCountX = m_imageWidth / CTile::TILESIZE;
	m_iCountY = m_imageHeight / CTile::TILESIZE;

	m_iTileX = m_uiTileIndex % m_iCountX;
	m_iTileY = m_uiTileIndex / m_iCountX;
}

void CTileButton::Init()
{
}

void CTileButton::Render()
{
	RENDER->FrameRect(
		m_vecRenderPos.x,
		m_vecRenderPos.y,
		m_vecRenderPos.x + m_vecScale.x,
		m_vecRenderPos.y + m_vecScale.y,
		Color(0, 0, 0, 1)
	);

	// 0번 타일은 빈타일로 정의
	if (0 == m_uiTileIndex)
		return;

	if (nullptr != m_pImage)
	{
		RENDER->FrameImage(
			m_pImage,
			m_vecRenderPos.x,
			m_vecRenderPos.y,
			m_vecRenderPos.x + m_vecScale.x,
			m_vecRenderPos.y + m_vecScale.y,
			(float)(m_iTileX * CTile::TILESIZE),
			(float)(m_iTileY * CTile::TILESIZE),
			(float)((m_iTileX + 1) * CTile::TILESIZE),
			(float)((m_iTileY + 1) * CTile::TILESIZE)
		);
	}
	else
	{
		RENDER->FillRect(
			m_vecRenderPos.x,
			m_vecRenderPos.y,
			m_vecRenderPos.x + m_vecScale.x,
			m_vecRenderPos.y + m_vecScale.y,
			Color(255, 255, 255, 1)
		);
	}
}

void CTileButton::Update()
{
}

void CTileButton::Release()
{
}
