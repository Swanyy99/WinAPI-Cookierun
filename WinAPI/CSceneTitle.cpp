#include "framework.h"
#include "CSceneTitle.h"

#include "WinAPI.h"
#include "CRenderManager.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"

extern bool pause;
bool inTitle;

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

	inTitle = true;

	//pause = true;

	// 게임 시작버튼
	auto StartButtonClicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* StartButton = (CButton*)(button);
		int paramInt = (int)(param);


		Logger::Debug(StartButton->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");
		pause = false;
		inTitle = false;
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::PrePare, 0.25f);
		//CHANGESCENE(GroupScene::Stage01);
		//pause = false;
		//inTitle = false;
	};

	CButton* StartButton = new CButton;
	StartButton->SetName(L"게임시작 버튼");
	StartButton->SetPos(790, 405);
	StartButton->SetScale(300, 70);
	StartButton->SetClickedCallback(StartButtonClicked, (DWORD_PTR)StartButton, (DWORD_PTR)1);
	AddGameObject(StartButton);


	//게임 종료버튼
	auto ExitButtonClicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* ExitButton = (CButton*)(button);
		int paramInt = (int)(param);


		Logger::Debug(ExitButton->GetName() + L" 이 " + to_wstring(paramInt) + L"를 호출함");

		//wmId = IDM_EXIT;
		SendMessage(hWnd, WM_CLOSE, 0, 0);
	};

	CButton* ExitButton = new CButton;
	ExitButton->SetName(L"게임종료 버튼");
	ExitButton->SetPos(790, 545);
	ExitButton->SetScale(300, 70);
	ExitButton->SetClickedCallback(ExitButtonClicked, (DWORD_PTR)ExitButton, (DWORD_PTR)1);
	AddGameObject(ExitButton);

	SOUND->Play(pSound, 0.3f, true);

}

void CSceneTitle::Update()
{
	if (BUTTONDOWN(VK_F1))
	{
		CHANGESCENE(GroupScene::TileTool);
	}
	/*
	if (BUTTONDOWN(VK_SPACE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Stage01, 0.25f);
	}*/

	if (MOUSESCREENPOS.x > 790 && MOUSESCREENPOS.x < 1090 && MOUSESCREENPOS.y > 405 && MOUSESCREENPOS.y < 475)
	{
		TitleBackgroundImage = RESOURCE->LoadImg(L"TitleCsceneStartOverImage", L"Image\\TitleCsceneStartOverImage.png");
	}
	else if (MOUSESCREENPOS.x > 790 && MOUSESCREENPOS.x < 1090 && MOUSESCREENPOS.y > 545 && MOUSESCREENPOS.y < 615)
	{
		TitleBackgroundImage = RESOURCE->LoadImg(L"TitleCsceneExitOverImage", L"Image\\TitleCsceneExitOverImage.png");
	}
	else
	{
		TitleBackgroundImage = RESOURCE->LoadImg(L"TitleCsceneImage", L"Image\\TitleCsceneImage.png");
	}
	
}

void CSceneTitle::Render()
{

	RENDER->Image(
		TitleBackgroundImage,
		0,0, 1280, 730);
}


void CSceneTitle::Exit()
{

	SOUND->Pause(pSound);
}

void CSceneTitle::Release()
{
}
