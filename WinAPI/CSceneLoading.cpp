#include "framework.h"
#include "CSceneLoading.h"
#include "CRenderManager.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"


CSceneLoading::CSceneLoading()
{
	LoadingBackgroundImage = nullptr;
	m_fLoadingTimer = 0;
}

CSceneLoading::~CSceneLoading()
{
}

void CSceneLoading::Init()
{
	LoadingBackgroundImage = RESOURCE->LoadImg(L"Loading", L"Image\\Loading2.png");
}


void CSceneLoading::Enter()
{
	m_fLoadingTimer = 0;

	CAMERA->FadeIn(0.25f);

}

void CSceneLoading::Update()
{

	m_fLoadingTimer += ABSDT;

	if (m_fLoadingTimer >= 1.5)
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Stage01, 0.25f);
	}

}

void CSceneLoading::Render()
{

	RENDER->Image(
		LoadingBackgroundImage,
		0, 0, 1280, 735);
}


void CSceneLoading::Exit()
{

}

void CSceneLoading::Release()
{
}
