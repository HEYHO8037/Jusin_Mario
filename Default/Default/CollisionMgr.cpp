#include "stdafx.h"
#include "CollisionMgr.h"

CCollisionMgr* CCollisionMgr::m_pInstance = nullptr;

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::SetObjList(const list<CObj*>(*pObjList)[OBJ_END])
{
	m_ObjList = pObjList;
}

bool CCollisionMgr::Check_Rect(CObj * pDest, CObj * pSour, float * pX, float * pY) //px와 pY의 주소값을 넘겨주어야 함수가 끝난후에도 변수에 대입한 값을 계속 쓸수있다
{
	float fWidth = abs(pDest->Get_Info().fX - pSour->Get_Info().fX); // 두 중점간 x의 길이, 밑변
	float fHeight = abs(pDest->Get_Info().fY - pSour->Get_Info().fY); // 두 중점간 y의 길이, 높이

	float fCX = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f; // 각각의 반지를을 구한뒤 더한 값(x) 
	float fCY = (pDest->Get_Info().fCY + pSour->Get_Info().fCY) * 0.5f; // 각각의 반지를을 구한뒤 더한 값(y)

	if ((fCX > fWidth) && (fCY > fHeight)) // 두점 사이의 거리가 두객체의 반지름을 더한값보다 작아지면 충돌
	{
		*pX = fCX - fWidth;
		*pY = fCY - fHeight; // 두객체의 반지름을 더한값에서 두점사이의 거리를 빼주면 충돌한 거리, 길이가 나온다

		return true; // 충돌했을경우 true 반환
	}

	return false;
}

bool CCollisionMgr::Check_Sphere(CObj * pDest, CObj * pSour)
{
	// abs 절대값구하는 함수 f- float이므로 붙여줌
	float fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX); //밑변
	float fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY); //높이

																	   //sqrt : 루트를 씌워주는 함수
	float fDiagonal = sqrtf(fWidth*fWidth + fHeight*fHeight); //빗변

	float	fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f; // 두 원의 반지름 더한값

	return fRadius > fDiagonal; // 두 원의 반지름을 더한값이 두 객체사이의 길이보다 크다 = 충돌
}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour) // obj포인터 타입 리스트안에 있는 두 객체가 충돌했을시 처리하는 함수
{
	RECT rc{}; // 충돌한 범위를 담는 변수 

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
			{
				//두 객체가 충돌되었을때 true를 반환한다
				//true인 상태 = 두 객체가 충돌되었다는 것을 의미하므로 이때 원하는 행동을 하는 함수를 넣어주면된다
				//ex) Set_Dead
			}
		}
	}

}
//고정되어있는 물체		//움직이는 물체
void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto & Sour : _Sour)
		{
			float fX = 0.f, fY = 0.f; // 충돌한 길이로 사용할 변수

			if (Check_Rect(Dest, Sour, &fX, &fY))
			{
				//상하충돌
				if (fX > fY) // 충돌했을때 나온 X의 길이가 Y의 길이보다 길다면 상하충돌 
				{
					if (Dest->Get_Info().fY > Sour->Get_Info().fY) // 고정되어있는물체의 y의 값이 움직이는 물체의 y의 값보다 큰 경우, 상 충돌
					{
						//Sour->Set_PosY(-fY); // 충돌된 길이만큼 위로 올라가게 -fY값을 넣는다
					}
					else //하 충돌
					{
						//Sour->Set_PosY(fY); // 충돌된 길이만큼 밑으로 내려가게 fY값을 넣는다
					}
				}
				else // 좌우 s충돌 fX < fY
				{
					if (Dest->Get_Info().fX > Sour->Get_Info().fX) // 좌충돌(고정된물체가 움직이는 물체의 중점보다 오른쪽에 있으므로)
					{
						//Sour->Set_PostX(-fX);
					}
					else // 우 충돌
					{
						//Sour->Set_PostX(fX);
					}
				}
			}
		}
	}

}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				/*Dest->Set_Dead();
				Sour->Set_Dead();*/
			}
		}
	}
}

void CCollisionMgr::Collision_Player_Monster()
{
	float fX, fY;

	list<CObj*>::const_iterator iter = m_ObjList[OBJ_MONSTER]->begin();
	list<CObj*>::const_iterator iterEnd = m_ObjList[OBJ_MONSTER]->end();
	for (iter; iter != iterEnd; ++iter)
	{
		if (Check_Rect(m_ObjList[OBJ_PLAYER]->front(), (*iter), &fX, &fY))
		{

		}
	}
}

void CCollisionMgr::Collision_Player_Bullet()
{
	float fX, fY;

	list<CObj*>::const_iterator iter = m_ObjList[OBJ_BULLET]->begin();
	list<CObj*>::const_iterator iterEnd = m_ObjList[OBJ_BULLET]->end();
	for (iter; iter != iterEnd; ++iter)
	{
		if (Check_Rect(m_ObjList[OBJ_PLAYER]->front(), (*iter), &fX, &fY))
		{
			//충돌처리
		}
	}
}

void CCollisionMgr::Collision_Monster_Bullet()
{
	float fX, fY;

	list<CObj*>::const_iterator iter = m_ObjList[OBJ_MONSTER]->begin();
	list<CObj*>::const_iterator iterEnd = m_ObjList[OBJ_MONSTER]->end();
	
	for (iter; iter != iterEnd; ++iter)
	{
		list<CObj*>::const_iterator Biter = m_ObjList[OBJ_BULLET]->begin();
		list<CObj*>::const_iterator BiterEnd = m_ObjList[OBJ_BULLET]->end();
		
		for (Biter; Biter != BiterEnd; ++Biter)
		{
			if (Check_Rect((*iter), (*Biter),&fX, &fY))
			{
				//충돌처리
			}
		}
	}
}

void CCollisionMgr::Collision_Player_Item()
{
	float fX, fY;

	list<CObj*>::const_iterator iter = m_ObjList[OBJ_ITEM]->begin();
	list<CObj*>::const_iterator iterEnd = m_ObjList[OBJ_ITEM]->end();
	
	for (iter; iter != iterEnd; ++iter)
	{
		if (Check_Rect(m_ObjList[OBJ_PLAYER]->front(), (*iter), &fX, &fY))
		{
			//충돌처리
		}
	}
}

void CCollisionMgr::Collision_Player_Huddle()
{
	float fX, fY;

	list<CObj*>::const_iterator iter = m_ObjList[OBJ_HUDDLE]->begin();
	list<CObj*>::const_iterator iterEnd = m_ObjList[OBJ_HUDDLE]->end();
	
	for (iter; iter != iterEnd; ++iter)
	{
		if (Check_Rect(m_ObjList[OBJ_PLAYER]->front(), (*iter), &fX, &fY))
		{
			//충돌처리
		}
	}
}
