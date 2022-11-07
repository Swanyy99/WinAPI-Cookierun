#include "framework.h"
#include "CSceneStage01.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CPathManager.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CCameraController.h"
#include "CButton.h"
#include "CPanel.h"
#include "CFloor.h"
#include "CBackground.h"

#include "CImageObject.h"
#include "CGameObject.h"

CSceneStage01::CSceneStage01()
{
	pPlayer = nullptr;
}

CSceneStage01::~CSceneStage01()
{
}

void CSceneStage01::Init()
{

	//CMonster* pMonster = new CMonster();
	//pMonster->SetPos(1000, WINSIZEY * 0.5f);
	//AddGameObject(pMonster);

	pPlayer = new CPlayer();
	pPlayer->SetPos(200, WINSIZEY * 0.65f);
	AddGameObject(pPlayer);

	CCameraController* pCamController = new CCameraController;
	AddGameObject(pCamController);
}

void CSceneStage01::Enter()
{
	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\Stage01.tile");

	/*CImageObject* BackGround = new CImageObject;
	BackGround->SetImage(RESOURCE->LoadImg(L"BackGround" , L"Image\\Stage1_BackGround.png"));
	AddGameObject(BackGround);*/

	

	CFloor* pFloor2 = new CFloor();
	pFloor2->SetPos(WINSIZEX, WINSIZEY * 0.9);
	pFloor2->SetDir(Vector(1, 0));
	AddGameObject(pFloor2);

	CFloor* pFloor3 = new CFloor();
	pFloor3->SetPos(WINSIZEX - 320, WINSIZEY * 0.9);
	pFloor3->SetDir(Vector(1, 0));
	AddGameObject(pFloor3);

	CFloor* pFloor4 = new CFloor();
	pFloor4->SetPos(WINSIZEX - 640, WINSIZEY * 0.9);
	pFloor4->SetDir(Vector(1, 0));
	AddGameObject(pFloor4);

	CFloor* pFloor5 = new CFloor();
	pFloor5->SetPos(WINSIZEX - 960, WINSIZEY * 0.9);
	pFloor5->SetDir(Vector(1, 0));
	AddGameObject(pFloor5);

	CFloor* pFloor1 = new CFloor();
	pFloor1->SetPos(WINSIZEX - 1280, WINSIZEY * 0.9);
	pFloor1->SetDir(Vector(1, 0));
	AddGameObject(pFloor1);


	CBackground* pBackground = new CBackground();
	pBackground->SetPos(WINSIZEX * 0.5, WINSIZEY * 0.5);
	pBackground->SetDir(Vector(1, 0));
	AddGameObject(pBackground);

	CBackground* pBackground2 = new CBackground();
	pBackground2->SetPos(WINSIZEX * 2, WINSIZEY * 0.5);
	pBackground2->SetDir(Vector(1, 0));
	AddGameObject(pBackground2);
}

void CSceneStage01::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
	}

	
}

void CSceneStage01::Render()
{

}

void CSceneStage01::Exit()
{
}

void CSceneStage01::Release()
{
}
