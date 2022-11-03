#pragma once
#include "CButton.h"

class CImage;

class CTileButton : public CButton
{
public:
	CTileButton();
	virtual ~CTileButton();

private:
	CImage*	m_pImage;
	UINT	m_uiTileIndex;

	int		m_imageWidth;
	int		m_imageHeight;
	int		m_iCountX;
	int		m_iCountY;
	int		m_iTileX;
	int		m_iTileY;

public:
	CImage* GetImage();
	void SetImage(CImage* pImage);

	UINT GetTileIndex();
	void SetTileIndex(UINT index);

private:
	void Init() override;
	void Render() override;
	void Update() override;
	void Release() override;
};

