#include "framework.h"
#include "CScenePrepare.h"

#include "WinAPI.h"
#include "CRenderManager.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CImages.h"

extern bool pause;
extern bool inTitle;
bool isPrepare;
int choicePet;

int myJem;
int myCoin;

bool	ownPet1;
bool	ownPet2;
bool	ownPet3;

bool MoneyWarning;
bool PetWarning;

wstring myJemStr;
wstring myCoinStr;

CScenePrepare::CScenePrepare()
{
	PrepareSceneBackgroundImages = nullptr;
	PrepareSceneBackgroundImage = nullptr;
	PrepareScenePetChoiceImage = nullptr;
	PrepareSceneBackgroundImage = nullptr;
	ChoosedImage = nullptr;
	choosePet1 = nullptr;
	choosePet2 = nullptr;
	choosePet3 = nullptr;
	purchasePet1 = nullptr;
	purchasePet2 = nullptr;
	purchasePet3 = nullptr;
	purchaseDisable = nullptr;
	stage1Start = nullptr;
	choicePet = 0;

	ownPet1 = false;
	ownPet2 = false;
	ownPet3 = false;

	Price5000 = nullptr;

	NoPetWarning = nullptr;
	NoMoneyWarning = nullptr;

	NoMoneyWordTimer = 0;
	NoPetWordTimer = 0;

	PetWarning = false;
	MoneyWarning = false;

	myCoin = 0;
	myJem = 0;
}

CScenePrepare::~CScenePrepare()
{
}

void CScenePrepare::Init()
{
	PrepareSceneBackgroundImage = RESOURCE->LoadImg(L"PrepareSceneBackgroundImage", L"Image\\PrepareSceneBackground.png");
	PrepareScenePetChoiceImage = RESOURCE->LoadImg(L"PrepareScenePetChoice", L"Image\\PrepareScenePetChoice.png");
	ChoosedImage = RESOURCE->LoadImg(L"ChoosedImage", L"Image\\Choiced.png");
	Price5000 = RESOURCE->LoadImg(L"Price5000", L"Image\\5000Price.png");
	NoPetWarning = RESOURCE->LoadImg(L"NoPetWarning", L"Image\\NoPetWarning.png");
	NoMoneyWarning = RESOURCE->LoadImg(L"NoMoneyWarning", L"Image\\NoMoneyWarning.png");

}


void CScenePrepare::Enter()
{
	isPrepare = true;
	CAMERA->FadeIn(0.2f);

	// 펫 1 선택버튼
	auto choosePet1Clicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* choosePet1 = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(choosePet1->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		//CAMERA->FadeOut(1);
		if (ownPet1 == true)
			choicePet = 1;
		else if (ownPet1 == false)
		{
			PetWarning = true;
		}
	};

	choosePet1 = new CButton;
	choosePet1->SetName(L"펫1 선택 버튼");
	choosePet1->SetLayer(Layer::Ui);
	choosePet1->SetImage(L"ChoiceButtonIdle.png", L"ChoiceButtonMouseOver.png");
	choosePet1->SetPos(970, 180);
	choosePet1->SetScale(75, 48);
	choosePet1->SetText(L"", 32, Color(0, 0, 0, 1));
	choosePet1->SetClickedCallback(choosePet1Clicked, (DWORD_PTR)choosePet1, (DWORD_PTR)1);
	AddGameObject(choosePet1);



	// 펫 1 구매버튼
	auto purchasePet1Clicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* purchasePet1 = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(purchasePet1->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		if (myCoin >= 5000 && ownPet1 == false)
		{
			myCoin -= 5000;
			ownPet1 = true;
		}

		else if (myCoin < 5000 && ownPet1 == false)
		{
			MoneyWarning = true;
		}
	};

	purchasePet1 = new CButton;
	purchasePet1->SetName(L"펫1 구매 버튼");
	purchasePet1->SetLayer(Layer::Ui);
	purchasePet1->SetImage(L"PurchaseButtonIdle.png", L"PurchaseButtonMouseOver.png");
	purchasePet1->SetPos(970, 120);
	purchasePet1->SetScale(75, 48);
	purchasePet1->SetText(L"", 32, Color(0, 0, 0, 1));
	purchasePet1->SetClickedCallback(purchasePet1Clicked, (DWORD_PTR)purchasePet1, (DWORD_PTR)1);
	AddGameObject(purchasePet1);




	// 펫 2 선택 버튼
	auto choosePet2Clicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* choosePet2 = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(choosePet2->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		//CAMERA->FadeOut(1);
		if (ownPet2 == true)
			choicePet = 2;
		else if (ownPet2 == false)
		{
			PetWarning = true;
		}
	};

	choosePet2 = new CButton;
	choosePet2->SetName(L"펫2 선택 버튼");
	choosePet2->SetLayer(Layer::Ui);
	choosePet2->SetImage(L"ChoiceButtonIdle.png", L"ChoiceButtonMouseOver.png");
	choosePet2->SetPos(970, 360);
	choosePet2->SetScale(75, 48);
	choosePet2->SetText(L"", 32, Color(0, 0, 0, 1));
	choosePet2->SetClickedCallback(choosePet2Clicked, (DWORD_PTR)choosePet2, (DWORD_PTR)1);
	AddGameObject(choosePet2);

	PrepareSceneBackgroundImages = new CImages();
	PrepareSceneBackgroundImages->SetImageName(L"PrepareScenePetChoice.png");
	PrepareSceneBackgroundImages->SetPos(0, 0);
	PrepareSceneBackgroundImages->SetScale(WINSIZEX, WINSIZEY);
	AddGameObject(PrepareSceneBackgroundImages);


	// 펫 2 구매버튼
	auto purchasePet2Clicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* purchasePet2 = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(purchasePet2->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		if (myCoin >= 5000 && ownPet2 == false)
		{
			myCoin -= 5000;
			ownPet2 = true;
		}
		else if (myCoin < 5000 && ownPet2 == false)
		{
			MoneyWarning = true;
		}
	};

	purchasePet2 = new CButton;
	purchasePet2->SetName(L"펫2 구매 버튼");
	purchasePet2->SetLayer(Layer::Ui);
	purchasePet2->SetImage(L"PurchaseButtonIdle.png", L"PurchaseButtonMouseOver.png");
	purchasePet2->SetPos(970, 300);
	purchasePet2->SetScale(75, 48);
	purchasePet2->SetText(L"", 32, Color(0, 0, 0, 1));
	purchasePet2->SetClickedCallback(purchasePet2Clicked, (DWORD_PTR)purchasePet2, (DWORD_PTR)1);
	AddGameObject(purchasePet2);





	// 펫 3 버튼
	auto choosePet3Clicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* choosePet3 = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(choosePet3->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		//CAMERA->FadeOut(1);
		if (ownPet3 == true)
			choicePet = 3;
		else if (ownPet3 == false)
		{
			PetWarning = true;
		}
	};

	choosePet3 = new CButton;
	choosePet3->SetName(L"펫3 선택 버튼");
	choosePet3->SetLayer(Layer::Ui);
	choosePet3->SetImage(L"ChoiceButtonIdle.png", L"ChoiceButtonMouseOver.png");
	choosePet3->SetPos(970, 540);
	choosePet3->SetScale(75, 48);
	choosePet3->SetText(L"", 32, Color(0, 0, 0, 1));
	choosePet3->SetClickedCallback(choosePet3Clicked, (DWORD_PTR)choosePet3, (DWORD_PTR)1);
	AddGameObject(choosePet3);

	PrepareSceneBackgroundImages = new CImages();
	PrepareSceneBackgroundImages->SetImageName(L"PrepareScenePetChoice.png");
	PrepareSceneBackgroundImages->SetPos(0, 0);
	PrepareSceneBackgroundImages->SetScale(WINSIZEX, WINSIZEY);
	AddGameObject(PrepareSceneBackgroundImages);

	// 펫 3 구매버튼
	auto purchasePet3Clicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* purchasePet3 = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(purchasePet3->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		if (myCoin >= 5000 && ownPet3 == false)
		{
			myCoin -= 5000;
			ownPet3 = true;
		}
		else if (myCoin < 5000 && ownPet3 == false)
		{
			MoneyWarning = true;
		}
	};

	purchasePet3 = new CButton;
	purchasePet3->SetName(L"펫3 구매 버튼");
	purchasePet3->SetLayer(Layer::Ui);
	purchasePet3->SetImage(L"PurchaseButtonIdle.png", L"PurchaseButtonMouseOver.png");
	purchasePet3->SetPos(970, 480);
	purchasePet3->SetScale(75, 48);
	purchasePet3->SetText(L"", 32, Color(0, 0, 0, 1));
	purchasePet3->SetClickedCallback(purchasePet3Clicked, (DWORD_PTR)purchasePet3, (DWORD_PTR)1);
	AddGameObject(purchasePet3);


	// 게임시작 버튼
	auto stage1StartClicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* stage1Start = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(stage1Start->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Stage01, 0.25f);
	};

	stage1Start = new CButton;
	stage1Start->SetName(L"스테이지 1 진입 버튼");
	stage1Start->SetLayer(Layer::Ui);
	stage1Start->SetImage(L"GameStartButton.png", L"GameStartButtonMouseOver.png");
	stage1Start->SetPos(540, 632); // 764 658
	stage1Start->SetScale(210, 70);
	stage1Start->SetText(L"", 32, Color(0, 0, 0, 1));
	stage1Start->SetClickedCallback(stage1StartClicked, (DWORD_PTR)stage1Start, (DWORD_PTR)1);
	AddGameObject(stage1Start);



	PrepareSceneBackgroundImages = new CImages();
	PrepareSceneBackgroundImages->SetImageName(L"PrepareScenePetChoice.png");
	PrepareSceneBackgroundImages->SetPos(0, 0);
	PrepareSceneBackgroundImages->SetScale(WINSIZEX, WINSIZEY);
	AddGameObject(PrepareSceneBackgroundImages);

}

void CScenePrepare::Update()
{
	myJemStr = to_wstring(myJem);
	myCoinStr = to_wstring(myCoin);


	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
	}

	if (BUTTONDOWN('A'))
	{
		myCoin += 10000;
		myJem += 10000;
	}

	

	/*
	RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	RENDER->Text(myCoinStr, 800, 10, 900, 30, Color(255, 255, 255, 1.f), 20);
	RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);*/
}

void CScenePrepare::Render()
{
	RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	RENDER->Text(myCoinStr, 550, 15, 630, 40, Color(255, 255, 255, 1.f), 16);

	RENDER->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	RENDER->Text(myJemStr, 670, 15, 750, 40, Color(255, 255, 255, 1.f), 16);


	if (choicePet == 1 && ownPet1 == true)
	{
		RENDER->Image(
			ChoosedImage,
			275, 135, 365, 205);
	}

	else if (choicePet == 2 && ownPet2 == true)
	{
		RENDER->Image(
			ChoosedImage,
			275, 310, 365, 380);
	}

	else if (choicePet == 3 && ownPet3 == true)
	{
		RENDER->Image(
			ChoosedImage,
			275, 485, 365, 555);
	}



	if (ownPet1 == true)
	{
		purchasePet1->SetImage(L"PurchaseButtonDisableIdle.png", L"PurchaseButtonDisableMouseOver.png");
	}
	else
	{
		RENDER->Image(
			Price5000,
			980, 95, 1055, 125);
	}



	if (ownPet2 == true)
	{
		purchasePet2->SetImage(L"PurchaseButtonDisableIdle.png", L"PurchaseButtonDisableMouseOver.png");
	}
	else
	{
		RENDER->Image(
			Price5000,
			980, 275, 1055, 305);
	}

	if (ownPet3 == true)
	{
		purchasePet3->SetImage(L"PurchaseButtonDisableIdle.png", L"PurchaseButtonDisableMouseOver.png");
	}
	else
	{
		RENDER->Image(
			Price5000,
			980, 455, 1055, 485);
	}

	if (MoneyWarning == true)
	{
		PetWarning = false;
		NoPetWordTimer = 0;

		NoMoneyWordTimer += DT;

		RENDER->Image(
			NoMoneyWarning,
			320, 290, 960, 395);

		if (NoMoneyWordTimer >= 0.7)
		{
			MoneyWarning = false;
			NoMoneyWordTimer = 0;
		}
	}

	if (PetWarning == true)
	{
		MoneyWarning = false;
		NoMoneyWordTimer = 0;

		NoPetWordTimer += DT;

		RENDER->Image(
			NoPetWarning,
			200, 290, 1080, 395);

		if (NoPetWordTimer >= 0.7)
		{
			PetWarning = false;
			NoPetWordTimer = 0;
		}
	}
}


void CScenePrepare::Exit()
{
}

void CScenePrepare::Release()
{
}
