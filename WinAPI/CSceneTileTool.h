#pragma once
#include "CScene.h"

class CImageObject;

class CSceneTileTool : public CScene
{
public:
	CSceneTileTool();
	virtual ~CSceneTileTool();

private:
	HWND m_hWndTileTool;
	CImageObject* m_pImageObj;
	float m_fScrollSpeed;

	UINT m_uiTilePanelPage;
	UINT m_uiTileCountX;
	UINT m_uiTileCountY;

	UINT m_uiSelectedTileIndex;
	TypeTile m_typeSelectedTileType;

private:
	void SetTile(UINT index, TypeTile type);

	void CameraMove();

public:
	void CreateTiles(UINT sizeX, UINT sizeY, bool line = false);
	void SaveTile(const wstring& strPath);
	void SaveTileData();
	void LoadTile(const wstring& strPath);
	void LoadTileData();
	void SaveMap(const wstring& strPath);
	void SaveMapData();
	void LoadMap(const wstring& strPath);
	void LoadMapData();

	void ClickTileButton(UINT index);
	void ClickTileType(TypeTile type);

private:
	void Init() override;
	void Enter() override;
	void Update() override;
	void Render() override;
	void Exit() override;
	void Release() override;
};

