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
#include "CPet.h"
#include "CPet2.h"
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
#include "CObstacle2.h"
#include "CObstacle3.h"
#include "CJelly1.h"
#include "CObstacleSky.h"
#include "CHeartItem.h"
#include "CMagnetItem.h"
#include "CDashItem.h"
#include "CImages.h"

bool pause;
bool isRetry;
bool isDebugMode;

int score;
wstring ScreenScore;

extern bool isSliding;
extern bool isJumping;
extern bool isDash;
extern bool isMagnet;
extern bool isDead;
extern bool isHurt;
extern float playerHp;
extern bool revive;
extern float playerPosX;
extern float playerPosY;
extern bool skillOn;

extern int choicePet;
int nowPet;


CSceneStage01::CSceneStage01()
{
	pPlayer = nullptr;
	pPet = nullptr;
	pPet2 = nullptr;


	RetryButton = nullptr;
	ResumeButton = nullptr;
	QuitButton = nullptr;


	pause = false;

	PauseImage = nullptr;
	FailImage = nullptr;

	CookierunTitle = nullptr;

	slideImage = nullptr;
	jumpImage = nullptr;
	SlideButtonImage = nullptr;
	JumpButtonImage = nullptr;
	HPProgressBar = nullptr;
	HPBar = nullptr;
	HPBackBar = nullptr;
	HPIcon = nullptr;
	HPEffect = nullptr;
	Tear = nullptr;
	obstacleTimer = 0;
	HpTimer = 0;
	ScreenScore = L"";
	score = 0;
	isRetry = false;
	isDebugMode = false;
	
}

CSceneStage01::~CSceneStage01()
{
}

void CSceneStage01::Init()
{
	
	
	
}

void CSceneStage01::Enter()
{
	CAMERA->FadeIn(0.1f);
	
	nowPet = choicePet;

	if (choicePet == 1)			// 하프물범 선택
	{
		pPet = new CPet();
		pPet->SetPos(200, WINSIZEY * 0.45f);
		AddGameObject(pPet);
	}

	else if (choicePet == 2)	// 파도 방울 선택
	{
		pPet2 = new CPet2();
		pPet2->SetPos(200, WINSIZEY * 0.45f);
		AddGameObject(pPet2);
	}
	

	obstacleTimer = 0;
	HpTimer = 0;
	ScreenScore = L"";
	score = 0;
	isDash = false;
	isMagnet = false;
	isDebugMode = false;

	// ESC 계속하기 && FAIL 부활하기 버튼
	auto ResumeButtonClicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* ResumeButton = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(ResumeButton->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		pause = false;
		if (isDead == true)
		{
			//TearOn = true;
			playerHp += 50;
			isDead = false;
			revive = true;
		}
	};

	ResumeButton = new CButton;
	ResumeButton->SetName(L"계속하기 / 부활하기 버튼");
	ResumeButton->SetLayer(Layer::Ui);
	ResumeButton->SetPos(540, 250);	// 689 296
	ResumeButton->SetScale(0, 0);
	//ResumeButton->SetImage(L"Idle_jump.png");
	ResumeButton->SetText(L"", 32, Color(0, 0, 0, 1));
	ResumeButton->SetClickedCallback(ResumeButtonClicked, (DWORD_PTR)ResumeButton, (DWORD_PTR)1);
	AddGameObject(ResumeButton);


	// 다시하기 버튼
	auto RetryButtonClicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* RetryButton = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(RetryButton->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		playerHp += 1;
		pause = false;
		isDead = false;
		isRetry = true;
		CAMERA->FadeOut(0.1f);
		DELAYCHANGESCENE(GroupScene::Stage01, 0.1f);
	};

	RetryButton = new CButton;
	RetryButton->SetName(L"다시하기 버튼");
	RetryButton->SetLayer(Layer::Ui);
	RetryButton->SetPos(540, 350);
	RetryButton->SetScale(0, 0);
	RetryButton->SetText(L"", 32, Color(0, 0, 0, 1));
	RetryButton->SetClickedCallback(RetryButtonClicked, (DWORD_PTR)RetryButton, (DWORD_PTR)1);
	AddGameObject(RetryButton);


	// 나가기 버튼
	auto QuitButtonClicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* QuitButton = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(QuitButton->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		CAMERA->FadeOut(0.1f);
		playerHp += 1;
		isDead = false;
		pause = false;
		DELAYCHANGESCENE(GroupScene::Title, 0.1f);
	};

	QuitButton = new CButton;
	QuitButton->SetName(L"나가기 버튼");
	QuitButton->SetLayer(Layer::Ui);
	QuitButton->SetPos(540, 450);
	QuitButton->SetScale(0, 0);
	QuitButton->SetText(L"", 32, Color(0, 0, 0, 1));
	QuitButton->SetClickedCallback(QuitButtonClicked, (DWORD_PTR)QuitButton, (DWORD_PTR)1);
	AddGameObject(QuitButton);

	pPlayer = new CPlayer();
	pPlayer->SetPos(300, WINSIZEY * 0.65f);
	AddGameObject(pPlayer);

	

	CCameraController* pCamController = new CCameraController;
	AddGameObject(pCamController);

	// CookierRun title 이미지
	CookierunTitle = new CImages();
	CookierunTitle->SetImageName(L"CookierunTitle.png");
	CookierunTitle->SetPos(1130, 15);
	CookierunTitle->SetScale(1270, 80);
	AddGameObject(CookierunTitle);

	// HP Back Bar 이미지
	HPBackBar = new CImages();
	HPBackBar->SetImageName(L"HP_BackBar.png");
	HPBackBar->SetPos(70, 70);
	HPBackBar->SetScale(572, 85);
	AddGameObject(HPBackBar);

	// HP Bar 이미지
	HPBar = new CImages();
	HPBar->SetImageName(L"HP_Bar.png");
	HPBar->SetPos(70, 68);
	HPBar->SetScale(570, 87);
	AddGameObject(HPBar);

	// HP Progress Bar 이미지
	HPProgressBar = new CImages();
	HPProgressBar->SetImageName(L"HP_ProgressBar.png");
	HPProgressBar->SetPos(70 + 500 * playerHp / 100, 70);
	HPProgressBar->SetScale(570, 85);
	AddGameObject(HPProgressBar);

	// HP Effect 이미지
	HPEffect = new CImages();
	HPEffect->SetImageName(L"HP_Effect.png");
	HPEffect->SetPos(60 + 500 * playerHp / 100, 68);
	HPEffect->SetScale(80 + 500 * playerHp / 100, 87);
	AddGameObject(HPEffect);

	// HP Icon 이미지
	HPIcon = new CImages();
	HPIcon->SetImageName(L"HP_Icon.png");
	HPIcon->SetPos(40, 50);
	HPIcon->SetScale(90, 100);
	AddGameObject(HPIcon);

	// 슬라이드 버튼 이미지
	SlideButtonImage = new CImages();
	SlideButtonImage->SetImageName(L"Idle_Slide.png");
	SlideButtonImage->SetPos(30, 580);
	SlideButtonImage->SetScale(180, 680);
	AddGameObject(SlideButtonImage);


	// 점프 버튼 이미지
	JumpButtonImage = new CImages();
	JumpButtonImage->SetImageName(L"Idle_Jump.png");
	JumpButtonImage->SetPos(1100, 580);
	JumpButtonImage->SetScale(1250, 680);
	AddGameObject(JumpButtonImage);

	// 일시정지 화면 반투명효과 + 일시정지 글자
	PauseImage = new CImages();
	PauseImage->SetImageName(L"Pause.png");
	PauseImage->SetPos(0, 0);
	PauseImage->SetScale(0, 0);
	AddGameObject(PauseImage);

	// 사망 화면 반투명효과 + 으앙주금 글자
	FailImage = new CImages();
	FailImage->SetImageName(L"Fail.png");
	FailImage->SetPos(0, 0);
	FailImage->SetScale(0, 0);
	AddGameObject(FailImage);

	CAMERA->FadeIn(0.25f);

	CFloor* pFloor2 = new CFloor();
	pFloor2->SetPos(0, WINSIZEY * 0.9);
	pFloor2->SetDir(Vector(1, 0));
	AddGameObject(pFloor2);

	CFloor* pFloor3 = new CFloor();
	pFloor3->SetPos(320, WINSIZEY * 0.9);
	pFloor3->SetDir(Vector(1, 0));
	AddGameObject(pFloor3);

	CFloor* pFloor4 = new CFloor();
	pFloor4->SetPos(640, WINSIZEY * 0.9);
	pFloor4->SetDir(Vector(1, 0));
	AddGameObject(pFloor4);

	CFloor* pFloor5 = new CFloor();
	pFloor5->SetPos(960, WINSIZEY * 0.9);
	pFloor5->SetDir(Vector(1, 0));
	AddGameObject(pFloor5);

	CFloor* pFloor1 = new CFloor();
	pFloor1->SetPos(1280, WINSIZEY * 0.9);
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
	if (pause == true && isDead == false)
	{
		ResumeButton->SetScale(200, 80);
		ResumeButton->SetText(L"계속하기", 32, Color(0, 0, 0, 1));

		RetryButton->SetScale(200, 80);
		RetryButton->SetText(L"다시하기", 32, Color(0, 0, 0, 1));

		QuitButton->SetScale(200, 80);
		QuitButton->SetText(L"나가기", 32, Color(0, 0, 0, 1));
	}

	if (isDead == true)
	{
		ResumeButton->SetScale(200, 80);
		ResumeButton->SetText(L"부활하기", 32, Color(0, 0, 0, 1));

		RetryButton->SetScale(200, 80);
		RetryButton->SetText(L"다시하기", 32, Color(0, 0, 0, 1));

		QuitButton->SetScale(200, 80);
		QuitButton->SetText(L"나가기", 32, Color(0, 0, 0, 1));
	}

	if (pause == false && isDead == false)
	{
		ResumeButton->SetScale(0, 0);
		ResumeButton->SetText(L"", 32, Color(0, 0, 0, 1));

		RetryButton->SetScale(0, 0);
		RetryButton->SetText(L"", 32, Color(0, 0, 0, 1));

		QuitButton->SetScale(0, 0);
		QuitButton->SetText(L"", 32, Color(0, 0, 0, 1));
	}

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

	

	if (BUTTONDOWN('G') && isDebugMode == false)
	{
		isDebugMode = true;
	}
	else if (BUTTONDOWN('G') && isDebugMode == true)
	{
		isDebugMode = false;
	}

	obstacleTimer += DT;

	#pragma region 맵패턴노가다
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

		CDashItem* pDashItem1 = new CDashItem();
		pDashItem1->SetPos(WINSIZEX, WINSIZEY * 0.5);
		AddGameObject(pDashItem1);

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

		CJelly1* pJelly20 = new CJelly1();
		pJelly20->SetPos(WINSIZEX + 500, WINSIZEY * 0.6);
		AddGameObject(pJelly20);

		CJelly1* pJelly19 = new CJelly1();
		pJelly19->SetPos(WINSIZEX + 600, WINSIZEY * 0.75);
		AddGameObject(pJelly19);

		CJelly1* pJelly22 = new CJelly1();
		pJelly22->SetPos(WINSIZEX + 600, WINSIZEY * 0.6);
		AddGameObject(pJelly22);

		CMagnetItem* pMagent1 = new CMagnetItem();
		pMagent1->SetPos(WINSIZEX + 600, WINSIZEY * 0.45);
		AddGameObject(pMagent1);

		//CJelly1* pJelly21 = new CJelly1();
		//pJelly21->SetPos(WINSIZEX + 500, WINSIZEY * 0.75);
		//AddGameObject(pJelly21);

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
		obstacleTimer += 1;
		CObstacle* pObstacle1 = new CObstacle();
		pObstacle1->SetPos(WINSIZEX, WINSIZEY * 0.79);
		AddGameObject(pObstacle1);

		CObstacle* pObstacle2 = new CObstacle();
		pObstacle2->SetPos(WINSIZEX + 20, WINSIZEY * 0.79);
		AddGameObject(pObstacle2);

		CHeartItem* pHeart1 = new CHeartItem();
		pHeart1->SetPos(WINSIZEX + 10, WINSIZEY * 0.35);
		AddGameObject(pHeart1);

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

	if (obstacleTimer >= 18.5 && obstacleTimer <= 18.6)
	{
		obstacleTimer += 1;

		CJelly1* pJelly1 = new CJelly1();
		pJelly1->SetPos(WINSIZEX + 100, WINSIZEY * 0.51);
		AddGameObject(pJelly1);

		CJelly1* pJelly43 = new CJelly1();
		pJelly43->SetPos(WINSIZEX + 100, WINSIZEY * 0.63);
		AddGameObject(pJelly43);

		CJelly1* pJelly44 = new CJelly1();
		pJelly44->SetPos(WINSIZEX + 100, WINSIZEY * 0.75);
		AddGameObject(pJelly44);

		CJelly1* pJelly2 = new CJelly1();
		pJelly2->SetPos(WINSIZEX + 200, WINSIZEY * 0.51);
		AddGameObject(pJelly2);

		CJelly1* pJelly45 = new CJelly1();
		pJelly45->SetPos(WINSIZEX + 200, WINSIZEY * 0.63);
		AddGameObject(pJelly45);

		CJelly1* pJelly46 = new CJelly1();
		pJelly46->SetPos(WINSIZEX + 200, WINSIZEY * 0.75);
		AddGameObject(pJelly46);

		CJelly1* pJelly3 = new CJelly1();
		pJelly3->SetPos(WINSIZEX + 300, WINSIZEY * 0.51);
		AddGameObject(pJelly3);

		CJelly1* pJelly47 = new CJelly1();
		pJelly47->SetPos(WINSIZEX + 300, WINSIZEY * 0.63);
		AddGameObject(pJelly47);

		CJelly1* pJelly48 = new CJelly1();
		pJelly48->SetPos(WINSIZEX + 300, WINSIZEY * 0.75);
		AddGameObject(pJelly48);

		CJelly1* pJelly4 = new CJelly1();
		pJelly4->SetPos(WINSIZEX + 400, WINSIZEY * 0.51);
		AddGameObject(pJelly4);

		CJelly1* pJelly49 = new CJelly1();
		pJelly49->SetPos(WINSIZEX + 400, WINSIZEY * 0.63);
		AddGameObject(pJelly49);

		CJelly1* pJelly50 = new CJelly1();
		pJelly50->SetPos(WINSIZEX + 400, WINSIZEY * 0.75);
		AddGameObject(pJelly50);

		CJelly1* pJelly5 = new CJelly1();
		pJelly5->SetPos(WINSIZEX + 500, WINSIZEY * 0.51);
		AddGameObject(pJelly5);

		CJelly1* pJelly34 = new CJelly1();
		pJelly34->SetPos(WINSIZEX + 500, WINSIZEY * 0.63);
		AddGameObject(pJelly34);

		CJelly1* pJelly35 = new CJelly1();
		pJelly35->SetPos(WINSIZEX + 500, WINSIZEY * 0.75);
		AddGameObject(pJelly35);

		CJelly1* pJelly6 = new CJelly1();
		pJelly6->SetPos(WINSIZEX + 600, WINSIZEY * 0.51);
		AddGameObject(pJelly6);

		CJelly1* pJelly36 = new CJelly1();
		pJelly36->SetPos(WINSIZEX + 600, WINSIZEY * 0.63);
		AddGameObject(pJelly36);

		CJelly1* pJelly37 = new CJelly1();
		pJelly37->SetPos(WINSIZEX + 600, WINSIZEY * 0.75);
		AddGameObject(pJelly37);

	}

	if (obstacleTimer >= 21.7 && obstacleTimer <= 21.8)
	{
		obstacleTimer += 1;

		CJelly1* pJelly43 = new CJelly1();
		pJelly43->SetPos(WINSIZEX + 100, WINSIZEY * 0.7);
		AddGameObject(pJelly43);

		CJelly1* pJelly44 = new CJelly1();
		pJelly44->SetPos(WINSIZEX + 200, WINSIZEY * 0.7);
		AddGameObject(pJelly44);

		CJelly1* pJelly45 = new CJelly1();
		pJelly45->SetPos(WINSIZEX + 300, WINSIZEY * 0.7);
		AddGameObject(pJelly45);

		CJelly1* pJelly46 = new CJelly1();
		pJelly46->SetPos(WINSIZEX + 400, WINSIZEY * 0.7);
		AddGameObject(pJelly46);

		CJelly1* pJelly47 = new CJelly1();
		pJelly47->SetPos(WINSIZEX + 500, WINSIZEY * 0.7);
		AddGameObject(pJelly47);

		CObstacle2* Obstacle2 = new CObstacle2();
		Obstacle2->SetPos(WINSIZEX + 600, WINSIZEY * 0.7);
		AddGameObject(Obstacle2);

		CJelly1* pJelly48 = new CJelly1();
		pJelly48->SetPos(WINSIZEX + 640, WINSIZEY * 0.5);
		AddGameObject(pJelly48);

		CJelly1* pJelly49 = new CJelly1();
		pJelly49->SetPos(WINSIZEX + 790, WINSIZEY * 0.7);
		AddGameObject(pJelly49);

		CJelly1* pJelly50 = new CJelly1();
		pJelly50->SetPos(WINSIZEX + 890, WINSIZEY * 0.7);
		AddGameObject(pJelly50);

		CObstacle2* Obstacle3 = new CObstacle2();
		Obstacle3->SetPos(WINSIZEX + 1000, WINSIZEY * 0.7);
		AddGameObject(Obstacle3);

		CJelly1* pJelly51 = new CJelly1();
		pJelly51->SetPos(WINSIZEX + 1040, WINSIZEY * 0.5);
		AddGameObject(pJelly51);

		CJelly1* pJelly52 = new CJelly1();
		pJelly52->SetPos(WINSIZEX + 1190, WINSIZEY * 0.7);
		AddGameObject(pJelly52);

		CJelly1* pJelly53 = new CJelly1();
		pJelly53->SetPos(WINSIZEX + 1290, WINSIZEY * 0.7);
		AddGameObject(pJelly53);

		CObstacle2* Obstacle4 = new CObstacle2();
		Obstacle4->SetPos(WINSIZEX + 1400, WINSIZEY * 0.7);
		AddGameObject(Obstacle4);

		CJelly1* pJelly54 = new CJelly1();
		pJelly54->SetPos(WINSIZEX + 1440, WINSIZEY * 0.5);
		AddGameObject(pJelly54);

		CJelly1* pJelly55 = new CJelly1();
		pJelly55->SetPos(WINSIZEX + 1590, WINSIZEY * 0.7);
		AddGameObject(pJelly55);

		CJelly1* pJelly56 = new CJelly1();
		pJelly56->SetPos(WINSIZEX + 1690, WINSIZEY * 0.7);
		AddGameObject(pJelly56);

		CObstacle2* Obstacle5 = new CObstacle2();
		Obstacle5->SetPos(WINSIZEX + 1800, WINSIZEY * 0.7);
		AddGameObject(Obstacle5);

		CJelly1* pJelly57 = new CJelly1();
		pJelly57->SetPos(WINSIZEX + 1840, WINSIZEY * 0.5);
		AddGameObject(pJelly57);

		CJelly1* pJelly58 = new CJelly1();
		pJelly58->SetPos(WINSIZEX + 1990, WINSIZEY * 0.7);
		AddGameObject(pJelly58);

		CJelly1* pJelly59 = new CJelly1();
		pJelly59->SetPos(WINSIZEX + 2090, WINSIZEY * 0.7);
		AddGameObject(pJelly59);

		CObstacle2* Obstacle6 = new CObstacle2();
		Obstacle6->SetPos(WINSIZEX + 2200, WINSIZEY * 0.7);
		AddGameObject(Obstacle6);

		CJelly1* pJelly60 = new CJelly1();
		pJelly60->SetPos(WINSIZEX + 2240, WINSIZEY * 0.5);
		AddGameObject(pJelly60);

		CJelly1* pJelly61 = new CJelly1();
		pJelly61->SetPos(WINSIZEX + 2390, WINSIZEY * 0.7);
		AddGameObject(pJelly61);

		CJelly1* pJelly62 = new CJelly1();
		pJelly62->SetPos(WINSIZEX + 2490, WINSIZEY * 0.7);
		AddGameObject(pJelly62);
	}

	if (obstacleTimer >= 31 && obstacleTimer <= 31.1)
	{
		obstacleTimer += 1;

		CJelly1* pJelly43 = new CJelly1();
		pJelly43->SetPos(WINSIZEX + 100, WINSIZEY * 0.7);
		AddGameObject(pJelly43);

		CJelly1* pJelly44 = new CJelly1();
		pJelly44->SetPos(WINSIZEX + 200, WINSIZEY * 0.7);
		AddGameObject(pJelly44);

		CJelly1* pJelly45 = new CJelly1();
		pJelly45->SetPos(WINSIZEX + 300, WINSIZEY * 0.7);
		AddGameObject(pJelly45);

		CJelly1* pJelly46 = new CJelly1();
		pJelly46->SetPos(WINSIZEX + 400, WINSIZEY * 0.7);
		AddGameObject(pJelly46);

		CDashItem* pDashItem1 = new CDashItem();
		pDashItem1->SetPos(WINSIZEX + 500, WINSIZEY * 0.7);
		AddGameObject(pDashItem1);

		CObstacle2* Obstacle1 = new CObstacle2();
		Obstacle1->SetPos(WINSIZEX + 600, WINSIZEY * 0.7);
		AddGameObject(Obstacle1);

		CObstacle2* Obstacle2 = new CObstacle2();
		Obstacle2->SetPos(WINSIZEX + 700, WINSIZEY * 0.7);
		AddGameObject(Obstacle2);

		CObstacle2* Obstacle4 = new CObstacle2();
		Obstacle4->SetPos(WINSIZEX + 800, WINSIZEY * 0.7);
		AddGameObject(Obstacle4);

		CObstacle2* Obstacle5 = new CObstacle2();
		Obstacle5->SetPos(WINSIZEX + 900, WINSIZEY * 0.7);
		AddGameObject(Obstacle5);

		CObstacle2* Obstacle6 = new CObstacle2();
		Obstacle6->SetPos(WINSIZEX + 1000, WINSIZEY * 0.7);
		AddGameObject(Obstacle6);

		CObstacle2* Obstacle7 = new CObstacle2();
		Obstacle7->SetPos(WINSIZEX + 1100, WINSIZEY * 0.7);
		AddGameObject(Obstacle7);

		CObstacle2* Obstacle8 = new CObstacle2();
		Obstacle8->SetPos(WINSIZEX + 1200, WINSIZEY * 0.7);
		AddGameObject(Obstacle8);

		CObstacle2* Obstacle9 = new CObstacle2();
		Obstacle9->SetPos(WINSIZEX + 1300, WINSIZEY * 0.7);
		AddGameObject(Obstacle9);

		CObstacle2* Obstacle10 = new CObstacle2();
		Obstacle10->SetPos(WINSIZEX + 1400, WINSIZEY * 0.7);
		AddGameObject(Obstacle10);

		CObstacle2* Obstacle11 = new CObstacle2();
		Obstacle11->SetPos(WINSIZEX + 1500, WINSIZEY * 0.7);
		AddGameObject(Obstacle11);

		CObstacle2* Obstacle12 = new CObstacle2();
		Obstacle12->SetPos(WINSIZEX + 1600, WINSIZEY * 0.7);
		AddGameObject(Obstacle12);

		CObstacle2* Obstacle13 = new CObstacle2();
		Obstacle13->SetPos(WINSIZEX + 1700, WINSIZEY * 0.7);
		AddGameObject(Obstacle13);

		CObstacle2* Obstacle14 = new CObstacle2();
		Obstacle14->SetPos(WINSIZEX + 1800, WINSIZEY * 0.7);
		AddGameObject(Obstacle14);

		CObstacle2* Obstacle15 = new CObstacle2();
		Obstacle15->SetPos(WINSIZEX + 1900, WINSIZEY * 0.7);
		AddGameObject(Obstacle15);

		CObstacle2* Obstacle16 = new CObstacle2();
		Obstacle16->SetPos(WINSIZEX + 2000, WINSIZEY * 0.7);
		AddGameObject(Obstacle16);

		CObstacle2* Obstacle17 = new CObstacle2();
		Obstacle17->SetPos(WINSIZEX + 2100, WINSIZEY * 0.7);
		AddGameObject(Obstacle17);

		CObstacle2* Obstacle18 = new CObstacle2();
		Obstacle18->SetPos(WINSIZEX + 2200, WINSIZEY * 0.7);
		AddGameObject(Obstacle18);

		CObstacle2* Obstacle19 = new CObstacle2();
		Obstacle19->SetPos(WINSIZEX + 2300, WINSIZEY * 0.7);
		AddGameObject(Obstacle19);

		CObstacle2* Obstacle20 = new CObstacle2();
		Obstacle20->SetPos(WINSIZEX + 2400, WINSIZEY * 0.7);
		AddGameObject(Obstacle20);

		CObstacle2* Obstacle21 = new CObstacle2();
		Obstacle21->SetPos(WINSIZEX + 2500, WINSIZEY * 0.7);
		AddGameObject(Obstacle21);

		CObstacle2* Obstacle22 = new CObstacle2();
		Obstacle22->SetPos(WINSIZEX + 2600, WINSIZEY * 0.7);
		AddGameObject(Obstacle22);

		CObstacle2* Obstacle23 = new CObstacle2();
		Obstacle23->SetPos(WINSIZEX + 2700, WINSIZEY * 0.7);
		AddGameObject(Obstacle23);

		CObstacle2* Obstacle24 = new CObstacle2();
		Obstacle24->SetPos(WINSIZEX + 2800, WINSIZEY * 0.7);
		AddGameObject(Obstacle24);

		CObstacle2* Obstacle25 = new CObstacle2();
		Obstacle25->SetPos(WINSIZEX + 2900, WINSIZEY * 0.7);
		AddGameObject(Obstacle25);

		CObstacle2* Obstacle26 = new CObstacle2();
		Obstacle26->SetPos(WINSIZEX + 3000, WINSIZEY * 0.7);
		AddGameObject(Obstacle26);

		CObstacle2* Obstacle27 = new CObstacle2();
		Obstacle27->SetPos(WINSIZEX + 3100, WINSIZEY * 0.7);
		AddGameObject(Obstacle27);

		CObstacle2* Obstacle28 = new CObstacle2();
		Obstacle28->SetPos(WINSIZEX + 3200, WINSIZEY * 0.7);
		AddGameObject(Obstacle28);

		CObstacle2* Obstacle29 = new CObstacle2();
		Obstacle29->SetPos(WINSIZEX + 3300, WINSIZEY * 0.7);
		AddGameObject(Obstacle29);

		CObstacle2* Obstacle30 = new CObstacle2();
		Obstacle30->SetPos(WINSIZEX + 3400, WINSIZEY * 0.7);
		AddGameObject(Obstacle30);

		CObstacle2* Obstacle31 = new CObstacle2();
		Obstacle31->SetPos(WINSIZEX + 3500, WINSIZEY * 0.7);
		AddGameObject(Obstacle31);

		CObstacle2* Obstacle32 = new CObstacle2();
		Obstacle32->SetPos(WINSIZEX + 3600, WINSIZEY * 0.7);
		AddGameObject(Obstacle32);

		CObstacle2* Obstacle33 = new CObstacle2();
		Obstacle33->SetPos(WINSIZEX + 3700, WINSIZEY * 0.7);
		AddGameObject(Obstacle33);

		CObstacle2* Obstacle34 = new CObstacle2();
		Obstacle34->SetPos(WINSIZEX + 3800, WINSIZEY * 0.7);
		AddGameObject(Obstacle34);

		CObstacle2* Obstacle35 = new CObstacle2();
		Obstacle35->SetPos(WINSIZEX + 3900, WINSIZEY * 0.7);
		AddGameObject(Obstacle35);

		CJelly1* pJelly30 = new CJelly1();
		pJelly30->SetPos(WINSIZEX + 4070, WINSIZEY * 0.75);
		AddGameObject(pJelly30);

		CJelly1* pJelly31 = new CJelly1();
		pJelly31->SetPos(WINSIZEX + 4170, WINSIZEY * 0.7);
		AddGameObject(pJelly31);

		CJelly1* pJelly32 = new CJelly1();
		pJelly32->SetPos(WINSIZEX + 4270, WINSIZEY * 0.7);
		AddGameObject(pJelly32);

		CJelly1* pJelly33 = new CJelly1();
		pJelly33->SetPos(WINSIZEX + 4370, WINSIZEY * 0.7);
		AddGameObject(pJelly33);

		CJelly1* pJelly34 = new CJelly1();
		pJelly34->SetPos(WINSIZEX + 4435, WINSIZEY * 0.65);
		AddGameObject(pJelly34);
	
	}

	if (obstacleTimer >= 47 && obstacleTimer <= 47.1)
	{
		obstacleTimer += 1;
		CJelly1* pJelly50 = new CJelly1();
		pJelly50->SetPos(WINSIZEX , WINSIZEY * 0.6);
		AddGameObject(pJelly50);

		CObstacle3* p3Obs1 = new CObstacle3();
		p3Obs1->SetPos(WINSIZEX + 50, WINSIZEY * 0.75);
		AddGameObject(p3Obs1);

		CJelly1* pJelly51 = new CJelly1();
		pJelly51->SetPos(WINSIZEX + 70, WINSIZEY * 0.6);
		AddGameObject(pJelly51);

		CJelly1* pJelly52 = new CJelly1();
		pJelly52->SetPos(WINSIZEX + 140, WINSIZEY * 0.6);
		AddGameObject(pJelly52);

		CJelly1* pJelly53 = new CJelly1();
		pJelly53->SetPos(WINSIZEX + 210, WINSIZEY * 0.6);
		AddGameObject(pJelly53);

		CJelly1* pJelly54 = new CJelly1();
		pJelly54->SetPos(WINSIZEX + 280, WINSIZEY * 0.6);
		AddGameObject(pJelly54);

		CJelly1* pJelly55 = new CJelly1();
		pJelly55->SetPos(WINSIZEX + 350, WINSIZEY * 0.6);
		AddGameObject(pJelly55);

		CJelly1* pJelly56 = new CJelly1();
		pJelly56->SetPos(WINSIZEX + 420, WINSIZEY * 0.6);
		AddGameObject(pJelly56);

		CJelly1* pJelly57 = new CJelly1();
		pJelly57->SetPos(WINSIZEX + 490, WINSIZEY * 0.6);
		AddGameObject(pJelly57);

		CJelly1* pJelly58 = new CJelly1();
		pJelly58->SetPos(WINSIZEX + 560, WINSIZEY * 0.6);
		AddGameObject(pJelly58);
	}

	if (obstacleTimer >= 49.9 && obstacleTimer <= 50)
	{
		obstacleTimer += 1;

		CObstacle3* p3Obs1 = new CObstacle3();
		p3Obs1->SetPos(WINSIZEX + 50, WINSIZEY * 0.75);
		AddGameObject(p3Obs1);

		CJelly1* pJelly51 = new CJelly1();
		pJelly51->SetPos(WINSIZEX + 70, WINSIZEY * 0.6);
		AddGameObject(pJelly51);

		CJelly1* pJelly52 = new CJelly1();
		pJelly52->SetPos(WINSIZEX + 140, WINSIZEY * 0.6);
		AddGameObject(pJelly52);

		CJelly1* pJelly53 = new CJelly1();
		pJelly53->SetPos(WINSIZEX + 210, WINSIZEY * 0.6);
		AddGameObject(pJelly53);

		CJelly1* pJelly54 = new CJelly1();
		pJelly54->SetPos(WINSIZEX + 280, WINSIZEY * 0.6);
		AddGameObject(pJelly54);

		CJelly1* pJelly55 = new CJelly1();
		pJelly55->SetPos(WINSIZEX + 350, WINSIZEY * 0.6);
		AddGameObject(pJelly55);

		CJelly1* pJelly56 = new CJelly1();
		pJelly56->SetPos(WINSIZEX + 420, WINSIZEY * 0.6);
		AddGameObject(pJelly56);

		CJelly1* pJelly57 = new CJelly1();
		pJelly57->SetPos(WINSIZEX + 490, WINSIZEY * 0.6);
		AddGameObject(pJelly57);

		CJelly1* pJelly58 = new CJelly1();
		pJelly58->SetPos(WINSIZEX + 560, WINSIZEY * 0.6);
		AddGameObject(pJelly58);
	}

	if (obstacleTimer >= 52.8 && obstacleTimer <= 52.9)
	{
		obstacleTimer += 1;

		CObstacle3* p3Obs1 = new CObstacle3();
		p3Obs1->SetPos(WINSIZEX + 50, WINSIZEY * 0.75);
		AddGameObject(p3Obs1);

		CJelly1* pJelly51 = new CJelly1();
		pJelly51->SetPos(WINSIZEX + 70, WINSIZEY * 0.6);
		AddGameObject(pJelly51);

		CJelly1* pJelly52 = new CJelly1();
		pJelly52->SetPos(WINSIZEX + 140, WINSIZEY * 0.6);
		AddGameObject(pJelly52);

		CJelly1* pJelly53 = new CJelly1();
		pJelly53->SetPos(WINSIZEX + 210, WINSIZEY * 0.6);
		AddGameObject(pJelly53);

		CJelly1* pJelly54 = new CJelly1();
		pJelly54->SetPos(WINSIZEX + 280, WINSIZEY * 0.6);
		AddGameObject(pJelly54);

		CJelly1* pJelly55 = new CJelly1();
		pJelly55->SetPos(WINSIZEX + 350, WINSIZEY * 0.6);
		AddGameObject(pJelly55);

		CJelly1* pJelly56 = new CJelly1();
		pJelly56->SetPos(WINSIZEX + 420, WINSIZEY * 0.6);
		AddGameObject(pJelly56);

		CJelly1* pJelly57 = new CJelly1();
		pJelly57->SetPos(WINSIZEX + 490, WINSIZEY * 0.6);
		AddGameObject(pJelly57);

		CJelly1* pJelly58 = new CJelly1();
		pJelly58->SetPos(WINSIZEX + 560, WINSIZEY * 0.6);
		AddGameObject(pJelly58);
	}

	if (obstacleTimer >= 55.7 && obstacleTimer <= 55.8)
	{
		obstacleTimer = -1;

		CObstacle3* p3Obs1 = new CObstacle3();
		p3Obs1->SetPos(WINSIZEX + 50, WINSIZEY * 0.75);
		AddGameObject(p3Obs1);

		CJelly1* pJelly51 = new CJelly1();
		pJelly51->SetPos(WINSIZEX + 70, WINSIZEY * 0.6);
		AddGameObject(pJelly51);

		CJelly1* pJelly52 = new CJelly1();
		pJelly52->SetPos(WINSIZEX + 140, WINSIZEY * 0.6);
		AddGameObject(pJelly52);

		CJelly1* pJelly53 = new CJelly1();
		pJelly53->SetPos(WINSIZEX + 210, WINSIZEY * 0.6);
		AddGameObject(pJelly53);

		CJelly1* pJelly54 = new CJelly1();
		pJelly54->SetPos(WINSIZEX + 280, WINSIZEY * 0.6);
		AddGameObject(pJelly54);

		CJelly1* pJelly55 = new CJelly1();
		pJelly55->SetPos(WINSIZEX + 350, WINSIZEY * 0.6);
		AddGameObject(pJelly55);

		CJelly1* pJelly56 = new CJelly1();
		pJelly56->SetPos(WINSIZEX + 420, WINSIZEY * 0.6);
		AddGameObject(pJelly56);

		CJelly1* pJelly57 = new CJelly1();
		pJelly57->SetPos(WINSIZEX + 490, WINSIZEY * 0.6);
		AddGameObject(pJelly57);

		CJelly1* pJelly58 = new CJelly1();
		pJelly58->SetPos(WINSIZEX + 560, WINSIZEY * 0.6);
		AddGameObject(pJelly58);
	}


	#pragma endregion

	if (playerHp > 0)
	{
		if (skillOn == false)
		{
			HpTimer += ABSDT;

			if (HpTimer >= 0.1)
			{
				HpTimer -= 0.1;
				playerHp -= 0.2;
			}
		}
	}

	if (BUTTONDOWN('R'))
	{
		playerHp = 0;
	}

}

void CSceneStage01::Render()
{

	RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	RENDER->Text(L"Score : " + ScreenScore + L"점", 50, 107, 300, 107, Color(255, 255, 255, 1.f), 20);
	RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	// Hp 이미지 효과 업데이트
	HPProgressBar->SetPos(70 + 500 * playerHp / 100, 70);
	HPEffect->SetPos(60 + 500 * playerHp / 100, 68);
	HPEffect->SetScale(80 + 500 * playerHp / 100, 87);

	/*RENDER->Image(
		CookierunTitle,
		1130, 15, 1270, 80);*/
	

	//일시정지 UI
	if (pause == true)
	{
		PauseImage->SetScale(WINSIZEX, WINSIZEY);
	}

	else if (pause == false)
	{
		PauseImage->SetScale(0, 0);
	}

	if (isDead == true)
	{
		FailImage->SetScale(WINSIZEX, WINSIZEY);
	}

	else if (isDead == false)
	{
		FailImage->SetScale(0, 0);
	}
	
	if (BUTTONSTAY(VK_DOWN) || BUTTONSTAY(VK_CONTROL))
	{
		SlideButtonImage->SetImageName(L"Pushed_Slide.png");
		isSliding = true;
	}
	if (BUTTONUP(VK_DOWN) || BUTTONUP(VK_CONTROL))
	{
		SlideButtonImage->SetImageName(L"Idle_Slide.png");
		isSliding = false;
	}

	if (BUTTONSTAY(VK_SPACE))
	{
		JumpButtonImage->SetImageName(L"Pushed_Jump.png");
	}
	if (BUTTONUP(VK_SPACE))
	{
		JumpButtonImage->SetImageName(L"Idle_Jump.png");
	}

	// 사망 시 UI
	/*if (isDead == true)
	{
		RENDER->Image(
			failImage,
			0, 0, WINSIZEX, WINSIZEY);
	}*/

}

void CSceneStage01::Exit()
{
	DeleteAll();
}

void CSceneStage01::Release()
{
}


