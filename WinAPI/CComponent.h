#pragma once

class CGameObject;

// 디자인패턴 컴포지트 - 컴포넌트 : 
// 프로그래밍에 있어 기능 재사용이 가능한 각각의 독립된 모듈
// 객체에 포함할 경우 각각의 기능을 독립적으로 수행하는 조립식 모듈
// 상속의 경우 모든 상속하는 자식에게 반드시 기능이 포함되지만
// 컴포넌트의 경우 필요한 객체에만 조립식으로 붙일 수 있음
class CComponent
{
	friend CGameObject;
public:
	CComponent();
	virtual ~CComponent();

private:
	CGameObject* m_pOwner;

private:
	void SetOwner(CGameObject* pOwner);

public:
	CGameObject* GetOwner();

private:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void PhysicsUpdate(){};		// 물리처리가 필요한 컴포넌트만 재정의하여 사용
	virtual void Render() = 0;
	virtual void Release() = 0;
};

