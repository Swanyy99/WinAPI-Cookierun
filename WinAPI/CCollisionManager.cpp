#include "framework.h"
#include "CCollisionManager.h"

#include "CSceneManager.h"
#include "CGameObject.h"
#include "CScene.h"
#include "CCollider.h"

CCollisionManager::CCollisionManager()
{
	m_arrLayer[0][0] = { 0 };
}

CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::Init()
{
	CheckLayer(Layer::Monster, Layer::Missile);
	CheckLayer(Layer::Obstacle, Layer::Missile);
	CheckLayer(Layer::Monster, Layer::Player);
	CheckLayer(Layer::Tile, Layer::Player);
	CheckLayer(Layer::Floor, Layer::Player);
	CheckLayer(Layer::Obstacle, Layer::Player);
	CheckLayer(Layer::Jelly, Layer::Player);
	CheckLayer(Layer::HeartItem, Layer::Player);
}

void CCollisionManager::Update()
{
	for (int left = 0; left < (int)Layer::Size; left++)
	{
		for (int right = left; right < (int)Layer::Size; right++)
		{
			if (m_arrLayer[left][right])
			{
				// 충돌 확인 진행
				CollisionUpdate((Layer)left, (Layer)right);
			}
		}
	}
}

void CCollisionManager::Release()
{
}

void CCollisionManager::CollisionUpdate(Layer leftLayer, Layer rightLayer)
{
	CScene* pCurScene = SCENE->GetCurScene();
	const list<CGameObject*>& leftListObj = pCurScene->m_listObj[(int)leftLayer];
	const list<CGameObject*>& rightListObj = pCurScene->m_listObj[(int)rightLayer];

	for (CGameObject* pLeftObj : leftListObj)
	{
		// 충돌체 컴포넌트가 없는 경우 무시
		if (nullptr == pLeftObj->GetCollider())
			continue;

		for (CGameObject* pRightObj : rightListObj)
		{
			// 충돌체 컴포넌트가 없는 경우 무시
			if (nullptr == pRightObj->GetCollider())
				continue;

			// 자기 자신과의 충돌은 무시
			if (pLeftObj == pRightObj)
				continue;

			// 충돌체와 충돌체의 ID 확인
			CCollider* pLeftCollider = pLeftObj->GetCollider();
			CCollider* pRightCollider = pRightObj->GetCollider();
			UINT64 id = CollisionID(pLeftCollider->GetID(), pRightCollider->GetID());

			// 충돌 정보가 없었던 경우, 충돌하지 않은 상태로 보관
			if (m_umapPrevCollision.find(id) == m_umapPrevCollision.end())
				m_umapPrevCollision.insert(make_pair(id, false));
			
			// 충돌처리 확인
			if (IsCollision(pLeftCollider, pRightCollider))
			{
				// Prev O, Cur O
				if (m_umapPrevCollision[id])
				{
					// 충돌체 중 하나라도 삭제예정인 경우 충돌 해제
					if (pLeftObj->GetReserveDelete() || pRightObj->GetReserveDelete())
					{
						pLeftCollider->OnCollisionExit(pRightCollider);
						pRightCollider->OnCollisionExit(pLeftCollider);
						m_umapPrevCollision[id] = false;
					}
					else
					{
						pLeftCollider->OnCollisionStay(pRightCollider);
						pRightCollider->OnCollisionStay(pLeftCollider);
						m_umapPrevCollision[id] = true;
					}
				}
				// Prev X, Cur O
				else
				{
					// 충돌체 중 하나라도 삭제예정인 경우 충돌시키지 않음
					if (pLeftObj->GetReserveDelete() || pRightObj->GetReserveDelete())
					{
						// 아무것도 하지 않음
					}
					else
					{
						pLeftCollider->OnCollisionEnter(pRightCollider);
						pRightCollider->OnCollisionEnter(pLeftCollider);
						m_umapPrevCollision[id] = true;
					}
				}
			}
			else
			{
				// Prev O, Cur X
				if (m_umapPrevCollision[id])
				{
					pLeftCollider->OnCollisionExit(pRightCollider);
					pRightCollider->OnCollisionExit(pLeftCollider);
					m_umapPrevCollision[id] = false;
				}
				// Prev X, Cur X
				else
				{
					m_umapPrevCollision[id] = false;
				}
			}
		}
	}
}

bool CCollisionManager::IsCollision(CCollider* pLeftCollider, CCollider* pRightCollider)
{
	ColliderType leftType = pLeftCollider->GetType();
	ColliderType rightType = pRightCollider->GetType();
	
	if (leftType == ColliderType::Rect && rightType == ColliderType::Rect)
	{
		return RectCollision(
			pLeftCollider->GetPos(),
			pLeftCollider->GetScale(), 
			pRightCollider->GetPos(),
			pRightCollider->GetScale()
		);
	}
	else if (leftType == ColliderType::Circle && rightType == ColliderType::Circle)
	{
		return CircleCollision(
			pLeftCollider->GetPos(),
			pLeftCollider->GetScale().x,
			pRightCollider->GetPos(),
			pRightCollider->GetScale().x
		);
	}
	else if (leftType == ColliderType::Rect && rightType == ColliderType::Circle)
	{
		return RectCircleCollision(
			pLeftCollider->GetPos(),
			pLeftCollider->GetScale(),
			pRightCollider->GetPos(),
			pRightCollider->GetScale().x
		);
	}
	else if (leftType == ColliderType::Circle && rightType == ColliderType::Rect)
	{
		return RectCircleCollision(
			pRightCollider->GetPos(),
			pRightCollider->GetScale(),
			pLeftCollider->GetPos(),
			pLeftCollider->GetScale().x
		);
	}
	else
	{
		return false;
	}
}

bool CCollisionManager::RectCollision(Vector leftPos, Vector leftScale, Vector rightPos, Vector rightScale)
{
	// 사각 충돌 : 사각형의 중점간의 거리가 크기합의 반보다 작은 경우 충돌한다
	if (abs(leftPos.x - rightPos.x) < (leftScale.x + rightScale.x) / 2.f
		&& abs(leftPos.y - rightPos.y) < (leftScale.y + rightScale.y) / 2.f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CCollisionManager::CircleCollision(Vector leftPos, float leftScale, Vector rightPos, float rightScale)
{
	// 원 충돌 : 원의 중점간의 거리합이 반지름의 합보다 작은 경우 충돌한다
	if (pow(leftPos.x - rightPos.x, 2) + pow(leftPos.y - rightPos.y, 2)
		< pow(leftScale + rightScale, 2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CCollisionManager::RectCircleCollision(Vector rectPos, Vector rectScale, Vector circlePos, float circleScale)
{
	int totalPoint, xPoint, yPoint;
	// 사각 원 충돌 : 사각형을 중심으로 원이 어느 영역에 있느냐에 따라 다르게 처리
	/*	totalPoint (xPoint, yPoint)

		-4 (-1,-1) | -3 ( 0,-1) | -2 (+1,-1)
		-----------+------------+-----------
		-1 (-1, 0) |  0 ( 0, 0) | +1 (+1, 0)
		-----------+------------+-----------
		+2 (-1,+1) | +3 ( 0,+1) | +4 (+1,+1)
	*/
	if (circlePos.x < rectPos.x - rectScale.x * 0.5f)
		xPoint = -1;
	else if (circlePos.x > rectPos.x + rectScale.x * 0.5f)
		xPoint = 1;
	else
		xPoint = 0;

	if (circlePos.y < rectPos.y - rectScale.y * 0.5f)
		yPoint = -1;
	else if (circlePos.y > rectPos.y + rectScale.y * 0.5f)
		yPoint = 1;
	else
		yPoint = 0;

	totalPoint = 3 * yPoint + xPoint;

	switch (totalPoint)
	{
	// 사각형 안에 원이 있을 경우 : 항상 충돌
	case 0:
		return true;
		break;
	// 좌우에 원이 있을 경우 : 사각형의 가로 크기 + 원의 반지름이 둘사이의 거리보다 작은경우 충돌
	case -1:
	case +1:
		if (abs(rectPos.x - circlePos.x) < rectScale.x * 0.5f + circleScale)
			return true;
		break;
	// 상하에 원이 있을 경우 : 사각형의 세로 크기 + 원의 반지름이 둘사이의 거리보다 작은경우 충돌
	case -3:
	case +3:
		if (abs(rectPos.y - circlePos.y) < rectScale.y * 0.5f + circleScale)
			return true;
		break;
	// 사각형의 대각선에 원이 있을 경우 : 사각형의 코너가 원 안에 있을 경우 충돌
	case -4:
	case -2:
	case +2:
	case +4:
	{
		float cornerX = (xPoint < 0) ? rectPos.x - rectScale.x * 0.5f : rectPos.x + rectScale.x * 0.5f;
		float cornerY = (yPoint < 0) ? rectPos.y - rectScale.y * 0.5f : rectPos.y + rectScale.y * 0.5f;
		if (pow(cornerX - circlePos.x, 2) + pow(cornerY - circlePos.y, 2)
			< pow(circleScale, 2))
			return true;
		break;
	}
	}

	return false;
}

void CCollisionManager::CheckLayer(Layer left, Layer right)
{
	m_arrLayer[(int)left][(int)right] = true;
	m_arrLayer[(int)right][(int)left] = true;
}

void CCollisionManager::UnCheckLayer(Layer left, Layer right)
{
	m_arrLayer[(int)left][(int)right] = false;
	m_arrLayer[(int)right][(int)left] = false;
}

void CCollisionManager::ResetCheck()
{
	// memset(시작주소, 설정할 데이터, 설정할 크기) : 메모리 초기화 함수
	memset(m_arrLayer, 0, sizeof(bool) * (int)Layer::Size * (int)Layer::Size);
	/*
	for (bool check : m_arrCheckLayer)
	{
		check = false;
	}
	*/
}

UINT64 CCollisionManager::CollisionID(UINT leftID, UINT rightID)
{
	UINT64 result = 0;
	if (leftID < rightID)
	{
		result |= (UINT64)leftID << 32;
		result |= rightID;
		return result;
	}
	else
	{
		result |= (UINT64)rightID << 32;
		result |= leftID;
		return result;
	}
}
