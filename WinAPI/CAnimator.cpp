#include "framework.h"
#include "CAnimator.h"

#include "CAnimation.h"

CAnimator::CAnimator()
{
	m_pCurAni = nullptr;
}

CAnimator::~CAnimator()
{
}

void CAnimator::Init()
{
}

void CAnimator::Update()
{
	if (nullptr != m_pCurAni)
		m_pCurAni->Update();
}

void CAnimator::Render()
{
	if (nullptr != m_pCurAni)
		m_pCurAni->Render();
}

void CAnimator::Release()
{
	for (pair<wstring, CAnimation*> animation : m_mapAni)
	{
		delete animation.second;
	}
	m_mapAni.clear();
}

void CAnimator::CreateAnimation(const wstring& aniName, CImage* pImg, Vector lt, Vector slice, Vector step, float duration, UINT count, bool repeat)
{
	// 같은 이름의 애니메이션이 이미 있을 경우 프로그램 경고
	CAnimation* pAni = FindAnimation(aniName);
	assert(nullptr == pAni && L"Animation already exist");

	// 애니메이션의 이름과 생성 후 자료구조에 보관
	pAni = new CAnimation;
	pAni->SetName(aniName);
	pAni->Create(pImg, lt, slice, step, duration, count, repeat);
	pAni->m_pAnimator = this;

	m_mapAni.insert(make_pair(aniName, pAni));
}

void CAnimator::RemoveAnimation(const wstring& aniName)
{
	// 같은 이름의 애니메이션을 찾았을 경우 제거
	CAnimation* pAni = FindAnimation(aniName);

	if (nullptr != pAni)
		m_mapAni.erase(aniName);
}

CAnimation* CAnimator::FindAnimation(const wstring& aniName)
{
	// 이름을 통해 자료구조에서 애니메이션을 탐색하고 있을 경우 반환
	auto iter = m_mapAni.find(aniName);
	if (iter == m_mapAni.end())
		return nullptr;
	else
		return m_mapAni[aniName];
}

void CAnimator::Play(const wstring& aniName, bool trigger)
{
	// 현재 애니메이션이 플레이하고자 하는 애니메이션이며
	// Tigger가 아닐 경우 현재 애니메이션을 변경하지 않음
	// Tigger : 같은 애니메이션을 처음부터 재생 (ex. 공격 모션처럼 누를때마다 처음부터 재생해야하는 애니메이션)
	if (nullptr != m_pCurAni && aniName == m_pCurAni->GetName() && !trigger)
		return;

	// 애니메이션 자료구조에서 애니메이션을 탐색
	CAnimation* pAnimation = FindAnimation(aniName);
	// 탐색한 결과 애니메이션이 없는 경우 프로그램 경고
	assert(nullptr != pAnimation && L"Animation no exist");
	// 트리거 타입일 경우이거나 애니메이션이 바뀌었을 경우 애니메이션을 처음부터 재생
	if (trigger || m_pCurAni != pAnimation) pAnimation->Replay();
	// 현재 애니메이션을 탐색한 애니메이션으로 교체
	m_pCurAni = pAnimation;
}

void CAnimator::Stop()
{
	// 현재 애니메이션이 없도록 하여 정지
	m_pCurAni = nullptr;
}
