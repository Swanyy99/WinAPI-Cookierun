#pragma once
#include "WinAPI.h"

class CCore;
class CGameObject;

class CEventManager : public SingleTon<CEventManager>
{
	friend SingleTon<CEventManager>;
	friend CCore;
private:
	CEventManager();
	virtual ~CEventManager();

	queue<CGameObject*> m_queueAddObject;		// AddObject 이벤트 보관
	queue<CGameObject*> m_queueDeleteObject;	// DeleteObject 이벤트 보관
	pair<GroupScene, float>* m_pChangeScene;	// ChangeScene 이벤트 보관
	//list<GroupScene> m_listChangeScene;			// ChangeScene 이벤트 보관

	void Init();
	void Update();
	void Release();

public:
	void EventAddObject(CGameObject* pObj);						// 다음프레임에 추가될 오브젝트 이벤트 추가
	void EventDeleteObject(CGameObject* pObj);					// 삭제 예정인 오브젝트 이벤트 추가
	void EventChangeScene(GroupScene scene, float delay = 0);	// 씬전환 이벤트 추가

private:
	void ProgressAddObject();					// 프레임 초기에 추가될 오브젝트를 추가
	void ProgressDeleteObject();				// 삭제 예정인 오브젝트를 표시, 이후 씬에서 표시된 오브젝트를 제거
	void ProgressChangeScene();					// 마지막으로 저장된 씬전환 이벤트 진행
};

#define EVENT							CEventManager::GetInstance()
#define ADDOBJECT(pObj)					CEventManager::GetInstance()->EventAddObject(pObj)
#define DELETEOBJECT(pObj)				CEventManager::GetInstance()->EventDeleteObject(pObj)
#define CHANGESCENE(scene)				CEventManager::GetInstance()->EventChangeScene(scene)
#define DELAYCHANGESCENE(scene, delay)	CEventManager::GetInstance()->EventChangeScene(scene, delay)