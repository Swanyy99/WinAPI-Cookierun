#include "framework.h"
#include "CDashFireEffect.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"
#include "CImage.h"

extern bool isMagnet;
extern bool isDash;

extern float playerPosX;
extern float playerPosY;

CDashFireEffect::CDashFireEffect()
{

	m_vecScale = Vector(10, 10);
	m_strName = L"대쉬이펙트";
	m_layer = Layer::DashEffect;
	m_vecDir = Vector(-2, 0);
	m_fVelocity = 300;
	DashEffectImage = nullptr;
	m_fEffectRemoveTimer = 0;
}

CDashFireEffect::~CDashFireEffect()
{
}

void CDashFireEffect::Init()
{
}

void CDashFireEffect::Update()
{
	m_vecPos += m_vecDir * m_fVelocity * DT;

	m_fEffectRemoveTimer += ABSDT;

	if (m_fEffectRemoveTimer > 0.3)
		DELETEOBJECT(this);

	// 화면밖으로 나갈경우 삭제
	/*if (m_vecPos.x < 0 ||
		m_vecPos.x > WINSIZEX ||
		m_vecPos.y < 0 ||
		m_vecPos.y > WINSIZEY)
		DELETEOBJECT(this);*/
}

void CDashFireEffect::Render()
{
	DashEffectImage = RESOURCE->LoadImg(L"DashImage", L"Image\\DashFireEffect.png");

	RENDER->Image(
		DashEffectImage,
		m_vecPos.x - DashEffectImage->GetWidth() * 0.4,
		m_vecPos.y - DashEffectImage->GetHeight() * 0.4,
		m_vecPos.x + DashEffectImage->GetWidth() * 0.4,
		m_vecPos.y + DashEffectImage->GetHeight() * 0.4);
}

void CDashFireEffect::Release()
{
}



void CDashFireEffect::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CDashFireEffect::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
