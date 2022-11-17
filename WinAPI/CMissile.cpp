#include "framework.h"
#include "CMissile.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"
#include "CImage.h"

extern int score;

CMissile::CMissile()
{
	m_vecScale = Vector(10, 10);
	m_vecDir = Vector(0, 0);
	m_fVelocity = 300;
	m_layer = Layer::Missile;
	m_strName = L"미사일";
	missileImage = nullptr;
}

CMissile::~CMissile()
{
}

void CMissile::Init()
{
	AddCollider(ColliderType::Circle, Vector(8, 8), Vector(0, 0));
}

void CMissile::Update()
{
	m_vecPos += m_vecDir * m_fVelocity * DT;

	// 화면밖으로 나갈경우 삭제
	if (m_vecPos.x < 0 ||
		m_vecPos.x > WINSIZEX ||
		m_vecPos.y < 0 ||
		m_vecPos.y > WINSIZEY)
		DELETEOBJECT(this);
}

void CMissile::Render()
{
	missileImage = RESOURCE->LoadImg(L"Missile", L"Image\\Missile.png");

	RENDER->Image(
		missileImage,
		m_vecPos.x - missileImage->GetWidth() * 0.3,
		m_vecPos.y - missileImage->GetHeight() * 0.3,
		m_vecPos.x + missileImage->GetWidth() * 0.3,
		m_vecPos.y + missileImage->GetHeight() * 0.3);
}

void CMissile::Release()
{
}

void CMissile::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"장애물")
	{
		Logger::Debug(L"미사일이 장애물을 부쉈습니다.");
		score += 5000;
		DELETEOBJECT(this);

		
	}
}

void CMissile::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CMissile::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
