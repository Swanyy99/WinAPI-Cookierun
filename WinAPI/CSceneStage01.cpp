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
#include "CPet3.h"
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

#include "CJemBottle.h"
#include "CCoin.h"

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

int JemADD;
int CoinADD;

CSceneStage01::CSceneStage01()
{
	pPlayer = nullptr;
	pPet = nullptr;
	pPet2 = nullptr;
	pPet3 = nullptr;


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
	ScreenJem = L"";
	ScreenCoin = L"";
	score = 0;
	isRetry = false;
	isDebugMode = false;
	

	JemAcquire = nullptr;
	JemADD = 0;
	CoinAcquire = nullptr;
	CoinADD = 0;
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
	
	else if (choicePet == 3)	// 3 선택
	{
		pPet3 = new CPet3();
		pPet3->SetPos(200, WINSIZEY * 0.45f);
		AddGameObject(pPet3);
	}

	JemADD = 0;
	CoinADD = 0;
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
		CAMERA->FadeOut(0.2f);
		playerHp += 1;
		isDead = false;
		isDash = false;
		pause = false;
		DELAYCHANGESCENE(GroupScene::Title, 0.2f);
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


	JemAcquire = RESOURCE->LoadImg(L"JemScreen", L"Image\\Jem.png");
	CoinAcquire = RESOURCE->LoadImg(L"CoinScreen", L"Image\\Coin.png");



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
	ScreenJem = to_wstring(JemADD);
	ScreenCoin = to_wstring(CoinADD);

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

		SummonCoin(WINSIZEX, WINSIZEY * 0.5);
		SummonObstacle1(WINSIZEX, WINSIZEY * 0.79);
		SummonJelly1(WINSIZEX, WINSIZEY * 0.65);
		SummonJelly1(WINSIZEX + 100, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 200, WINSIZEY * 0.75);
		SummonObstacleSky(WINSIZEX + 300, WINSIZEY * 0.3);
		SummonJelly1(WINSIZEX + 300, WINSIZEY * 0.77);
		SummonJelly1(WINSIZEX + 400, WINSIZEY * 0.75);
		SummonJelly1(WINSIZEX + 500, WINSIZEY * 0.7);
	}

	if (obstacleTimer >= 5 && obstacleTimer <= 5.1)
	{
		obstacleTimer += 1;

		SummonObstacle1(WINSIZEX, WINSIZEY * 0.79);
		SummonJelly1(WINSIZEX, WINSIZEY * 0.65);
		SummonDashItem(WINSIZEX, WINSIZEY * 0.5);
		SummonJelly1(WINSIZEX + 100, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 200, WINSIZEY * 0.75);
		SummonJelly1(WINSIZEX + 300, WINSIZEY * 0.77);
		SummonObstacleSky(WINSIZEX + 300, WINSIZEY * 0.3);
		SummonJelly1(WINSIZEX + 400, WINSIZEY * 0.75);
		SummonJelly1(WINSIZEX + 500, WINSIZEY * 0.7);

	}

	if (obstacleTimer >= 8 && obstacleTimer <= 8.1)
	{
		obstacleTimer += 1;

		SummonObstacle1(WINSIZEX, WINSIZEY * 0.79);
		SummonJelly1(WINSIZEX, WINSIZEY * 0.65);
		SummonMagnetItem(WINSIZEX, WINSIZEY * 0.5);
		SummonJelly1(WINSIZEX + 100, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 200, WINSIZEY * 0.75);
		SummonJelly1(WINSIZEX + 300, WINSIZEY * 0.77);
		SummonObstacleSky(WINSIZEX + 300, WINSIZEY * 0.3);
		SummonJelly1(WINSIZEX + 400, WINSIZEY * 0.75);
		SummonJelly1(WINSIZEX + 400, WINSIZEY * 0.6);
		SummonJelly1(WINSIZEX + 500, WINSIZEY * 0.75);
		SummonJelly1(WINSIZEX + 500, WINSIZEY * 0.6);
		SummonJelly1(WINSIZEX + 600, WINSIZEY * 0.75);
		SummonJelly1(WINSIZEX + 600, WINSIZEY * 0.6);
		SummonJelly1(WINSIZEX + 700, WINSIZEY * 0.75);
		SummonJelly1(WINSIZEX + 700, WINSIZEY * 0.6);
		SummonJelly1(WINSIZEX + 800, WINSIZEY * 0.75);
		SummonJelly1(WINSIZEX + 800, WINSIZEY * 0.6);

	}

	if (obstacleTimer >= 11.7 && obstacleTimer <= 11.8)
	{
		obstacleTimer += 1;

		SummonObstacleSky(WINSIZEX + 100, WINSIZEY * 0.3);
		SummonJelly1(WINSIZEX + 100, WINSIZEY * 0.77);
		SummonJelly1(WINSIZEX + 175, WINSIZEY * 0.77);
		SummonObstacleSky(WINSIZEX + 250, WINSIZEY * 0.3);
		SummonJelly1(WINSIZEX + 255, WINSIZEY * 0.77);
		SummonJelly1(WINSIZEX + 325, WINSIZEY * 0.77);
		SummonObstacleSky(WINSIZEX + 400, WINSIZEY * 0.3);
		SummonJelly1(WINSIZEX + 400, WINSIZEY * 0.77);
		SummonJelly1(WINSIZEX + 475, WINSIZEY * 0.77);
		SummonObstacleSky(WINSIZEX + 550, WINSIZEY * 0.3);
		SummonJelly1(WINSIZEX + 550, WINSIZEY * 0.77);
		SummonJelly1(WINSIZEX + 650, WINSIZEY * 0.75);
		SummonJelly1(WINSIZEX + 750, WINSIZEY * 0.7);

	}

	if (obstacleTimer >= 15.5 && obstacleTimer <= 15.6)
	{
		obstacleTimer += 1;

		SummonObstacle1(WINSIZEX, WINSIZEY * 0.79);
		SummonObstacle1(WINSIZEX + 20, WINSIZEY * 0.79);
		SummonHpItem(WINSIZEX + 10, WINSIZEY * 0.35);
		SummonJelly1(WINSIZEX + 10, WINSIZEY * 0.5);
		SummonJelly1(WINSIZEX + 10, WINSIZEY * 0.62);
		SummonJelly1(WINSIZEX + 100, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 200, WINSIZEY * 0.75);
		SummonJelly1(WINSIZEX + 300, WINSIZEY * 0.77);
		SummonObstacleSky(WINSIZEX + 300, WINSIZEY * 0.3);
		SummonJelly1(WINSIZEX + 400, WINSIZEY * 0.75);
		SummonJelly1(WINSIZEX + 500, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 600, WINSIZEY * 0.7);

	}

	if (obstacleTimer >= 18.5 && obstacleTimer <= 18.6)
	{
		obstacleTimer += 1;

		SummonJelly1(WINSIZEX + 100, WINSIZEY * 0.51);
		SummonJelly1(WINSIZEX + 100, WINSIZEY * 0.63);
		SummonJelly1(WINSIZEX + 100, WINSIZEY * 0.75);
		SummonJelly1(WINSIZEX + 200, WINSIZEY * 0.51);
		SummonJelly1(WINSIZEX + 200, WINSIZEY * 0.63);
		SummonJelly1(WINSIZEX + 200, WINSIZEY * 0.75);
		SummonJelly1(WINSIZEX + 300, WINSIZEY * 0.51);
		SummonJelly1(WINSIZEX + 300, WINSIZEY * 0.63);
		SummonJelly1(WINSIZEX + 300, WINSIZEY * 0.75);
		SummonJelly1(WINSIZEX + 400, WINSIZEY * 0.51);
		SummonJelly1(WINSIZEX + 400, WINSIZEY * 0.63);
		SummonJelly1(WINSIZEX + 400, WINSIZEY * 0.75);
		SummonJelly1(WINSIZEX + 500, WINSIZEY * 0.51);
		SummonJelly1(WINSIZEX + 500, WINSIZEY * 0.63);
		SummonJelly1(WINSIZEX + 500, WINSIZEY * 0.75);
		SummonJelly1(WINSIZEX + 600, WINSIZEY * 0.51);
		SummonJelly1(WINSIZEX + 600, WINSIZEY * 0.63);
		SummonJelly1(WINSIZEX + 600, WINSIZEY * 0.75);

		SummonCoin(WINSIZEX + 100, WINSIZEY * 0.4);
		SummonCoin(WINSIZEX + 200, WINSIZEY * 0.4);
		SummonCoin(WINSIZEX + 300, WINSIZEY * 0.4);
		SummonCoin(WINSIZEX + 400, WINSIZEY * 0.4);
		SummonCoin(WINSIZEX + 500, WINSIZEY * 0.4);
		SummonCoin(WINSIZEX + 600, WINSIZEY * 0.4);

	}

	if (obstacleTimer >= 21.7 && obstacleTimer <= 21.8)
	{
		obstacleTimer += 1;

		SummonJelly1(WINSIZEX + 100, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 200, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 300, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 400, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 500, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 600, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 640, WINSIZEY * 0.5);
		SummonJelly1(WINSIZEX + 790, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 890, WINSIZEY * 0.7);
		SummonCoin(WINSIZEX + 790, WINSIZEY * 0.55);
		SummonCoin(WINSIZEX + 890, WINSIZEY * 0.55);
		SummonObstacle2(WINSIZEX + 1000, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 1040, WINSIZEY * 0.5);
		SummonJelly1(WINSIZEX + 1190, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 1290, WINSIZEY * 0.7);
		SummonCoin(WINSIZEX + 1190, WINSIZEY * 0.55);
		SummonCoin(WINSIZEX + 1290, WINSIZEY * 0.55);
		SummonObstacle2(WINSIZEX + 1400, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 1440, WINSIZEY * 0.5);
		SummonJelly1(WINSIZEX + 1590, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 1690, WINSIZEY * 0.7);
		SummonCoin(WINSIZEX + 1590, WINSIZEY * 0.55);
		SummonCoin(WINSIZEX + 1690, WINSIZEY * 0.55);
		SummonObstacle2(WINSIZEX + 1800, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 1840, WINSIZEY * 0.5);
		SummonJelly1(WINSIZEX + 1990, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 2090, WINSIZEY * 0.7);
		SummonCoin(WINSIZEX + 1990, WINSIZEY * 0.55);
		SummonCoin(WINSIZEX + 2090, WINSIZEY * 0.55);
		SummonObstacle2(WINSIZEX + 2200, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 2240, WINSIZEY * 0.5);
		SummonJelly1(WINSIZEX + 2390, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 2490, WINSIZEY * 0.7);
		SummonCoin(WINSIZEX + 2390, WINSIZEY * 0.55);
		SummonCoin(WINSIZEX + 2490, WINSIZEY * 0.55);
	}

	if (obstacleTimer >= 31 && obstacleTimer <= 31.1)
	{
		obstacleTimer += 1;

		SummonJelly1(WINSIZEX + 100, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 200, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 300, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 400, WINSIZEY * 0.7);

		SummonCoin(WINSIZEX + 100, WINSIZEY * 0.55);
		SummonCoin(WINSIZEX + 200, WINSIZEY * 0.55);
		SummonCoin(WINSIZEX + 300, WINSIZEY * 0.55);
		SummonCoin(WINSIZEX + 400, WINSIZEY * 0.55);

		SummonDashItem(WINSIZEX + 500, WINSIZEY * 0.7);
		SummonMagnetItem(WINSIZEX + 500, WINSIZEY * 0.6);
		SummonObstacle2(WINSIZEX + 600, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 700, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 800, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 900, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 1000, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 1100, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 1200, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 1300, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 1400, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 1500, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 1600, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 1700, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 1800, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 1900, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 2000, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 2100, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 2200, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 2300, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 2400, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 2500, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 2600, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 2700, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 2800, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 2900, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 3000, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 3100, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 3200, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 3300, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 3400, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 3500, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 3600, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 3700, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 3800, WINSIZEY * 0.7);
		SummonObstacle2(WINSIZEX + 3900, WINSIZEY * 0.7);

		SummonJelly1(WINSIZEX + 600, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 700, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 800, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 900, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 1000, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 1100, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 1200, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 1300, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 1400, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 1500, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 1600, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 1700, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 1800, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 1900, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 2000, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 2100, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 2200, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 2300, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 2400, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 2500, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 2600, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 2700, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 2800, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 2900, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 3000, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 3100, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 3200, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 3300, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 3400, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 3500, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 3600, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 3700, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 3800, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 3900, WINSIZEY * 0.53);								   
		SummonJelly1(WINSIZEX + 4070, WINSIZEY * 0.53);
		SummonJelly1(WINSIZEX + 4170, WINSIZEY * 0.6);
		SummonJelly1(WINSIZEX + 4270, WINSIZEY * 0.65);
		SummonJelly1(WINSIZEX + 4370, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 4470, WINSIZEY * 0.7);
		SummonJelly1(WINSIZEX + 4570, WINSIZEY * 0.7);

	
	}

	if (obstacleTimer >= 48 && obstacleTimer <= 48.1)
	{
		obstacleTimer = 1;
		SummonObstacle3(WINSIZEX, WINSIZEY * 0.75);
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
	RENDER->Text(L"Score : " + ScreenScore + L"점", 50, 109, 300, 109, Color(255, 255, 255, 1.f), 21);
	RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	// Hp 이미지 효과 업데이트
	HPProgressBar->SetPos(70 + 500 * playerHp / 100, 70);
	HPEffect->SetPos(60 + 500 * playerHp / 100, 68);
	HPEffect->SetScale(80 + 500 * playerHp / 100, 87);

	RENDER->Image(
		CoinAcquire,
		50, 130, 80, 160);

	RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	RENDER->Text(ScreenCoin, 90, 130, 250, 160, Color(255, 255, 255, 1.f), 20);

	RENDER->Image(
		JemAcquire,
		50, 170, 80, 200);
	
	RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	RENDER->Text(ScreenJem, 90, 170, 250, 200, Color(255, 255, 255, 1.f), 20);
	RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);


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

void CSceneStage01::SummonJelly1(float x, float y)
{
	CJelly1* J1 = new CJelly1();
	J1->SetPos(x, y);
	AddGameObject(J1);
}

void CSceneStage01::SummonObstacle1(float x, float y)
{
	CObstacle* O1 = new CObstacle();
	O1->SetPos(x, y);
	AddGameObject(O1);
}

void CSceneStage01::SummonObstacle2(float x, float y)
{
	CObstacle2* O2 = new CObstacle2();
	O2->SetPos(x, y);
	AddGameObject(O2);
}

void CSceneStage01::SummonObstacle3(float x, float y)
{
	CObstacle3* O3 = new CObstacle3();
	O3->SetPos(x, y);
	AddGameObject(O3);
}

void CSceneStage01::SummonObstacleSky(float x, float y)
{
	CObstacleSky* OS = new CObstacleSky();
	OS->SetPos(x, y);
	AddGameObject(OS);
}

void CSceneStage01::SummonDashItem(float x, float y)
{
	CDashItem* DI = new CDashItem();
	DI->SetPos(x, y);
	AddGameObject(DI);
}

void CSceneStage01::SummonHpItem(float x, float y)
{
	CHeartItem* HI = new CHeartItem();
	HI->SetPos(x, y);
	AddGameObject(HI);
}

void CSceneStage01::SummonMagnetItem(float x, float y)
{
	CMagnetItem* MI = new CMagnetItem();
	MI->SetPos(x, y);
	AddGameObject(MI);
}

void CSceneStage01::SummonJemBottle(float x, float y)
{
	CJemBottle* JB = new CJemBottle();
	JB->SetPos(x, y);
	AddGameObject(JB);
}

void CSceneStage01::SummonCoin(float x, float y)
{
	CCoin* C = new CCoin();
	C->SetPos(x, y);
	AddGameObject(C);
}




