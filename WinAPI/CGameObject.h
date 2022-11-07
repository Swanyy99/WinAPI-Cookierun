#pragma once
#include "WinAPI.h"

class CEventManager;
class CCollisionManager;
class CScene;
class CComponent;
class CCollider;
enum class ColliderType;

// 게임오브젝트 : 
// 씬 내에 존재하는 물체, ex) 캐릭터, 미사일, 몬스터, 아이템, 등
// 게임오브젝트를 캡슐화하여 행동과 표현을 정의할 경우
// 다른 게임오브젝트와 독립적으로 설계할 수 있음
class CGameObject
{
	friend CEventManager;
	friend CCollisionManager;
	friend CScene;
	friend CCollider;
public:
	CGameObject();
	virtual ~CGameObject();

protected:
	Vector m_vecPos;	// 게임오브젝트의 위치
	Vector m_vecScale;	// 게임오브젝트의 크기
	Layer m_layer;		// 게임오브젝트의 레이어
	wstring m_strName;	// 게임오브젝트의 이름

public:
	Vector GetPos();
	void SetPos(Vector pos);
	void SetPos(float x, float y);
	Vector GetScale();
	void SetScale(Vector scale);
	void SetScale(float x, float y);
	Layer GetLayer();
	void SetLayer(Layer layer);
	wstring GetName();
	void SetName(wstring name);

private:
	bool m_bReservedDelete;		// 게임오브젝트가 삭제예정인지 여부
	bool m_bSafeToDelete;		// 게임오브젝트가 삭제해도 문제없는지 여부

	void SetReserveDelete();	// 게임오브젝트 삭제 예약
	bool GetSafeToDelete();		// 게임오브젝트 삭제 가능 상태 확인
	void SetSafeToDelete();		// 게임오브젝트 삭제 가능 상태 표시
public:
	bool GetReserveDelete();		// 게임오브젝트가 삭제예정인지 확인

protected:
	list<CComponent*> m_listComponent;	// 컴포넌트들을 보관할 자료구조

	void AddComponent(CComponent* component);		// 컴포넌트 추가
	void RemoveComponent(CComponent* component);	// 컴포넌트 삭제

	void ComponentRender();

	// 충돌 컴포넌트
private:
	CCollider* m_pCollider;

protected:
	CCollider* GetCollider();
	void AddCollider(ColliderType type, Vector scale, Vector offsetPos);
	void SetColliderSize(Vector scale, Vector offsetPos);
	void RemoveCollider();

	virtual void OnCollisionEnter(CCollider* pOtherCollider) {};	// 충돌체크를 확인하는 오브젝트는 재정의하여 사용
	virtual void OnCollisionStay(CCollider* pOtherCollider) {};	// 충돌체크를 확인하는 오브젝트는 재정의하여 사용
	virtual void OnCollisionExit(CCollider* pOtherCollider) {};	// 충돌체크를 확인하는 오브젝트는 재정의하여 사용

protected:
	// 게임오브젝트 부모 전용 함수들 :
	// 게임오브젝트에 있는 모든 컴포넌트들을 갱신
	virtual void GameObjectInit();
	virtual void GameObjectUpdate();
	virtual void GameObjectPhysicsUpdate();
	virtual void GameObjectRender();
	virtual void GameObjectRelease();

	// 순수가상함수:
	// 함수를 추상화하여 구체화하지 않을 경우 인스턴스 생성을 막음
	// 게임오브젝트를 상속받아 순수가상함수들을 구체화시켜 게임오브젝트를 완성시킴
	virtual void Init() = 0;		// 초기화
	virtual void Update() = 0;		// 게임오브젝트의 행동정의
	virtual void Render() = 0;		// 게임오브젝트의 표현정의
	virtual void Release() = 0;		// 마무리
};
