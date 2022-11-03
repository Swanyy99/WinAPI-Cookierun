#include "framework.h"
#include "CSceneTileTool.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CSceneManager.h"
#include "CPathManager.h"
#include "CResourceManager.h"
#include "CRenderManager.h"

#include "CImage.h"
#include "CTile.h"
#include "CPanel.h"
#include "CTileButton.h"
#include "CTilePanel.h"
#include "CImageObject.h"

LRESULT CALLBACK    WinTileToolProc(HWND, UINT, WPARAM, LPARAM);

CSceneTileTool::CSceneTileTool()
{
	m_hWndTileTool = 0;
	m_pImageObj = nullptr;
	m_iTileSizeX = 0;
	m_iTileSizeY = 0;
	m_fScrollSpeed = 300;

	m_uiTilePanelPage = 0;
	m_uiTileCountX = 0;
	m_uiTileCountY = 0;
	m_uiSelectedTileIndex = 0;
	m_typeSelectedTileType = TypeTile::None;
}

CSceneTileTool::~CSceneTileTool()
{
}

void CSceneTileTool::SetTile(UINT index, TypeTile type)
{
	Vector vecMousePos = MOUSEWORLDPOS;
	float tilePosX = vecMousePos.x / CTile::TILESIZE;
	float tilePosY = vecMousePos.y / CTile::TILESIZE;

	// 타일이 없는 위치일 경우 무시
	if (tilePosX < 0.f || (int)m_iTileSizeX <= tilePosX ||
		tilePosY < 0.f || (int)m_iTileSizeY <= tilePosY)
		return;

	const list<CGameObject*>& listTile = GetLayerObject(Layer::Tile);
	for (CGameObject* pGameObject : listTile)
	{
		CTile* pTile = dynamic_cast<CTile*>(pGameObject);
		if (pTile->GetTilePosX() != (int)tilePosX ||
			pTile->GetTilePosY() != (int)tilePosY)
			continue;

		pTile->SetTileIndex(index);
		pTile->SetType(type);
		return;
	}
}

void CSceneTileTool::CameraMove()
{
	Vector dir;
	if (BUTTONSTAY('A'))
	{
		dir.x = -1;
	}
	else if (BUTTONSTAY('D'))
		dir.x = 1;
	else dir.x = 0;

	if (BUTTONSTAY('W'))
		dir.y = -1;
	else if (BUTTONSTAY('S'))
		dir.y = 1;
	else
		dir.y = 0;

	CAMERA->Scroll(dir, m_fScrollSpeed);
}

void CSceneTileTool::CreateTiles(UINT sizeX, UINT sizeY, bool line)
{
	DeleteLayerObject(Layer::Tile);

	m_iTileSizeX = sizeX;
	m_iTileSizeY = sizeY;
	for (UINT y = 0; y < sizeY; y++)
	{
		for (UINT x = 0; x < sizeX; x++)
		{
			CTile* pTile = new CTile();
			pTile->SetTilePos(x, y);
			pTile->SetLineRender(line);
			AddGameObject(pTile);
		}
	}
}

void CSceneTileTool::SaveTile(const wstring& strPath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strPath.c_str(), L"wb");		// w : write, b : binary
	assert(pFile);

	UINT xCount = m_iTileSizeX;
	UINT yCount = m_iTileSizeY;
	UINT tileCount = 0;

	for (CGameObject* pGameObject : m_listObj[(int)Layer::Tile])
	{
		CTile* pTile = (CTile*)pGameObject;
		if (0 != pTile->GetTileIndex() ||
			TypeTile::None != pTile->GetType())
			tileCount++;
	}

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);
	fwrite(&tileCount, sizeof(UINT), 1, pFile);

	for (CGameObject* pGameObject : m_listObj[(int)Layer::Tile])
	{
		CTile* pTile = dynamic_cast<CTile*>(pGameObject);
		if (0 != pTile->GetTileIndex() ||
			TypeTile::None != pTile->GetType())
			pTile->Save(pFile);
	}

	fclose(pFile);
}

void CSceneTileTool::SaveTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // 구조체 사이즈.
	ofn.hwndOwner = hWnd;					// 부모 윈도우 지정.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // 나중에 완성된 경로가 채워질 버퍼 지정.
	ofn.nMaxFile = sizeof(szName); // lpstrFile에 지정된 버퍼의 문자 수.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; // 필터 설정
	ofn.nFilterIndex = 0; // 기본 필터 세팅. 0는 all로 초기 세팅됨. 처음꺼.
	ofn.lpstrFileTitle = nullptr; // 타이틀 바
	ofn.nMaxFileTitle = 0; // 타이틀 바 문자열 크기. nullptr이면 0.
	wstring strTileFolder = GETPATH;
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // 초기경로. 우리는 타일 저장할거기 때문에, content->tile 경로로 해두자.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // 스타일

	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}
}

void CSceneTileTool::LoadTile(const wstring& strPath)
{
	DeleteLayerObject(Layer::Tile);

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strPath.c_str(), L"rb");      // w : write, b : binary
	assert(pFile);

	UINT xCount = 0;
	UINT yCount = 0;
	UINT tileCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);
	fread(&tileCount, sizeof(UINT), 1, pFile);

	CreateTiles(xCount, yCount, true);

	CTile loadTile;
	for (UINT count = 0; count < tileCount; count++)
	{
		loadTile.Load(pFile);

		for (CGameObject* pGameObject : m_listObj[(int)Layer::Tile])
		{
			CTile* pTile = (CTile*)pGameObject;
			if (pTile->GetTilePosX() == loadTile.GetTilePosX() &&
				pTile->GetTilePosY() == loadTile.GetTilePosY())
			{
				pTile->SetTileIndex(loadTile.GetTileIndex());
				pTile->SetType(loadTile.GetType());
			}
		}
	}

	fclose(pFile);
}

void CSceneTileTool::LoadTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // 구조체 사이즈.
	ofn.hwndOwner = hWnd; // 부모 윈도우 지정.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // 나중에 완성된 경로가 채워질 버퍼 지정.
	ofn.nMaxFile = sizeof(szName); // lpstrFile에 지정된 버퍼의 문자 수.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; // 필터 설정
	ofn.nFilterIndex = 0; // 기본 필터 세팅. 0는 all로 초기 세팅됨. 처음꺼.
	ofn.lpstrFileTitle = nullptr; // 타이틀 바
	ofn.nMaxFileTitle = 0; // 타이틀 바 문자열 크기. nullptr이면 0.
	wstring strTileFolder = GETPATH;
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // 초기경로. 우리는 타일 저장할거기 때문에, content->tile 경로로 해두자.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // 스타일

	if (GetOpenFileName(&ofn))
	{
		LoadTile(szName);
	}
}

void CSceneTileTool::SaveMap(const wstring& strPath)
{
	// TODO : 맵 저장 구현
}

void CSceneTileTool::SaveMapData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // 구조체 사이즈.
	ofn.hwndOwner = hWnd;					// 부모 윈도우 지정.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // 나중에 완성된 경로가 채워질 버퍼 지정.
	ofn.nMaxFile = sizeof(szName); // lpstrFile에 지정된 버퍼의 문자 수.
	ofn.lpstrFilter = L"ALL\0*.*\0png\0*.png"; // 필터 설정
	ofn.nFilterIndex = 0; // 기본 필터 세팅. 0는 all로 초기 세팅됨. 처음꺼.
	ofn.lpstrFileTitle = nullptr; // 타이틀 바
	ofn.nMaxFileTitle = 0; // 타이틀 바 문자열 크기. nullptr이면 0.
	wstring strTileFolder = GETPATH;
	strTileFolder += L"Image";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // 초기경로. 우리는 타일 저장할거기 때문에, content->tile 경로로 해두자.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // 스타일

	if (GetSaveFileName(&ofn))
	{
		SaveMap(szName);
	}
}

void CSceneTileTool::LoadMap(const wstring& strPath)
{
	CImage* pImage = RESOURCE->LoadImgWithPath(strPath, strPath);
	m_pImageObj->SetImage(pImage);
}

void CSceneTileTool::LoadMapData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // 구조체 사이즈.
	ofn.hwndOwner = hWnd; // 부모 윈도우 지정.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // 나중에 완성된 경로가 채워질 버퍼 지정.
	ofn.nMaxFile = sizeof(szName); // lpstrFile에 지정된 버퍼의 문자 수.
	ofn.lpstrFilter = L"ALL\0*.*\0png\0*.png"; // 필터 설정
	ofn.nFilterIndex = 0; // 기본 필터 세팅. 0는 all로 초기 세팅됨. 처음꺼.
	ofn.lpstrFileTitle = nullptr; // 타이틀 바
	ofn.nMaxFileTitle = 0; // 타이틀 바 문자열 크기. nullptr이면 0.
	wstring strTileFolder = GETPATH;
	strTileFolder += L"Image";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // 초기경로. 우리는 타일 저장할거기 때문에, content->tile 경로로 해두자.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // 스타일

	if (GetOpenFileName(&ofn))
	{
		LoadMap(szName);
	}
}

void CSceneTileTool::ClickTileButton(UINT index)
{
	m_uiSelectedTileIndex = index;
}

void CSceneTileTool::ClickTileType(TypeTile type)
{
	m_typeSelectedTileType = type;
}

void CSceneTileTool::Init()
{
}

void CSceneTileTool::Enter()
{
	// DialogBox : 모달방식 (창이 포커싱이 잃지 않도록 제한함)
	// CreateDialog : 모달리스 방식 (창이 포커싱 제한을 하지 않음)
	m_hWndTileTool = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TILETOOLBOX), hWnd, WinTileToolProc);
	ShowWindow(m_hWndTileTool, SW_SHOW);

	RECT rect;
	GetWindowRect(m_hWndTileTool, &rect);
	MoveWindow(m_hWndTileTool, WINSTARTX + WINSIZEX, WINSTARTY,
		rect.right - rect.left, rect.bottom - rect.top, true);

	CreateTiles(10, 10, true);

	m_pImageObj = new CImageObject;
	AddGameObject(m_pImageObj);

	CTilePanel* pTilePanel = new CTilePanel;
	pTilePanel->SetScale(Vector(400.f, 600.f));
	pTilePanel->SetPos(Vector(WINSIZEX - 450.f, 50.f));
	AddGameObject(pTilePanel);
}

void CSceneTileTool::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CHANGESCENE(GroupScene::Title);
	}

	if (LMOUSESTAY(false))
	{
		SetTile(m_uiSelectedTileIndex, m_typeSelectedTileType);
	}
	if (RMOUSESTAY(false))
	{
		SetTile(0, TypeTile::None);
	}

	CameraMove();
}

void CSceneTileTool::Render()
{
}

void CSceneTileTool::Exit()
{
	EndDialog(m_hWndTileTool, IDOK);

	DeleteAll();
}

void CSceneTileTool::Release()
{
}

LRESULT CALLBACK    WinTileToolProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
		break;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_TILEBUTTON)
		{
			int x = GetDlgItemInt(hDlg, IDC_EDITTILEXSIZE, nullptr, false);
			int y = GetDlgItemInt(hDlg, IDC_EDITTILEYSIZE, nullptr, false);

			CScene* pCurScene = SCENE->GetCurScene();
			CSceneTileTool* pTileToolScene = dynamic_cast<CSceneTileTool*>(pCurScene);
			pTileToolScene->CreateTiles(x, y, true);
		}
		else if (LOWORD(wParam) == IDC_BUTTONTILESAVE)
		{
			CScene* pCurScene = SCENE->GetCurScene();
			CSceneTileTool* pTileToolScene = dynamic_cast<CSceneTileTool*>(pCurScene);
			assert(nullptr != pTileToolScene && L"TileTool Scene cast Failed");

			pTileToolScene->SaveTileData();
		}
		else if (LOWORD(wParam) == IDC_BUTTONTILELOAD)
		{
			CScene* pCurScene = SCENE->GetCurScene();
			CSceneTileTool* pTileToolScene = dynamic_cast<CSceneTileTool*>(pCurScene);
			assert(nullptr != pTileToolScene && L"TileTool Scene cast Failed");

			pTileToolScene->LoadTileData();
		}
		else if (LOWORD(wParam) == IDC_BUTTONMAPSAVE)
		{
			CScene* pCurScene = SCENE->GetCurScene();
			CSceneTileTool* pTileToolScene = dynamic_cast<CSceneTileTool*>(pCurScene);
			assert(nullptr != pTileToolScene && L"TileTool Scene cast Failed");

			pTileToolScene->SaveMapData();
		}
		else if (LOWORD(wParam) == IDC_BUTTONMAPLOAD)
		{
			CScene* pCurScene = SCENE->GetCurScene();
			CSceneTileTool* pTileToolScene = dynamic_cast<CSceneTileTool*>(pCurScene);
			assert(nullptr != pTileToolScene && L"TileTool Scene cast Failed");

			pTileToolScene->LoadMapData();
		}
		return (INT_PTR)TRUE;
		break;
	}
	return (INT_PTR)FALSE;
}