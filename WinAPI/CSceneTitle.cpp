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
	CAMERA->FadeIn(1);

	inTitle = true;
	//pause = true;

	// ���� ���۹�ư
	auto StartButtonClicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* StartButton = (CButton*)(button);
		int paramInt = (int)(param);


		Logger::Debug(StartButton->GetName() + L" �� " + to_wstring(paramInt) + L"�� ȣ����");
		pause = false;
		inTitle = false;
		CAMERA->FadeIn(0.25f);
		CHANGESCENE(GroupScene::Stage01);
		//pause = false;
		//inTitle = false;
	};

	CButton* StartButton = new CButton;
	StartButton->SetName(L"���ӽ��� ��ư");
	StartButton->SetPos(790, 405);
	StartButton->SetScale(300, 70);
	StartButton->SetClickedCallback(StartButtonClicked, (DWORD_PTR)StartButton, (DWORD_PTR)1);
	AddGameObject(StartButton);


	//���� �����ư
	auto ExitButtonClicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* ExitButton = (CButton*)(button);
		int paramInt = (int)(param);


		Logger::Debug(ExitButton->GetName() + L" �� " + to_wstring(paramInt) + L"�� ȣ����");

		//wmId = IDM_EXIT;
	};

	CButton* ExitButton = new CButton;
	ExitButton->SetName(L"�������� ��ư");
	ExitButton->SetPos(790, 545);
	ExitButton->SetScale(300, 70);
	ExitButton->SetClickedCallback(ExitButtonClicked, (DWORD_PTR)ExitButton, (DWORD_PTR)1);
	AddGameObject(ExitButton);
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
