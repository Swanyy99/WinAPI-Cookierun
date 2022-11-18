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

int choiceJelly;

int myJem;
int myCoin;

bool	ownPet1;
bool	ownPet2;
bool	ownPet3;

bool	ownJelly1;
bool	ownJelly2;
bool	ownJelly3;
bool	ownJelly4;
bool	ownJelly5;

bool	Equip;
bool	Purchase;

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
	choiceJelly = 1;

	ownPet1 = false;
	ownPet2 = false;
	ownPet3 = false;

	ownJelly1 = true;
	ownJelly2 = false;
	ownJelly3 = false;
	ownJelly4 = false;
	ownJelly5 = false;

	Price5000 = nullptr;
	Price500 = nullptr;

	NoPetWarning = nullptr;
	NoMoneyWarning = nullptr;

	NoMoneyWordTimer = 0;
	NoPetWordTimer = 0;
	PurchaseTimer = 0;
	EquipTimer = 0;

	PetWarning = false;
	MoneyWarning = false;

	Equip = false;
	Purchase = false;

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
	Price500 = RESOURCE->LoadImg(L"Price500", L"Image\\500Price.png");
	NoPetWarning = RESOURCE->LoadImg(L"NoPetWarning", L"Image\\NoPetWarning.png");
	NoMoneyWarning = RESOURCE->LoadImg(L"NoMoneyWarning", L"Image\\NoMoneyWarning.png");
	EquipAlarm = RESOURCE->LoadImg(L"EquipAlarm", L"Image\\EquipAlarm.png");
	PurchaseAlarm = RESOURCE->LoadImg(L"PurchaseAlarm", L"Image\\PurchaseAlarm.png");

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
		{
			choicePet = 1;
			Equip = true;
		}
		else if (ownPet1 == false)
		{
			PetWarning = true;
		}
	};

	choosePet1 = new CButton;
	choosePet1->SetName(L"펫1 선택 버튼");
	choosePet1->SetLayer(Layer::Ui);
	choosePet1->SetImage(L"ChoiceButtonIdle.png", L"ChoiceButtonMouseOver.png");
	choosePet1->SetPos(870, 180);
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
			Purchase = true;

			CSound* pSound = RESOURCE->LoadSound(L"Buy", L"Sound\\Buy.wav");
			SOUND->Play(pSound, 0.2f, false);

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
	purchasePet1->SetPos(870, 120);
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
		{
			choicePet = 2;
			Equip = true;
		}
		else if (ownPet2 == false)
		{
			PetWarning = true;
		}
	};

	choosePet2 = new CButton;
	choosePet2->SetName(L"펫2 선택 버튼");
	choosePet2->SetLayer(Layer::Ui);
	choosePet2->SetImage(L"ChoiceButtonIdle.png", L"ChoiceButtonMouseOver.png");
	choosePet2->SetPos(870, 360);
	choosePet2->SetScale(75, 48);
	choosePet2->SetText(L"", 32, Color(0, 0, 0, 1));
	choosePet2->SetClickedCallback(choosePet2Clicked, (DWORD_PTR)choosePet2, (DWORD_PTR)1);
	AddGameObject(choosePet2);


	// 펫 2 구매버튼
	auto purchasePet2Clicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* purchasePet2 = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(purchasePet2->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		if (myCoin >= 5000 && ownPet2 == false)
		{
			myCoin -= 5000;
			ownPet2 = true;
			Purchase = true;

			CSound* pSound = RESOURCE->LoadSound(L"Buy", L"Sound\\Buy.wav");
			SOUND->Play(pSound, 0.2f, false);

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
	purchasePet2->SetPos(870, 300);
	purchasePet2->SetScale(75, 48);
	purchasePet2->SetText(L"", 32, Color(0, 0, 0, 1));
	purchasePet2->SetClickedCallback(purchasePet2Clicked, (DWORD_PTR)purchasePet2, (DWORD_PTR)1);
	AddGameObject(purchasePet2);





	// 펫 3 선택 버튼
	auto choosePet3Clicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* choosePet3 = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(choosePet3->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		//CAMERA->FadeOut(1);
		if (ownPet3 == true)
		{
			choicePet = 3;
			Equip = true;
		}
		else if (ownPet3 == false)
		{
			PetWarning = true;
		}
	};

	choosePet3 = new CButton;
	choosePet3->SetName(L"펫3 선택 버튼");
	choosePet3->SetLayer(Layer::Ui);
	choosePet3->SetImage(L"ChoiceButtonIdle.png", L"ChoiceButtonMouseOver.png");
	choosePet3->SetPos(870, 540);
	choosePet3->SetScale(75, 48);
	choosePet3->SetText(L"", 32, Color(0, 0, 0, 1));
	choosePet3->SetClickedCallback(choosePet3Clicked, (DWORD_PTR)choosePet3, (DWORD_PTR)1);
	AddGameObject(choosePet3);


	// 펫 3 구매버튼
	auto purchasePet3Clicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* purchasePet3 = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(purchasePet3->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		if (myCoin >= 5000 && ownPet3 == false)
		{
			myCoin -= 5000;
			ownPet3 = true;
			Purchase = true;

			CSound* pSound = RESOURCE->LoadSound(L"Buy", L"Sound\\Buy.wav");
			SOUND->Play(pSound, 0.2f, false);

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
	purchasePet3->SetPos(870, 480);
	purchasePet3->SetScale(75, 48);
	purchasePet3->SetText(L"", 32, Color(0, 0, 0, 1));
	purchasePet3->SetClickedCallback(purchasePet3Clicked, (DWORD_PTR)purchasePet3, (DWORD_PTR)1);
	AddGameObject(purchasePet3);







	// 젤리스킨1 구매 버튼
	auto purchaseJelly1Clicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* purchaseJelly1 = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(purchaseJelly1->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		if (myJem >= 500 && ownJelly1 == false)
		{
			myJem -= 500;
			ownJelly1 = true;
			Purchase = true;

			CSound* pSound = RESOURCE->LoadSound(L"Buy", L"Sound\\Buy.wav");
			SOUND->Play(pSound, 0.2f, false);

		}
		else if (myJem < 500 && ownJelly1 == false)
		{
			MoneyWarning = true;
		}



	};

	purchaseJelly1 = new CButton;
	purchaseJelly1->SetName(L"젤리1 구매 버튼");
	purchaseJelly1->SetLayer(Layer::Ui);
	purchaseJelly1->SetImage(L"PurchaseButtonIdle.png", L"PurchaseButtonMouseOver.png");
	purchaseJelly1->SetPos(1115, 100);
	purchaseJelly1->SetScale(55, 35);
	purchaseJelly1->SetText(L"", 32, Color(0, 0, 0, 1));
	purchaseJelly1->SetClickedCallback(purchaseJelly1Clicked, (DWORD_PTR)purchaseJelly1, (DWORD_PTR)1);
	AddGameObject(purchaseJelly1);

	// 젤리스킨1 선택 버튼
	auto chooseJelly1Clicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* chooseJelly1 = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(chooseJelly1->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		if (ownJelly1 == true)
		{
			choiceJelly = 1;
			Equip = true;
		}
		else if (ownJelly1 == false)
		{
			PetWarning = true;
		}



	};

	chooseJelly1 = new CButton;
	chooseJelly1->SetName(L"젤리1 선택 버튼");
	chooseJelly1->SetLayer(Layer::Ui);
	chooseJelly1->SetImage(L"ChoiceButtonIdle.png", L"ChoiceButtonMouseOver.png");
	chooseJelly1->SetPos(1115, 140);
	chooseJelly1->SetScale(55, 35);
	chooseJelly1->SetText(L"", 32, Color(0, 0, 0, 1));
	chooseJelly1->SetClickedCallback(chooseJelly1Clicked, (DWORD_PTR)chooseJelly1, (DWORD_PTR)1);
	AddGameObject(chooseJelly1);





	// 젤리스킨2 구매 버튼
	auto purchaseJelly2Clicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* purchaseJelly2 = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(purchaseJelly2->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		if (myJem >= 500 && ownJelly2 == false)
		{
			myJem -= 500;
			ownJelly2 = true;
			Purchase = true;

			CSound* pSound = RESOURCE->LoadSound(L"Buy", L"Sound\\Buy.wav");
			SOUND->Play(pSound, 0.2f, false);


		}
		else if (myJem < 500 && ownJelly2 == false)
		{
			MoneyWarning = true;
		}



	};

	purchaseJelly2 = new CButton;
	purchaseJelly2->SetName(L"젤리2 구매 버튼");
	purchaseJelly2->SetLayer(Layer::Ui);
	purchaseJelly2->SetImage(L"PurchaseButtonIdle.png", L"PurchaseButtonMouseOver.png");
	purchaseJelly2->SetPos(1115, 210);
	purchaseJelly2->SetScale(55, 35);
	purchaseJelly2->SetText(L"", 32, Color(0, 0, 0, 1));
	purchaseJelly2->SetClickedCallback(purchaseJelly2Clicked, (DWORD_PTR)purchaseJelly2, (DWORD_PTR)1);
	AddGameObject(purchaseJelly2);

	// 젤리스킨2 선택 버튼
	auto chooseJelly2Clicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* chooseJelly2 = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(chooseJelly2->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		if (ownJelly2 == true)
		{
			choiceJelly = 2;
			Equip = true;
		}
		else if (ownJelly2 == false)
		{
			PetWarning = true;
		}
	};

	chooseJelly2 = new CButton;
	chooseJelly2->SetName(L"젤리2 선택 버튼");
	chooseJelly2->SetLayer(Layer::Ui);
	chooseJelly2->SetImage(L"ChoiceButtonIdle.png", L"ChoiceButtonMouseOver.png");
	chooseJelly2->SetPos(1115, 250);
	chooseJelly2->SetScale(55, 35);
	chooseJelly2->SetText(L"", 32, Color(0, 0, 0, 1));
	chooseJelly2->SetClickedCallback(chooseJelly2Clicked, (DWORD_PTR)chooseJelly2, (DWORD_PTR)1);
	AddGameObject(chooseJelly2);




	// 젤리스킨3 구매 버튼
	auto purchaseJelly3Clicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* purchaseJelly3 = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(purchaseJelly3->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		if (myJem >= 500 && ownJelly3 == false)
		{
			myJem -= 500;
			ownJelly3 = true;
			Purchase = true;

			CSound* pSound = RESOURCE->LoadSound(L"Buy", L"Sound\\Buy.wav");
			SOUND->Play(pSound, 0.2f, false);


		}
		else if (myJem < 500 && ownJelly3 == false)
		{
			MoneyWarning = true;
		}


	};

	purchaseJelly3 = new CButton;
	purchaseJelly3->SetName(L"젤리3 구매 버튼");
	purchaseJelly3->SetLayer(Layer::Ui);
	purchaseJelly3->SetImage(L"PurchaseButtonIdle.png", L"PurchaseButtonMouseOver.png");
	purchaseJelly3->SetPos(1115, 320);
	purchaseJelly3->SetScale(55, 35);
	purchaseJelly3->SetText(L"", 32, Color(0, 0, 0, 1));
	purchaseJelly3->SetClickedCallback(purchaseJelly3Clicked, (DWORD_PTR)purchaseJelly3, (DWORD_PTR)1);
	AddGameObject(purchaseJelly3);

	// 젤리스킨3 선택 버튼
	auto chooseJelly3Clicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* chooseJelly3 = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(chooseJelly3->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		if (ownJelly3 == true)
		{
			choiceJelly = 3;
			Equip = true;
		}
		else if (ownJelly3 == false)
		{
			PetWarning = true;
		}
	};

	chooseJelly3 = new CButton;
	chooseJelly3->SetName(L"젤리3 선택 버튼");
	chooseJelly3->SetLayer(Layer::Ui);
	chooseJelly3->SetImage(L"ChoiceButtonIdle.png", L"ChoiceButtonMouseOver.png");
	chooseJelly3->SetPos(1115, 360);
	chooseJelly3->SetScale(55, 35);
	chooseJelly3->SetText(L"", 32, Color(0, 0, 0, 1));
	chooseJelly3->SetClickedCallback(chooseJelly3Clicked, (DWORD_PTR)chooseJelly3, (DWORD_PTR)1);
	AddGameObject(chooseJelly3);




	// 젤리스킨4 구매 버튼
	auto purchaseJelly4Clicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* purchaseJelly4 = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(purchaseJelly4->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		if (myJem >= 500 && ownJelly4 == false)
		{
			myJem -= 500;
			ownJelly4 = true;
			Purchase = true;

			CSound* pSound = RESOURCE->LoadSound(L"Buy", L"Sound\\Buy.wav");
			SOUND->Play(pSound, 0.2f, false);


		}
		else if (myJem < 500 && ownJelly4 == false)
		{
			MoneyWarning = true;
		}



	};

	purchaseJelly4 = new CButton;
	purchaseJelly4->SetName(L"젤리4 구매 버튼");
	purchaseJelly4->SetLayer(Layer::Ui);
	purchaseJelly4->SetImage(L"PurchaseButtonIdle.png", L"PurchaseButtonMouseOver.png");
	purchaseJelly4->SetPos(1115, 430);
	purchaseJelly4->SetScale(55, 35);
	purchaseJelly4->SetText(L"", 32, Color(0, 0, 0, 1));
	purchaseJelly4->SetClickedCallback(purchaseJelly4Clicked, (DWORD_PTR)purchaseJelly4, (DWORD_PTR)1);
	AddGameObject(purchaseJelly4);

	// 젤리스킨4 선택 버튼
	auto chooseJelly4Clicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* chooseJelly4 = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(chooseJelly4->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		if (ownJelly4 == true)
		{
			choiceJelly = 4;
			Equip = true;
		}
		else if (ownJelly4 == false)
		{
			PetWarning = true;
		}
	};

	chooseJelly4 = new CButton;
	chooseJelly4->SetName(L"젤리4 선택 버튼");
	chooseJelly4->SetLayer(Layer::Ui);
	chooseJelly4->SetImage(L"ChoiceButtonIdle.png", L"ChoiceButtonMouseOver.png");
	chooseJelly4->SetPos(1115, 470);
	chooseJelly4->SetScale(55, 35);
	chooseJelly4->SetText(L"", 32, Color(0, 0, 0, 1));
	chooseJelly4->SetClickedCallback(chooseJelly4Clicked, (DWORD_PTR)chooseJelly4, (DWORD_PTR)1);
	AddGameObject(chooseJelly4);




	// 젤리스킨5 구매 버튼
	auto purchaseJelly5Clicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* purchaseJelly5 = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(purchaseJelly5->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		if (myJem >= 500 && ownJelly5 == false)
		{
			myJem -= 500;
			ownJelly5 = true;
			Purchase = true;

			CSound* pSound = RESOURCE->LoadSound(L"Buy", L"Sound\\Buy.wav");
			SOUND->Play(pSound, 0.2f, false);
		}
		else if (myJem < 500 && ownJelly5 == false)
		{
			MoneyWarning = true;
		}



	};

	purchaseJelly5 = new CButton;
	purchaseJelly5->SetName(L"젤리5 구매 버튼");
	purchaseJelly5->SetLayer(Layer::Ui);
	purchaseJelly5->SetImage(L"PurchaseButtonIdle.png", L"PurchaseButtonMouseOver.png");
	purchaseJelly5->SetPos(1115, 540);
	purchaseJelly5->SetScale(55, 35);
	purchaseJelly5->SetText(L"", 32, Color(0, 0, 0, 1));
	purchaseJelly5->SetClickedCallback(purchaseJelly5Clicked, (DWORD_PTR)purchaseJelly5, (DWORD_PTR)1);
	AddGameObject(purchaseJelly5);

	// 젤리스킨5 선택 버튼
	auto chooseJelly5Clicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* chooseJelly5 = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(chooseJelly5->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		if (ownJelly5 == true)
		{
			choiceJelly = 5;
			Equip = true;
		}
		else if (ownJelly5 == false)
		{
			PetWarning = true;
		}
	};

	chooseJelly5 = new CButton;
	chooseJelly5->SetName(L"젤리5 선택 버튼");
	chooseJelly5->SetLayer(Layer::Ui);
	chooseJelly5->SetImage(L"ChoiceButtonIdle.png", L"ChoiceButtonMouseOver.png");
	chooseJelly5->SetPos(1115, 580);
	chooseJelly5->SetScale(55, 35);
	chooseJelly5->SetText(L"", 32, Color(0, 0, 0, 1));
	chooseJelly5->SetClickedCallback(chooseJelly5Clicked, (DWORD_PTR)chooseJelly5, (DWORD_PTR)1);
	AddGameObject(chooseJelly5);








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
	PrepareSceneBackgroundImages->SetImageName(L"PrepareScenePetChoice2.png");
	PrepareSceneBackgroundImages->SetPos(0, 0);
	PrepareSceneBackgroundImages->SetScale(WINSIZEX, WINSIZEY);
	AddGameObject(PrepareSceneBackgroundImages);


	SOUND->Play(pSound, 0.1f, true);

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
		myCoin += 1000;
		myJem += 100;
	}

	if (BUTTONDOWN('Z'))
	{
		choiceJelly = 1;
	}
	if (BUTTONDOWN('X'))
	{
		choiceJelly = 2;
	}
	if (BUTTONDOWN('C'))
	{
		choiceJelly = 3;
	}
	if (BUTTONDOWN('V'))
	{
		choiceJelly = 4;
	}
	if (BUTTONDOWN('B'))
	{
		choiceJelly = 5;
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
			165, 135, 255, 205);
	}

	else if (choicePet == 2 && ownPet2 == true)
	{
		RENDER->Image(
			ChoosedImage,
			165, 310, 255, 380);
	}

	else if (choicePet == 3 && ownPet3 == true)
	{
		RENDER->Image(
			ChoosedImage,
			165, 490, 255, 560);
	}





	if (ownPet1 == true)
	{
		purchasePet1->SetImage(L"PurchaseButtonDisableIdle.png", L"PurchaseButtonDisableMouseOver.png");
	}
	else
	{
		RENDER->Image(
			Price5000,
			880, 95, 955, 125);
	}



	if (ownPet2 == true)
	{
		purchasePet2->SetImage(L"PurchaseButtonDisableIdle.png", L"PurchaseButtonDisableMouseOver.png");
	}
	else
	{
		RENDER->Image(
			Price5000,
			880, 275, 955, 305);
	}

	if (ownPet3 == true)
	{
		purchasePet3->SetImage(L"PurchaseButtonDisableIdle.png", L"PurchaseButtonDisableMouseOver.png");
	}
	else
	{
		RENDER->Image(
			Price5000,
			880, 455, 955, 485);
	}



	if (choiceJelly == 1 && ownJelly1 == true)
	{
		RENDER->Image(
			ChoosedImage,
			1030, 110, 1090, 160);
	}

	if (choiceJelly == 2 && ownJelly2 == true)
	{
		RENDER->Image(
			ChoosedImage,
			1030, 220, 1090, 270);
	}

	if (choiceJelly == 3 && ownJelly3 == true)
	{
		RENDER->Image(
			ChoosedImage,
			1030, 315, 1090, 375);
	}

	if (choiceJelly == 4 && ownJelly4 == true)
	{
		RENDER->Image(
			ChoosedImage,
			1030, 435, 1090, 485);
	}

	if (choiceJelly == 5 && ownJelly5 == true)
	{
		RENDER->Image(
			ChoosedImage,
			1030, 545, 1090, 595);
	}

	if (ownJelly1 == true)
	{
		purchaseJelly1->SetImage(L"PurchaseButtonDisableIdle.png", L"PurchaseButtonDisableMouseOver.png");
	}
	else
	{
		RENDER->Image(
			Price500,
			1000, 445, 1050, 475);
	}

	if (ownJelly2 == true)
	{
		purchaseJelly2->SetImage(L"PurchaseButtonDisableIdle.png", L"PurchaseButtonDisableMouseOver.png");
	}
	else
	{
		RENDER->Image(
			Price500,
			1122, 190, 1185, 215);
	}


	if (ownJelly3 == true)
	{
		purchaseJelly3->SetImage(L"PurchaseButtonDisableIdle.png", L"PurchaseButtonDisableMouseOver.png");
	}
	else
	{
		RENDER->Image(
			Price500,
			1122, 300, 1185, 325);
	}
	

	if (ownJelly4 == true)
	{
		purchaseJelly4->SetImage(L"PurchaseButtonDisableIdle.png", L"PurchaseButtonDisableMouseOver.png");
	}
	else
	{
		RENDER->Image(
			Price500,
			1122, 410, 1185, 435);
	}

	if (ownJelly5 == true)
	{
		purchaseJelly5->SetImage(L"PurchaseButtonDisableIdle.png", L"PurchaseButtonDisableMouseOver.png");
	}
	else
	{
		RENDER->Image(
			Price500,
			1122, 520, 1185, 545);
	}



	if (MoneyWarning == true)
	{
		NoPetWordTimer = 0;
		PetWarning = false;

		NoMoneyWordTimer += DT;

		RENDER->Image(
			NoMoneyWarning,
			320, 290, 960, 395);

		if (NoMoneyWordTimer >= 0.7)
		{
			NoMoneyWordTimer = 0;
			MoneyWarning = false;
		}
	}

	if (PetWarning == true)
	{
		NoMoneyWordTimer = 0;
		MoneyWarning = false;

		NoPetWordTimer += DT;

		RENDER->Image(
			NoPetWarning,
			220, 290, 1060, 395);

		if (NoPetWordTimer >= 0.7)
		{
			NoPetWordTimer = 0;
			PetWarning = false;
		}
	}


	if (Equip == true)
	{
		NoMoneyWordTimer = 0;
		MoneyWarning = false;

		NoPetWordTimer = 0;
		PetWarning = false;

		PurchaseTimer = 0;
		Purchase = false;

		EquipTimer += DT;

		RENDER->Image(
			EquipAlarm,
			220, 290, 1060, 395);

		if (EquipTimer >= 0.7)
		{
			EquipTimer = 0;
			Equip = false;
		}
	}

	if (Purchase == true)
	{
		NoMoneyWordTimer = 0;
		MoneyWarning = false;

		NoPetWordTimer = 0;
		PetWarning = false;

		EquipTimer = 0;
		Equip = false;

		PurchaseTimer += DT;

		RENDER->Image(
			PurchaseAlarm,
			220, 290, 1060, 395);

		if (PurchaseTimer >= 0.7)
		{
			PurchaseTimer = 0;
			Purchase = false;
		}
	}
}


void CScenePrepare::Exit()
{
	SOUND->Pause(pSound);

}

void CScenePrepare::Release()
{
}
