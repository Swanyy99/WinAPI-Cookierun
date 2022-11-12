#include "framework.h"
#include "CScenePrepare.h"

#include "WinAPI.h"
#include "CRenderManager.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"

extern bool pause;

CScenePrepare::CScenePrepare()
{
	PrepareSceneBackgroundImage = nullptr;
}

CScenePrepare::~CScenePrepare()
{
}

void CScenePrepare::Init()
{
	PrepareSceneBackgroundImage = RESOURCE->LoadImg(L"PrepareSceneBackgroundImage", L"Image\\PrepareSceneBackground.png");
}


void CScenePrepare::Enter()
{
	CAMERA->FadeIn(1);


	// ���� ���۹�ư
	auto StartButtonClicked = [](DWORD_PTR button, DWORD_PTR param) {
		CButton* StartButton = (CButton*)(button);
		int paramInt = (int)(param);


		Logger::Debug(StartButton->GetName() + L" �� " + to_wstring(paramInt) + L"�� ȣ����");
		pause = false;
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
		SendMessage(hWnd, WM_CLOSE, 0, 0);
	};

	CButton* ExitButton = new CButton;
	ExitButton->SetName(L"�������� ��ư");
	ExitButton->SetPos(790, 545);
	ExitButton->SetScale(300, 70);
	ExitButton->SetClickedCallback(ExitButtonClicked, (DWORD_PTR)ExitButton, (DWORD_PTR)1);
	AddGameObject(ExitButton);
}

void CScenePrepare::Update()
{

	if (MOUSESCREENPOS.x > 790 && MOUSESCREENPOS.x < 1090 && MOUSESCREENPOS.y > 405 && MOUSESCREENPOS.y < 475)
	{
		PrepareSceneBackgroundImage = RESOURCE->LoadImg(L"TitleCsceneStartOverImage", L"Image\\TitleCsceneStartOverImage.png");
	}
	else if (MOUSESCREENPOS.x > 790 && MOUSESCREENPOS.x < 1090 && MOUSESCREENPOS.y > 545 && MOUSESCREENPOS.y < 615)
	{
		PrepareSceneBackgroundImage = RESOURCE->LoadImg(L"TitleCsceneExitOverImage", L"Image\\TitleCsceneExitOverImage.png");
	}
	else
	{
		PrepareSceneBackgroundImage = RESOURCE->LoadImg(L"TitleCsceneImage", L"Image\\TitleCsceneImage.png");
	}

}

void CScenePrepare::Render()
{

	RENDER->Image(
		PrepareSceneBackgroundImage,
		0, 0, 1280, 730);
}


void CScenePrepare::Exit()
{
}

void CScenePrepare::Release()
{
}
