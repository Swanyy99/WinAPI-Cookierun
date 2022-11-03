#pragma once
#include "CComponent.h"

class CCollisionManager;
class CGameObject;

enum class ColliderType { Rect, Circle };

class CCollider : public CComponent
{
	friend CCollisionManager;
	friend CGameObject;
public:
	CCollider();
	virtual ~CCollider();

private:
	static UINT s_uiID;		// 모든 충돌체가 공유하는 ID 값
	UINT m_uiID;			// 충돌체의 고유 ID 값
	UINT m_uiCollisionCount;// 충돌중인 충돌체 갯수

	ColliderType m_type;	// 충돌체의 타입
	Vector m_vecPos;		// 충돌체의 위치
	Vector m_vecOffsetPos;	// 충돌체의 변위차(수정값)
	Vector m_vecScale;		// 충돌체의 크기

private:
	void SetType(ColliderType type);
	void SetPos(Vector pos);
	void SetOffsetPos(Vector offset);
	void SetScale(Vector scale);

public:
	ColliderType GetType();
	wstring GetObjName();
	UINT GetID();
	Vector GetPos();
	Vector GetOffsetPos();
	Vector GetScale();

private:
	void Init() override;
	void Update() override;
	void PhysicsUpdate() override;	// 충돌체의 물리처리
	void Render() override;
	void Release() override;

	// 충돌 시점 함수
private:
	void OnCollisionEnter(CCollider* pOtherCollider);	// 충돌진입
	void OnCollisionStay(CCollider* pOtherCollider);	// 충돌중
	void OnCollisionExit(CCollider* pOtherCollider);	// 충돌탈출
};

