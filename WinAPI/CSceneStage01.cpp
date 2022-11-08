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
#include "CBottomCloud.h"

#include "CImageObject.h"
#include "CGameObject.h"
#include "CObstacle.h"
#include "CJelly1.h"
#include "CObstacleSky.h"

bool pause;
extern bool isSliding;
extern bool isJumping;
extern bool isDead;
extern float playerHp;

CSceneStage01::CSceneStage01()
{
	pPlayer = nullptr;
	obstacleTimer = 0;
	HpTimer = 0;
	pause = false;
	pauseImage = nullptr;
	failImage = nullptr;
	slideImage = nullptr;
	jumpImage = nullptr;
	HPProgressBar = nullptr;
	HPBar = nullptr;
	HPBackBar = nullptr;
	HPIcon = nullptr;
	HPEffect = nullptr;
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
	pPlayer->SetPos(300, WINSIZEY * 0.65f);
	AddGameObject(pPlayer);

	CCameraController* pCamController = new CCameraController;
	AddGameObject(pCamController);

	pauseImage = RESOURCE->LoadImg(L"Pause", L"Image\\Pause.png");

	failImage = RESOURCE->LoadImg(L"Fail", L"Image\\Fail.png");

	slideImage = RESOURCE->LoadImg(L"SlideButton1", L"Image\\Idle_Slide.png");
	
	jumpImage = RESOURCE->LoadImg(L"JumpButton1", L"Image\\Idle_Jump.png");

	HPIcon = RESOURCE->LoadImg(L"HpIcon", L"Image\\Hp_Icon.png");

	HPEffect = RESOURCE->LoadImg(L"HpEffect", L"Image\\Hp_Effect.png");

	HPBar = RESOURCE->LoadImg(L"HpBar", L"Image\\Hp_Bar.png");

	HPBackBar = RESOURCE->LoadImg(L"HpBackBar", L"Image\\Hp_BackBar.png");

	HPProgressBar = RESOURCE->LoadImg(L"HpProgressBar", L"Image\\Hp_ProgressBar.png");
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

	CBottomCloud* pBottomBackground1 = new CBottomCloud();
	pBottomBackground1->SetPos(WINSIZEX - 1280, WINSIZEY * 0.85);
	pBottomBackground1->SetDir(Vector(1, 0));
	AddGameObject(pBottomBackground1);

	CBottomCloud* pBottomBackground2 = new CBottomCloud();
	pBottomBackground2->SetPos(WINSIZEX, WINSIZEY * 0.85);
	pBottomBackground2->SetDir(Vector(1, 0));
	AddGameObject(pBottomBackground2);

	CBottomCloud* pBottomBackground3 = new CBottomCloud();
	pBottomBackground3->SetPos(WINSIZEX + 1280, WINSIZEY * 0.85);
	pBottomBackground3->SetDir(Vector(1, 0));
	AddGameObject(pBottomBackground3);


}

void CSceneStage01::Update()
{


	if (BUTTONDOWN(VK_ESCAPE) && pause == false && isDead == false)
	{
		pause = true;

		/*CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);*/
	}
	else if (BUTTONDOWN(VK_ESCAPE) && pause == true && isDead == false)
	{
		pause = false;

	}

	if (BUTTONSTAY(VK_CONTROL))
	{
		slideImage = RESOURCE->LoadImg(L"SlideButton2", L"Image\\Pushed_Slide.png");
	}
	if (BUTTONUP(VK_CONTROL))
	{
		slideImage = RESOURCE->LoadImg(L"SlideButton1", L"Image\\Idle_Slide.png");
	}

	if (BUTTONSTAY(VK_SPACE))
	{
		jumpImage = RESOURCE->LoadImg(L"JumpButton2", L"Image\\Pushed_Jump.png");
	}
	if (BUTTONUP(VK_SPACE))
	{
		jumpImage = RESOURCE->LoadImg(L"JumpButton1", L"Image\\Idle_Jump.png");
	}


	//if (BUTTONUP(VK_CONTROL))
	//{
	//	slideImage = RESOURCE->LoadImg(L"SlideButton2", L"Image\\Idle_Slide.png");
	//}



	obstacleTimer += DT;

	HpTimer += DT;

	if (obstacleTimer >= 2)
	{
		obstacleTimer -= 2;
		CObstacle* pObstacle1 = new CObstacle();
		pObstacle1->SetPos(WINSIZEX, WINSIZEY * 0.79);
		AddGameObject(pObstacle1);

		CJelly1* pJelly1 = new CJelly1();
		pJelly1->SetPos(WINSIZEX, WINSIZEY * 0.65);
		AddGameObject(pJelly1);

		CJelly1* pJelly2 = new CJelly1();
		pJelly2->SetPos(WINSIZEX + 100, WINSIZEY * 0.7);
		AddGameObject(pJelly2);

		CJelly1* pJelly3 = new CJelly1();
		pJelly3->SetPos(WINSIZEX + 200, WINSIZEY * 0.75);
		AddGameObject(pJelly3);

		CJelly1* pJelly4 = new CJelly1();
		pJelly4->SetPos(WINSIZEX + 300, WINSIZEY * 0.78);
		AddGameObject(pJelly4);

		CObstacleSky* pObstacleSky1 = new CObstacleSky();
		pObstacleSky1->SetPos(WINSIZEX + 300, WINSIZEY * 0.3);
		AddGameObject(pObstacleSky1);

		CJelly1* pJelly5 = new CJelly1();
		pJelly5->SetPos(WINSIZEX + 400, WINSIZEY * 0.75);
		AddGameObject(pJelly5);

		CJelly1* pJelly6 = new CJelly1();
		pJelly6->SetPos(WINSIZEX + 500, WINSIZEY * 0.7);
		AddGameObject(pJelly6);

	}

	if (playerHp > 0)
	{
		HpTimer += DT;

		if (HpTimer >= 0.2)
		{
			HpTimer -= 0.2;
			playerHp -= 0.1;
		}
	}

}

void CSceneStage01::Render()
{
	

	if (pause == true)
	{
		RENDER->Image(
			pauseImage,
			0, 0, WINSIZEX, WINSIZEY);
	}

	if (isDead== true)
	{
		RENDER->Image(
			failImage,
			0, 0, WINSIZEX, WINSIZEY);
	}

	// 슬라이드 버튼
	RENDER->Image(
		slideImage,
		WINSIZEX * 0.86, WINSIZEY * 0.8, WINSIZEX * 0.98, WINSIZEY * 0.95);

	// 점프 버튼
	RENDER->Image(
		jumpImage,
		WINSIZEX * 0.02, WINSIZEY * 0.8, WINSIZEX * 0.14, WINSIZEY * 0.95);

	// HP Back 바
	RENDER->Image(
		HPBackBar,
		70, 70, 572, 85);

	// HP 바
	RENDER->Image(
		HPBar,
		70, 68, 570, 87);

	// HP 프로그레스 바
	RENDER->Image(
		HPProgressBar,
		70 + 500 * playerHp / 100, 70, 570, 85);

	// HP 이펙트
	RENDER->Image(
		HPEffect,
		60 + 500 * playerHp / 100, 68, 80 + 500 * playerHp / 100, 87);

	// HP 아이콘
	RENDER->Image(
		HPIcon,
		40, 50, 90, 100);

	//// 슬라이드 버튼
	//RENDER->Image(
	//	slideImage,
	//	WINSIZEX * 0.86, WINSIZEY * 0.8, WINSIZEX * 0.98, WINSIZEY * 0.95);

	//// 점프 버튼
	//RENDER->Image(
	//	jumpImage,
	//	WINSIZEX * 0.02, WINSIZEY * 0.8, WINSIZEX * 0.14, WINSIZEY * 0.95);

	//// HP Back 바
	//RENDER->Image(
	//	HPBackBar,
	//	WINSIZEX * 0.04, WINSIZEY * 0.075, WINSIZEX * 0.402, WINSIZEY * 0.095);
	//
	//// HP 바
	//RENDER->Image(
	//	HPBar,
	//	WINSIZEX * 0.04, WINSIZEY * 0.07, WINSIZEX * 0.4, WINSIZEY * 0.1);

	//// HP 프로그레스 바
	//RENDER->Image(
	//	HPProgressBar,
	//	WINSIZEX * (0.402 * playerHp / 100), WINSIZEY * 0.075, WINSIZEX * 0.402, WINSIZEY * 0.095);

	//// HP 이펙트
	//RENDER->Image(
	//	HPEffect,
	//	WINSIZEX * (0.392 * playerHp / 100), WINSIZEY * 0.072, WINSIZEX * (0.408 * playerHp / 100), WINSIZEY * 0.098);

	//// HP 아이콘
	//RENDER->Image(
	//	HPIcon,
	//	WINSIZEX * 0.02, WINSIZEY * 0.05, WINSIZEX * 0.06, WINSIZEY * 0.12);

}

void CSceneStage01::Exit()
{
}

void CSceneStage01::Release()
{
}
