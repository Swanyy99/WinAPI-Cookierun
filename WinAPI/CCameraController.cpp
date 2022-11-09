#include "framework.h"
#include "CCameraController.h"

#include "CInputManager.h"
#include "CCameraManager.h"

CCameraController::CCameraController()
{
}

CCameraController::~CCameraController()
{
}

void CCameraController::Init()
{
}

void CCameraController::Update()
{
	/*if (LMOUSEDOWN(false))
	{
		CAMERA->SetTargetPos(MOUSEWORLDPOS, 1);
	}*/

	Vector dir;
	if (BUTTONSTAY(VK_LEFT))
	{
		dir.x = -1;
	}
	else if (BUTTONSTAY(VK_RIGHT))
		dir.x = 1;
	else dir.x = 0;

	if (BUTTONSTAY(VK_UP))
		dir.y = -1;
	else if (BUTTONSTAY(VK_DOWN))
		dir.y = 1;
	else
		dir.y = 0;

	CAMERA->Scroll(dir, m_fScrollSpeed);
}

void CCameraController::Render()
{
}

void CCameraController::Release()
{
}
