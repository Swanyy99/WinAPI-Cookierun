#include "framework.h"
#include "CSceneTitle.h"

#include "WinAPI.h"
#include "CRenderManager.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"

extern bool pause;

CSceneTitle::CSceneTitle()
{
	TitleBackgroundImage = nullptr;
}

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Init()
{
	TitleBackgroundImage = RESOURCE->LoadImg(L"TitleCsceneImage", L"Image\\TitleCsceneImage.png");
}

void CSceneTitle::Enter()
{
	CAMERA->FadeIn(0.25f);

	pause = true;

	// 게임 시작버튼
	auto StartButtonClicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* StartButton = (CButton*)(button);
		int paramInt = (int)(param);


		Logger::Debug(StartButton->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		CAMERA->FadeIn(0.25f);
		CHANGESCENE(GroupScene::Stage01);
		pause = false;
	};

	CButton* StartButton = new CButton;
	StartButton->SetName(L"게임시작 버튼");
	StartButton->SetPos(790, 405);
	StartButton->SetScale(200, 70);
	StartButton->SetClickedCallback(StartButtonClicked, (DWORD_PTR)StartButton, (DWORD_PTR)1);
	AddGameObject(StartButton);
}

void CSceneTitle::Update()
{
	/*if (BUTTONDOWN(VK_F1))
	{
		CHANGESCENE(GroupScene::TileTool);
	}
	if (BUTTONDOWN(VK_SPACE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Stage01, 0.25f);
	}*/
}

void CSceneTitle::Render()
{
	/*RENDER->Text(L"press space to start",
		WINSIZEX * 0.5f - 100,
		WINSIZEY * 0.5f - 10,
		WINSIZEX * 0.5f + 100,
		WINSIZEY * 0.5f + 10,
		Color(0, 0, 0, 1.f),
		20.f);*/

	RENDER->Image(
		TitleBackgroundImage,
		0,0, 1280, 730);
}


void CSceneTitle::Exit()
{
}

void CSceneTitle::Release()
{
}
