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
	if (LMOUSEDOWN(false))
	{
		CAMERA->SetTargetPos(MOUSEWORLDPOS, 1);
	}

	Vector dir;
	if (BUTTONSTAY('A'))
	{
		dir.x = -1;
	}
	else if (BUTTONSTAY('D'))
		dir.x = 1;
	else dir.x = 0;

	if (BUTTONSTAY('W'))
		dir.y = -1;
	else if (BUTTONSTAY('S'))
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
