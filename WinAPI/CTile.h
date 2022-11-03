#pragma once
#include "CGameObject.h"

class CImage;
class CScene;

class CTile : public CGameObject
{
	friend CScene;
public:
	CTile();
	virtual ~CTile();

public:
	const static int TILESIZE = 32;

protected:
	TypeTile m_type;

	CImage* m_pImage;
	UINT m_uiImageXCount;
	UINT m_uiImageYCount;

	UINT m_uiTilePosX;
	UINT m_uiTilePosY;
	UINT m_uiTileIndex;

	bool m_bLineRender;

public:
	void SetType(TypeTile type);
	void SetPos(Vector pos) = delete;
	void SetPos(float x, float y) = delete;

	void SetTilePosX(UINT x);
	void SetTilePosY(UINT y);
	void SetTilePos(UINT x, UINT y);
	void SetTileIndex(UINT index);
	void SetLineRender(bool line);

	TypeTile GetType();
	int GetTilePosX();
	int GetTilePosY();
	int GetTileIndex();
	bool GetLineRender();

	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);

protected:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

