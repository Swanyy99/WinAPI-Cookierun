#pragma once

class CCore;

class CInputManager : public SingleTon<CInputManager>
{
	friend SingleTon<CInputManager>;
	friend CCore;
private:
	CInputManager();
	virtual ~CInputManager();

	static const int VKEY_SIZE = 0xFF;	// VK의 최대 갯수

	bool m_arrPrevKey[VKEY_SIZE];		// 이전 키의 입력상태
	bool m_arrCurKey[VKEY_SIZE];		// 현재 키의 입력상태
	Vector m_vecMousePos;				// 현재 마우스 위치

	void Init();
	void Update();
	void Release();

public:

	bool GetButton(const int key);		// 키를 누르고 있는 중
	bool GetButtonUp(const int key);	// 키가 올라간 순간
	bool GetButtonDown(const int key);	// 키가 내려간 순간
	Vector GetMouseScreenPos();			// 현재 마우스 화면위치
	Vector GetMouseWorldPos();			// 현재 마우스 게임위치

	bool GetMouseOnUI();				// 현재 마우스가 UI위에 있는 여부 확인
	bool GetLMouse(bool ignoreUI);		// 마우스 왼쪽 키를 누르고 있는 중
	bool GetLMouseUp(bool ignoreUI);	// 마우스 왼쪽 키가 올라간 순간
	bool GetLMouseDown(bool ignoreUI);	// 마우스 왼쪽 키가 내려간 순간
	bool GetRMouse(bool ignoreUI);		// 마우스 오른쪽 키를 누르고 있는 중
	bool GetRMouseUp(bool ignoreUI);	// 마우스 오른쪽 키가 올라간 순간
	bool GetRMouseDown(bool ignoreUI);	// 마우스 오른쪽 키가 내려간 순간
};

#define	INPUT					CInputManager::GetInstance()
#define BUTTONSTAY(key)			CInputManager::GetInstance()->GetButton(key)
#define BUTTONUP(key)			CInputManager::GetInstance()->GetButtonUp(key)	
#define BUTTONDOWN(key)			CInputManager::GetInstance()->GetButtonDown(key)	
#define MOUSESCREENPOS			CInputManager::GetInstance()->GetMouseScreenPos()
#define MOUSEWORLDPOS			CInputManager::GetInstance()->GetMouseWorldPos()
#define LMOUSESTAY(ignoreUI)	CInputManager::GetInstance()->GetLMouse(ignoreUI)
#define LMOUSEUP(ignoreUI)		CInputManager::GetInstance()->GetLMouseUp(ignoreUI)
#define LMOUSEDOWN(ignoreUI)	CInputManager::GetInstance()->GetLMouseDown(ignoreUI)
#define RMOUSESTAY(ignoreUI)	CInputManager::GetInstance()->GetRMouse(ignoreUI)
#define RMOUSEUP(ignoreUI)		CInputManager::GetInstance()->GetRMouseUp(ignoreUI)
#define RMOUSEDOWN(ignoreUI)	CInputManager::GetInstance()->GetRMouseDown(ignoreUI)