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
#include "CUnderUI.h"

#include "CJemBottle.h"
#include "CCoin.h"

#include "CStage01MapPattern.h"

CStage01MapPattern* Stage01;

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
extern bool skillOn3;

extern int choicePet;

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
	/*LoadingImage = new CUnderUI();
	LoadingImage->SetImageName(L"Loading.png");
	LoadingImage->SetPos(-100, 0);
	LoadingImage->SetScale(WINSIZEX + 100, WINSIZEY);
	AddGameObject(LoadingImage);*/


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
	
	else if (choicePet == 3)	// 우유 엔젤 선택
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

		CSound* pSound = RESOURCE->LoadSound(L"ButtonClick", L"Sound\\ButtonClick.wav");
		SOUND->Play(pSound, 0.15f, false);

		if (isDead == true)
		{
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

		CSound* pSound = RESOURCE->LoadSound(L"ButtonClick", L"Sound\\ButtonClick.wav");
		SOUND->Play(pSound, 0.15f, false);

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

		CSound* pSound = RESOURCE->LoadSound(L"ButtonClick", L"Sound\\ButtonClick.wav");
		SOUND->Play(pSound, 0.15f, false);

		CAMERA->FadeOut(0.2f);
		playerHp += 1;
		isDead = false;
		isDash = false;
		pause = false;
		skillOn3 = false;
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

	

	// 슬라이드 버튼 이미지
	SlideButtonImage = new CUnderUI();
	SlideButtonImage->SetImageName(L"Idle_Slide.png");
	SlideButtonImage->SetPos(30, 580);
	SlideButtonImage->SetScale(180, 680);
	AddGameObject(SlideButtonImage);


	// 점프 버튼 이미지
	JumpButtonImage = new CUnderUI();
	JumpButtonImage->SetImageName(L"Idle_Jump.png");
	JumpButtonImage->SetPos(1100, 580);
	JumpButtonImage->SetScale(1250, 680);
	AddGameObject(JumpButtonImage);

	// 일시정지 화면 반투명효과 + 일시정지 글자
	PauseImage = new CUnderUI();
	PauseImage->SetImageName(L"Pause.png");
	PauseImage->SetPos(0, 0);
	PauseImage->SetScale(0, 0);
	AddGameObject(PauseImage);

	// 사망 화면 반투명효과 + 으앙주금 글자
	FailImage = new CUnderUI();
	FailImage->SetImageName(L"Fail.png");
	FailImage->SetPos(0, 0);
	FailImage->SetScale(0, 0);
	AddGameObject(FailImage);


	// CookierRun title 이미지
	CookierunTitle = new CUnderUI();
	CookierunTitle->SetImageName(L"CookierunTitle.png");
	CookierunTitle->SetPos(1130, 15);
	CookierunTitle->SetScale(1270, 80);
	AddGameObject(CookierunTitle);

	// HP Back Bar 이미지
	HPBackBar = new CUnderUI();
	HPBackBar->SetImageName(L"HP_BackBar.png");
	HPBackBar->SetPos(70, 70);
	HPBackBar->SetScale(572, 85);
	AddGameObject(HPBackBar);

	// HP Bar 이미지
	HPBar = new CUnderUI();
	HPBar->SetImageName(L"HP_Bar.png");
	HPBar->SetPos(70, 68);
	HPBar->SetScale(570, 87);
	AddGameObject(HPBar);

	// HP Progress Bar 이미지
	HPProgressBar = new CUnderUI();
	HPProgressBar->SetImageName(L"HP_ProgressBar.png");
	HPProgressBar->SetPos(70 + 500 * playerHp / 100, 70);
	HPProgressBar->SetScale(570, 85);
	AddGameObject(HPProgressBar);

	// HP Effect 이미지
	HPEffect = new CUnderUI();
	HPEffect->SetImageName(L"HP_Effect.png");
	HPEffect->SetPos(60 + 500 * playerHp / 100, 68);
	HPEffect->SetScale(80 + 500 * playerHp / 100, 87);
	AddGameObject(HPEffect);

	// HP Icon 이미지
	HPIcon = new CUnderUI();
	HPIcon->SetImageName(L"HP_Icon.png");
	HPIcon->SetPos(40, 50);
	HPIcon->SetScale(90, 100);
	AddGameObject(HPIcon);


	JemAcquire = RESOURCE->LoadImg(L"JemScreen", L"Image\\Jem.png");
	CoinAcquire = RESOURCE->LoadImg(L"CoinScreen", L"Image\\Coin.png");



	CFloor* pFloor2 = new CFloor();
	pFloor2->SetPos(0, WINSIZEY * 0.9);
	pFloor2->SetDir(Vector(1, 0));
	AddGameObject(pFloor2);

	CFloor* pFloor3 = new CFloor();
	pFloor3->SetPos(319, WINSIZEY * 0.9);
	pFloor3->SetDir(Vector(1, 0));
	AddGameObject(pFloor3);

	CFloor* pFloor4 = new CFloor();
	pFloor4->SetPos(638, WINSIZEY * 0.9);
	pFloor4->SetDir(Vector(1, 0));
	AddGameObject(pFloor4);

	CFloor* pFloor5 = new CFloor();
	pFloor5->SetPos(957, WINSIZEY * 0.9);
	pFloor5->SetDir(Vector(1, 0));
	AddGameObject(pFloor5);

	CFloor* pFloor1 = new CFloor();
	pFloor1->SetPos(1276, WINSIZEY * 0.9);
	pFloor1->SetDir(Vector(1, 0));
	AddGameObject(pFloor1);

	CFloor* pFloor6 = new CFloor();
	pFloor6->SetPos(1595, WINSIZEY * 0.9);
	pFloor6->SetDir(Vector(1, 0));
	AddGameObject(pFloor6);

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


	CAMERA->FadeIn(0.1f);

	SOUND->Play(pSound, 0.2f, true);


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

	#pragma region 맵패턴 생성
	if (obstacleTimer >= 2 && obstacleTimer <= 2.1)
	{
		obstacleTimer += 1;

		Stage01->Stage01MapPattern01();

	}

	if (obstacleTimer >= 5 && obstacleTimer <= 5.1)
	{
		obstacleTimer += 1;

		Stage01->Stage01MapPattern02();

	}

	if (obstacleTimer >= 8 && obstacleTimer <= 8.1)
	{
		obstacleTimer += 1;

		Stage01->Stage01MapPattern03();

	}

	if (obstacleTimer >= 11.7 && obstacleTimer <= 11.8)
	{
		obstacleTimer += 1;

		Stage01->Stage01MapPattern04();

	}

	if (obstacleTimer >= 15.5 && obstacleTimer <= 15.6)
	{
		obstacleTimer += 1;

		Stage01->Stage01MapPattern05();

	}

	if (obstacleTimer >= 18.5 && obstacleTimer <= 18.6)
	{
		obstacleTimer += 1;

		Stage01->Stage01MapPattern06();

	}

	if (obstacleTimer >= 21.7 && obstacleTimer <= 21.8)
	{
		obstacleTimer += 1;

		Stage01->Stage01MapPattern07();
	}

	if (obstacleTimer >= 31 && obstacleTimer <= 31.1)
	{
		obstacleTimer += 1;

		Stage01->Stage01MapPattern08();

	
	}

	if (obstacleTimer >= 48 && obstacleTimer <= 48.1)
	{
		obstacleTimer = 1;
		Stage01->Stage01MapPattern09();
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
	// Score
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


	// 일시정지 UI
	if (pause == true)
	{
		PauseImage->SetScale(WINSIZEX, WINSIZEY);
	}

	else if (pause == false)
	{
		PauseImage->SetScale(0, 0);
	}

	// 사망 UI
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
	}
	if (BUTTONUP(VK_DOWN) || BUTTONUP(VK_CONTROL))
	{
		SlideButtonImage->SetImageName(L"Idle_Slide.png");
	}

	if (BUTTONSTAY(VK_SPACE))
	{
		JumpButtonImage->SetImageName(L"Pushed_Jump.png");
	}
	if (BUTTONUP(VK_SPACE))
	{
		JumpButtonImage->SetImageName(L"Idle_Jump.png");
	}

}

void CSceneStage01::Exit()
{
	DeleteAll();
	SOUND->Pause(pSound);
}

void CSceneStage01::Release()
{
}






