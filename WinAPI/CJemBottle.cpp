#include "framework.h"
#include "CJemBottle.h"
#include "CJellyEatEffect.h"

extern bool isDash;
extern float playerPosX;
extern float playerPosY;
extern bool skillOn;
extern bool skillOn2;

CJemBottle::CJemBottle()
{
	m_vecScale = Vector(100, 100);
	m_strName = L"Áª";
	m_layer = Layer::Coin;
	m_vecDir = Vector(1, 0);
	m_fVelocity = 300;
	m_pAnimators = nullptr;
	m_pObstacle1Image = nullptr;

	m_pImg = nullptr;
}

CJemBottle::~CJemBottle()
{
}

void CJemBottle::Init()
{

	AddCollider(ColliderType::Rect, Vector(50, 50), Vector(0, 10));

}

void CJemBottle::Update()
{

	m_vecPos -= m_vecDir * m_fVelocity * DT;


	if (m_vecPos.x < 0)
		DELETEOBJECT(this);

	obstacleImage = L"IdleObstacle";
}

void CJemBottle::Render()
{
	m_pImg = RESOURCE->LoadImg(L"Jem", L"Image\\JemBox.png");

	RENDER->Image(
		m_pImg,
		m_vecPos.x - m_pImg->GetWidth() * 0.1,
		m_vecPos.y - m_pImg->GetHeight() * 0.1,
		m_vecPos.x + m_pImg->GetWidth() * 0.1,
		m_vecPos.y + m_pImg->GetHeight() * 0.1);
}

void CJemBottle::Release()
{
}

void CJemBottle::AnimatorUpdate()
{
	//m_pAnimators->Play(obstacleImage, false);
}


void CJemBottle::OnCollisionEnter(CCollider* pOtherCollider)
{


	if (pOtherCollider->GetObjName() == L"ÇÃ·¹ÀÌ¾î")
	{
		Logger::Debug(L"ÇÃ·¹ÀÌ¾î°¡ Áª¹Ú½º¸¦ ¸Ô¾ú½À´Ï´Ù");
		CJellyEatEffect* pJellyEffect = new CJellyEatEffect();
		pJellyEffect->SetPos(m_vecPos.x - 10, m_vecPos.y);
		ADDOBJECT(pJellyEffect);
		DELETEOBJECT(this);
	}

	if (pOtherCollider->GetObjName() == L"Æê¹Ì»çÀÏ" && skillOn == true)
	{
		Logger::Debug(L"¿Õ ÇÏÇÁ¹°¹üÀÌ Áª¹Ú½º¸¦ ¸Ô¾ú½À´Ï´Ù");
		CJellyEatEffect* pJellyEffect = new CJellyEatEffect();
		pJellyEffect->SetPos(m_vecPos.x - 10, m_vecPos.y);
		ADDOBJECT(pJellyEffect);
		DELETEOBJECT(this);
	}

	if (pOtherCollider->GetObjName() == L"Æê¹Ì»çÀÏ2")
	{
		Logger::Debug(L"¹°º¸¶ó°¡ Áª¹Ú½º¸¦ ¸Ô¾ú½À´Ï´Ù");
		CJellyEatEffect* pJellyEffect = new CJellyEatEffect();
		pJellyEffect->SetPos(m_vecPos.x - 10, m_vecPos.y);
		ADDOBJECT(pJellyEffect);
		DELETEOBJECT(this);
	}

	if (pOtherCollider->GetObjName() == L"Æê¹Ì»çÀÏ3")
	{
		Logger::Debug(L"ºûÀÇ ¿ìÀ¯ ¹æÆÐ°¡ Áª¹Ú½º¸¦ ¸Ô¾ú½À´Ï´Ù");
		CJellyEatEffect* pJellyEffect = new CJellyEatEffect();
		pJellyEffect->SetPos(m_vecPos.x - 10, m_vecPos.y);
		ADDOBJECT(pJellyEffect);
		DELETEOBJECT(this);
	}
}

void CJemBottle::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CJemBottle::OnCollisionExit(CCollider* pOtherCollider)
{
}

void CJemBottle::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CJemBottle::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
