#include "framework.h"
#include "CCore.h"
#include "WinAPI.h"

#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CInputManager.h"
#include "CSceneManager.h"
#include "CEventManager.h"
#include "CCollisionManager.h"
#include "CPathManager.h"
#include "CResourceManager.h"
#include "CCameraManager.h"
#include "CUIManager.h"
#include "CSoundManager.h"

CCore::CCore()
{

}

CCore::~CCore()
{

}

void CCore::Init()
{
	TIME->Init();
	RENDER->Init();
	INPUT->Init();
	EVENT->Init();
	COLLISION->Init();
	PATH->Init();
	RESOURCE->Init();
	CAMERA->Init();
	UI->Init();
	SOUND->Init();

	SCENE->Init();
}

void CCore::Update()
{
	// 이전 프레임에서 추가된 이벤트를 프레임 초기에 한꺼번에 처리
	EVENT->Update();

	TIME->Update();
	INPUT->Update();
	SCENE->Update();
	CAMERA->Update();
	UI->Update();
	SOUND->Update();

	// 게임 오브젝트들이 업데이트 된 후 충돌처리 진행
	COLLISION->Update();
}

void CCore::Render()
{
	RENDER->BeginDraw();

	//// 게임 표현 내용
	SCENE->Render();
	CAMERA->Render();

	//// 우상단에 현재 게임FPS 출력 (60프레임 이상을 목표로 최적화 해야함)
	Vector framePos = CAMERA->ScreenToWorldPoint(Vector(WINSIZEX - 50, 20));
	wstring frame = to_wstring(FPS);
	RENDER->Text(frame, framePos.x - 50, framePos.y - 10, framePos.x + 50, framePos.y + 10, Color(0, 0, 0, 1.f), 15);

	RENDER->EndDraw();
}

void CCore::Release()
{
	SCENE->Release();

	TIME->Release();
	RENDER->Release();
	INPUT->Release();
	EVENT->Release();
	COLLISION->Release();
	PATH->Release();
	RESOURCE->Release();
	CAMERA->Release();
	UI->Release();
	SOUND->Release();
}
