#include "framework.h"
#include "CEventManager.h"
#include "CSceneManager.h"
#include "CScene.h"
#include "CGameObject.h"

#include "CTimeManager.h"

CEventManager::CEventManager()
{
	m_pChangeScene = nullptr;
}

CEventManager::~CEventManager()
{
}

void CEventManager::Init()
{
}

void CEventManager::Update()
{
	ProgressAddObject();
	ProgressDeleteObject();

	// 씬 전환은 다른 이벤트보다 가장 마지막에 진행
	ProgressChangeScene();
}

void CEventManager::Release()
{
}

void CEventManager::EventAddObject(CGameObject* pObj)
{
	// 다음 프레임에 추가될 게임오브젝트를 자료구조에 보관
	m_queueAddObject.push(pObj);
}

void CEventManager::EventDeleteObject(CGameObject* pObj)
{
	// 삭제 예정인 게임오브젝트를 자료구조에 보관
	m_queueDeleteObject.push(pObj);
}

void CEventManager::EventChangeScene(GroupScene scene, float delay)
{
	// 씬 전환 이벤트를 자료구조에 보관
	if (nullptr == m_pChangeScene)
	{
		m_pChangeScene = new pair<GroupScene, float>(scene, delay);
	}
	else if (m_pChangeScene->second > delay)
	{
		delete m_pChangeScene;
		m_pChangeScene = new pair<GroupScene, float>(scene, delay);
	}
	else
	{
		// 딜레이가 더욱 큰 씬전환 이벤트는 무시
	}
}

void CEventManager::ProgressAddObject()
{
	// 프레임의 초기에 추가될 게임오브젝트를 추가

	while (!m_queueAddObject.empty())
	{
		CGameObject* pGameObject = m_queueAddObject.front();
		m_queueAddObject.pop();
		SCENE->GetCurScene()->AddGameObject(pGameObject);
	}
}

void CEventManager::ProgressDeleteObject()
{
	// 삭제 예정인 게임오브젝트에 삭제예정 표시를 진행

	while (!m_queueDeleteObject.empty())
	{
		CGameObject* pGameObject = m_queueDeleteObject.front();
		m_queueDeleteObject.pop();
		pGameObject->SetReserveDelete();
	}
}

void CEventManager::ProgressChangeScene()
{
	// 저장된 씬 전환 이벤트 중 가장 마지막의 이벤트만 진행

	if (nullptr == m_pChangeScene)
		return;

	// 지연실행 이벤트가 잔여시간이 모두 소진되었을 경우 이벤트 진행
	m_pChangeScene->second -= DT;
	if (m_pChangeScene->second <= 0)
	{
		GroupScene scene = m_pChangeScene->first;
		delete m_pChangeScene;
		m_pChangeScene = nullptr;
		SCENE->ChangeScene(scene);
	}
}
