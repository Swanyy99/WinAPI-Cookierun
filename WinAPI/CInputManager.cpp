#include "framework.h"
#include "CInputManager.h"

#include "CCameraManager.h"
#include "CUIManager.h"
#include "WinAPI.h"

CInputManager::CInputManager()
{
	// 키 상태를 모두 누르지 않은 상태로 초기화
	m_arrPrevKey[0] = { false };
	m_arrCurKey[0] = { false };
	m_vecMousePos = { 0, 0 };
}

CInputManager::~CInputManager()
{
}

void CInputManager::Init()
{
}

void CInputManager::Update()
{
	// 현재 선택(Focus)된 윈도우가 게임 윈도우인가를 확인
	if (hWnd != GetFocus())
	{
		// 윈도우가 선택(Focus)된 상태가 아닐 경우 키입력을 해제시킴
		for (int key = 0; key < VKEY_SIZE; key++)
		{
			m_arrPrevKey[key] = m_arrCurKey[key];
			m_arrCurKey[key] = false;
		}
		return;
	}

	// 모든 키 사이즈만큼 반복하며 입력상태를 확인
	for (int key = 0; key < VKEY_SIZE; key++)
	{
		m_arrPrevKey[key] = m_arrCurKey[key];
		if (GetAsyncKeyState(key) & 0x8000)
		{
			m_arrCurKey[key] = true;
		}
		else
		{
			m_arrCurKey[key] = false;
		}
	}

	POINT point;
	// GetCursorPos() 윈도우에서 모니터 좌상단 기준 마우스의 좌표를 반환
	GetCursorPos(&point);
	// 모니터 좌상단 기준 마우스 좌표를 게임 윈도우 기준 마우스 위치로 계산
	ScreenToClient(hWnd, &point);
	m_vecMousePos = Vector((float)point.x, (float)point.y);
}

void CInputManager::Release()
{
}

bool CInputManager::GetButton(const int key)
{
	// 키가 눌리고 있는 중
	return (true == m_arrCurKey[key] && true == m_arrPrevKey[key]);
}

bool CInputManager::GetButtonUp(const int key)
{
	// 키가 올라간 순간
	return (false == m_arrCurKey[key] && true == m_arrPrevKey[key]);
}

bool CInputManager::GetButtonDown(const int key)
{
	// 키가 내려간 순간
	return (true == m_arrCurKey[key] && false == m_arrPrevKey[key]);
}

Vector CInputManager::GetMouseScreenPos()
{
	return m_vecMousePos;
}

Vector CInputManager::GetMouseWorldPos()
{
	return CAMERA->ScreenToWorldPoint(m_vecMousePos);
}

bool CInputManager::GetMouseOnUI()
{
	return UI->GetMouseOnUI();
}

bool CInputManager::GetLMouse(bool ignoreUI)
{
	if (GetButton(VK_LBUTTON))
	{
		if (ignoreUI) return true;
		else return !GetMouseOnUI();
	}
	else
		return false;
}

bool CInputManager::GetLMouseUp(bool ignoreUI)
{
	if (GetButtonUp(VK_LBUTTON))
	{
		if (ignoreUI) return true;
		else return !GetMouseOnUI();
	}
	else
		return false;
}

bool CInputManager::GetLMouseDown(bool ignoreUI)
{
	if (GetButtonDown(VK_LBUTTON))
	{
		if (ignoreUI) return true;
		else return !GetMouseOnUI();
	}
	else
		return false;
}

bool CInputManager::GetRMouse(bool ignoreUI)
{
	if (GetButton(VK_RBUTTON))
	{
		if (ignoreUI) return true;
		else return !GetMouseOnUI();
	}
	else
		return false;
}

bool CInputManager::GetRMouseUp(bool ignoreUI)
{
	if (GetButtonUp(VK_RBUTTON))
	{
		if (ignoreUI) return true;
		else return !GetMouseOnUI();
	}
	else
		return false;
}

bool CInputManager::GetRMouseDown(bool ignoreUI)
{
	if (GetButtonDown(VK_RBUTTON))
	{
		if (ignoreUI) return true;
		else return !GetMouseOnUI();
	}
	else
		return false;
}
