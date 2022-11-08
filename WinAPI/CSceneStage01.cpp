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

int score;
wstring ScreenScore;

extern bool isSliding;
extern bool isJumping;
extern bool isDead;
extern float playerHp;



CSceneStage01::CSceneStage01()
{
	pPlayer = nullptr;
	pause = false;
	pauseImage = nullptr;
	CookierunTitle = nullptr;
	failImage = nullptr;
	slideImage = nullptr;
	jumpImage = nullptr;
	HPProgressBar = nullptr;
	HPBar = nullptr;
	HPBackBar = nullptr;
	HPIcon = nullptr;
	HPEffect = nullptr;
	obstacleTimer = 0;
	HpTimer = 0;
	ScreenScore = L"";
	score = 0;
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

	CookierunTitle = RESOURCE->LoadImg(L"CookierunTitle", L"Image\\CookierunTitle.png");

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

	ScreenScore = to_wstring(score);

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

	#pragma region 맵패턴
	if (obstacleTimer >= 2 && obstacleTimer <= 2.1)
	{
		obstacleTimer += 1;
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

	if (obstacleTimer >= 5 && obstacleTimer <= 5.1)
	{
		obstacleTimer += 1;
		CObstacle* pObstacle1 = new CObstacle();
		pObstacle1->SetPos(WINSIZEX, WINSIZEY * 0.79);
		AddGameObject(pObstacle1);

		CJelly1* pJelly7 = new CJelly1();
		pJelly7->SetPos(WINSIZEX, WINSIZEY * 0.65);
		AddGameObject(pJelly7);

		CJelly1* pJelly8 = new CJelly1();
		pJelly8->SetPos(WINSIZEX + 100, WINSIZEY * 0.7);
		AddGameObject(pJelly8);

		CJelly1* pJelly9 = new CJelly1();
		pJelly9->SetPos(WINSIZEX + 200, WINSIZEY * 0.75);
		AddGameObject(pJelly9);

		CJelly1* pJelly10 = new CJelly1();
		pJelly10->SetPos(WINSIZEX + 300, WINSIZEY * 0.78);
		AddGameObject(pJelly10);

		CObstacleSky* pObstacleSky1 = new CObstacleSky();
		pObstacleSky1->SetPos(WINSIZEX + 300, WINSIZEY * 0.3);
		AddGameObject(pObstacleSky1);

		CJelly1* pJelly11 = new CJelly1();
		pJelly11->SetPos(WINSIZEX + 400, WINSIZEY * 0.75);
		AddGameObject(pJelly11);

		CJelly1* pJelly12 = new CJelly1();
		pJelly12->SetPos(WINSIZEX + 500, WINSIZEY * 0.7);
		AddGameObject(pJelly12);

	}

	if (obstacleTimer >= 8 && obstacleTimer <= 8.1)
	{
		obstacleTimer += 1;
		CObstacle* pObstacle1 = new CObstacle();
		pObstacle1->SetPos(WINSIZEX, WINSIZEY * 0.79);
		AddGameObject(pObstacle1);

		CJelly1* pJelly13 = new CJelly1();
		pJelly13->SetPos(WINSIZEX, WINSIZEY * 0.65);
		AddGameObject(pJelly13);

		CJelly1* pJelly14 = new CJelly1();
		pJelly14->SetPos(WINSIZEX + 100, WINSIZEY * 0.7);
		AddGameObject(pJelly14);

		CJelly1* pJelly15 = new CJelly1();
		pJelly15->SetPos(WINSIZEX + 200, WINSIZEY * 0.75);
		AddGameObject(pJelly15);

		CJelly1* pJelly16 = new CJelly1();
		pJelly16->SetPos(WINSIZEX + 300, WINSIZEY * 0.78);
		AddGameObject(pJelly16);

		CObstacleSky* pObstacleSky1 = new CObstacleSky();
		pObstacleSky1->SetPos(WINSIZEX + 300, WINSIZEY * 0.3);
		AddGameObject(pObstacleSky1);

		CJelly1* pJelly17 = new CJelly1();
		pJelly17->SetPos(WINSIZEX + 400, WINSIZEY * 0.75);
		AddGameObject(pJelly17);

		CJelly1* pJelly43 = new CJelly1();
		pJelly43->SetPos(WINSIZEX + 400, WINSIZEY * 0.6);
		AddGameObject(pJelly43);

		CJelly1* pJelly18 = new CJelly1();
		pJelly18->SetPos(WINSIZEX + 500, WINSIZEY * 0.75);
		AddGameObject(pJelly18);

		CJelly1* pJelly19 = new CJelly1();
		pJelly19->SetPos(WINSIZEX + 600, WINSIZEY * 0.75);
		AddGameObject(pJelly19);

		CJelly1* pJelly20 = new CJelly1();
		pJelly20->SetPos(WINSIZEX + 500, WINSIZEY * 0.6);
		AddGameObject(pJelly20);

		CJelly1* pJelly21 = new CJelly1();
		pJelly21->SetPos(WINSIZEX + 500, WINSIZEY * 0.75);
		AddGameObject(pJelly21);

		CJelly1* pJelly22 = new CJelly1();
		pJelly22->SetPos(WINSIZEX + 600, WINSIZEY * 0.6);
		AddGameObject(pJelly22);

		CJelly1* pJelly23 = new CJelly1();
		pJelly23->SetPos(WINSIZEX + 700, WINSIZEY * 0.75);
		AddGameObject(pJelly23);

		CJelly1* pJelly24 = new CJelly1();
		pJelly24->SetPos(WINSIZEX + 700, WINSIZEY * 0.6);
		AddGameObject(pJelly24);

		CJelly1* pJelly25 = new CJelly1();
		pJelly25->SetPos(WINSIZEX + 800, WINSIZEY * 0.75);
		AddGameObject(pJelly25);

		CJelly1* pJelly26 = new CJelly1();
		pJelly26->SetPos(WINSIZEX + 800, WINSIZEY * 0.6);
		AddGameObject(pJelly26);

	}

	if (obstacleTimer >= 11.7 && obstacleTimer <= 11.8)
	{
		obstacleTimer += 1;

		CObstacleSky* pObstacleSky2 = new CObstacleSky();
		pObstacleSky2->SetPos(WINSIZEX + 100, WINSIZEY * 0.3);
		AddGameObject(pObstacleSky2);

		CJelly1* pJelly27 = new CJelly1();
		pJelly27->SetPos(WINSIZEX + 100, WINSIZEY * 0.78);
		AddGameObject(pJelly27);

		CJelly1* pJelly28 = new CJelly1();
		pJelly28->SetPos(WINSIZEX + 175, WINSIZEY * 0.78);
		AddGameObject(pJelly28);

		CObstacleSky* pObstacleSky3 = new CObstacleSky();
		pObstacleSky3->SetPos(WINSIZEX + 250, WINSIZEY * 0.3);
		AddGameObject(pObstacleSky3);

		CJelly1* pJelly29 = new CJelly1();
		pJelly29->SetPos(WINSIZEX + 250, WINSIZEY * 0.78);
		AddGameObject(pJelly29);

		CObstacleSky* pObstacleSky4 = new CObstacleSky();
		pObstacleSky4->SetPos(WINSIZEX + 400, WINSIZEY * 0.3);
		AddGameObject(pObstacleSky4);

		CJelly1* pJelly30 = new CJelly1();
		pJelly30->SetPos(WINSIZEX + 325, WINSIZEY * 0.78);
		AddGameObject(pJelly30);

		CJelly1* pJelly31 = new CJelly1();
		pJelly31->SetPos(WINSIZEX + 400, WINSIZEY * 0.78);
		AddGameObject(pJelly31);

		CJelly1* pJelly32 = new CJelly1();
		pJelly32->SetPos(WINSIZEX + 475, WINSIZEY * 0.78);
		AddGameObject(pJelly32);

		CObstacleSky* pObstacleSky5 = new CObstacleSky();
		pObstacleSky5->SetPos(WINSIZEX + 550, WINSIZEY * 0.3);
		AddGameObject(pObstacleSky5);

		CJelly1* pJelly33 = new CJelly1();
		pJelly33->SetPos(WINSIZEX + 550, WINSIZEY * 0.78);
		AddGameObject(pJelly33);

		CJelly1* pJelly34 = new CJelly1();
		pJelly34->SetPos(WINSIZEX + 650, WINSIZEY * 0.75);
		AddGameObject(pJelly34);

		CJelly1* pJelly35 = new CJelly1();
		pJelly35->SetPos(WINSIZEX + 750, WINSIZEY * 0.7);
		AddGameObject(pJelly35);

	}

	if (obstacleTimer >= 15.5 && obstacleTimer <= 15.6)
	{
		obstacleTimer = -0.4;
		CObstacle* pObstacle1 = new CObstacle();
		pObstacle1->SetPos(WINSIZEX, WINSIZEY * 0.79);
		AddGameObject(pObstacle1);

		CObstacle* pObstacle2 = new CObstacle();
		pObstacle2->SetPos(WINSIZEX + 20, WINSIZEY * 0.79);
		AddGameObject(pObstacle2);

		CJelly1* pJelly36 = new CJelly1();
		pJelly36->SetPos(WINSIZEX + 10, WINSIZEY * 0.5);
		AddGameObject(pJelly36);

		CJelly1* pJelly151 = new CJelly1();
		pJelly151->SetPos(WINSIZEX + 10, WINSIZEY * 0.62);
		AddGameObject(pJelly151);

		CJelly1* pJelly37 = new CJelly1();
		pJelly37->SetPos(WINSIZEX + 100, WINSIZEY * 0.7);
		AddGameObject(pJelly37);

		CJelly1* pJelly38 = new CJelly1();
		pJelly38->SetPos(WINSIZEX + 200, WINSIZEY * 0.75);
		AddGameObject(pJelly38);

		CJelly1* pJelly39 = new CJelly1();
		pJelly39->SetPos(WINSIZEX + 300, WINSIZEY * 0.78);
		AddGameObject(pJelly39);

		CObstacleSky* pObstacleSky1 = new CObstacleSky();
		pObstacleSky1->SetPos(WINSIZEX + 300, WINSIZEY * 0.3);
		AddGameObject(pObstacleSky1);

		CJelly1* pJelly40 = new CJelly1();
		pJelly40->SetPos(WINSIZEX + 400, WINSIZEY * 0.75);
		AddGameObject(pJelly40);

		CJelly1* pJelly41 = new CJelly1();
		pJelly41->SetPos(WINSIZEX + 500, WINSIZEY * 0.7);
		AddGameObject(pJelly41);

		CJelly1* pJelly42 = new CJelly1();
		pJelly42->SetPos(WINSIZEX + 600, WINSIZEY * 0.7);
		AddGameObject(pJelly42);

	}
	#pragma endregion

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
	RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	RENDER->Text(L"Score : " + ScreenScore + L"점", 50, 107, 300, 107, Color(255, 255, 255, 1.f), 20);
	RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	RENDER->Image(
		CookierunTitle,
		1130, 15, 1270, 80);

	// 일시정지 UI
	if (pause == true)
	{
		RENDER->Image(
			pauseImage,
			0, 0, WINSIZEX, WINSIZEY);
	}

	// 사망 시 UI
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
