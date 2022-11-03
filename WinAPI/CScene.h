#pragma once
#include "WinAPI.h"

class CSceneManager;
class CEventManager;
class CCollisionManager;
class CUIManager;
class CGameObject;

class CScene
{
	friend CSceneManager;
	friend CEventManager;
	friend CCollisionManager;
	friend CUIManager;
protected:
	list<CGameObject*> m_listObj[(int)Layer::Size];

public:
	CScene();
	virtual ~CScene();

protected:
	UINT m_iTileSizeX;
	UINT m_iTileSizeY;

private:
	// 씬 부모 전용 함수들 :
	// 씬에 있는 모든 게임오브젝트들을 갱신
	void SceneInit();
	void SceneEnter();
	void SceneUpdate();
	void ScenePhysicsUpdate();
	void SceneRender();
	void SceneExit();
	void SceneRelease();

	// 순수가상함수:
	// 함수를 추상화하여 구체화하지 않을 경우 인스턴스 생성을 막음
	// 씬을 상속받아 순수가상함수들을 구체화시켜 씬을 완성시킴
	virtual void Init() = 0;		// 초기화
	virtual void Enter() = 0;		// 진입
	virtual void Update() = 0;		// 게임로직 갱신
	virtual void Render() = 0;		// 게임표현 갱신
	virtual void Exit() = 0;		// 탈출
	virtual void Release() = 0;		// 마무리

	void TileRender();

public:
	void LoadTile(const wstring& strPath);

protected:
	list<CGameObject*>& GetLayerObject(Layer layer);

	void AddGameObject(CGameObject* pGameObj);
	// 삭제과정은 게임오브젝트 자료구조에서 삭제될 게임오브젝트를 찾아서 제거하는 방법을 채택하지 않음
	// 1. 게임오브젝트를 탐색하여 삭제하는 것이 비효율적
	// 2. 삭제예정인 게임오브젝트를 참조하고 있는 게임오브젝트들에게 유예시간을 줘야함
	// -> Update 진행중 삭제예정인 오브젝트를 한프레임만 보관하고 다음프레임이 시작될 때 삭제함
	// void DeleteGameObject(CGameObject* pGameObj);
	void DeleteLayerObject(Layer layer);
	void DeleteAll();
};
