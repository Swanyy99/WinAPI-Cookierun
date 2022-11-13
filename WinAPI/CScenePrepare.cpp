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

CScenePrepare::CScenePrepare()
{
	PrepareSceneBackgroundImages = nullptr;
	PrepareSceneBackgroundImage = nullptr;
	PrepareScenePetChoiceImage = nullptr;
	PrepareSceneBackgroundImage = nullptr;
	ChoosedImage = nullptr;
	choosePet1 = nullptr;
	choosePet2 = nullptr;
	stage1Start = nullptr;
	choicePet = 1;
}

CScenePrepare::~CScenePrepare()
{
}

void CScenePrepare::Init()
{
	PrepareSceneBackgroundImage = RESOURCE->LoadImg(L"PrepareSceneBackgroundImage", L"Image\\PrepareSceneBackground.png");
	PrepareScenePetChoiceImage = RESOURCE->LoadImg(L"PrepareScenePetChoice", L"Image\\PrepareScenePetChoice.png");
	ChoosedImage = RESOURCE->LoadImg(L"ChoosedImage", L"Image\\Choiced.png");

}


void CScenePrepare::Enter()
{
	isPrepare = true;


	// 펫 1 버튼
	auto choosePet1Clicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* choosePet1 = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(choosePet1->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		//CAMERA->FadeOut(1);
		choicePet = 1;
	};

	choosePet1 = new CButton;
	choosePet1->SetName(L"펫1 선택 버튼");
	choosePet1->SetLayer(Layer::Ui);
	choosePet1->SetImage(L"ChoiceButtonIdle.png", L"ChoiceButtonMouseOver.png");
	choosePet1->SetPos(1005, 225);
	choosePet1->SetScale(95, 60);
	choosePet1->SetText(L"", 32, Color(0, 0, 0, 1));
	choosePet1->SetClickedCallback(choosePet1Clicked, (DWORD_PTR)choosePet1, (DWORD_PTR)1);
	AddGameObject(choosePet1);

	// 펫 2 버튼
	auto choosePet2Clicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* choosePet2 = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(choosePet2->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		//CAMERA->FadeOut(1);
		choicePet = 2;
	};

	choosePet2 = new CButton;
	choosePet2->SetName(L"펫2 선택 버튼");
	choosePet2->SetLayer(Layer::Ui);
	choosePet2->SetImage(L"ChoiceButtonIdle.png", L"ChoiceButtonMouseOver.png");
	choosePet2->SetPos(1005, 425);
	choosePet2->SetScale(95, 60);
	choosePet2->SetText(L"", 32, Color(0, 0, 0, 1));
	choosePet2->SetClickedCallback(choosePet2Clicked, (DWORD_PTR)choosePet2, (DWORD_PTR)1);
	AddGameObject(choosePet2);

	PrepareSceneBackgroundImages = new CImages();
	PrepareSceneBackgroundImages->SetImageName(L"PrepareScenePetChoice.png");
	PrepareSceneBackgroundImages->SetPos(0, 0);
	PrepareSceneBackgroundImages->SetScale(WINSIZEX, WINSIZEY);
	AddGameObject(PrepareSceneBackgroundImages);


	// 게임시작 버튼
	auto stage1StartClicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* stage1Start = (CButton*)(button);
		int paramInt = (int)(param);

		Logger::Debug(stage1Start->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		//CAMERA->FadeOut(1);
		CHANGESCENE(GroupScene::Stage01);
	};

	stage1Start = new CButton;
	stage1Start->SetName(L"스테이지 1 진입 버튼");
	stage1Start->SetLayer(Layer::Ui);
	stage1Start->SetImage(L"GameStartButton.png", L"GameStartButtonMouseOver.png");
	stage1Start->SetPos(510, 580); // 764 658
	stage1Start->SetScale(220, 75);
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
}

void CScenePrepare::Render()
{


	if (choicePet == 1)
	{
		RENDER->Image(
			ChoosedImage,
			200, 210, 310, 290);
	}

	if (choicePet == 2)
	{
		RENDER->Image(
			ChoosedImage,
			200, 410, 310, 490);
	}
}


void CScenePrepare::Exit()
{
}

void CScenePrepare::Release()
{
}
